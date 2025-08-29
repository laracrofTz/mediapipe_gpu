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

load("@org_tensorflow//tensorflow/lite/core/shims:cc_library_with_tflite.bzl", "cc_library_with_tflite", "cc_test_with_tflite")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_cc//cc:cc_test.bzl", "cc_test")

package(default_visibility = ["//visibility:public"])

licenses(["notice"])

cc_library(
    name = "base_options",
    srcs = ["base_options.cc"],
    hdrs = ["base_options.h"],
    deps = [
        ":mediapipe_builtin_op_resolver",
        "//mediapipe_custom/calculators/tensor:inference_calculator_cc_proto",
        "//mediapipe_custom/tasks/cc/core/proto:acceleration_cc_proto",
        "//mediapipe_custom/tasks/cc/core/proto:base_options_cc_proto",
        "//mediapipe_custom/tasks/cc/core/proto:external_file_cc_proto",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/memory",
        "@org_tensorflow//tensorflow/lite/core/api:op_resolver",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
    ],
)

cc_test(
    name = "base_options_test",
    srcs = ["base_options_test.cc"],
    data = [
        "//mediapipe_custom/tasks/testdata/core:test_models",
    ],
    deps = [
        ":base_options",
        ":utils",
        "//mediapipe_custom/calculators/tensor:inference_calculator_cc_proto",
        "//mediapipe_custom/framework/port:gtest",
        "//mediapipe_custom/tasks/cc/core/proto:acceleration_cc_proto",
        "//mediapipe_custom/tasks/cc/core/proto:external_file_cc_proto",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "external_file_handler",
    srcs = ["external_file_handler.cc"],
    hdrs = ["external_file_handler.h"],
    deps = [
        "//mediapipe_custom/framework/port:integral_types",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/core/proto:external_file_cc_proto",
        "//mediapipe_custom/util:resource_util",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
    ],
)

cc_library(
    name = "mediapipe_builtin_op_resolver",
    srcs = ["mediapipe_builtin_op_resolver.cc"],
    hdrs = ["mediapipe_builtin_op_resolver.h"],
    deps = [
        "//mediapipe_custom/tasks/cc/text/custom_ops/ragged:ragged_tensor_to_tensor_tflite",
        "//mediapipe_custom/tasks/cc/text/custom_ops/sentencepiece:sentencepiece_tokenizer_tflite",
        "//mediapipe_custom/tasks/cc/text/language_detector/custom_ops:kmeans_embedding_lookup",
        "//mediapipe_custom/tasks/cc/text/language_detector/custom_ops:ngram_hash",
        "//mediapipe_custom/tasks/cc/vision/custom_ops:fused_batch_norm",
        "//mediapipe_custom/util/tflite/operations:landmarks_to_transform_matrix",
        "//mediapipe_custom/util/tflite/operations:max_pool_argmax",
        "//mediapipe_custom/util/tflite/operations:max_unpooling",
        "//mediapipe_custom/util/tflite/operations:transform_landmarks",
        "//mediapipe_custom/util/tflite/operations:transform_tensor_bilinear",
        "//mediapipe_custom/util/tflite/operations:transpose_conv_bias",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
    ],
)

cc_library_with_tflite(
    name = "model_task_graph",
    srcs = ["model_task_graph.cc"],
    hdrs = ["model_task_graph.h"],
    tflite_deps = [
        ":model_resources",
        ":model_resources_cache",
    ],
    deps = [
        ":model_asset_bundle_resources",
        ":model_resources_calculator",
        "//mediapipe_custom/calculators/tensor:inference_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:subgraph",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/core/proto:acceleration_cc_proto",
        "//mediapipe_custom/tasks/cc/core/proto:base_options_cc_proto",
        "//mediapipe_custom/tasks/cc/core/proto:external_file_cc_proto",
        "//mediapipe_custom/tasks/cc/core/proto:inference_subgraph_cc_proto",
        "//mediapipe_custom/tasks/cc/core/proto:model_resources_calculator_cc_proto",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
    ],
)

# TODO: Enable this test

cc_library_with_tflite(
    name = "model_resources",
    srcs = ["model_resources.cc"],
    hdrs = ["model_resources.h"],
    tflite_deps = [
        "@org_tensorflow//tensorflow/lite:framework_stable",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
        "@org_tensorflow//tensorflow/lite/tools:verifier",
    ],
    deps = [
        ":external_file_handler",
        "//mediapipe_custom/framework/api2:packet",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/core/proto:external_file_cc_proto",
        "//mediapipe_custom/tasks/cc/metadata:metadata_extractor",
        "//mediapipe_custom/util:resource_util",
        "//mediapipe_custom/util:resource_util_custom",
        "//mediapipe_custom/util/tflite:error_reporter",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@org_tensorflow//tensorflow/lite/core/api:error_reporter",
        "@org_tensorflow//tensorflow/lite/core/api:op_resolver",
    ],
)

cc_test_with_tflite(
    name = "model_resources_test",
    srcs = ["model_resources_test.cc"],
    data = [
        "//mediapipe_custom/tasks/testdata/core:test_models",
    ],
    tflite_deps = [
        ":model_resources",
        "@org_tensorflow//tensorflow/lite:framework_stable",
        "@org_tensorflow//tensorflow/lite:test_util",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
    ],
    deps = [
        ":utils",
        "//mediapipe_custom/framework/api2:packet",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/core/proto:external_file_cc_proto",
        "//mediapipe_custom/tasks/cc/metadata:metadata_extractor",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:cord",
        "@org_tensorflow//tensorflow/lite:mutable_op_resolver",
        "@org_tensorflow//tensorflow/lite/c:common",
        "@org_tensorflow//tensorflow/lite/core/api:op_resolver",
    ],
)

cc_library_with_tflite(
    name = "model_resources_cache",
    srcs = ["model_resources_cache.cc"],
    hdrs = ["model_resources_cache.h"],
    tflite_deps = [
        ":model_resources",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
    ],
    deps = [
        ":model_asset_bundle_resources",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/api2:packet",
        "//mediapipe_custom/tasks/cc:common",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@org_tensorflow//tensorflow/lite/core/api:op_resolver",
    ],
)

cc_library_with_tflite(
    name = "model_resources_calculator",
    srcs = ["model_resources_calculator.cc"],
    tflite_deps = [
        ":model_resources",
        ":model_resources_cache",
    ],
    deps = [
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/tasks/cc/core/proto:external_file_cc_proto",
        "//mediapipe_custom/tasks/cc/core/proto:model_resources_calculator_cc_proto",
        "//mediapipe_custom/tasks/cc/metadata:metadata_extractor",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@org_tensorflow//tensorflow/lite/core/api:op_resolver",
    ],
    alwayslink = 1,
)

cc_test(
    name = "model_resources_calculator_test",
    srcs = ["model_resources_calculator_test.cc"],
    data = [
        "//mediapipe_custom/tasks/testdata/core:test_models",
    ],
    deps = [
        ":model_resources",
        ":model_resources_cache",
        ":model_resources_calculator",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "//mediapipe_custom/tasks/cc/core/proto:external_file_cc_proto",
        "//mediapipe_custom/tasks/cc/core/proto:model_resources_calculator_cc_proto",
        "//mediapipe_custom/tasks/cc/metadata:metadata_extractor",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@org_tensorflow//tensorflow/lite:test_util",
        "@org_tensorflow//tensorflow/lite/core/api:op_resolver",
    ],
)

cc_library_with_tflite(
    name = "task_runner",
    srcs = ["task_runner.cc"],
    hdrs = ["task_runner.h"],
    tflite_deps = [
        ":model_resources",
        ":model_resources_cache",
        ":model_resources_calculator",
    ],
    deps = [
        "//mediapipe_custom/framework:calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:executor",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/framework/tool:name_util",
        "//mediapipe_custom/gpu:gpu_shared_data_internal",
        "//mediapipe_custom/tasks/cc:common",
        "@com_google_absl//absl/base:core_headers",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/synchronization",
        "@org_tensorflow//tensorflow/lite/core/api:op_resolver",
    ],
)

cc_test_with_tflite(
    name = "task_runner_test",
    srcs = ["task_runner_test.cc"],
    data = [
        "//mediapipe_custom/tasks/testdata/core:test_models",
    ],
    tflite_deps = [
        ":task_runner",
        ":model_resources",
        ":model_resources_cache",
        "@org_tensorflow//tensorflow/lite:test_util",
    ],
    deps = [
        "//mediapipe_custom/calculators/core:pass_through_calculator",
        "//mediapipe_custom/calculators/core:side_packet_to_stream_calculator",
        "//mediapipe_custom/framework:calculator_cc_proto",
        "//mediapipe_custom/framework:packet",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "//mediapipe_custom/tasks/cc/core/proto:external_file_cc_proto",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
    ],
)

cc_library_with_tflite(
    name = "base_task_api",
    hdrs = ["base_task_api.h"],
    tflite_deps = [
        ":task_runner",
    ],
    deps = [
        "//mediapipe_custom/calculators/core:flow_limiter_calculator",
    ],
)

cc_library_with_tflite(
    name = "task_api_factory",
    hdrs = ["task_api_factory.h"],
    tflite_deps = [
        ":base_task_api",
        ":model_resources",
        ":task_runner",
    ],
    deps = [
        ":utils",
        "//mediapipe_custom/framework:calculator_cc_proto",
        "//mediapipe_custom/framework:executor",
        "//mediapipe_custom/framework/port:requires",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/core/proto:base_options_cc_proto",
        "//mediapipe_custom/tasks/cc/core/proto:external_file_cc_proto",
        "//mediapipe_custom/tasks/cc/core/proto:inference_subgraph_cc_proto",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@org_tensorflow//tensorflow/lite/core/api:op_resolver",
    ],
)

cc_library(
    name = "utils",
    srcs = ["utils.cc"],
    hdrs = ["utils.h"],
    visibility = [
        "//mediapipe_custom/calculators:__subpackages__",
        "//mediapipe_custom/tasks:internal",
    ],
    deps = [
        ":external_file_handler",
        "//mediapipe_custom/calculators/core:flow_limiter_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_cc_proto",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/tasks/cc/core/proto:external_file_cc_proto",
        "//mediapipe_custom/tasks/metadata:metadata_schema_cc",
        "@com_google_absl//absl/strings",
        "@flatbuffers//:runtime_cc",
    ],
)

cc_library(
    name = "model_asset_bundle_resources",
    srcs = ["model_asset_bundle_resources.cc"],
    hdrs = ["model_asset_bundle_resources.h"],
    deps = [
        ":external_file_handler",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/core/proto:external_file_cc_proto",
        "//mediapipe_custom/tasks/cc/metadata/utils:zip_utils",
        "//mediapipe_custom/util:resource_util",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
    ],
)

cc_test(
    name = "model_asset_bundle_resources_test",
    srcs = ["model_asset_bundle_resources_test.cc"],
    data = [
        "//mediapipe_custom/tasks/testdata/core:test_models",
    ],
    deps = [
        ":model_asset_bundle_resources",
        ":model_resources",
        ":utils",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/core/proto:external_file_cc_proto",
        "//mediapipe_custom/tasks/cc/metadata/utils:zip_utils",
    ],
)
