// Copyright 2019 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "mediapipe_custom/java/com/google/mediapipe/framework/jni/packet_creator_jni.h"

#include <cstring>
#include <memory>
#include <utility>

#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "mediapipe_custom/framework/calculator.pb.h"
#include "mediapipe_custom/framework/camera_intrinsics.h"
#include "mediapipe_custom/framework/formats/image.h"
#include "mediapipe_custom/framework/formats/image_format.pb.h"
#include "mediapipe_custom/framework/formats/image_frame.h"
#include "mediapipe_custom/framework/formats/matrix.h"
#include "mediapipe_custom/framework/formats/time_series_header.pb.h"
#include "mediapipe_custom/framework/formats/video_stream_header.h"
#include "mediapipe_custom/framework/packet.h"
#include "mediapipe_custom/framework/port/core_proto_inc.h"
#include "mediapipe_custom/framework/port/logging.h"
#include "mediapipe_custom/java/com/google/mediapipe/framework/jni/colorspace.h"
#include "mediapipe_custom/java/com/google/mediapipe/framework/jni/graph.h"
#include "mediapipe_custom/java/com/google/mediapipe/framework/jni/jni_util.h"
#if !MEDIAPIPE_DISABLE_GPU
#include "mediapipe_custom/gpu/gl_calculator_helper.h"
#include "mediapipe_custom/gpu/gpu_buffer.h"
#endif  // !MEDIAPIPE_DISABLE_GPU

