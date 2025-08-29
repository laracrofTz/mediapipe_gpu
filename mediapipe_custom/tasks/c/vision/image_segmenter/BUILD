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

load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_cc//cc:cc_test.bzl", "cc_test")

package(default_visibility = ["//mediapipe_custom/tasks:internal"])

licenses(["notice"])

cc_library(
    name = "image_segmenter_result",
    hdrs = ["image_segmenter_result.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/tasks/c/vision/core:common",
    ],
)

cc_library(
    name = "image_segmenter_result_converter",
    srcs = ["image_segmenter_result_converter.cc"],
    hdrs = ["image_segmenter_result_converter.h"],
    deps = [
        ":image_segmenter_result",
        "//mediapipe_custom/tasks/c/vision/core:common",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter:image_segmenter_result",
    ],
)

cc_test(
    name = "image_segmenter_result_converter_test",
    srcs = ["image_segmenter_result_converter_test.cc"],
    data = [
        "//mediapipe_custom/framework/formats:image_frame_opencv",
        "//mediapipe_custom/framework/port:opencv_core",
        "//mediapipe_custom/framework/port:opencv_imgproc",
        "//mediapipe_custom/tasks/testdata/vision:test_images",
    ],
    linkstatic = 1,
    deps = [
        ":image_segmenter_result",
        ":image_segmenter_result_converter",
        "//mediapipe_custom/framework/deps:file_path",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/port:gtest",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/tasks/c/vision/core:common",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter:image_segmenter_result",
        "//mediapipe_custom/tasks/cc/vision/utils:image_utils",
        "@com_google_absl//absl/flags:flag",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "image_segmenter_lib",
    srcs = ["image_segmenter.cc"],
    hdrs = ["image_segmenter.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":image_segmenter_result",
        ":image_segmenter_result_converter",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:image_frame",
        "//mediapipe_custom/tasks/c/core:base_options",
        "//mediapipe_custom/tasks/c/core:base_options_converter",
        "//mediapipe_custom/tasks/c/vision/core:common",
        "//mediapipe_custom/tasks/cc/vision/core:running_mode",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter:image_segmenter_result",
        "//mediapipe_custom/tasks/cc/vision/utils:image_utils",
        "@com_google_absl//absl/log",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ],
    alwayslink = 1,
)

cc_test(
    name = "image_segmenter_test",
    srcs = ["image_segmenter_test.cc"],
    data = [
        "//mediapipe_custom/framework/formats:image_frame_opencv",
        "//mediapipe_custom/framework/port:opencv_core",
        "//mediapipe_custom/framework/port:opencv_imgproc",
        "//mediapipe_custom/tasks/testdata/vision:test_images",
        "//mediapipe_custom/tasks/testdata/vision:test_models",
    ],
    linkstatic = 1,
    deps = [
        ":image_segmenter_lib",
        ":image_segmenter_result",
        "//mediapipe_custom/framework/deps:file_path",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/port:gtest",
        "//mediapipe_custom/tasks/c/test:test_utils",
        "//mediapipe_custom/tasks/c/vision/core:common",
        "//mediapipe_custom/tasks/cc/vision/utils:image_utils",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/strings",
        "@com_google_googletest//:gtest_main",
    ],
)

# bazel build -c opt --linkopt -s --strip always --define MEDIAPIPE_DISABLE_GPU=1 \
# //mediapipe_custom/tasks/c/vision/image_segmenter:libimage_segmenter.so
cc_binary(
    name = "libimage_segmenter.so",
    linkopts = [
        "-Wl,-soname=libimage_segmenter.so",
        "-fvisibility=hidden",
    ],
    linkshared = True,
    tags = [
        "manual",
        "nobuilder",
        "notap",
    ],
    deps = [":image_segmenter_lib"],
)

# bazel build --config darwin_arm64 -c opt --strip always --define MEDIAPIPE_DISABLE_GPU=1 \
# //mediapipe_custom/tasks/c/vision/image_segmenter:libimage_segmenter.dylib
cc_binary(
    name = "libimage_segmenter.dylib",
    linkopts = [
        "-Wl,-install_name,libimage_segmenter.dylib",
        "-fvisibility=hidden",
    ],
    linkshared = True,
    tags = [
        "manual",
        "nobuilder",
        "notap",
    ],
    deps = [":image_segmenter_lib"],
)
