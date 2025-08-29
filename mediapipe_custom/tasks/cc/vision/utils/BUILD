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

cc_library_with_tflite(
    name = "image_tensor_specs",
    srcs = ["image_tensor_specs.cc"],
    hdrs = ["image_tensor_specs.h"],
    tflite_deps = [
        "//mediapipe_custom/tasks/cc/core:model_resources",
    ],
    deps = [
        "//mediapipe_custom/framework/port:integral_types",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/metadata:metadata_extractor",
        "//mediapipe_custom/tasks/metadata:metadata_schema_cc",
        "@com_google_absl//absl/algorithm:container",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/types:optional",
        "@flatbuffers//:runtime_cc",
        "@org_tensorflow//tensorflow/lite/c:common",
        "@org_tensorflow//tensorflow/lite/schema:schema_fbs",
    ],
)

cc_test_with_tflite(
    name = "image_tensor_specs_test",
    srcs = ["image_tensor_specs_test.cc"],
    data = ["//mediapipe_custom/tasks/testdata/vision:test_models"],
    tflite_deps = [
        ":image_tensor_specs",
        "//mediapipe_custom/tasks/cc/core:model_resources",
        "@org_tensorflow//tensorflow/lite:test_util",
    ],
    deps = [
        "//mediapipe_custom/framework/deps:file_path",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/core/proto:external_file_cc_proto",
        "//mediapipe_custom/tasks/cc/metadata:metadata_extractor",
        "//mediapipe_custom/tasks/metadata:metadata_schema_cc",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:cord",
        "@com_google_absl//absl/types:optional",
        "@org_tensorflow//tensorflow/lite/c:common",
    ],
)

cc_library(
    name = "image_utils",
    srcs = ["image_utils.cc"],
    hdrs = ["image_utils.h"],
    deps = [
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:image_frame",
        "//mediapipe_custom/framework/formats:tensor",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings:str_format",
        "@stblib//:stb_image",
    ],
)

cc_test(
    name = "image_utils_test",
    srcs = ["image_utils_test.cc"],
    deps = [
        ":image_utils",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:image_frame",
        "//mediapipe_custom/framework/formats:tensor",
        "//mediapipe_custom/framework/port:gtest_main",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "landmarks_duplicates_finder",
    hdrs = ["landmarks_duplicates_finder.h"],
    deps = [
        "//mediapipe_custom/framework/formats:landmark_cc_proto",
        "@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/status:statusor",
    ],
)

cc_library(
    name = "landmarks_utils",
    srcs = ["landmarks_utils.cc"],
    hdrs = ["landmarks_utils.h"],
    deps = ["//mediapipe_custom/tasks/cc/components/containers:rect"],
)

cc_test(
    name = "landmarks_utils_test",
    srcs = ["landmarks_utils_test.cc"],
    deps = [
        ":landmarks_utils",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/tasks/cc/components/containers:rect",
    ],
)

cc_library(
    name = "data_renderer",
    srcs = ["data_renderer.cc"],
    hdrs = ["data_renderer.h"],
    deps = [
        "//mediapipe_custom/calculators/util:annotation_overlay_calculator",
        "//mediapipe_custom/calculators/util:landmarks_to_render_data_calculator",
        "//mediapipe_custom/calculators/util:landmarks_to_render_data_calculator_cc_proto",
        "//mediapipe_custom/calculators/util:rect_to_render_data_calculator_cc_proto",
        "//mediapipe_custom/calculators/util:rect_to_render_scale_calculator",
        "//mediapipe_custom/calculators/util:rect_to_render_scale_calculator_cc_proto",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:landmark_cc_proto",
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/util:render_data_cc_proto",
        "@com_google_absl//absl/types:span",
    ],
)
