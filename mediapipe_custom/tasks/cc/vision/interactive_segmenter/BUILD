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

# Docs for Mediapipe Tasks Interactive Segmenter
# TODO: add doc link.
cc_library(
    name = "interactive_segmenter",
    srcs = ["interactive_segmenter.cc"],
    hdrs = ["interactive_segmenter.h"],
    deps = [
        ":interactive_segmenter_graph",
        "//mediapipe_custom/framework:calculator_cc_proto",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/components/containers:keypoint",
        "//mediapipe_custom/tasks/cc/core:base_options",
        "//mediapipe_custom/tasks/cc/vision/core:base_vision_task_api",
        "//mediapipe_custom/tasks/cc/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/cc/vision/core:running_mode",
        "//mediapipe_custom/tasks/cc/vision/core:vision_task_api_factory",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter:image_segmenter_result",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter/proto:image_segmenter_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter/proto:segmenter_options_cc_proto",
        "//mediapipe_custom/util:color_cc_proto",
        "//mediapipe_custom/util:render_data_cc_proto",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/types:optional",
    ],
)

cc_library(
    name = "interactive_segmenter_graph",
    srcs = ["interactive_segmenter_graph.cc"],
    deps = [
        "//mediapipe_custom/calculators/image:image_transformation_calculator",
        "//mediapipe_custom/calculators/image:set_alpha_calculator",
        "//mediapipe_custom/calculators/util:annotation_overlay_calculator",
        "//mediapipe_custom/calculators/util:flat_color_image_calculator",
        "//mediapipe_custom/calculators/util:flat_color_image_calculator_cc_proto",
        "//mediapipe_custom/calculators/util:from_image_calculator",
        "//mediapipe_custom/calculators/util:to_image_calculator",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/tasks/cc/components/processors:image_preprocessing_graph",
        "//mediapipe_custom/tasks/cc/core:model_task_graph",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter:image_segmenter_graph",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter/proto:image_segmenter_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter/proto:segmenter_options_cc_proto",
        "//mediapipe_custom/util:color_cc_proto",
        "//mediapipe_custom/util:graph_builder_utils",
        "//mediapipe_custom/util:label_map_cc_proto",
        "//mediapipe_custom/util:render_data_cc_proto",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
    ] + select({
        "//mediapipe_custom/gpu:disable_gpu": [],
        "//conditions:default": [
            "//mediapipe_custom/gpu:gpu_buffer_to_image_frame_calculator",
            "//mediapipe_custom/gpu:image_frame_to_gpu_buffer_calculator",
        ],
    }),
    alwayslink = 1,
)
