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

load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_cc//cc:cc_test.bzl", "cc_test")
load("//mediapipe_custom/framework:mediapipe_cc_test.bzl", "mediapipe_cc_test")
load("//mediapipe_custom/framework/port:build_config.bzl", "mediapipe_proto_library")
# Placeholder: load py_library

licenses(["notice"])

package(default_visibility = ["//visibility:private"])

mediapipe_proto_library(
    name = "audio_decoder_proto",
    srcs = ["audio_decoder.proto"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/framework:calculator_options_proto",
        "//mediapipe_custom/framework:calculator_proto",
    ],
)

mediapipe_proto_library(
    name = "color_proto",
    srcs = ["color.proto"],
    visibility = ["//visibility:public"],
)

mediapipe_proto_library(
    name = "label_map_proto",
    srcs = ["label_map.proto"],
    visibility = ["//visibility:public"],
)

mediapipe_proto_library(
    name = "render_data_proto",
    srcs = ["render_data.proto"],
    visibility = ["//visibility:public"],
    deps = ["//mediapipe_custom/util:color_proto"],
)

cc_library(
    name = "audio_decoder",
    srcs = ["audio_decoder.cc"],
    hdrs = ["audio_decoder.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":audio_decoder_cc_proto",
        "//mediapipe_custom/framework:packet",
        "//mediapipe_custom/framework:timestamp",
        "//mediapipe_custom/framework/deps:cleanup",
        "//mediapipe_custom/framework/formats:matrix",
        "//mediapipe_custom/framework/formats:time_series_header_cc_proto",
        "//mediapipe_custom/framework/port:integral_types",
        "//mediapipe_custom/framework/port:map_util",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/framework/tool:status_util",
        "//third_party:libffmpeg",
        "@com_google_absl//absl/base:endian",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/time",
        "@eigen//:eigen3",
    ],
)

cc_library(
    name = "cpu_util",
    srcs = ["cpu_util.cc"],
    hdrs = ["cpu_util.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/framework/port:integral_types",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/framework/port:statusor",
        "@com_google_absl//absl/algorithm:container",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/strings",
    ] + select({
        "//conditions:default": [],
        "//mediapipe_custom:android": [
            "@androidndk//:cpufeatures",
        ],
    }),
)

cc_library(
    name = "fd_test_util",
    testonly = True,
    hdrs = ["fd_test_util.h"],
    visibility = ["//mediapipe_custom:__subpackages__"],
)

cc_library(
    name = "header_util",
    srcs = ["header_util.cc"],
    hdrs = ["header_util.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:packet_set",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/framework/tool:status_util",
    ],
)

cc_library(
    name = "image_frame_util",
    srcs = ["image_frame_util.cc"],
    hdrs = ["image_frame_util.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/framework/deps:mathutil",
        "//mediapipe_custom/framework/formats:image_format_cc_proto",
        "//mediapipe_custom/framework/formats:image_frame",
        "//mediapipe_custom/framework/formats:image_frame_opencv",
        "//mediapipe_custom/framework/formats:yuv_image",
        "//mediapipe_custom/framework/port",
        "//mediapipe_custom/framework/port:aligned_malloc_and_free",
        "//mediapipe_custom/framework/port:integral_types",
        "//mediapipe_custom/framework/port:opencv_imgproc",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/framework/tool:status_util",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/strings",
        "@libyuv",
    ],
)

cc_library(
    name = "label_map_util",
    srcs = ["label_map_util.cc"],
    hdrs = ["label_map_util.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":label_map_cc_proto",
        ":str_util",
        "//mediapipe_custom/framework/port:core_proto",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/strings:string_view",
        "@com_google_protobuf//:protobuf",
    ],
)

cc_test(
    name = "label_map_util_test",
    srcs = ["label_map_util_test.cc"],
    deps = [
        ":label_map_util",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:status_matchers",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:string_view",
    ],
)

cc_library(
    name = "pose_util",
    srcs = ["pose_util.cc"],
    hdrs = ["pose_util.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/framework/formats:landmark_cc_proto",
        "//mediapipe_custom/framework/port:opencv_core",
        "//mediapipe_custom/framework/port:opencv_imgproc",
        "@com_google_absl//absl/log:absl_log",
    ],
)

cc_library(
    name = "annotation_renderer",
    srcs = ["annotation_renderer.cc"],
    hdrs = ["annotation_renderer.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":color_cc_proto",
        ":render_data_cc_proto",
        "//mediapipe_custom/framework/port:logging",
        "//mediapipe_custom/framework/port:opencv_core",
        "//mediapipe_custom/framework/port:opencv_imgproc",
        "//mediapipe_custom/framework/port:vector",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/log:absl_log",
    ],
)

