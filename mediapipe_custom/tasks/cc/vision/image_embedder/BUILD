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

# Docs for Mediapipe Tasks Image Embedder
# https://developers.google.com/mediapipe/solutions/vision/image_embedder
cc_library(
    name = "image_embedder",
    srcs = ["image_embedder.cc"],
    hdrs = ["image_embedder.h"],
    deps = [
        ":image_embedder_graph",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/framework/tool:options_map",
        "//mediapipe_custom/tasks/cc/components/containers:embedding_result",
        "//mediapipe_custom/tasks/cc/components/containers/proto:embeddings_cc_proto",
        "//mediapipe_custom/tasks/cc/components/processors:embedder_options",
        "//mediapipe_custom/tasks/cc/components/processors/proto:embedder_options_cc_proto",
        "//mediapipe_custom/tasks/cc/components/utils:cosine_similarity",
        "//mediapipe_custom/tasks/cc/core:base_options",
        "//mediapipe_custom/tasks/cc/core:task_runner",
        "//mediapipe_custom/tasks/cc/core:utils",
        "//mediapipe_custom/tasks/cc/core/proto:base_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/core:base_vision_task_api",
        "//mediapipe_custom/tasks/cc/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/cc/vision/core:running_mode",
        "//mediapipe_custom/tasks/cc/vision/core:vision_task_api_factory",
        "//mediapipe_custom/tasks/cc/vision/image_embedder/proto:image_embedder_graph_options_cc_proto",
        "@com_google_absl//absl/status:statusor",
    ],
)

cc_library(
    name = "image_embedder_graph",
    srcs = ["image_embedder_graph.cc"],
    deps = [
        "//mediapipe_custom/calculators/tensor:inference_calculator",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/tasks/cc/components/calculators:tensors_to_embeddings_calculator",
        "//mediapipe_custom/tasks/cc/components/containers/proto:embeddings_cc_proto",
        "//mediapipe_custom/tasks/cc/components/processors:embedding_postprocessing_graph",
        "//mediapipe_custom/tasks/cc/components/processors:image_preprocessing_graph",
        "//mediapipe_custom/tasks/cc/components/processors/proto:embedding_postprocessing_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/components/processors/proto:image_preprocessing_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/core:model_task_graph",
        "//mediapipe_custom/tasks/cc/vision/image_embedder/proto:image_embedder_graph_options_cc_proto",
        "@com_google_absl//absl/status:statusor",
    ],
    alwayslink = 1,
)

# TODO: This test fails in OSS
