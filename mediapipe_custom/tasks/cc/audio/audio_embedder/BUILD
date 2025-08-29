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

# Docs for Mediapipe Tasks Audio Embedder
# https://developers.google.com/mediapipe/solutions/audio/audio_embedder
cc_library(
    name = "audio_embedder",
    srcs = ["audio_embedder.cc"],
    hdrs = ["audio_embedder.h"],
    deps = [
        ":audio_embedder_graph",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/formats:matrix",
        "//mediapipe_custom/tasks/cc/audio/audio_embedder/proto:audio_embedder_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/audio/core:audio_task_api_factory",
        "//mediapipe_custom/tasks/cc/audio/core:base_audio_task_api",
        "//mediapipe_custom/tasks/cc/audio/core:running_mode",
        "//mediapipe_custom/tasks/cc/components/containers:embedding_result",
        "//mediapipe_custom/tasks/cc/components/containers/proto:embeddings_cc_proto",
        "//mediapipe_custom/tasks/cc/components/processors:embedder_options",
        "//mediapipe_custom/tasks/cc/components/processors/proto:embedder_options_cc_proto",
        "//mediapipe_custom/tasks/cc/core:base_options",
        "//mediapipe_custom/tasks/cc/core:task_runner",
        "//mediapipe_custom/tasks/cc/core/proto:inference_subgraph_cc_proto",
        "@com_google_absl//absl/status:statusor",
        "@org_tensorflow//tensorflow/lite/core/api:op_resolver",
    ],
)

cc_library(
    name = "audio_embedder_graph",
    srcs = ["audio_embedder_graph.cc"],
    deps = [
        "//mediapipe_custom/calculators/audio:time_series_framer_calculator",
        "//mediapipe_custom/calculators/core:constant_side_packet_calculator",
        "//mediapipe_custom/calculators/core:constant_side_packet_calculator_cc_proto",
        "//mediapipe_custom/calculators/core:side_packet_to_stream_calculator",
        "//mediapipe_custom/calculators/tensor:audio_to_tensor_calculator",
        "//mediapipe_custom/calculators/tensor:audio_to_tensor_calculator_cc_proto",
        "//mediapipe_custom/calculators/tensor:inference_calculator_cpu",
        "//mediapipe_custom/framework:calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:matrix",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/audio/audio_embedder/proto:audio_embedder_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/audio/utils:audio_tensor_specs",
        "//mediapipe_custom/tasks/cc/components/containers/proto:embeddings_cc_proto",
        "//mediapipe_custom/tasks/cc/components/processors:embedding_postprocessing_graph",
        "//mediapipe_custom/tasks/cc/components/processors/proto:embedding_postprocessing_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/core:model_resources",
        "//mediapipe_custom/tasks/cc/core:model_task_graph",
        "//mediapipe_custom/tasks/cc/core/proto:inference_subgraph_cc_proto",
        "//mediapipe_custom/tasks/cc/metadata:metadata_extractor",
        "//mediapipe_custom/tasks/metadata:metadata_schema_cc",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/types:optional",
        "@org_tensorflow//tensorflow/lite/schema:schema_fbs",
    ],
    alwayslink = 1,
)

# TODO: mediapipe/tasks/cc/audio/utils:test_utils does not compile in the OSS build
