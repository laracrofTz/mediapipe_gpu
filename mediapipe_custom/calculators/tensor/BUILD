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
#

load("@bazel_skylib//lib:selects.bzl", "selects")
load("@org_tensorflow//tensorflow/lite/core/shims:cc_library_with_tflite.bzl", "cc_library_with_tflite")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_cc//cc:cc_test.bzl", "cc_test")
load("//mediapipe_custom/framework:encode_binary_proto.bzl", "encode_binary_proto")
load("//mediapipe_custom/framework:mediapipe_cc_test.bzl", "mediapipe_cc_test")
load("//mediapipe_custom/framework:more_selects.bzl", "more_selects")
load("//mediapipe_custom/framework/port:build_config.bzl", "mediapipe_proto_library")
load(
    "//mediapipe_custom/framework/tool:mediapipe_graph.bzl",
    "mediapipe_binary_graph",
)

licenses(["notice"])

package(default_visibility = ["//visibility:public"])

exports_files(
    glob(["testdata/image_to_tensor/*"]),
    visibility = [
        "//mediapipe_custom/calculators/image:__subpackages__",
        "//mediapipe_custom/util:__subpackages__",
    ],
)

config_setting(
    name = "disable_gpu",
    define_values = {
        "MEDIAPIPE_DISABLE_GPU": "1",
    },
    visibility = ["//visibility:public"],
)

more_selects.config_setting_negation(
    name = "not_disable_gpu",
    negate = ":disable_gpu",
)

selects.config_setting_group(
    name = "platform_apple_with_gpu",
    match_all = [
        ":not_disable_gpu",
        "//mediapipe_custom:apple",
    ],
)

selects.config_setting_group(
    name = "platform_apple_without_gpu",
    match_all = [
        ":disable_gpu",
        "//mediapipe_custom:apple",
    ],
)

selects.config_setting_group(
    name = "compute_shader_unavailable",
    match_any = [
        "//mediapipe_custom/gpu:disable_gpu",
    ],
)

mediapipe_proto_library(
    name = "audio_to_tensor_calculator_proto",
    srcs = ["audio_to_tensor_calculator.proto"],
    deps = [
        "//mediapipe_custom/framework:calculator_options_proto",
        "//mediapipe_custom/framework:calculator_proto",
    ],
)

cc_library(
    name = "audio_to_tensor_calculator",
    srcs = ["audio_to_tensor_calculator.cc"],
    deps = [
        ":audio_to_tensor_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:memory_manager",
        "//mediapipe_custom/framework:memory_manager_service",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/api2:packet",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:matrix",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/formats:time_series_header_cc_proto",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/util:time_series_util",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_audio_tools//audio/dsp:resampler_q",
        "@com_google_audio_tools//audio/dsp:window_functions",
        "@org_tensorflow//tensorflow/lite/c:common",
        "@pffft",
    ],
    alwayslink = 1,
)

cc_test(
    name = "audio_to_tensor_calculator_test",
    srcs = ["audio_to_tensor_calculator_test.cc"],
    deps = [
        ":audio_to_tensor_calculator",
        ":audio_to_tensor_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:timestamp",
        "//mediapipe_custom/framework/api2:packet",
        "//mediapipe_custom/framework/formats:matrix",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "@com_google_absl//absl/strings",
        "@com_google_audio_tools//audio/dsp:resampler_q",
        "@org_tensorflow//tensorflow/lite/c:common",
    ],
)

mediapipe_proto_library(
    name = "tensors_to_audio_calculator_proto",
    srcs = ["tensors_to_audio_calculator.proto"],
    deps = [
        "//mediapipe_custom/framework:calculator_options_proto",
        "//mediapipe_custom/framework:calculator_proto",
    ],
)

cc_library(
    name = "tensors_to_audio_calculator",
    srcs = ["tensors_to_audio_calculator.cc"],
    deps = [
        ":tensors_to_audio_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/formats:matrix",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "@com_google_absl//absl/algorithm:container",
        "@com_google_absl//absl/status",
        "@com_google_audio_tools//audio/dsp:window_functions",
        "@pffft",
    ],
    alwayslink = 1,
)

cc_test(
    name = "tensors_to_audio_calculator_test",
    srcs = ["tensors_to_audio_calculator_test.cc"],
    deps = [
        ":audio_to_tensor_calculator",
        ":audio_to_tensor_calculator_cc_proto",
        ":tensors_to_audio_calculator",
        ":tensors_to_audio_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/formats:matrix",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
        "@com_google_audio_tools//audio/dsp:window_functions",
    ],
)

mediapipe_proto_library(
    name = "feedback_tensors_calculator_proto",
    srcs = ["feedback_tensors_calculator.proto"],
    deps = [
        "//mediapipe_custom/framework:calculator_options_proto",
        "//mediapipe_custom/framework:calculator_proto",
    ],
)

cc_library(
    name = "feedback_tensors_calculator",
    srcs = ["feedback_tensors_calculator.cc"],
    deps = [
        ":feedback_tensors_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:memory_manager",
        "//mediapipe_custom/framework:memory_manager_service",
        "//mediapipe_custom/framework/api2:contract",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/formats:tensor",
        "@com_google_absl//absl/status",
    ],
    alwayslink = 1,
)

cc_test(
    name = "feedback_tensors_calculator_test",
    srcs = ["feedback_tensors_calculator_test.cc"],
    deps = [
        ":feedback_tensors_calculator",
        ":feedback_tensors_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:timestamp",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "@com_google_absl//absl/log:absl_check",
        "@org_tensorflow//tensorflow/lite/c:common",
    ],
)

mediapipe_proto_library(
    name = "bert_preprocessor_calculator_proto",
    srcs = ["bert_preprocessor_calculator.proto"],
    deps = [
        "//mediapipe_custom/framework:calculator_options_proto",
        "//mediapipe_custom/framework:calculator_proto",
    ],
)

cc_library(
    name = "bert_preprocessor_calculator",
    srcs = ["bert_preprocessor_calculator.cc"],
    deps = [
        ":bert_preprocessor_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:memory_manager",
        "//mediapipe_custom/framework:memory_manager_service",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/tasks/cc/core:utils",
        "//mediapipe_custom/tasks/cc/metadata:metadata_extractor",
        "//mediapipe_custom/tasks/cc/text/tokenizers:tokenizer",
        "//mediapipe_custom/tasks/cc/text/tokenizers:tokenizer_utils",
        "//mediapipe_custom/tasks/metadata:metadata_schema_cc",
        "@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
    ],
    alwayslink = 1,
)

cc_test(
    name = "bert_preprocessor_calculator_test",
    srcs = ["bert_preprocessor_calculator_test.cc"],
    data = [
        "//mediapipe_custom/tasks/testdata/text:bert_text_classifier_models",
    ],
    linkopts = ["-ldl"],
    deps = [
        ":bert_preprocessor_calculator",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "//mediapipe_custom/tasks/cc/core:utils",
        "//mediapipe_custom/tasks/cc/metadata:metadata_extractor",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_sentencepiece//:sentencepiece_processor",  # fixdeps: keep
    ],
)

mediapipe_proto_library(
    name = "regex_preprocessor_calculator_proto",
    srcs = ["regex_preprocessor_calculator.proto"],
    deps = [
        "//mediapipe_custom/framework:calculator_options_proto",
        "//mediapipe_custom/framework:calculator_proto",
    ],
)

cc_library(
    name = "regex_preprocessor_calculator",
    srcs = ["regex_preprocessor_calculator.cc"],
    deps = [
        ":regex_preprocessor_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:memory_manager",
        "//mediapipe_custom/framework:memory_manager_service",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/tasks/cc/metadata:metadata_extractor",
        "//mediapipe_custom/tasks/cc/text/tokenizers:regex_tokenizer",
        "//mediapipe_custom/tasks/cc/text/tokenizers:tokenizer_utils",
        "//mediapipe_custom/tasks/metadata:metadata_schema_cc",
        "@com_google_absl//absl/status",
    ],
    alwayslink = 1,
)

cc_test(
    name = "regex_preprocessor_calculator_test",
    srcs = ["regex_preprocessor_calculator_test.cc"],
    data = ["//mediapipe_custom/tasks/testdata/text:text_classifier_models"],
    linkopts = ["-ldl"],
    deps = [
        ":regex_preprocessor_calculator",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "//mediapipe_custom/framework/tool:sink",
        "//mediapipe_custom/tasks/cc/core:utils",
        "//mediapipe_custom/tasks/cc/metadata:metadata_extractor",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_sentencepiece//:sentencepiece_processor",  # fixdeps: keep
    ],
)

cc_library(
    name = "text_to_tensor_calculator",
    srcs = ["text_to_tensor_calculator.cc"],
    deps = [
        "//mediapipe_custom/framework:calculator_context",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:memory_manager",
        "//mediapipe_custom/framework:memory_manager_service",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:tensor",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
    ],
    alwayslink = 1,
)