namespace {
using mediapipe_custom::android::SerializedMessageIds;
using mediapipe_custom::android::ThrowIfError;

template <class T>
int64_t CreatePacketScalar(jlong context, const T& value) {
  mediapipe_custom::android::Graph* mediapipe_graph =
      reinterpret_cast<mediapipe_custom::android::Graph*>(context);
  mediapipe_custom::Packet packet = mediapipe_custom::Adopt(new T(value));
  return mediapipe_graph->WrapPacketIntoContext(packet);
}

// Creates a new internal::PacketWithContext object, and returns the native
// handle.
int64_t CreatePacketWithContext(jlong context,
                                const mediapipe_custom::Packet& packet) {
  mediapipe_custom::android::Graph* mediapipe_graph =
      reinterpret_cast<mediapipe_custom::android::Graph*>(context);
  return mediapipe_graph->WrapPacketIntoContext(packet);
}

#if !MEDIAPIPE_DISABLE_GPU
absl::StatusOr<mediapipe_custom::GpuBuffer> CreateGpuBuffer(
    JNIEnv* env, jobject thiz, jlong context, jint name, jint width,
    jint height, jobject texture_release_callback) {
  mediapipe_custom::android::Graph* mediapipe_graph =
      reinterpret_cast<mediapipe_custom::android::Graph*>(context);
  auto* gpu_resources = mediapipe_graph->GetGpuResources();
  RET_CHECK(gpu_resources)
      << "Cannot create a mediapipe_custom::GpuBuffer packet on a "
         "graph without GPU support";
  mediapipe_custom::GlTextureBuffer::DeletionCallback cc_callback;

  if (texture_release_callback) {
    // TODO: see if this can be cached.
    // Note: we don't get this from the object because people may pass a
    // subclass of PacketCreator, and the method is private.
    jclass my_class =
        env->FindClass("com/google/mediapipe/framework/PacketCreator");
    jmethodID release_method =
        env->GetMethodID(my_class, "releaseWithSyncToken",
                         "(JL"
                         "com/google/mediapipe/framework/TextureReleaseCallback"
                         ";)V");
    RET_CHECK(release_method);
    env->DeleteLocalRef(my_class);

    jobject java_callback = env->NewGlobalRef(texture_release_callback);
    jobject packet_creator = env->NewGlobalRef(thiz);
    cc_callback = [packet_creator, release_method,
                   java_callback](mediapipe_custom::GlSyncToken release_token) {
      JNIEnv* env = mediapipe_custom::java::GetJNIEnv();

      jlong raw_token = reinterpret_cast<jlong>(
          new mediapipe_custom::GlSyncToken(std::move(release_token)));
      env->CallVoidMethod(packet_creator, release_method, raw_token,
                          java_callback);

      // Note that this callback is called only once, and is not saved
      // anywhere else, so we can and should delete it here.
      env->DeleteGlobalRef(java_callback);
      env->DeleteGlobalRef(packet_creator);
    };
  }
  return mediapipe_custom::GpuBuffer(mediapipe_custom::GlTextureBuffer::Wrap(
      GL_TEXTURE_2D, name, width, height, mediapipe_custom::GpuBufferFormat::kBGRA32,
      gpu_resources->gl_context(), cc_callback));
}
#endif  // !MEDIAPIPE_DISABLE_GPU

// Create a 1, 3, or 4 channel 8-bit ImageFrame shared pointer from a Java
// ByteBuffer.
absl::StatusOr<std::unique_ptr<mediapipe_custom::ImageFrame>>
CreateImageFrameFromByteBuffer(JNIEnv* env, jobject byte_buffer, jint width,
                               jint height, jint width_step,
                               mediapipe_custom::ImageFormat::Format format) {
  const int64_t buffer_size = env->GetDirectBufferCapacity(byte_buffer);
  const void* buffer_data = env->GetDirectBufferAddress(byte_buffer);
  if (buffer_data == nullptr || buffer_size < 0) {
    return absl::InvalidArgumentError(
        "Cannot get direct access to the input buffer. It should be created "
        "using allocateDirect.");
  }

  const int expected_buffer_size = height * width_step;
  RET_CHECK_EQ(buffer_size, expected_buffer_size)
      << "Input buffer size should be " << expected_buffer_size
      << " but is: " << buffer_size;

  auto image_frame = std::make_unique<mediapipe_custom::ImageFrame>();
  // TODO: we could retain the buffer with a special deleter and use
  // the data directly without a copy. May need a new Java API since existing
  // code might expect to be able to overwrite the buffer after creating an
  // ImageFrame from it.
  image_frame->CopyPixelData(
      format, width, height, width_step,
      static_cast<const uint8_t*>(buffer_data),
      mediapipe_custom::ImageFrame::kGlDefaultAlignmentBoundary);

  return image_frame;
}

}  // namespace

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateReferencePacket)(
    JNIEnv* env, jobject thiz, jlong context, jlong packet) {
  auto mediapipe_graph = reinterpret_cast<mediapipe_custom::android::Graph*>(context);
  mediapipe_custom::Packet mediapipe_packet =
      mediapipe_custom::android::Graph::GetPacketFromHandle(packet);
  auto reference_packet = mediapipe_custom::AdoptAsUniquePtr(
      new mediapipe_custom::SyncedPacket(mediapipe_packet));
  // assigned the initial value of the packet reference.
  return mediapipe_graph->WrapPacketIntoContext(reference_packet);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateRgbImage)(
    JNIEnv* env, jobject thiz, jlong context, jobject byte_buffer, jint width,
    jint height) {
  // We require 4-byte alignment. See Java method.
  constexpr int kAlignment = 4;
  int width_step = ((width * 3 - 1) | (kAlignment - 1)) + 1;
  auto image_frame_or =
      CreateImageFrameFromByteBuffer(env, byte_buffer, width, height,
                                     width_step, mediapipe_custom::ImageFormat::SRGB);
  if (ThrowIfError(env, image_frame_or.status())) return 0L;

  mediapipe_custom::Packet packet = mediapipe_custom::Adopt(image_frame_or->release());
  return CreatePacketWithContext(context, packet);
}

