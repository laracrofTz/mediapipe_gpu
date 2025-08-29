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

# Docs for Mediapipe Tasks Text Embedder
# https://developers.google.com/mediapipe/solutions/text/text_embedder
cc_library(
    name = "text_embedder",
    srcs = ["text_embedder.cc"],
    hdrs = ["text_embedder.h"],
    deps = [
        ":text_embedder_graph",
        "//mediapipe_custom/calculators/tensor:inference_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_cc_proto",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/tasks/cc/components/containers:embedding_result",
        "//mediapipe_custom/tasks/cc/components/containers/proto:embeddings_cc_proto",
        "//mediapipe_custom/tasks/cc/components/processors:embedder_options",
        "//mediapipe_custom/tasks/cc/components/processors/proto:embedder_options_cc_proto",
        "//mediapipe_custom/tasks/cc/components/utils:cosine_similarity",
        "//mediapipe_custom/tasks/cc/core:base_options",
        "//mediapipe_custom/tasks/cc/core:base_task_api",
        "//mediapipe_custom/tasks/cc/core:task_api_factory",
        "//mediapipe_custom/tasks/cc/core/proto:base_options_cc_proto",
        "//mediapipe_custom/tasks/cc/text/text_embedder/proto:text_embedder_graph_options_cc_proto",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "text_embedder_graph",
    srcs = ["text_embedder_graph.cc"],
    deps = [
        "//mediapipe_custom/calculators/tensor:inference_calculator_cc_proto",
        "//mediapipe_custom/calculators/tensor:inference_calculator_cpu",
        "//mediapipe_custom/framework:calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/tasks/cc/components/calculators:tensors_to_embeddings_calculator_cc_proto",
        "//mediapipe_custom/tasks/cc/components/containers/proto:embeddings_cc_proto",
        "//mediapipe_custom/tasks/cc/components/processors:embedding_postprocessing_graph",
        "//mediapipe_custom/tasks/cc/components/processors:text_preprocessing_graph",
        "//mediapipe_custom/tasks/cc/components/processors/proto:embedding_postprocessing_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/components/processors/proto:text_model_type_cc_proto",
        "//mediapipe_custom/tasks/cc/components/processors/proto:text_preprocessing_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/core:model_resources",
        "//mediapipe_custom/tasks/cc/core:model_task_graph",
        "//mediapipe_custom/tasks/cc/core/proto:model_resources_calculator_cc_proto",
        "//mediapipe_custom/tasks/cc/text/text_embedder/proto:text_embedder_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/text/utils:text_model_utils",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
    ],
    alwayslink = 1,
)

cc_test(
    name = "text_embedder_test",
    srcs = ["text_embedder_test.cc"],
    data = [
        "//mediapipe_custom/tasks/testdata/text:mobilebert_embedding_model",
        "//mediapipe_custom/tasks/testdata/text:regex_embedding_with_metadata",
        "//mediapipe_custom/tasks/testdata/text:universal_sentence_encoder_qa",
    ],
    tags = ["not_run:arm"],
    deps = [
        ":text_embedder",
        "//mediapipe_custom/framework/deps:file_path",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/components/containers:embedding_result",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:cord",
        "@org_tensorflow//tensorflow/lite:test_util",
    ],
)