cc_test(
    name = "text_to_tensor_calculator_test",
    srcs = ["text_to_tensor_calculator_test.cc"],
    deps = [
        ":text_to_tensor_calculator",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:calculator_graph",
        "//mediapipe_custom/framework:packet",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "//mediapipe_custom/framework/tool:options_map",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "universal_sentence_encoder_preprocessor_calculator",
    srcs = ["universal_sentence_encoder_preprocessor_calculator.cc"],
    deps = [
        "//mediapipe_custom/framework:calculator_context",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:memory_manager",
        "//mediapipe_custom/framework:memory_manager_service",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/tasks/cc/core:utils",
        "//mediapipe_custom/tasks/cc/metadata:metadata_extractor",
        "@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
    ],
    alwayslink = 1,
)

cc_test(
    name = "universal_sentence_encoder_preprocessor_calculator_test",
    srcs = ["universal_sentence_encoder_preprocessor_calculator_test.cc"],
    data = ["//mediapipe_custom/tasks/testdata/text:universal_sentence_encoder_qa"],
    deps = [
        ":universal_sentence_encoder_preprocessor_calculator",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:packet",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/framework/tool:options_map",
        "//mediapipe_custom/tasks/cc/core:utils",
        "//mediapipe_custom/tasks/cc/metadata:metadata_extractor",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
    ],
)

mediapipe_proto_library(
    name = "inference_calculator_proto",
    srcs = ["inference_calculator.proto"],
    deps = [
        "//mediapipe_custom/framework:calculator_options_proto",
        "//mediapipe_custom/framework:calculator_proto",
    ],
)

config_setting(
    name = "force_cpu_inference",
    values = {
        "define": "MEDIAPIPE_FORCE_CPU_INFERENCE=true",
    },
    visibility = ["//visibility:public"],
)

# This target defines the "InferenceCalculator" component, which looks for the available concrete
# implementations linked into the current binary and picks the one to use.
# You can depend on :inference_calculator instead if you want to automatically include a default
# set of implementations tailored for the current build configuration.
# If you want to have precise control of which implementations to include (e.g. for strict binary
# size concerns), depend on those implementations directly, and do not depend on
# :inference_calculator.
# In all cases, use "InferenceCalculator" in your graphs.
cc_library_with_tflite(
    name = "inference_calculator_interface",
    srcs = ["inference_calculator.cc"],
    hdrs = ["inference_calculator.h"],
    local_defines = select({
        ":force_cpu_inference": ["MEDIAPIPE_FORCE_CPU_INFERENCE=1"],
        "//conditions:default": ["MEDIAPIPE_FORCE_CPU_INFERENCE=0"],
    }),
    tflite_deps = [
        ":inference_runner",
        ":inference_io_mapper",
        "//mediapipe_custom/util/tflite:tflite_model_loader",
        "@org_tensorflow//tensorflow/lite:framework_stable",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
    ],
    deps = [
        ":inference_calculator_cc_proto",
        ":inference_calculator_options_lib",
        ":tensor_span",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:port",
        "//mediapipe_custom/framework:resources",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/api2:packet",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/framework/stream_handler:fixed_size_input_stream_handler",
        "//mediapipe_custom/framework/tool:subgraph_expansion",
        "//mediapipe_custom/util:cpu_util",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/time",
        "@org_tensorflow//tensorflow/lite/core/api:op_resolver",
    ],
    alwayslink = 1,
)

# Helper utility to more easily iterate over a collection of Tensor references
cc_library(
    name = "tensor_span",
    srcs = ["tensor_span.cc"],
    hdrs = ["tensor_span.h"],
    deps = ["//mediapipe_custom/framework/formats:tensor"],
)

cc_library_with_tflite(
    name = "inference_io_mapper",
    srcs = ["inference_io_mapper.cc"],
    hdrs = ["inference_io_mapper.h"],
    tflite_deps = [
        "@org_tensorflow//tensorflow/lite/c:c_api_types",
        "@org_tensorflow//tensorflow/lite:framework_stable",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
        "//mediapipe_custom/util/tflite:tflite_signature_reader",
    ],
    deps = [
        ":inference_calculator_cc_proto",
        ":tensor_span",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@org_tensorflow//tensorflow/lite/core/api:op_resolver",
    ],
)

# TODO b/336756170 - convert test to use cc_test_with_tflite
cc_test(
    name = "inference_io_mapper_test",
    srcs = ["inference_io_mapper_test.cc"],
    data = [
        ":testdata/3in3out_model_swaps_input_2_and_0.tflite",
        ":testdata/test_two_signature_keys_model.tflite",
    ],
    deps = [
        ":inference_calculator",
        ":inference_calculator_cc_proto",
        ":inference_calculator_cpu",
        ":inference_io_mapper",
        ":tensor_span",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:packet",
        "//mediapipe_custom/framework:resources",
        "//mediapipe_custom/framework/api2:packet",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "//mediapipe_custom/framework/tool:sink",
        "//mediapipe_custom/util/tflite:tflite_model_loader",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
        "@org_tensorflow//tensorflow/lite:framework_stable",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
    ],
)

cc_library_with_tflite(
    name = "inference_feedback_manager",
    srcs = ["inference_feedback_manager.cc"],
    hdrs = ["inference_feedback_manager.h"],
    tflite_deps = [
        ":inference_io_mapper",
        "//mediapipe_custom/util/tflite:utils",
        "//mediapipe_custom/util/tflite:tflite_signature_reader",
        "@org_tensorflow//tensorflow/lite:framework_stable",
        "@org_tensorflow//tensorflow/lite:namespace",
        "@org_tensorflow//tensorflow/lite/c:common",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
    ],
    deps = [
        ":inference_calculator_cc_proto",
        ":inference_calculator_utils",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
    ],
)

cc_test(
    name = "inference_feedback_manager_test",
    srcs = ["inference_feedback_manager_test.cc"],
    data = [
        ":testdata/feedback_tensor_test_model.tflite",
        ":testdata/feedback_tensor_with_state_copy_model.tflite",
    ],
    deps = [
        ":inference_calculator",
        ":inference_calculator_cc_proto",
        ":inference_calculator_cpu",
        ":inference_calculator_interface",
        ":inference_feedback_manager",
        ":inference_io_mapper",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:resources",
        "//mediapipe_custom/framework/api2:packet",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "//mediapipe_custom/framework/port:status_matchers",
        "//mediapipe_custom/framework/tool:sink",
        "//mediapipe_custom/util/tflite:tflite_model_loader",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
        "@org_tensorflow//tensorflow/lite:framework_stable",
        "@org_tensorflow//tensorflow/lite:util",
        "@org_tensorflow//tensorflow/lite/core:framework",
        "@org_tensorflow//tensorflow/lite/core/api:op_resolver",
        "@org_tensorflow//tensorflow/lite/delegates/xnnpack:xnnpack_delegate_hdrs_only",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
    ],
)

cc_library(
    name = "inference_calculator_gl",
    srcs = ["inference_calculator_gl.cc"],
    tags = ["nomac"],  # config problem with cpuinfo via TF
    deps = [
        ":inference_calculator_cc_proto",
        ":inference_calculator_interface",
        ":inference_io_mapper",
        ":tensor_span",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:mediapipe_profiling",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/api2:packet",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/gpu:gl_base_hdr",
        "//mediapipe_custom/gpu:gl_calculator_helper",
        "//mediapipe_custom/gpu:gl_context",
        "//mediapipe_custom/util/tflite:tflite_model_loader",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/time",
        "@org_tensorflow//tensorflow/lite:framework_stable",
        "@org_tensorflow//tensorflow/lite/core:framework",
        "@org_tensorflow//tensorflow/lite/delegates/gpu:gl_delegate",
    ],
    alwayslink = 1,
)

cc_library(
    name = "inference_calculator_gl_advanced",
    srcs = ["inference_calculator_gl_advanced.cc"],
    tags = ["nomac"],
    deps = [
        ":inference_calculator_interface",
        ":inference_io_mapper",
        ":inference_on_disk_cache_helper",
        ":inference_runner",
        ":tensor_span",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:mediapipe_profiling",
        "//mediapipe_custom/framework/api2:packet",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/gpu:gl_calculator_helper",
        "//mediapipe_custom/gpu:gl_context",
        "//mediapipe_custom/util/tflite:tflite_gpu_runner",
        "//mediapipe_custom/util/tflite:tflite_model_loader",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:string_view",
        "@com_google_absl//absl/time",
        "@org_tensorflow//tensorflow/lite:framework_stable",
    ],
    alwayslink = 1,
)

cc_library(
    name = "inference_calculator_metal",
    srcs = ["inference_calculator_metal.cc"],
    copts = [
        "-x objective-c++",
        "-fobjc-arc",  # enable reference-counting
    ],
    tags = ["ios"],
    deps = [
        ":inference_calculator_interface",
        ":inference_io_mapper",
        ":tensor_span",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/gpu:MPPMetalHelper",
        "//mediapipe_custom/gpu:MPPMetalUtil",
        "//mediapipe_custom/gpu:gpu_buffer",
        "//mediapipe_custom/objc:mediapipe_framework_ios",
        "//mediapipe_custom/util/tflite:config",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/strings:str_format",
        "@org_tensorflow//tensorflow/lite/delegates/gpu:metal_delegate",
        "@org_tensorflow//tensorflow/lite/delegates/gpu:metal_delegate_internal",
        "@org_tensorflow//tensorflow/lite/delegates/gpu/common:shape",
        "@org_tensorflow//tensorflow/lite/delegates/gpu/metal:buffer_convert",
    ] + select({
        "//mediapipe_custom:apple": [
            "//third_party/apple_frameworks:CoreVideo",
            "//third_party/apple_frameworks:MetalKit",
        ],
        "//conditions:default": [],
    }),
    alwayslink = 1,
)

cc_library_with_tflite(
    name = "inference_runner",
    hdrs = ["inference_runner.h"],
    tflite_deps = [
        ":inference_io_mapper",
    ],
    deps = [
        ":tensor_span",
        "//mediapipe_custom/framework:calculator_context",
        "//mediapipe_custom/framework/formats:tensor",
        "@com_google_absl//absl/status:statusor",
    ],
)

cc_library_with_tflite(
    name = "tflite_delegate_ptr",
    hdrs = ["tflite_delegate_ptr.h"],
    tflite_deps = [
        "@org_tensorflow//tensorflow/lite/c:c_api_types",
    ],
)

cc_library_with_tflite(
    name = "inference_interpreter_delegate_runner",
    srcs = ["inference_interpreter_delegate_runner.cc"],
    hdrs = ["inference_interpreter_delegate_runner.h"],
    tflite_deps = [
        ":inference_runner",
        ":tflite_delegate_ptr",
        ":inference_io_mapper",
        ":inference_feedback_manager",
        "//mediapipe_custom/util/tflite:tflite_model_loader",
        "@org_tensorflow//tensorflow/lite:framework_stable",
        "@org_tensorflow//tensorflow/lite/c:c_api_types",
        "@org_tensorflow//tensorflow/lite/c:common",
    ],
    deps = [
        ":inference_calculator_utils",
        ":tensor_span",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:mediapipe_profiling",
        "//mediapipe_custom/framework/api2:packet",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@org_tensorflow//tensorflow/lite:string_util",
        "@org_tensorflow//tensorflow/lite:util",
        "@org_tensorflow//tensorflow/lite/core/api:op_resolver",
    ],
)

cc_test(
    name = "inference_interpreter_delegate_runner_test",
    srcs = ["inference_interpreter_delegate_runner_test.cc"],
    data = [
        ":testdata/1x3_square_float32.tflite",
        ":testdata/1x3_square_int32.tflite",
        ":testdata/3in3out_model_swaps_input_2_and_0.tflite",
    ],
    deps = [
        ":inference_interpreter_delegate_runner",
        ":tensor_span",
        ":tflite_delegate_ptr",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:calculator_state",
        "//mediapipe_custom/framework:resources",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/api2:packet",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/util/tflite:tflite_model_loader",
        "@com_google_absl//absl/functional:any_invocable",
        "@com_google_absl//absl/status",
        "@org_tensorflow//tensorflow/lite:framework_stable",
        "@org_tensorflow//tensorflow/lite:util",
        "@org_tensorflow//tensorflow/lite/core/api:op_resolver",
        "@org_tensorflow//tensorflow/lite/delegates/xnnpack:xnnpack_delegate_hdrs_only",
        "@org_tensorflow//tensorflow/lite/kernels:builtin_ops",
    ],
)

cc_library(
    name = "inference_calculator_cpu",
    srcs = [
        "inference_calculator_cpu.cc",
    ],
    local_defines = select({
        ":force_cpu_inference": ["MEDIAPIPE_FORCE_CPU_INFERENCE=1"],
        "//conditions:default": ["MEDIAPIPE_FORCE_CPU_INFERENCE=0"],
    }),
    deps = [
        ":inference_calculator_interface",
        ":inference_calculator_utils",
        ":inference_interpreter_delegate_runner",
        ":inference_runner",
        ":tensor_span",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/time",
        "@org_tensorflow//tensorflow/lite:framework_stable",
        "@org_tensorflow//tensorflow/lite/c:c_api_types",
        "@org_tensorflow//tensorflow/lite/delegates/xnnpack:xnnpack_delegate",
    ] + select({
        "//conditions:default": [],
        "//mediapipe_custom:android": ["@org_tensorflow//tensorflow/lite/delegates/nnapi:nnapi_delegate"],
    }),
    alwayslink = 1,
)

cc_library(
    name = "inference_calculator_utils",
    srcs = ["inference_calculator_utils.cc"],
    hdrs = ["inference_calculator_utils.h"],
    deps = [
        ":inference_calculator_cc_proto",
        "//mediapipe_custom/framework:memory_manager",
        "//mediapipe_custom/framework:port",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/types:span",
        "@org_tensorflow//tensorflow/lite:framework_stable",
        "@org_tensorflow//tensorflow/lite:string_util",
        "@org_tensorflow//tensorflow/lite:type_to_tflitetype",
        "@org_tensorflow//tensorflow/lite:util",
        "@org_tensorflow//tensorflow/lite/c:common",
        "@org_tensorflow//tensorflow/lite/core:framework",
    ] + select({
        "//mediapipe_custom:emscripten": [],
        "//conditions:default": [
            "//mediapipe_custom/util:cpu_util",
        ],
    }),
    alwayslink = 1,
)

cc_test(
    name = "inference_calculator_utils_test",
    srcs = ["inference_calculator_utils_test.cc"],
    deps = [
        ":inference_calculator_cc_proto",
        ":inference_calculator_utils",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/log",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/types:span",
        "@org_tensorflow//tensorflow/lite:framework_stable",
        "@org_tensorflow//tensorflow/lite:string_util",
        "@org_tensorflow//tensorflow/lite:util",
        "@org_tensorflow//tensorflow/lite/c:common",
        "@org_tensorflow//tensorflow/lite/kernels:cast_test_common",
        "@org_tensorflow//tensorflow/lite/schema:schema_fbs",
    ],
)

cc_library(
    name = "inference_on_disk_cache_helper",
    srcs = ["inference_on_disk_cache_helper.cc"],
    hdrs = ["inference_on_disk_cache_helper.h"],
    tags = ["nomac"],
    deps = [
        ":inference_calculator_cc_proto",
        ":inference_calculator_interface",
        ":inference_io_mapper",
        "//mediapipe_custom/framework/deps:file_path",
        "//mediapipe_custom/framework/port:file_helpers",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/util/tflite:tflite_gpu_runner",
        "//mediapipe_custom/util/tflite:tflite_model_loader",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:string_view",
    ],
)

cc_library(
    name = "inference_calculator_xnnpack",
    srcs = [
        "inference_calculator_xnnpack.cc",
    ],
    deps = [
        ":inference_calculator_interface",
        ":inference_calculator_utils",
        ":inference_interpreter_delegate_runner",
        ":inference_runner",
        ":tensor_span",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/time",
        "@org_tensorflow//tensorflow/lite/delegates/xnnpack:xnnpack_delegate",
    ],
    alwayslink = 1,
)

cc_library(
    name = "inference_calculator_gl_if_compute_shader_available",
    deps = selects.with_or({
        ":compute_shader_unavailable": [],
        "//conditions:default": [
            ":inference_calculator_gl",
            ":inference_calculator_gl_advanced",
        ],
    }),
)

# This target provides the InferenceCalculator and a default set of implementations tailored for the
# current build platforms. More implementations can be added as separate dependencies to a client;
# for clients that want a narrower set of implementations than the default should see the comment on
# inference_calculator_interface.
cc_library(
    name = "inference_calculator",
    deps = [
        ":inference_calculator_cpu",
        ":inference_calculator_interface",
    ] + select({
        "//conditions:default": [":inference_calculator_gl_if_compute_shader_available"],
        ":platform_apple_with_gpu": [":inference_calculator_metal"],
    }),
    alwayslink = 1,
)

mediapipe_proto_library(
    name = "tensor_converter_calculator_proto",
    srcs = ["tensor_converter_calculator.proto"],
    deps = [
        "//mediapipe_custom/framework:calculator_options_proto",
        "//mediapipe_custom/framework:calculator_proto",
        "//mediapipe_custom/gpu:gpu_origin_proto",
    ],
)

cc_library(
    name = "tensor_converter_calculator",
    srcs = ["tensor_converter_calculator.cc"],
    copts = select({
        "//mediapipe_custom:apple": [
            "-x objective-c++",
            "-fobjc-arc",  # enable reference-counting
        ],
        "//conditions:default": [],
    }),
    features = ["-layering_check"],  # allow depending on tensor_converter_calculator_gpu_deps
    deps = [
        ":tensor_converter_calculator_cc_proto",
        ":tensor_converter_cpu",
        ":tensor_converter_gpu",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:memory_manager",
        "//mediapipe_custom/framework:memory_manager_service",
        "//mediapipe_custom/framework:port",
        "//mediapipe_custom/framework/formats:image_frame",
        "//mediapipe_custom/framework/formats:matrix",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/framework/port:statusor",
        "//mediapipe_custom/gpu:gpu_origin_cc_proto",
        "//mediapipe_custom/gpu:gpu_origin_utils",
        "//mediapipe_custom/util:resource_util",
        "@com_google_absl//absl/log",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/log:check",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
    ] + select({
        "//mediapipe_custom/gpu:disable_gpu": [],
        "//conditions:default": [
            ":tensor_converter_calculator_gpu_deps",
            "//mediapipe_custom/gpu:gl_base",
            "//mediapipe_custom/gpu:gl_calculator_helper",
            "//mediapipe_custom/gpu:gpu_buffer",
        ],
    }) + select({
        "//mediapipe_custom:apple": [
            ":tensor_converter_metal",
            "//third_party/apple_frameworks:MetalKit",
        ],
        "//conditions:default": [],
    }),
    alwayslink = 1,
)

cc_library(
    name = "tensor_converter_cpu",
    srcs = ["tensor_converter_cpu.cc"],
    hdrs = ["tensor_converter_cpu.h"],
    deps = [
        "//mediapipe_custom/framework:memory_manager",
        "//mediapipe_custom/framework/formats:image_frame",
        "//mediapipe_custom/framework/formats:matrix",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ],
)

cc_test(
    name = "tensor_converter_cpu_test",
    srcs = ["tensor_converter_cpu_test.cc"],
    deps = [
        ":tensor_converter_cpu",
        "//mediapipe_custom/framework:memory_manager",
        "//mediapipe_custom/framework/formats:matrix",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:status_matchers",
        "//mediapipe_custom/util:image_test_utils",
    ],
)

cc_library(
    name = "tensor_converter_gpu",
    hdrs = ["tensor_converter_gpu.h"],
    deps = [
        "//mediapipe_custom/framework:memory_manager",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/gpu:gpu_buffer",
        "@com_google_absl//absl/status",
    ],
)

cc_library(
    name = "tensor_converter_gl30",
    srcs = ["tensor_converter_gl30.cc"],
    hdrs = ["tensor_converter_gl30.h"],
    features = ["-layering_check"],  # allow depending on tensor_converter_calculator_gpu_deps
    deps = [
        ":tensor_converter_gpu",
        "//mediapipe_custom/framework:port",
        "//mediapipe_custom/framework/port:status",
    ] + select({
        "//mediapipe_custom:apple": [],
        "//conditions:default": [
            "//mediapipe_custom/framework:calculator_framework",
            "//mediapipe_custom/framework:memory_manager",
            "//mediapipe_custom/framework/formats:image_frame",
            "//mediapipe_custom/framework/formats:matrix",
            "//mediapipe_custom/framework/formats:tensor",
            "//mediapipe_custom/framework/port:ret_check",
            "//mediapipe_custom/gpu:gl_base_hdr",
            "//mediapipe_custom/gpu:gl_calculator_helper",
            "//mediapipe_custom/gpu:gl_simple_shaders",
            "//mediapipe_custom/gpu:gl_texture_view",
            "//mediapipe_custom/gpu:gpu_buffer",
            "//mediapipe_custom/gpu:gpu_buffer_format",
            "//mediapipe_custom/gpu:shader_util",
            "@com_google_absl//absl/log:absl_log",
            "@com_google_absl//absl/status",
            "@com_google_absl//absl/strings",
        ],
    }),
)

cc_library(
    name = "tensor_converter_metal",
    srcs = ["tensor_converter_metal.cc"],
    hdrs = ["tensor_converter_metal.h"],
    copts = select({
        "//mediapipe_custom:apple": [
            "-x objective-c++",
            "-fobjc-arc",  # enable reference-counting
        ],
        "//conditions:default": [],
    }),
    features = ["-layering_check"],  # allow depending on tensor_converter_calculator_gpu_deps
    linkopts = select({
        "//mediapipe_custom:apple": [
            "-framework CoreVideo",
            "-framework MetalKit",
        ],
        "//conditions:default": [],
    }),
    deps = [
        "//mediapipe_custom/framework:port",
    ] + select({
        "//mediapipe_custom:apple": [
            ":tensor_converter_calculator_gpu_deps",
            ":tensor_converter_gpu",
            "//mediapipe_custom/framework/formats:tensor",
            "//mediapipe_custom/framework/port:ret_check",
            "//mediapipe_custom/framework/port:status",
            "//third_party/apple_frameworks:MetalKit",
        ],
        "//conditions:default": [],
    }),
)

cc_library(
    name = "tensor_converter_gl31",
    srcs = ["tensor_converter_gl31.cc"],
    hdrs = ["tensor_converter_gl31.h"],
    features = ["-layering_check"],  # allow depending on tensor_converter_calculator_gpu_deps
    deps = [
        ":tensor_converter_gpu",
        "//mediapipe_custom/framework:port",
        "//mediapipe_custom/framework/port:status",
    ] + select({
        "//mediapipe_custom:apple": [],
        "//conditions:default": [
            "//mediapipe_custom/framework:calculator_context",
            "//mediapipe_custom/framework:memory_manager",
            "//mediapipe_custom/framework/formats:tensor",
            "//mediapipe_custom/framework/port:ret_check",
            "//mediapipe_custom/gpu:gl_calculator_helper",
            "//mediapipe_custom/gpu:gl_simple_shaders",
            "//mediapipe_custom/gpu:gpu_buffer",
            "//mediapipe_custom/gpu:shader_util",
            "@com_google_absl//absl/status",
            "@com_google_absl//absl/strings",
        ],
    }),
)

cc_library(
    name = "tensor_converter_calculator_gpu_deps",
    visibility = ["//visibility:private"],
    deps = select({
        "//mediapipe_custom:android": [
            ":tensor_converter_gl30",
            ":tensor_converter_gl31",
            "//mediapipe_custom/gpu:gl_calculator_helper",
            "//mediapipe_custom/gpu:gpu_buffer",
        ],
        ":platform_apple_with_gpu": [
            "//mediapipe_custom/gpu:MPPMetalHelper",
            "//mediapipe_custom/gpu:MPPMetalUtil",
            "//mediapipe_custom/objc:mediapipe_framework_ios",
        ],
        # This setting is needed to allow bazel to build all targets on Mac with GPU disabled
        ":platform_apple_without_gpu": [],
        "//conditions:default": [
            ":tensor_converter_gl30",
            ":tensor_converter_gl31",
            "//mediapipe_custom/gpu:gl_calculator_helper",
            "//mediapipe_custom/gpu:gl_simple_shaders",
            "//mediapipe_custom/gpu:gpu_buffer",
            "//mediapipe_custom/gpu:shader_util",
        ],
    }),
)

cc_test(
    name = "tensor_converter_calculator_test",
    srcs = ["tensor_converter_calculator_test.cc"],
    tags = [
        "noasan",  # TODO: Remove noasan tag when SwiftShader supports sanitizers
    ],
    deps = [
        ":tensor_converter_calculator",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:calculator_runner",
        "//mediapipe_custom/framework:memory_manager",
        "//mediapipe_custom/framework:memory_manager_service",
        "//mediapipe_custom/framework/formats:image_format_cc_proto",
        "//mediapipe_custom/framework/formats:image_frame",
        "//mediapipe_custom/framework/formats:image_frame_opencv",
        "//mediapipe_custom/framework/formats:matrix",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:opencv_core",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "//mediapipe_custom/framework/tool:validate_type",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
    ],
)

mediapipe_proto_library(
    name = "tensors_to_detections_calculator_proto",
    srcs = ["tensors_to_detections_calculator.proto"],
    deps = [
        "//mediapipe_custom/framework:calculator_options_proto",
        "//mediapipe_custom/framework:calculator_proto",
    ],
)

cc_library(
    name = "tensors_to_detections_calculator",
    srcs = ["tensors_to_detections_calculator.cc"],
    copts = select({
        "//mediapipe_custom:apple": [
            "-x objective-c++",
            "-fobjc-arc",  # enable reference-counting
        ],
        "//conditions:default": [],
    }),
    features = ["-layering_check"],  # allow depending on tensors_to_detections_calculator_gpu_deps
    deps = [
        ":tensors_to_detections_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:port",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/deps:file_path",
        "//mediapipe_custom/framework/formats:detection_cc_proto",
        "//mediapipe_custom/framework/formats:location",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/formats/object_detection:anchor_cc_proto",
        "//mediapipe_custom/framework/port:ret_check",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/types:span",
    ] + selects.with_or({
        ":compute_shader_unavailable": [],
        "//conditions:default": [":tensors_to_detections_calculator_gpu_deps"],
    }) + select({
        "//mediapipe_custom:apple": [
            "//third_party/apple_frameworks:CoreVideo",
            "//third_party/apple_frameworks:MetalKit",
        ],
        "//conditions:default": [],
    }),
    alwayslink = 1,
)

cc_library(
    name = "tensors_to_detections_calculator_gpu_deps",
    visibility = ["//visibility:private"],
    deps = select({
        ":platform_apple_with_gpu": [
            "//mediapipe_custom/gpu:MPPMetalHelper",
            "//mediapipe_custom/gpu:MPPMetalUtil",
        ],
        # This setting is needed to allow bazel to build all targets on Mac with GPU disabled
        ":platform_apple_without_gpu": [],
        "//conditions:default": [
            "//mediapipe_custom/gpu:gl_calculator_helper",
        ],
    }),
)

mediapipe_proto_library(
    name = "tensors_to_landmarks_calculator_proto",
    srcs = ["tensors_to_landmarks_calculator.proto"],
    deps = [
        "//mediapipe_custom/framework:calculator_options_proto",
        "//mediapipe_custom/framework:calculator_proto",
    ],
)

cc_library(
    name = "tensors_to_landmarks_calculator",
    srcs = ["tensors_to_landmarks_calculator.cc"],
    copts = select({
        "//mediapipe_custom:apple": [
            "-x objective-c++",
            "-fobjc-arc",  # enable reference-counting
        ],
        "//conditions:default": [],
    }),
    deps = [
        ":tensors_to_landmarks_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/formats:landmark_cc_proto",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "@com_google_absl//absl/log:absl_check",
    ],
    alwayslink = 1,
)

mediapipe_proto_library(
    name = "landmarks_to_tensor_calculator_proto",
    srcs = ["landmarks_to_tensor_calculator.proto"],
    deps = [
        "//mediapipe_custom/framework:calculator_options_proto",
        "//mediapipe_custom/framework:calculator_proto",
    ],
)

cc_library(
    name = "landmarks_to_tensor_calculator",
    srcs = ["landmarks_to_tensor_calculator.cc"],
    hdrs = ["landmarks_to_tensor_calculator.h"],
    copts = select({
        "//mediapipe_custom:apple": [
            "-x objective-c++",
            "-fobjc-arc",  # enable reference-counting
        ],
        "//conditions:default": [],
    }),
    deps = [
        ":landmarks_to_tensor_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:memory_manager",
        "//mediapipe_custom/framework:memory_manager_service",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/formats:landmark_cc_proto",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
    ],
    alwayslink = 1,
)

cc_test(
    name = "landmarks_to_tensor_calculator_test",
    srcs = ["landmarks_to_tensor_calculator_test.cc"],
    deps = [
        ":landmarks_to_tensor_calculator",
        ":landmarks_to_tensor_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:calculator_runner",
        "//mediapipe_custom/framework/formats:landmark_cc_proto",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "@com_google_absl//absl/memory",
        "@com_google_googletest//:gtest_main",
    ],
)

mediapipe_proto_library(
    name = "tensors_to_floats_calculator_proto",
    srcs = ["tensors_to_floats_calculator.proto"],
    deps = [
        "//mediapipe_custom/framework:calculator_options_proto",
        "//mediapipe_custom/framework:calculator_proto",
    ],
)

cc_library(
    name = "tensors_to_floats_calculator",
    srcs = ["tensors_to_floats_calculator.cc"],
    copts = select({
        "//mediapipe_custom:apple": [
            "-x objective-c++",
            "-fobjc-arc",  # enable reference-counting
        ],
        "//conditions:default": [],
    }),
    deps = [
        ":tensors_to_floats_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
    ],
    alwayslink = 1,
)

cc_test(
    name = "tensors_to_floats_calculator_test",
    srcs = ["tensors_to_floats_calculator_test.cc"],
    deps = [
        ":tensors_to_floats_calculator",
        ":tensors_to_floats_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:calculator_runner",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "@com_google_absl//absl/memory",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "tensors_to_classification_calculator",
    srcs = ["tensors_to_classification_calculator.cc"],
    copts = select({
        "//mediapipe_custom:apple": [
            "-x objective-c++",
            "-fobjc-arc",  # enable reference-counting
        ],
        "//conditions:default": [],
    }),
    deps = [
        ":tensors_to_classification_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:resources",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:classification_cc_proto",
        "//mediapipe_custom/framework/formats:location",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/util:label_map_cc_proto",
        "//mediapipe_custom/util:label_map_util",
        "//mediapipe_custom/util:resource_util",
        "@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/container:node_hash_map",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/strings:string_view",
        "@com_google_absl//absl/types:span",
    ] + select({
        "//mediapipe_custom:android": [
            "//mediapipe_custom/util/android/file/base",
        ],
        "//mediapipe_custom:ios": [
            "//mediapipe_custom/util/android/file/base",
        ],
        "//mediapipe_custom:emscripten": [
            "//mediapipe_custom/util/android/file/base",
        ],
        "//conditions:default": [
            "//mediapipe_custom/framework/port:file_helpers",
        ],
    }),
    alwayslink = 1,
)

mediapipe_proto_library(
    name = "tensors_to_classification_calculator_proto",
    srcs = ["tensors_to_classification_calculator.proto"],
    deps = [
        "//mediapipe_custom/framework:calculator_options_proto",
        "//mediapipe_custom/framework:calculator_proto",
        "//mediapipe_custom/util:label_map_proto",
    ],
)

cc_test(
    name = "tensors_to_classification_calculator_test",
    srcs = ["tensors_to_classification_calculator_test.cc"],
    data = ["testdata/labelmap.txt"],
    deps = [
        ":tensors_to_classification_calculator",
        ":tensors_to_classification_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:calculator_runner",
        "//mediapipe_custom/framework/formats:classification_cc_proto",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "@com_google_absl//absl/memory",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "tensor_to_joints_calculator",
    srcs = ["tensor_to_joints_calculator.cc"],
    hdrs = ["tensor_to_joints_calculator.h"],
    deps = [
        ":tensor_to_joints_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/formats:body_rig_cc_proto",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
    ],
    alwayslink = 1,
)

mediapipe_proto_library(
    name = "tensor_to_joints_calculator_proto",
    srcs = ["tensor_to_joints_calculator.proto"],
    deps = [
        "//mediapipe_custom/framework:calculator_options_proto",
        "//mediapipe_custom/framework:calculator_proto",
    ],
)

cc_test(
    name = "tensor_to_joints_calculator_test",
    srcs = ["tensor_to_joints_calculator_test.cc"],
    deps = [
        ":tensor_to_joints_calculator",
        ":tensor_to_joints_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:calculator_runner",
        "//mediapipe_custom/framework:timestamp",
        "//mediapipe_custom/framework/formats:body_rig_cc_proto",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "image_to_tensor_calculator",
    srcs = ["image_to_tensor_calculator.cc"],
    copts = select({
        "//mediapipe_custom:apple": [
            "-x objective-c++",
            "-fobjc-arc",  # enable reference-counting
        ],
        "//conditions:default": [],
    }),
    features = ["-layering_check"],  # allow depending on image_to_tensor_calculator_gpu_deps
    deps = [
        ":image_to_tensor_calculator_cc_proto",
        ":image_to_tensor_converter",
        ":image_to_tensor_utils",
        ":loose_headers",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:memory_manager_service",
        "//mediapipe_custom/framework:port",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:image_frame",
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/framework/port:statusor",
        "//mediapipe_custom/gpu:gpu_origin_cc_proto",
        "//mediapipe_custom/gpu:gpu_origin_utils",
        "//mediapipe_custom/gpu/webgpu:webgpu_check",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/log:absl_log",
    ] + select({
        "//mediapipe_custom/gpu:disable_gpu": [],
        "//conditions:default": [":image_to_tensor_calculator_gpu_deps"],
    }) + select({
        "//mediapipe_custom/framework/port:disable_opencv": [],
        "//conditions:default": [":image_to_tensor_converter_opencv"],
    }) + select({
        "//mediapipe_custom/framework/port:enable_halide": [
            ":image_to_tensor_converter_frame_buffer",
        ],
        "//conditions:default": [],
    }),
    alwayslink = 1,
)

cc_library(
    name = "image_to_tensor_calculator_gpu_deps",
    visibility = ["//visibility:private"],
    deps = selects.with_or({
        "//mediapipe_custom:android": [
            ":image_to_tensor_converter_gl_buffer",
            "//mediapipe_custom/gpu:gl_calculator_helper",
            "//mediapipe_custom/gpu:gpu_buffer",
            "//mediapipe_custom/gpu:gpu_service",
        ],
        "//mediapipe_custom:emscripten": [
            ":image_to_tensor_converter_gl_texture",
            "//mediapipe_custom/gpu:gl_calculator_helper",
            "//mediapipe_custom/gpu:gpu_buffer",
            "//mediapipe_custom/gpu:gpu_service",
        ],
        "//mediapipe_custom:apple": [
            ":image_to_tensor_converter_metal",
            "//mediapipe_custom/gpu:gl_calculator_helper",
            "//mediapipe_custom/gpu:MPPMetalHelper",
            "//mediapipe_custom/gpu:gpu_buffer",
            "//mediapipe_custom/gpu:gpu_service",
        ],
        "//conditions:default": [
            ":image_to_tensor_converter_gl_buffer",
            "//mediapipe_custom/gpu:gl_calculator_helper",
            "//mediapipe_custom/gpu:gpu_buffer",
            "//mediapipe_custom/gpu:gpu_service",
        ],
    }) + select({
        "//mediapipe_custom/gpu/webgpu:use_webgpu": [
            "//mediapipe_custom/gpu/webgpu:image_to_tensor_converter_webgpu_texture",
            "//mediapipe_custom/gpu/webgpu:webgpu_texture_buffer",
        ],
        "//conditions:default": [],
    }),
)

mediapipe_proto_library(
    name = "image_to_tensor_calculator_proto",
    srcs = ["image_to_tensor_calculator.proto"],
    deps = [
        "//mediapipe_custom/framework:calculator_options_proto",
        "//mediapipe_custom/framework:calculator_proto",
        "//mediapipe_custom/gpu:gpu_origin_proto",
    ],
)

cc_test(
    name = "image_to_tensor_calculator_test",
    srcs = ["image_to_tensor_calculator_test.cc"],
    data = [
        "testdata/image_to_tensor/input.jpg",
        "testdata/image_to_tensor/large_sub_rect.png",
        "testdata/image_to_tensor/large_sub_rect_border_zero.png",
        "testdata/image_to_tensor/large_sub_rect_keep_aspect.png",
        "testdata/image_to_tensor/large_sub_rect_keep_aspect_border_zero.png",
        "testdata/image_to_tensor/large_sub_rect_keep_aspect_with_rotation.png",
        "testdata/image_to_tensor/large_sub_rect_keep_aspect_with_rotation_border_zero.png",
        "testdata/image_to_tensor/medium_sub_rect_keep_aspect.png",
        "testdata/image_to_tensor/medium_sub_rect_keep_aspect_border_zero.png",
        "testdata/image_to_tensor/medium_sub_rect_keep_aspect_with_rotation.png",
        "testdata/image_to_tensor/medium_sub_rect_keep_aspect_with_rotation_border_zero.png",
        "testdata/image_to_tensor/medium_sub_rect_with_rotation.png",
        "testdata/image_to_tensor/medium_sub_rect_with_rotation_border_zero.png",
        "testdata/image_to_tensor/noop_except_range.png",
    ],
    tags = ["not_run:arm"],
    deps = [
        ":image_to_tensor_calculator",
        ":image_to_tensor_converter",
        ":image_to_tensor_utils",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:calculator_runner",
        "//mediapipe_custom/framework/deps:file_path",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:image_format_cc_proto",
        "//mediapipe_custom/framework/formats:image_frame",
        "//mediapipe_custom/framework/formats:image_frame_opencv",
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:integral_types",
        "//mediapipe_custom/framework/port:opencv_core",
        "//mediapipe_custom/framework/port:opencv_imgcodecs",
        "//mediapipe_custom/framework/port:opencv_imgproc",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "//mediapipe_custom/util:image_test_utils",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/types:optional",
    ] + select({
        "//mediapipe_custom:apple": [],
        "//conditions:default": ["//mediapipe_custom/gpu:gl_context"],
    }),
)

cc_library(
    name = "image_to_tensor_converter",
    hdrs = ["image_to_tensor_converter.h"],
    copts = select({
        "//mediapipe_custom:apple": [
            "-x objective-c++",
            "-fobjc-arc",  # enable reference-counting
        ],
        "//conditions:default": [],
    }),
    deps = [
        ":image_to_tensor_utils",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:statusor",
    ],
)

cc_library(
    name = "image_to_tensor_converter_opencv",
    srcs = ["image_to_tensor_converter_opencv.cc"],
    hdrs = ["image_to_tensor_converter_opencv.h"],
    copts = select({
        "//mediapipe_custom:apple": [
            "-x objective-c++",
            "-fobjc-arc",  # enable reference-counting
        ],
        "//conditions:default": [],
    }),
    deps = [
        ":image_to_tensor_converter",
        ":image_to_tensor_utils",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:image_format_cc_proto",
        "//mediapipe_custom/framework/formats:image_opencv",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:opencv_core",
        "//mediapipe_custom/framework/port:opencv_imgproc",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/framework/port:statusor",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "image_to_tensor_converter_frame_buffer",
    srcs = ["image_to_tensor_converter_frame_buffer.cc"],
    hdrs = ["image_to_tensor_converter_frame_buffer.h"],
    deps = [
        ":image_to_tensor_converter",
        ":image_to_tensor_utils",
        "//mediapipe_custom/framework:calculator_context",
        "//mediapipe_custom/framework/formats:frame_buffer",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/gpu:frame_buffer_view",
        "//mediapipe_custom/util/frame_buffer:frame_buffer_util",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings:str_format",
    ],
)

cc_library(
    name = "image_to_tensor_converter_gl_buffer",
    srcs = ["image_to_tensor_converter_gl_buffer.cc"],
    hdrs = ["image_to_tensor_converter_gl_buffer.h"],
    visibility = ["//visibility:private"],
    deps = ["//mediapipe_custom/framework:port"] + selects.with_or({
        "//mediapipe_custom:emscripten": [],
        "//mediapipe_custom:apple": [],
        "//conditions:default": [
            ":image_to_tensor_converter",
            ":image_to_tensor_converter_gl_utils",
            ":image_to_tensor_utils",
            "@com_google_absl//absl/strings",
            "//mediapipe_custom/framework:calculator_framework",
            "//mediapipe_custom/framework/formats:rect_cc_proto",
            "//mediapipe_custom/framework/formats:tensor",
            "//mediapipe_custom/framework/port:ret_check",
            "//mediapipe_custom/framework/port:status",
            "//mediapipe_custom/framework/port:statusor",
            "//mediapipe_custom/gpu:gl_calculator_helper",
            "//mediapipe_custom/framework/formats:image",
            "//mediapipe_custom/gpu:gpu_buffer_format",
            "@org_tensorflow//tensorflow/lite/delegates/gpu/common:shape",
            "@org_tensorflow//tensorflow/lite/delegates/gpu/common:types",
            "@org_tensorflow//tensorflow/lite/delegates/gpu/gl:command_queue",
            "@org_tensorflow//tensorflow/lite/delegates/gpu/gl:gl_buffer",
            "@org_tensorflow//tensorflow/lite/delegates/gpu/gl:gl_call",
            "@org_tensorflow//tensorflow/lite/delegates/gpu/gl:gl_texture",
            "@org_tensorflow//tensorflow/lite/delegates/gpu/gl:request_gpu_info",
            "@org_tensorflow//tensorflow/lite/delegates/gpu/gl:variable",
            "@org_tensorflow//tensorflow/lite/delegates/gpu/gl/converters:util",
        ],
    }),
)

cc_library(
    name = "image_to_tensor_converter_gl_texture",
    srcs = ["image_to_tensor_converter_gl_texture.cc"],
    hdrs = ["image_to_tensor_converter_gl_texture.h"],
    visibility = ["//visibility:private"],
    deps = ["//mediapipe_custom/framework:port"] + select({
        "//mediapipe_custom/gpu:disable_gpu": [],
        "//conditions:default": [
            ":image_to_tensor_converter",
            ":image_to_tensor_converter_gl_utils",
            ":image_to_tensor_utils",
            "//mediapipe_custom/framework:calculator_framework",
            "//mediapipe_custom/framework/formats:image",
            "//mediapipe_custom/framework/formats:tensor",
            "//mediapipe_custom/framework/port:ret_check",
            "//mediapipe_custom/framework/port:status",
            "//mediapipe_custom/framework/port:statusor",
            "//mediapipe_custom/gpu:gl_calculator_helper",
            "//mediapipe_custom/gpu:gl_simple_shaders",
            "//mediapipe_custom/gpu:shader_util",
            "@com_google_absl//absl/log:absl_log",
            "@com_google_absl//absl/strings",
        ],
    }),
)

cc_library(
    name = "image_to_tensor_converter_gl_utils",
    srcs = ["image_to_tensor_converter_gl_utils.cc"],
    hdrs = ["image_to_tensor_converter_gl_utils.h"],
    visibility = ["//visibility:private"],
    deps = ["//mediapipe_custom/framework:port"] + select({
        "//mediapipe_custom/gpu:disable_gpu": [],
        "//conditions:default": [
            "//mediapipe_custom/framework/port:status",
            "//mediapipe_custom/framework/port:statusor",
            "//mediapipe_custom/gpu:gl_base",
            "//mediapipe_custom/gpu:gl_context",
        ],
    }),
)

cc_library(
    name = "image_to_tensor_converter_metal",
    srcs = ["image_to_tensor_converter_metal.cc"],
    hdrs = ["image_to_tensor_converter_metal.h"],
    copts = select({
        "//mediapipe_custom:apple": [
            "-x objective-c++",
            "-fobjc-arc",  # enable reference-counting
        ],
        "//conditions:default": [],
    }),
    linkopts = select({
        "//mediapipe_custom:apple": [
            "-framework CoreVideo",
            "-framework MetalKit",
        ],
        "//conditions:default": [],
    }),
    visibility = ["//visibility:private"],
    deps = ["//mediapipe_custom/framework:port"] + select({
        "//mediapipe_custom:apple": [
            ":image_to_tensor_converter",
            ":image_to_tensor_utils",
            "//mediapipe_custom/framework:calculator_framework",
            "//mediapipe_custom/framework/formats:image",
            "//mediapipe_custom/framework/formats:tensor",
            "//mediapipe_custom/framework/port:ret_check",
            "//mediapipe_custom/framework/port:status",
            "//mediapipe_custom/framework/port:statusor",
            "//mediapipe_custom/gpu:MPPMetalHelper",
            "//mediapipe_custom/gpu:gpu_buffer_format",
            "@com_google_absl//absl/strings",
            "@org_tensorflow//tensorflow/lite/delegates/gpu/common:shape",
            "@org_tensorflow//tensorflow/lite/delegates/gpu/common:types",
        ],
        "//conditions:default": [],
    }),
)

cc_library(
    name = "image_to_tensor_utils",
    srcs = ["image_to_tensor_utils.cc"],
    hdrs = ["image_to_tensor_utils.h"],
    copts = select({
        "//mediapipe_custom:apple": [
            "-x objective-c++",
            "-fobjc-arc",  # enable reference-counting
        ],
        "//conditions:default": [],
    }),
    deps = [
        ":image_to_tensor_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:packet",
        "//mediapipe_custom/framework/api2:packet",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:image_frame",
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/framework/port:statusor",
        "//mediapipe_custom/gpu:gpu_origin_cc_proto",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/types:optional",
    ] + select({
        "//mediapipe_custom/gpu:disable_gpu": [],
        "//conditions:default": ["//mediapipe_custom/gpu:gpu_buffer"],
    }),
)

cc_test(
    name = "image_to_tensor_utils_test",
    srcs = ["image_to_tensor_utils_test.cc"],
    deps = [
        ":image_to_tensor_calculator_cc_proto",
        ":image_to_tensor_utils",
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "//mediapipe_custom/framework/port:status",
    ],
)

# Copied from /mediapipe/calculators/tflite/BUILD
selects.config_setting_group(
    name = "gpu_inference_disabled",
    match_any = [
        "//mediapipe_custom/gpu:disable_gpu",
    ],
)

mediapipe_proto_library(
    name = "tensors_to_segmentation_calculator_proto",
    srcs = ["tensors_to_segmentation_calculator.proto"],
    deps = [
        "//mediapipe_custom/framework:calculator_options_proto",
        "//mediapipe_custom/framework:calculator_proto",
        "//mediapipe_custom/gpu:gpu_origin_proto",
    ],
)

cc_library(
    name = "tensors_to_segmentation_calculator",
    srcs = ["tensors_to_segmentation_calculator.cc"],
    copts = select({
        "//mediapipe_custom:apple": [
            "-x objective-c++",
            "-fobjc-arc",  # enable reference-counting
        ],
        "//conditions:default": [],
    }),
    features = ["-layering_check"],  # allow depending on tensors_to_segmentation_calculator_gpu_deps
    deps = [
        ":tensors_to_segmentation_calculator_cc_proto",
        ":tensors_to_segmentation_converter",
        ":tensors_to_segmentation_utils",
        "//mediapipe_custom/framework:calculator_context",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:port",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/util:resource_util",
        "@com_google_absl//absl/status",
        "@org_tensorflow//tensorflow/lite:framework",
    ] + select({
        "//mediapipe_custom/gpu:disable_gpu": [],
        "//conditions:default": [":tensors_to_segmentation_calculator_gpu_deps"],
    }) + select({
        "//mediapipe_custom/framework/port:disable_opencv": [],
        "//conditions:default": [
            ":tensors_to_segmentation_converter_opencv",
        ],
    }),
    alwayslink = 1,
)

cc_library(
    name = "tensors_to_segmentation_calculator_gpu_deps",
    visibility = ["//visibility:private"],
    deps = selects.with_or({
        "//mediapipe_custom:android": [
            ":tensors_to_segmentation_converter_gl_buffer",
            "//mediapipe_custom/gpu:gl_calculator_helper",
        ],
        "//mediapipe_custom:emscripten": [
            ":tensors_to_segmentation_converter_gl_texture",
            "//mediapipe_custom/gpu:gl_calculator_helper",
        ],
        ":platform_apple_with_gpu": [
            ":tensors_to_segmentation_converter_metal",
            "//mediapipe_custom/gpu:MPPMetalHelper",
            "//mediapipe_custom/gpu:gl_calculator_helper",
        ],
        # This setting is needed to allow bazel to build all targets on Mac with GPU disabled
        ":platform_apple_without_gpu": [],
        "//conditions:default": [
            ":tensors_to_segmentation_converter_gl_buffer",
            "//mediapipe_custom/gpu:gl_calculator_helper",
        ],
    }),
)

cc_library(
    name = "tensors_to_segmentation_utils",
    srcs = ["tensors_to_segmentation_utils.cc"],
    hdrs = ["tensors_to_segmentation_utils.h"],
    deps = [
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:port",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/gpu:gpu_origin_cc_proto",
        "@com_google_absl//absl/status:statusor",
    ] + selects.with_or({
        "//mediapipe_custom/gpu:disable_gpu": [],
        "//conditions:default": [
            "//mediapipe_custom/gpu:gl_base_hdr",
        ],
    }),
)

cc_test(
    name = "tensors_to_segmentation_utils_test",
    srcs = ["tensors_to_segmentation_utils_test.cc"],
    deps = [
        ":tensors_to_segmentation_utils",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:status_matchers",
        "@com_google_absl//absl/status:statusor",
    ],
)

cc_library(
    name = "tensors_to_segmentation_converter",
    hdrs = ["tensors_to_segmentation_converter.h"],
    visibility = ["//visibility:private"],
    deps = [
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:tensor",
        "@com_google_absl//absl/status:statusor",
    ],
)

cc_library(
    name = "tensors_to_segmentation_converter_opencv",
    srcs = ["tensors_to_segmentation_converter_opencv.cc"],
    hdrs = ["tensors_to_segmentation_converter_opencv.h"],
    visibility = ["//visibility:private"],
    deps = [
        ":tensors_to_segmentation_calculator_cc_proto",
        ":tensors_to_segmentation_converter",
        ":tensors_to_segmentation_utils",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:image_frame",
        "//mediapipe_custom/framework/formats:image_opencv",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:opencv_core",
        "//mediapipe_custom/framework/port:opencv_imgproc",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ],
)

cc_library(
    name = "tensors_to_segmentation_converter_gl_texture",
    srcs = ["tensors_to_segmentation_converter_gl_texture.cc"],
    hdrs = ["tensors_to_segmentation_converter_gl_texture.h"],
    visibility = ["//visibility:private"],
    deps = [
        "//mediapipe_custom/framework:port",
    ] + select({
        "//mediapipe_custom/gpu:disable_gpu": [],
        "//conditions:default": [
            ":tensors_to_segmentation_calculator_cc_proto",
            ":tensors_to_segmentation_converter",
            ":tensors_to_segmentation_utils",
            "//mediapipe_custom/framework:calculator_context",
            "//mediapipe_custom/framework:calculator_framework",
            "//mediapipe_custom/framework/formats:image",
            "//mediapipe_custom/framework/formats:tensor",
            "//mediapipe_custom/framework/port:ret_check",
            "//mediapipe_custom/framework/port:status",
            "//mediapipe_custom/gpu:gl_base_hdr",
            "//mediapipe_custom/gpu:gl_calculator_helper",
            "//mediapipe_custom/gpu:gl_simple_shaders",
            "//mediapipe_custom/gpu:gpu_buffer",
            "//mediapipe_custom/gpu:gpu_buffer_format",
            "//mediapipe_custom/gpu:gpu_origin_cc_proto",
            "//mediapipe_custom/gpu:gpu_origin_utils",
            "//mediapipe_custom/gpu:shader_util",
            "@com_google_absl//absl/status",
            "@com_google_absl//absl/status:statusor",
            "@com_google_absl//absl/strings",
            "@com_google_absl//absl/strings:str_format",
        ],
    }),
)

cc_library(
    name = "tensors_to_segmentation_converter_gl_buffer",
    srcs = ["tensors_to_segmentation_converter_gl_buffer.cc"],
    hdrs = ["tensors_to_segmentation_converter_gl_buffer.h"],
    visibility = ["//visibility:private"],
    deps = ["//mediapipe_custom/framework:port"] + selects.with_or({
        "//mediapipe_custom:emscripten": [],
        "//mediapipe_custom:apple": [],
        "//conditions:default": [
            ":tensors_to_segmentation_calculator_cc_proto",
            ":tensors_to_segmentation_converter",
            ":tensors_to_segmentation_utils",
            "@com_google_absl//absl/memory",
            "@com_google_absl//absl/status",
            "@com_google_absl//absl/status:statusor",
            "@com_google_absl//absl/strings",
            "@com_google_absl//absl/strings:str_format",
            "//mediapipe_custom/framework:calculator_context",
            "//mediapipe_custom/framework:calculator_framework",
            "//mediapipe_custom/framework/formats:image",
            "//mediapipe_custom/framework/formats:tensor",
            "//mediapipe_custom/framework/port:ret_check",
            "//mediapipe_custom/framework/port:status",
            "//mediapipe_custom/gpu:gpu_origin_cc_proto",
            "//mediapipe_custom/gpu:gpu_origin_utils",
            "//mediapipe_custom/gpu:gl_base_hdr",
            "//mediapipe_custom/gpu:gl_calculator_helper",
            "//mediapipe_custom/gpu:gl_simple_shaders",
            "//mediapipe_custom/gpu:gpu_buffer",
            "//mediapipe_custom/gpu:gpu_buffer_format",
            "//mediapipe_custom/gpu:shader_util",
            "@org_tensorflow//tensorflow/lite/delegates/gpu/gl:gl_program",
            "@org_tensorflow//tensorflow/lite/delegates/gpu/gl:gl_shader",
            "@org_tensorflow//tensorflow/lite/delegates/gpu/gl:gl_texture",
            "@org_tensorflow//tensorflow/lite/delegates/gpu/gl/converters:util",
            "@org_tensorflow//tensorflow/lite/delegates/gpu/common:data_type",
            "@org_tensorflow//tensorflow/lite/delegates/gpu/common:types",
        ],
    }),
)

cc_library(
    name = "tensors_to_segmentation_converter_metal",
    srcs = ["tensors_to_segmentation_converter_metal.cc"],
    hdrs = ["tensors_to_segmentation_converter_metal.h"],
    copts = select({
        "//mediapipe_custom:apple": [
            "-x objective-c++",
            "-fobjc-arc",  # enable reference-counting
        ],
        "//conditions:default": [],
    }),
    visibility = ["//visibility:private"],
    deps = [
        "//mediapipe_custom/framework:port",
    ] + selects.with_or({
        ":gpu_inference_disabled": [],
        ":platform_apple_with_gpu": [
            ":tensors_to_segmentation_calculator_cc_proto",
            ":tensors_to_segmentation_converter",
            ":tensors_to_segmentation_utils",
            "//mediapipe_custom/gpu:MPPMetalUtil",
            "//mediapipe_custom/gpu:MPPMetalHelper",
            "//third_party/apple_frameworks:MetalKit",
            "@com_google_absl//absl/status",
            "@com_google_absl//absl/status:statusor",
            "//mediapipe_custom/framework:calculator_context",
            "//mediapipe_custom/framework:calculator_framework",
            "//mediapipe_custom/framework/formats:image",
            "//mediapipe_custom/framework/formats:tensor",
            "//mediapipe_custom/framework/port:ret_check",
            "//mediapipe_custom/framework/port:status",
            "//mediapipe_custom/gpu:gl_calculator_helper",
            "//mediapipe_custom/gpu:gl_simple_shaders",
            "//mediapipe_custom/gpu:gpu_origin_cc_proto",
            "//mediapipe_custom/gpu:gpu_origin_utils",
            "//mediapipe_custom/gpu:shader_util",
            "//mediapipe_custom/util:resource_util",
            "@org_tensorflow//tensorflow/lite:framework",
        ],
        "//conditions:default": [],
    }),
)

cc_test(
    name = "tensors_to_segmentation_calculator_test",
    srcs = ["tensors_to_segmentation_calculator_test.cc"],
    deps = [
        ":tensors_to_segmentation_calculator",
        ":tensors_to_segmentation_calculator_cc_proto",
        ":tensors_to_segmentation_calculator_test_utils",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:calculator_runner",
        "//mediapipe_custom/framework:packet",
        "//mediapipe_custom/framework:timestamp",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:image_format_cc_proto",
        "//mediapipe_custom/framework/formats:image_opencv",
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
    ],
)

cc_library(
    name = "tensors_to_segmentation_calculator_test_utils",
    testonly = True,
    srcs = ["tensors_to_segmentation_calculator_test_utils.cc"],
    hdrs = ["tensors_to_segmentation_calculator_test_utils.h"],
    deps = [
        ":tensors_to_segmentation_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:packet",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
    ],
)

cc_test(
    name = "tensors_to_segmentation_calculator_test_utils_test",
    srcs = ["tensors_to_segmentation_calculator_test_utils_test.cc"],
    deps = [
        ":tensors_to_segmentation_calculator_cc_proto",
        ":tensors_to_segmentation_calculator_test_utils",
        "//mediapipe_custom/framework/port:gtest_main",
    ],
)

cc_library(
    name = "tensors_dequantization_calculator",
    srcs = ["tensors_dequantization_calculator.cc"],
    copts = select({
        "//mediapipe_custom:apple": [
            "-x objective-c++",
            "-fobjc-arc",  # enable reference-counting
        ],
        "//conditions:default": [],
    }),
    deps = [
        "//mediapipe_custom/framework:calculator_context",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:memory_manager",
        "//mediapipe_custom/framework:memory_manager_service",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
    ],
    alwayslink = 1,
)

# For a more maintainable build this target should not exist and the headers
# should  be split into the existing cc_library targets, but this change was
# automatically  done so that we can remove long standing issues and complexity
# in the build system. It's up to the OWNERS of this package to get rid of it or
# not. The use of the textual_hdrs attribute is discouraged, use hdrs instead.
# Here it is used to avoid header parsing errors in packages where the feature
# parse_headers was enabled since loose headers were not being parsed.
cc_library(
    name = "loose_headers",
    tags = ["avoid_dep"],
    textual_hdrs = [
        "image_to_tensor_converter_gl_buffer.h",
        "image_to_tensor_converter_gl_texture.h",
    ],
    visibility = ["//visibility:private"],
)

cc_test(
    name = "tensors_dequantization_calculator_test",
    srcs = ["tensors_dequantization_calculator_test.cc"],
    deps = [
        ":tensors_dequantization_calculator",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:calculator_runner",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "@com_google_absl//absl/status",
    ],
)

cc_library(
    name = "vector_to_tensor_calculator",
    srcs = ["vector_to_tensor_calculator.cc"],
    deps = [
        ":vector_to_tensor_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:memory_manager",
        "//mediapipe_custom/framework:memory_manager_service",
        "//mediapipe_custom/framework/api2:node",
        "//mediapipe_custom/framework/api2:packet",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "@com_google_absl//absl/log",
        "@com_google_absl//absl/log:check",
        "@com_google_absl//absl/status",
    ],
    alwayslink = 1,
)

mediapipe_proto_library(
    name = "vector_to_tensor_calculator_proto",
    srcs = ["vector_to_tensor_calculator.proto"],
)

cc_test(
    name = "vector_to_tensor_calculator_test",
    srcs = ["vector_to_tensor_calculator_test.cc"],
    deps = [
        ":vector_to_tensor_calculator",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:calculator_runner",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "//mediapipe_custom/framework/port:status",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
    ],
)
