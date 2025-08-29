// Copyright 2020 The MediaPipe Authors.
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

#include "mediapipe_custom/framework/formats/image.h"

#include "absl/log/absl_check.h"
#include "mediapipe_custom/framework/type_map.h"

#if !MEDIAPIPE_DISABLE_GPU
#include "mediapipe_custom/gpu/gl_texture_view.h"
#endif  // !MEDIAPIPE_DISABLE_GPU

namespace mediapipe_custom {

// TODO Refactor common code from GpuBufferToImageFrameCalculator
bool Image::ConvertToCpu() const {
  auto view = gpu_buffer_.GetReadView<ImageFrame>();
  use_gpu_ = false;
  return true;
}

// TODO Refactor common code from ImageFrameToGpuBufferCalculator
bool Image::ConvertToGpu() const {
#if MEDIAPIPE_DISABLE_GPU
  return false;
#else
  auto view = gpu_buffer_.GetReadView<GlTextureView>(0);
  use_gpu_ = true;
  return true;
#endif  // MEDIAPIPE_DISABLE_GPU
}

MEDIAPIPE_REGISTER_TYPE(mediapipe_custom::Image, "::mediapipe_custom::Image", nullptr,
                        nullptr);
MEDIAPIPE_REGISTER_TYPE(std::vector<mediapipe_custom::Image>,
                        "::std::vector<::mediapipe_custom::Image>", nullptr, nullptr);

}  // namespace mediapipe_custom