cc_library(
    name = "sync_wait",
    srcs = ["sync_wait.cc"],
    hdrs = ["sync_wait.h"],
    visibility = ["//mediapipe_custom:__subpackages__"],
    deps = [
        "//mediapipe_custom/framework/formats:shared_fd",
        "//mediapipe_custom/framework/formats:unique_fd",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:status",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/time",
    ],
)

cc_test(
    name = "sync_wait_test",
    srcs = ["sync_wait_test.cc"],
    deps = [
        ":sync_wait",
        "//mediapipe_custom/framework:port",
        "//mediapipe_custom/framework/formats:shared_fd",
        "//mediapipe_custom/framework/formats:unique_fd",
        "//mediapipe_custom/framework/port:benchmark",
        "//mediapipe_custom/framework/port:gtest_main",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/time",
    ],
)

# Prefer to use ":resource_util", Customization of the resource util is being restricted
# while we explore how it should best be implemented.
cc_library(
    name = "resource_util_custom",
    hdrs = ["resource_util_custom.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/framework/port:status",
    ],
)

cc_library(
    name = "resource_util",
    srcs = [
        "resource_util.cc",
        "resource_util_internal.h",
    ] + select({
        "//conditions:default": ["resource_util_default.cc"],
        "//mediapipe_custom:android": ["resource_util_android.cc"],
        "//mediapipe_custom/framework:android_no_jni": ["resource_util_loonix.cc"],
        "//mediapipe_custom:ios": ["resource_util_apple.cc"],
        "//mediapipe_custom:macos": ["resource_util_default.cc"],
        "//mediapipe_custom:emscripten": ["resource_util_emscripten.cc"],
        "//mediapipe_custom:windows": ["resource_util_windows.cc"],
    }),
    hdrs = [
        "resource_util.h",
    ],

    # We use Objective-C++ on iOS.
    copts = select({
        "//conditions:default": [],
        "//mediapipe_custom:ios": [
            "-ObjC++",
        ],
        "//mediapipe_custom:macos": [],
    }),
    visibility = ["//visibility:public"],
    deps = [
        ":resource_util_custom",
        "//mediapipe_custom/framework/deps:file_path",
        "//mediapipe_custom/framework/port:file_helpers",
        "//mediapipe_custom/framework/port:logging",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:singleton",
        "//mediapipe_custom/framework/port:status",
        "@com_google_absl//absl/base:core_headers",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
    ] + select({
        "//conditions:default": [
            "@com_google_absl//absl/flags:flag",
        ],
        "//mediapipe_custom:android": [
            "//mediapipe_custom/util/android:asset_manager_util",
            "//mediapipe_custom/util/android/file/base",
        ],
        "//mediapipe_custom/framework:android_no_jni": [],
        "//mediapipe_custom:ios": [],
        "//mediapipe_custom:emscripten": [],
        "//mediapipe_custom:macos": [
            "@com_google_absl//absl/flags:flag",
        ],
        "//mediapipe_custom:windows": [
            "@bazel_tools//tools/cpp/runfiles",
            "@com_google_absl//absl/flags:flag",
        ],
    }),
)

cc_library(
    name = "resource_cache",
    hdrs = ["resource_cache.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/framework/port:logging",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/functional:function_ref",
        "@com_google_absl//absl/log:absl_check",
    ],
)

cc_test(
    name = "resource_cache_test",
    srcs = ["resource_cache_test.cc"],
    deps = [
        ":resource_cache",
        "//mediapipe_custom/framework/port:gtest_main",
    ],
)

cc_library(
    name = "resources_test_util",
    testonly = True,
    srcs = ["resources_test_util.cc"],
    hdrs = ["resources_test_util.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/framework:resources",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:string_view",
    ],
)

cc_library(
    name = "tensor_to_detection",
    srcs = ["tensor_to_detection.cc"],
    hdrs = ["tensor_to_detection.h"],
    features = [
        # Layering check doesn't play nicely with portable proto wrappers.
        "no_layering_check",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/framework/formats:detection_cc_proto",
        "//mediapipe_custom/framework/formats:location",
        "//mediapipe_custom/framework/formats:location_opencv",
        "//mediapipe_custom/framework/port:map_util",
        "//mediapipe_custom/framework/port:status",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_absl//absl/types:variant",
    ] + select({
        "//conditions:default": [
            "@org_tensorflow//tensorflow/core:framework",
        ],
        "//mediapipe_custom:android": [
            "@org_tensorflow//tensorflow/core:portable_tensorflow_lib_lite",
        ],
    }),
)

