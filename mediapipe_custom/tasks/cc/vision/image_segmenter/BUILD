# Copyright 2022 The MediaPipe Authors.
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
    name = "image_segmenter_result",
    hdrs = ["image_segmenter_result.h"],
    deps = ["//mediapipe_custom/framework/formats:image"],
)

# Docs for Mediapipe Tasks Image Segmenter
# https://developers.google.com/mediapipe/solutions/vision/image_segmenter
cc_library(
    name = "image_segmenter",
    srcs = ["image_segmenter.cc"],
    hdrs = ["image_segmenter.h"],
    deps = [
        ":image_segmenter_graph",
        ":image_segmenter_result",
        "//mediapipe_custom/framework:calculator_cc_proto",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/tasks/cc/core:base_options",
        "//mediapipe_custom/tasks/cc/core:utils",
        "//mediapipe_custom/tasks/cc/vision/core:base_vision_task_api",
        "//mediapipe_custom/tasks/cc/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/cc/vision/core:running_mode",
        "//mediapipe_custom/tasks/cc/vision/core:vision_task_api_factory",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter/calculators:tensors_to_segmentation_calculator_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter/proto:image_segmenter_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter/proto:segmenter_options_cc_proto",
        "//mediapipe_custom/util:label_map_cc_proto",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings:str_format",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
    ],
)

cc_library(
    name = "image_segmenter_graph",
    srcs = ["image_segmenter_graph.cc"],
    deps = [
        "//mediapipe_custom/calculators/core:merge_to_vector_calculator",
        "//mediapipe_custom/calculators/image:image_clone_calculator_cc_proto",
        "//mediapipe_custom/calculators/image:image_properties_calculator",
        "//mediapipe_custom/calculators/image:image_transformation_calculator",
        "//mediapipe_custom/calculators/image:image_transformation_calculator_cc_proto",
        "//mediapipe_custom/calculators/image:set_alpha_calculator",
        "//mediapipe_custom/calculators/image:set_alpha_calculator_cc_proto",
        "//mediapipe_custom/calculators/tensor:image_to_tensor_calculator",
        "//mediapipe_custom/calculators/tensor:inference_calculator",
        "//mediapipe_custom/calculators/tensor:tensor_converter_calculator",
        "//mediapipe_custom/calculators/tensor:tensor_converter_calculator_cc_proto",
        "//mediapipe_custom/calculators/tensor:tensors_dequantization_calculator",
        "//mediapipe_custom/calculators/util:from_image_calculator",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/components/processors:image_preprocessing_graph",
        "//mediapipe_custom/tasks/cc/components/processors/proto:image_preprocessing_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/core:model_resources",
        "//mediapipe_custom/tasks/cc/core:model_task_graph",
        "//mediapipe_custom/tasks/cc/core/proto:inference_subgraph_cc_proto",
        "//mediapipe_custom/tasks/cc/metadata:metadata_extractor",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter/calculators:tensors_to_segmentation_calculator",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter/calculators:tensors_to_segmentation_calculator_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter/proto:image_segmenter_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter/proto:segmenter_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/utils:image_tensor_specs",
        "//mediapipe_custom/tasks/metadata:image_segmenter_metadata_schema_cc",
        "//mediapipe_custom/tasks/metadata:metadata_schema_cc",
        "//mediapipe_custom/util:graph_builder_utils",
        "//mediapipe_custom/util:label_map_cc_proto",
        "//mediapipe_custom/util:label_map_util",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings:str_format",
        "@org_tensorflow//tensorflow/lite/schema:schema_fbs",
    ],
    alwayslink = 1,
)

# TODO: This test fails in OSS
