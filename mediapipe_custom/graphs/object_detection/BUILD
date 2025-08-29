# Copyright 2019 The MediaPipe Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

load("@rules_cc//cc:cc_library.bzl", "cc_library")
load(
    "//mediapipe_custom/framework/tool:mediapipe_graph.bzl",
    "mediapipe_binary_graph",
)

licenses(["notice"])

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "mobile_calculators",
    deps = [
        "//mediapipe_custom/calculators/core:flow_limiter_calculator",
        "//mediapipe_custom/calculators/image:image_transformation_calculator",
        "//mediapipe_custom/calculators/tflite:ssd_anchors_calculator",
        "//mediapipe_custom/calculators/tflite:tflite_converter_calculator",
        "//mediapipe_custom/calculators/tflite:tflite_inference_calculator",
        "//mediapipe_custom/calculators/tflite:tflite_tensors_to_detections_calculator",
        "//mediapipe_custom/calculators/util:annotation_overlay_calculator",
        "//mediapipe_custom/calculators/util:detection_label_id_to_text_calculator",
        "//mediapipe_custom/calculators/util:detection_letterbox_removal_calculator",
        "//mediapipe_custom/calculators/util:detections_to_render_data_calculator",
        "//mediapipe_custom/calculators/util:non_max_suppression_calculator",
        "//mediapipe_custom/gpu:gpu_buffer_to_image_frame_calculator",
        "//mediapipe_custom/gpu:image_frame_to_gpu_buffer_calculator",
    ],
)

cc_library(
    name = "desktop_tensorflow_calculators",
    deps = [
        "//mediapipe_custom/calculators/tensorflow:image_frame_to_tensor_calculator",
        "//mediapipe_custom/calculators/tensorflow:lapped_tensor_buffer_calculator",
        "//mediapipe_custom/calculators/tensorflow:object_detection_tensors_to_detections_calculator",
        "//mediapipe_custom/calculators/tensorflow:tensor_squeeze_dimensions_calculator",
        "//mediapipe_custom/calculators/tensorflow:tensorflow_inference_calculator",
        "//mediapipe_custom/calculators/tensorflow:tensorflow_session_from_saved_model_calculator",
        "//mediapipe_custom/calculators/util:annotation_overlay_calculator",
        "//mediapipe_custom/calculators/util:detection_label_id_to_text_calculator",
        "//mediapipe_custom/calculators/util:detections_to_render_data_calculator",
        "//mediapipe_custom/calculators/util:non_max_suppression_calculator",
        "//mediapipe_custom/calculators/video:opencv_video_decoder_calculator",
        "//mediapipe_custom/calculators/video:opencv_video_encoder_calculator",
    ],
)

cc_library(
    name = "desktop_tflite_calculators",
    deps = [
        "//mediapipe_custom/calculators/core:concatenate_vector_calculator",
        "//mediapipe_custom/calculators/core:flow_limiter_calculator",
        "//mediapipe_custom/calculators/core:previous_loopback_calculator",
        "//mediapipe_custom/calculators/core:split_vector_calculator",
        "//mediapipe_custom/calculators/image:image_transformation_calculator",
        "//mediapipe_custom/calculators/tflite:ssd_anchors_calculator",
        "//mediapipe_custom/calculators/tflite:tflite_converter_calculator",
        "//mediapipe_custom/calculators/tflite:tflite_inference_calculator",
        "//mediapipe_custom/calculators/tflite:tflite_tensors_to_detections_calculator",
        "//mediapipe_custom/calculators/util:annotation_overlay_calculator",
        "//mediapipe_custom/calculators/util:detection_label_id_to_text_calculator",
        "//mediapipe_custom/calculators/util:detections_to_render_data_calculator",
        "//mediapipe_custom/calculators/util:non_max_suppression_calculator",
        "//mediapipe_custom/calculators/video:opencv_video_decoder_calculator",
        "//mediapipe_custom/calculators/video:opencv_video_encoder_calculator",
    ],
)

mediapipe_binary_graph(
    name = "mobile_cpu_binary_graph",
    graph = "object_detection_mobile_cpu.pbtxt",
    output_name = "mobile_cpu.binarypb",
    deps = [":mobile_calculators"],
)

mediapipe_binary_graph(
    name = "mobile_gpu_binary_graph",
    graph = "object_detection_mobile_gpu.pbtxt",
    output_name = "mobile_gpu.binarypb",
    deps = [":mobile_calculators"],
)