absl::StatusOr<std::unique_ptr<mediapipe_custom::ImageFrame>> CreateRgbImageFromRgba(
    JNIEnv* env, jobject byte_buffer, jint width, jint height) {
  const uint8_t* rgba_data =
      static_cast<uint8_t*>(env->GetDirectBufferAddress(byte_buffer));
  int64_t buffer_size = env->GetDirectBufferCapacity(byte_buffer);
  if (rgba_data == nullptr || buffer_size < 0) {
    return absl::InvalidArgumentError(
        "Cannot get direct access to the input buffer. It should be created "
        "using allocateDirect.");
  }

  const int expected_buffer_size = width * height * 4;
  RET_CHECK_EQ(buffer_size, expected_buffer_size)
      << "Input buffer size should be " << expected_buffer_size
      << " but is: " << buffer_size;

  auto image_frame = absl::make_unique<mediapipe_custom::ImageFrame>(
      mediapipe_custom::ImageFormat::SRGB, width, height,
      mediapipe_custom::ImageFrame::kGlDefaultAlignmentBoundary);
  mediapipe_custom::android::RgbaToRgb(rgba_data, width * 4, width, height,
                                image_frame->MutablePixelData(),
                                image_frame->WidthStep());
  return image_frame;
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateRgbImageFromRgba)(
    JNIEnv* env, jobject thiz, jlong context, jobject byte_buffer, jint width,
    jint height) {
  auto image_frame_or = CreateRgbImageFromRgba(env, byte_buffer, width, height);
  if (ThrowIfError(env, image_frame_or.status())) return 0L;

  mediapipe_custom::Packet packet = mediapipe_custom::Adopt(image_frame_or->release());
  return CreatePacketWithContext(context, packet);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateGrayscaleImage)(
    JNIEnv* env, jobject thiz, jlong context, jobject byte_buffer, jint width,
    jint height) {
  auto image_frame_or = CreateImageFrameFromByteBuffer(
      env, byte_buffer, width, height, width, mediapipe_custom::ImageFormat::GRAY8);
  if (ThrowIfError(env, image_frame_or.status())) return 0L;

  mediapipe_custom::Packet packet = mediapipe_custom::Adopt(image_frame_or->release());
  return CreatePacketWithContext(context, packet);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateFloatImageFrame)(
    JNIEnv* env, jobject thiz, jlong context, jobject byte_buffer, jint width,
    jint height) {
  auto image_frame_or =
      CreateImageFrameFromByteBuffer(env, byte_buffer, width, height, width * 4,
                                     mediapipe_custom::ImageFormat::VEC32F1);
  if (ThrowIfError(env, image_frame_or.status())) return 0L;
  mediapipe_custom::Packet packet = mediapipe_custom::Adopt(image_frame_or->release());
  return CreatePacketWithContext(context, packet);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateRgbaImageFrame)(
    JNIEnv* env, jobject thiz, jlong context, jobject byte_buffer, jint width,
    jint height) {
  auto image_frame_or =
      CreateImageFrameFromByteBuffer(env, byte_buffer, width, height, width * 4,
                                     mediapipe_custom::ImageFormat::SRGBA);
  if (ThrowIfError(env, image_frame_or.status())) return 0L;
  mediapipe_custom::Packet packet = mediapipe_custom::Adopt(image_frame_or->release());
  return CreatePacketWithContext(context, packet);
}

