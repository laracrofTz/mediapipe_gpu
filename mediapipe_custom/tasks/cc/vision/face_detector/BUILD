load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_cc//cc:cc_test.bzl", "cc_test")

# Copyright 2023 The MediaPipe Authors.
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

package(default_visibility = ["//visibility:public"])

licenses(["notice"])

cc_library(
    name = "face_detector_graph",
    srcs = ["face_detector_graph.cc"],
    deps = [
        "//mediapipe_custom/calculators/core:clip_vector_size_calculator",
        "//mediapipe_custom/calculators/core:clip_vector_size_calculator_cc_proto",
        "//mediapipe_custom/calculators/tensor:image_to_tensor_calculator_cc_proto",
        "//mediapipe_custom/calculators/tensor:inference_calculator",
        "//mediapipe_custom/calculators/tensor:tensors_to_detections_calculator",
        "//mediapipe_custom/calculators/tensor:tensors_to_detections_calculator_cc_proto",
        "//mediapipe_custom/calculators/tflite:ssd_anchors_calculator",
        "//mediapipe_custom/calculators/tflite:ssd_anchors_calculator_cc_proto",
        "//mediapipe_custom/calculators/util:detection_projection_calculator",
        "//mediapipe_custom/calculators/util:detection_transformation_calculator",
        "//mediapipe_custom/calculators/util:detections_to_rects_calculator",
        "//mediapipe_custom/calculators/util:detections_to_rects_calculator_cc_proto",
        "//mediapipe_custom/calculators/util:non_max_suppression_calculator",
        "//mediapipe_custom/calculators/util:non_max_suppression_calculator_cc_proto",
        "//mediapipe_custom/calculators/util:rect_transformation_calculator",
        "//mediapipe_custom/calculators/util:rect_transformation_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:detection_cc_proto",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/components/processors:image_preprocessing_graph",
        "//mediapipe_custom/tasks/cc/core:model_resources",
        "//mediapipe_custom/tasks/cc/core:model_task_graph",
        "//mediapipe_custom/tasks/cc/core:utils",
        "//mediapipe_custom/tasks/cc/core/proto:inference_subgraph_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/face_detector/proto:face_detector_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/utils:image_tensor_specs",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ],
    alwayslink = 1,
)

cc_library(
    name = "face_detector",
    srcs = ["face_detector.cc"],
    hdrs = ["face_detector.h"],
    deps = [
        ":face_detector_graph",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/formats:detection_cc_proto",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/tasks/cc/components/containers:detection_result",
        "//mediapipe_custom/tasks/cc/core:base_options",
        "//mediapipe_custom/tasks/cc/core:utils",
        "//mediapipe_custom/tasks/cc/vision/core:base_vision_task_api",
        "//mediapipe_custom/tasks/cc/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/cc/vision/core:running_mode",
        "//mediapipe_custom/tasks/cc/vision/core:vision_task_api_factory",
        "//mediapipe_custom/tasks/cc/vision/face_detector/proto:face_detector_graph_options_cc_proto",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ],
)
