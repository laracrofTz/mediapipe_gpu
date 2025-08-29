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

licenses(["notice"])

cc_library(
    name = "pose_landmarker_result",
    hdrs = ["pose_landmarker_result.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/tasks/c/components/containers:landmark",
        "//mediapipe_custom/tasks/c/vision/core:common",
    ],
)

cc_library(
    name = "pose_landmarker_result_converter",
    srcs = ["pose_landmarker_result_converter.cc"],
    hdrs = ["pose_landmarker_result_converter.h"],
    deps = [
        ":pose_landmarker_result",
        "//mediapipe_custom/tasks/c/components/containers:landmark",
        "//mediapipe_custom/tasks/c/components/containers:landmark_converter",
        "//mediapipe_custom/tasks/c/vision/core:common",
        "//mediapipe_custom/tasks/cc/components/containers:landmark",
        "//mediapipe_custom/tasks/cc/vision/pose_landmarker:pose_landmarker_result",
    ],
)

cc_test(
    name = "pose_landmarker_result_converter_test",
    srcs = ["pose_landmarker_result_converter_test.cc"],
    data = [
        "//mediapipe_custom/framework/formats:image_frame_opencv",
        "//mediapipe_custom/framework/port:opencv_core",
        "//mediapipe_custom/framework/port:opencv_imgproc",
        "//mediapipe_custom/tasks/testdata/vision:test_images",
    ],
    linkstatic = 1,
    deps = [
        ":pose_landmarker_result",
        ":pose_landmarker_result_converter",
        "//mediapipe_custom/framework/deps:file_path",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/port:gtest",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/tasks/c/components/containers:landmark",
        "//mediapipe_custom/tasks/cc/components/containers:landmark",
        "//mediapipe_custom/tasks/cc/vision/pose_landmarker:pose_landmarker_result",
        "//mediapipe_custom/tasks/cc/vision/utils:image_utils",
        "@com_google_absl//absl/flags:flag",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "pose_landmarker_lib",
    srcs = ["pose_landmarker.cc"],
    hdrs = ["pose_landmarker.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":pose_landmarker_result",
        ":pose_landmarker_result_converter",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:image_frame",
        "//mediapipe_custom/tasks/c/core:base_options",
        "//mediapipe_custom/tasks/c/core:base_options_converter",
        "//mediapipe_custom/tasks/c/vision/core:common",
        "//mediapipe_custom/tasks/cc/vision/core:running_mode",
        "//mediapipe_custom/tasks/cc/vision/pose_landmarker",
        "//mediapipe_custom/tasks/cc/vision/pose_landmarker:pose_landmarker_result",
        "//mediapipe_custom/tasks/cc/vision/utils:image_utils",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ],
    alwayslink = 1,
)

cc_test(
    name = "pose_landmarker_test",
    srcs = ["pose_landmarker_test.cc"],
    data = [
        "//mediapipe_custom/framework/formats:image_frame_opencv",
        "//mediapipe_custom/framework/port:opencv_core",
        "//mediapipe_custom/framework/port:opencv_imgproc",
        "//mediapipe_custom/tasks/testdata/vision:test_images",
        "//mediapipe_custom/tasks/testdata/vision:test_models",
    ],
    linkstatic = 1,
    deps = [
        ":pose_landmarker_lib",
        ":pose_landmarker_result",
        "//mediapipe_custom/framework/deps:file_path",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/port:gtest",
        "//mediapipe_custom/tasks/c/components/containers:landmark",
        "//mediapipe_custom/tasks/c/vision/core:common",
        "//mediapipe_custom/tasks/cc/vision/utils:image_utils",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/strings",
        "@com_google_googletest//:gtest_main",
    ],
)

# bazel build -c opt --linkopt -s --strip always --define MEDIAPIPE_DISABLE_GPU=1 \
# //mediapipe_custom/tasks/c/vision/pose_landmarker:libpose_landmarker.so
cc_binary(
    name = "libpose_landmarker.so",
    linkopts = [
        "-Wl,-soname=libpose_landmarker.so",
        "-fvisibility=hidden",
    ],
    linkshared = True,
    tags = [
        "manual",
        "nobuilder",
        "notap",
    ],
    deps = [":pose_landmarker_lib"],
)

# bazel build --config darwin_arm64 -c opt --strip always --define MEDIAPIPE_DISABLE_GPU=1 \
# //mediapipe_custom/tasks/c/vision/pose_landmarker:libpose_landmarker.dylib
cc_binary(
    name = "libpose_landmarker.dylib",
    linkopts = [
        "-Wl,-install_name,libpose_landmarker.dylib",
        "-fvisibility=hidden",
    ],
    linkshared = True,
    tags = [
        "manual",
        "nobuilder",
        "notap",
    ],
    deps = [":pose_landmarker_lib"],
)
