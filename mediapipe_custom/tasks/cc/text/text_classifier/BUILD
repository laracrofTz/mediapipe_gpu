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

# Docs for Mediapipe Tasks Text Classifier
# https://developers.google.com/mediapipe/solutions/text/text_classifier
cc_library(
    name = "text_classifier",
    srcs = ["text_classifier.cc"],
    hdrs = ["text_classifier.h"],
    deps = [
        ":text_classifier_graph",
        "//mediapipe_custom/framework:packet",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/tasks/cc/components/containers:category",
        "//mediapipe_custom/tasks/cc/components/containers:classification_result",
        "//mediapipe_custom/tasks/cc/components/containers/proto:classifications_cc_proto",
        "//mediapipe_custom/tasks/cc/components/processors:classifier_options",
        "//mediapipe_custom/tasks/cc/components/processors/proto:classifier_options_cc_proto",
        "//mediapipe_custom/tasks/cc/core:base_options",
        "//mediapipe_custom/tasks/cc/core:base_task_api",
        "//mediapipe_custom/tasks/cc/core:task_api_factory",
        "//mediapipe_custom/tasks/cc/text/text_classifier/proto:text_classifier_graph_options_cc_proto",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@org_tensorflow//tensorflow/lite/core/api:op_resolver",
    ],
)

cc_library(
    name = "text_classifier_graph",
    srcs = ["text_classifier_graph.cc"],
    deps = [
        "//mediapipe_custom/calculators/tensor:inference_calculator_cpu",
        "//mediapipe_custom/framework:calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/tasks/cc/components/containers/proto:classifications_cc_proto",
        "//mediapipe_custom/tasks/cc/components/processors:classification_postprocessing_graph",
        "//mediapipe_custom/tasks/cc/components/processors:text_preprocessing_graph",
        "//mediapipe_custom/tasks/cc/components/processors/proto:classification_postprocessing_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/components/processors/proto:text_preprocessing_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/core:model_resources",
        "//mediapipe_custom/tasks/cc/core:model_resources_calculator",
        "//mediapipe_custom/tasks/cc/core:model_task_graph",
        "//mediapipe_custom/tasks/cc/core/proto:model_resources_calculator_cc_proto",
        "//mediapipe_custom/tasks/cc/text/text_classifier/proto:text_classifier_graph_options_cc_proto",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ],
    alwayslink = 1,
)

cc_test(
    name = "text_classifier_test",
    srcs = ["text_classifier_test.cc"],
    data = [
        "//mediapipe_custom/tasks/testdata/text:bert_text_classifier_models",
        "//mediapipe_custom/tasks/testdata/text:text_classifier_models",
    ],
    tags = ["not_run:arm"],
    deps = [
        ":text_classifier",
        ":text_classifier_test_utils",
        "//mediapipe_custom/framework/deps:file_path",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/components/containers:category",
        "//mediapipe_custom/tasks/cc/components/containers:classification_result",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:cord",
        "@com_google_sentencepiece//:sentencepiece_processor",  # fixdeps: keep
        "@org_tensorflow//tensorflow/lite:test_util",
    ],
)

cc_library(
    name = "text_classifier_test_utils",
    srcs = ["text_classifier_test_utils.cc"],
    hdrs = ["text_classifier_test_utils.h"],
    visibility = ["//visibility:private"],
    deps = [
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/tasks/cc:common",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
        "@org_tensorflow//tensorflow/lite:mutable_op_resolver",
        "@org_tensorflow//tensorflow/lite:string_util",
        "@org_tensorflow//tensorflow/lite:type_to_tflitetype",
        "@org_tensorflow//tensorflow/lite/c:common",
        "@org_tensorflow//tensorflow/lite/kernels:kernel_util",
    ],
)
