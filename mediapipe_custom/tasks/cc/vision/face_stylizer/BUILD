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

load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_cc//cc:cc_test.bzl", "cc_test")

package(default_visibility = ["//visibility:public"])

licenses(["notice"])

cc_library(
    name = "face_stylizer_graph",
    srcs = ["face_stylizer_graph.cc"],
    deps = [
        "//mediapipe_custom/calculators/core:split_vector_calculator_cc_proto",
        "//mediapipe_custom/calculators/image:image_clone_calculator_cc_proto",
        "//mediapipe_custom/calculators/tensor:image_to_tensor_calculator_cc_proto",
        "//mediapipe_custom/calculators/tensor:inference_calculator",
        "//mediapipe_custom/calculators/util:detections_to_rects_calculator",
        "//mediapipe_custom/calculators/util:face_to_rect_calculator",
        "//mediapipe_custom/calculators/util:landmarks_to_detection_calculator_cc_proto",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:landmark_cc_proto",
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/gpu:gpu_origin_cc_proto",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/components/processors:image_preprocessing_graph",
        "//mediapipe_custom/tasks/cc/core:model_resources_cache",
        "//mediapipe_custom/tasks/cc/core:model_task_graph",
        "//mediapipe_custom/tasks/cc/core/proto:external_file_cc_proto",
        "//mediapipe_custom/tasks/cc/metadata/utils:zip_utils",
        "//mediapipe_custom/tasks/cc/vision/face_detector/proto:face_detector_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/face_landmarker:face_landmarker_graph",
        "//mediapipe_custom/tasks/cc/vision/face_landmarker/proto:face_landmarker_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/face_landmarker/proto:face_landmarks_detector_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/face_stylizer/calculators:tensors_to_image_calculator",
        "//mediapipe_custom/tasks/cc/vision/face_stylizer/calculators:tensors_to_image_calculator_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/face_stylizer/proto:face_stylizer_graph_options_cc_proto",
        "//mediapipe_custom/util:graph_builder_utils",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/status:statusor",
    ],
    alwayslink = 1,
)

cc_library(
    name = "face_stylizer",
    srcs = ["face_stylizer.cc"],
    hdrs = ["face_stylizer.h"],
    deps = [
        ":face_stylizer_graph",  # buildcleaner:keep
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/core:base_options",
        "//mediapipe_custom/tasks/cc/core:utils",
        "//mediapipe_custom/tasks/cc/vision/core:base_vision_task_api",
        "//mediapipe_custom/tasks/cc/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/cc/vision/core:running_mode",
        "//mediapipe_custom/tasks/cc/vision/core:vision_task_api_factory",
        "//mediapipe_custom/tasks/cc/vision/face_stylizer/proto:face_stylizer_graph_options_cc_proto",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@org_tensorflow//tensorflow/lite/core/api:op_resolver",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
    ],
)