static mediapipe_custom::Packet createAudioPacket(const uint8_t* audio_sample,
                                           int num_samples, int num_channels) {
  std::unique_ptr<mediapipe_custom::Matrix> matrix(
      new mediapipe_custom::Matrix(num_channels, num_samples));
  // Preparing and normalize the audio data.
  // kMultiplier is same as what used in av_sync_media_decoder.cc.
  static const float kMultiplier = 1.f / (1 << 15);
  for (int sample = 0; sample < num_samples; ++sample) {
    for (int channel = 0; channel < num_channels; ++channel) {
      // MediaPipe createAudioPacket can currently only handle
      // AudioFormat.ENCODING_PCM_16BIT data, so here we are reading 2 bytes per
      // sample, using ByteOrder.LITTLE_ENDIAN byte order, which is
      // ByteOrder.nativeOrder() on Android
      // (https://developer.android.com/ndk/guides/abis.html).
      int16_t value = (audio_sample[1] & 0xff) << 8 | audio_sample[0];
      (*matrix)(channel, sample) = kMultiplier * value;
      audio_sample += 2;
    }
  }
  return mediapipe_custom::Adopt(matrix.release());
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateAudioPacket)(
    JNIEnv* env, jobject thiz, jlong context, jbyteArray data, jint offset,
    jint num_channels, jint num_samples) {
  // Note, audio_data_ref is really a const jbyte* but this clashes with the
  // the expectation of ReleaseByteArrayElements below.
  jbyte* audio_data_ref = env->GetByteArrayElements(data, nullptr);
  const uint8_t* audio_sample =
      reinterpret_cast<uint8_t*>(audio_data_ref) + offset;
  mediapipe_custom::Packet packet =
      createAudioPacket(audio_sample, num_samples, num_channels);
  env->ReleaseByteArrayElements(data, audio_data_ref, JNI_ABORT);
  return CreatePacketWithContext(context, packet);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateAudioPacketDirect)(
    JNIEnv* env, jobject thiz, jlong context, jobject data, jint num_channels,
    jint num_samples) {
  const uint8_t* audio_sample =
      reinterpret_cast<uint8_t*>(env->GetDirectBufferAddress(data));
  if (!audio_sample) {
    ThrowIfError(env, absl::InvalidArgumentError(
                          "Cannot get direct access to the input buffer. It "
                          "should be created using allocateDirect."));
    return 0L;
  }
  mediapipe_custom::Packet packet =
      createAudioPacket(audio_sample, num_samples, num_channels);
  return CreatePacketWithContext(context, packet);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateInt16)(JNIEnv* env,
                                                                 jobject thiz,
                                                                 jlong context,
                                                                 jshort value) {
  return CreatePacketScalar<int16_t>(context, value);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateInt32)(JNIEnv* env,
                                                                 jobject thiz,
                                                                 jlong context,
                                                                 jint value) {
  return CreatePacketScalar<int>(context, value);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateInt64)(JNIEnv* env,
                                                                 jobject thiz,
                                                                 jlong context,
                                                                 jlong value) {
  return CreatePacketScalar<int64_t>(context, value);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateFloat32)(
    JNIEnv* env, jobject thiz, jlong context, jfloat value) {
  return CreatePacketScalar<float>(context, value);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateFloat64)(
    JNIEnv* env, jobject thiz, jlong context, jdouble value) {
  return CreatePacketScalar<double>(context, value);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateBool)(
    JNIEnv* env, jobject thiz, jlong context, jboolean value) {
  return CreatePacketScalar<bool>(context, value);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateString)(
    JNIEnv* env, jobject thiz, jlong context, jstring value) {
  return CreatePacketScalar<std::string>(
      context, mediapipe_custom::android::JStringToStdString(env, value));
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateVideoHeader)(
    JNIEnv* env, jobject thiz, jlong context, jint width, jint height) {
  mediapipe_custom::VideoHeader header;
  header.format = mediapipe_custom::ImageFormat::SRGB;
  header.width = width;
  header.height = height;
  return CreatePacketScalar<mediapipe_custom::VideoHeader>(context, header);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateTimeSeriesHeader)(
    JNIEnv* env, jobject thiz, jlong context, jint num_channels,
    jdouble sample_rate) {
  mediapipe_custom::TimeSeriesHeader header;
  header.set_num_channels(num_channels);
  header.set_sample_rate(sample_rate);
  return CreatePacketScalar<mediapipe_custom::TimeSeriesHeader>(context, header);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateMatrix)(
    JNIEnv* env, jobject thiz, jlong context, jint rows, jint cols,
    jfloatArray data) {
  if (env->GetArrayLength(data) != rows * cols) {
    ThrowIfError(
        env, absl::InvalidArgumentError(absl::StrCat(
                 "Please check the matrix data size, has to be rows * cols = ",
                 rows * cols)));
    return 0L;
  }
  std::unique_ptr<mediapipe_custom::Matrix> matrix(new mediapipe_custom::Matrix(rows, cols));
  // Android is always
  // little-endian(https://developer.android.com/ndk/guides/abis.html), even
  // though Java's ByteBuffer defaults to
  // big-endian(https://docs.oracle.com/javase/7/docs/api/java/nio/ByteBuffer.html),
  // there is no Java ByteBuffer involved, JNI does not change the endianness(we
  // have PacketGetterTest.testEndianOrder() to cover this case), so we can
  // safely copy data directly here.
  env->GetFloatArrayRegion(data, 0, rows * cols, matrix->data());
  mediapipe_custom::Packet packet = mediapipe_custom::Adopt(matrix.release());
  return CreatePacketWithContext(context, packet);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateCpuImage)(
    JNIEnv* env, jobject thiz, jlong context, jobject byte_buffer, jint width,
    jint height, jint width_step, jint num_channels) {
  mediapipe_custom::ImageFormat::Format format;
  switch (num_channels) {
    case 4:
      format = mediapipe_custom::ImageFormat::SRGBA;
      break;
    case 3:
      format = mediapipe_custom::ImageFormat::SRGB;
      break;
    case 1:
      format = mediapipe_custom::ImageFormat::GRAY8;
      break;
    default:
      ThrowIfError(env, absl::InvalidArgumentError(absl::StrCat(
                            "Channels must be either 1, 3, or 4, but are ",
                            num_channels)));
      return 0L;
  }

  auto image_frame_or = CreateImageFrameFromByteBuffer(
      env, byte_buffer, width, height, width_step, format);
  if (ThrowIfError(env, image_frame_or.status())) return 0L;

  mediapipe_custom::Packet packet =
      mediapipe_custom::MakePacket<mediapipe_custom::Image>(*std::move(image_frame_or));
  return CreatePacketWithContext(context, packet);
}