cc_library(
    name = "time_series_util",
    srcs = ["time_series_util.cc"],
    hdrs = ["time_series_util.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/formats:matrix",
        "//mediapipe_custom/framework/formats:time_series_header_cc_proto",
        "//mediapipe_custom/framework/port:integral_types",
        "//mediapipe_custom/framework/port:status",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "time_series_test_util",
    testonly = True,
    hdrs = ["time_series_test_util.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":time_series_util",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:calculator_runner",
        "//mediapipe_custom/framework/formats:matrix",
        "//mediapipe_custom/framework/formats:time_series_header_cc_proto",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:integral_types",
        "//mediapipe_custom/framework/port:logging",
        "//mediapipe_custom/framework/port:parse_text_proto",
        "//mediapipe_custom/framework/port:status",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/strings",
        "@eigen//:eigen3",
    ],
)

cc_test(
    name = "time_series_util_test",
    size = "small",
    srcs = ["time_series_util_test.cc"],
    deps = [
        ":time_series_util",
        "//mediapipe_custom/calculators/audio:resample_time_series_calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework/formats:time_series_header_cc_proto",
        "//mediapipe_custom/framework/port:gtest_main",
        "@eigen//:eigen3",
    ],
)

cc_library(
    name = "packet_test_util",
    testonly = True,
    hdrs = ["packet_test_util.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/framework:demangle",
        "//mediapipe_custom/framework:packet",
        "//mediapipe_custom/framework:timestamp",
        "//mediapipe_custom/framework/port:gtest",
    ],
)

cc_test(
    name = "packet_test_util_test",
    size = "small",
    srcs = ["packet_test_util_test.cc"],
    deps = [
        ":packet_test_util",
        "//mediapipe_custom/framework:packet",
        "//mediapipe_custom/framework:port",
        "//mediapipe_custom/framework:timestamp",
        "//mediapipe_custom/framework/port:gtest_main",
    ],
)

cc_library(
    name = "rectangle_util",
    srcs = ["rectangle_util.cc"],
    hdrs = ["rectangle_util.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/framework/port:rectangle",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:statusor",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/types:span",
    ],
)

cc_test(
    name = "rectangle_util_test",
    srcs = ["rectangle_util_test.cc"],
    deps = [
        ":rectangle_util",
        "//mediapipe_custom/framework/port:gtest_main",
    ],
)

cc_library(
    name = "image_test_utils",
    testonly = True,
    srcs = ["image_test_utils.cc"],
    hdrs = ["image_test_utils.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/framework:packet",
        "//mediapipe_custom/framework:timestamp",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:image_format_cc_proto",
        "//mediapipe_custom/framework/formats:image_frame",
        "//mediapipe_custom/framework/formats:image_frame_opencv",
        "//mediapipe_custom/framework/port:opencv_core",
        "//mediapipe_custom/framework/port:opencv_imgcodecs",
        "//mediapipe_custom/framework/port:opencv_imgproc",
        "//mediapipe_custom/gpu:gpu_buffer",
        "//mediapipe_custom/gpu:gpu_buffer_format",
        "@com_google_absl//absl/log:absl_log",
    ],
)

cc_library(
    name = "graph_builder_utils",
    srcs = ["graph_builder_utils.cc"],
    hdrs = ["graph_builder_utils.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/framework:calculator_cc_proto",
        "//mediapipe_custom/framework:calculator_framework",
        "@com_google_absl//absl/strings",
    ],
)

cc_test(
    name = "graph_builder_utils_test",
    srcs = ["graph_builder_utils_test.cc"],
    deps = [
        ":graph_builder_utils",
        "//mediapipe_custom/framework:calculator_cc_proto",
        "//mediapipe_custom/framework/port:gtest",
        "//mediapipe_custom/framework/port:gtest_main",
    ],
)

cc_library(
    name = "str_util",
    srcs = ["str_util.cc"],
    hdrs = ["str_util.h"],
    visibility = ["//visibility:public"],
    deps = [
        "@com_google_absl//absl/functional:any_invocable",
        "@com_google_absl//absl/strings:string_view",
    ],
)

cc_test(
    name = "str_util_test",
    srcs = ["str_util_test.cc"],
    deps = [
        ":str_util",
        "//mediapipe_custom/framework/port:gtest_main",
        "@com_google_absl//absl/strings:string_view",
    ],
)