#if !MEDIAPIPE_DISABLE_GPU

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateGpuImage)(
    JNIEnv* env, jobject thiz, jlong context, jint name, jint width,
    jint height, jobject texture_release_callback) {
  auto buffer_or = CreateGpuBuffer(env, thiz, context, name, width, height,
                                   texture_release_callback);
  if (ThrowIfError(env, buffer_or.status())) return 0L;
  mediapipe_custom::Packet packet =
      mediapipe_custom::MakePacket<mediapipe_custom::Image>(std::move(buffer_or).value());
  return CreatePacketWithContext(context, packet);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateGpuBuffer)(
    JNIEnv* env, jobject thiz, jlong context, jint name, jint width,
    jint height, jobject texture_release_callback) {
  auto buffer_or = CreateGpuBuffer(env, thiz, context, name, width, height,
                                   texture_release_callback);
  if (ThrowIfError(env, buffer_or.status())) return 0L;
  mediapipe_custom::Packet packet =
      mediapipe_custom::MakePacket<mediapipe_custom::GpuBuffer>(std::move(buffer_or).value());
  return CreatePacketWithContext(context, packet);
}

#endif  // !MEDIAPIPE_DISABLE_GPU

// TODO: Add vector creators.

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateFloat32Array)(
    JNIEnv* env, jobject thiz, jlong context, jfloatArray data) {
  jsize count = env->GetArrayLength(data);
  jfloat* data_ref = env->GetFloatArrayElements(data, nullptr);
  float* floats = new float[count];
  // jfloat is a "machine-dependent native type" which represents a 32-bit
  // float. C++ makes no guarantees about the size of floating point types, and
  // some exotic architectures don't even have 32-bit floats (or even binary
  // floats), but on all architectures we care about this is a float.
  static_assert(std::is_same<float, jfloat>::value, "jfloat must be float");
  std::memcpy(floats, data_ref, count * sizeof(float));
  env->ReleaseFloatArrayElements(data, data_ref, JNI_ABORT);

  // The reinterpret_cast is needed to make the Adopt template recognize
  // that this is an array - this way Holder will call delete[].
  mediapipe_custom::Packet packet =
      mediapipe_custom::Adopt(reinterpret_cast<float (*)[]>(floats));
  return CreatePacketWithContext(context, packet);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateFloat32Vector)(
    JNIEnv* env, jobject thiz, jlong context, jfloatArray data) {
  jsize count = env->GetArrayLength(data);
  jfloat* data_ref = env->GetFloatArrayElements(data, nullptr);
  // jfloat is a "machine-dependent native type" which represents a 32-bit
  // float. C++ makes no guarantees about the size of floating point types, and
  // some exotic architectures don't even have 32-bit floats (or even binary
  // floats), but on all architectures we care about this is a float.
  static_assert(std::is_same<float, jfloat>::value, "jfloat must be float");
  std::unique_ptr<std::vector<float>> floats =
      absl::make_unique<std::vector<float>>(data_ref, data_ref + count);

  env->ReleaseFloatArrayElements(data, data_ref, JNI_ABORT);
  mediapipe_custom::Packet packet = mediapipe_custom::Adopt(floats.release());
  return CreatePacketWithContext(context, packet);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateInt32Array)(
    JNIEnv* env, jobject thiz, jlong context, jintArray data) {
  jsize count = env->GetArrayLength(data);
  jint* data_ref = env->GetIntArrayElements(data, nullptr);
  int32_t* ints = new int32_t[count];
  static_assert(std::is_same<int32_t, jint>::value, "jint must be int32_t");
  std::memcpy(ints, data_ref, count * sizeof(int32_t));
  env->ReleaseIntArrayElements(data, data_ref, JNI_ABORT);

  // The reinterpret_cast is needed to make the Adopt template recognize
  // that this is an array - this way Holder will call delete[].
  mediapipe_custom::Packet packet =
      mediapipe_custom::Adopt(reinterpret_cast<int32_t (*)[]>(ints));
  return CreatePacketWithContext(context, packet);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateInt32Pair)(
    JNIEnv* env, jobject thiz, jlong context, jint first, jint second) {
  static_assert(std::is_same<int32_t, jint>::value, "jint must be int32_t");

  mediapipe_custom::Packet packet = mediapipe_custom::MakePacket<std::pair<int32_t, int32_t>>(
      std::make_pair(first, second));
  return CreatePacketWithContext(context, packet);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateStringFromByteArray)(
    JNIEnv* env, jobject thiz, jlong context, jbyteArray data) {
  jsize count = env->GetArrayLength(data);
  jbyte* data_ref = env->GetByteArrayElements(data, nullptr);
  mediapipe_custom::Packet packet = mediapipe_custom::Adopt(
      new std::string(reinterpret_cast<char*>(data_ref), count));
  env->ReleaseByteArrayElements(data, data_ref, JNI_ABORT);
  return CreatePacketWithContext(context, packet);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateCalculatorOptions)(
    JNIEnv* env, jobject thiz, jlong context, jbyteArray data) {
  jsize count = env->GetArrayLength(data);
  jbyte* data_ref = env->GetByteArrayElements(data, nullptr);
  auto options = absl::make_unique<mediapipe_custom::CalculatorOptions>();
  if (!options->ParseFromArray(data_ref, count)) {
    ThrowIfError(env, absl::InvalidArgumentError(absl::StrCat(
                          "Parsing binary-encoded CalculatorOptions failed.")));
    return 0L;
  }
  mediapipe_custom::Packet packet = mediapipe_custom::Adopt(options.release());
  env->ReleaseByteArrayElements(data, data_ref, JNI_ABORT);
  return CreatePacketWithContext(context, packet);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateProto)(JNIEnv* env,
                                                                 jobject thiz,
                                                                 jlong context,
                                                                 jobject data) {
  // Convert type_name and value from Java data.
  static SerializedMessageIds ids(env, data);
  jstring j_type_name = (jstring)env->GetObjectField(data, ids.type_name_id);
  std::string type_name =
      mediapipe_custom::android::JStringToStdString(env, j_type_name);
  jbyteArray value_array = (jbyteArray)env->GetObjectField(data, ids.value_id);
  jsize value_len = env->GetArrayLength(value_array);
  jbyte* value_ref = env->GetByteArrayElements(value_array, nullptr);

  // Create the C++ MessageLite and Packet.
  mediapipe_custom::Packet packet;
  auto packet_or = mediapipe_custom::packet_internal::PacketFromDynamicProto(
      type_name, std::string((char*)value_ref, value_len));
  if (!ThrowIfError(env, packet_or.status())) {
    packet = packet_or.value();
  }
  env->ReleaseByteArrayElements(value_array, value_ref, JNI_ABORT);
  return CreatePacketWithContext(context, packet);
}

JNIEXPORT jlong JNICALL PACKET_CREATOR_METHOD(nativeCreateCameraIntrinsics)(
    JNIEnv* env, jobject thiz, jlong context, jfloat fx, jfloat fy, jfloat cx,
    jfloat cy, jfloat width, jfloat height) {
  mediapipe_custom::Packet packet =
      mediapipe_custom::MakePacket<CameraIntrinsics>(fx, fy, cx, cy, width, height);
  return CreatePacketWithContext(context, packet);
}
