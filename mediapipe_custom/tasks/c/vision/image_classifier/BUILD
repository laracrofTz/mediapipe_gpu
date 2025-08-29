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
    name = "image_classifier_lib",
    srcs = ["image_classifier.cc"],
    hdrs = ["image_classifier.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:image_frame",
        "//mediapipe_custom/tasks/c/components/containers:classification_result",
        "//mediapipe_custom/tasks/c/components/containers:classification_result_converter",
        "//mediapipe_custom/tasks/c/components/processors:classifier_options",
        "//mediapipe_custom/tasks/c/components/processors:classifier_options_converter",
        "//mediapipe_custom/tasks/c/core:base_options",
        "//mediapipe_custom/tasks/c/core:base_options_converter",
        "//mediapipe_custom/tasks/c/vision/core:common",
        "//mediapipe_custom/tasks/cc/vision/core:running_mode",
        "//mediapipe_custom/tasks/cc/vision/image_classifier",
        "//mediapipe_custom/tasks/cc/vision/utils:image_utils",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ],
    alwayslink = 1,
)

cc_test(
    name = "image_classifier_test",
    srcs = ["image_classifier_test.cc"],
    data = [
        "//mediapipe_custom/framework/formats:image_frame_opencv",
        "//mediapipe_custom/framework/port:opencv_core",
        "//mediapipe_custom/framework/port:opencv_imgproc",
        "//mediapipe_custom/tasks/testdata/vision:test_images",
        "//mediapipe_custom/tasks/testdata/vision:test_models",
    ],
    linkstatic = 1,
    deps = [
        ":image_classifier_lib",
        "//mediapipe_custom/framework/deps:file_path",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/port:gtest",
        "//mediapipe_custom/tasks/c/components/containers:category",
        "//mediapipe_custom/tasks/c/vision/core:common",
        "//mediapipe_custom/tasks/cc/vision/utils:image_utils",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/strings",
        "@com_google_googletest//:gtest_main",
    ],
)

# bazel build -c opt --linkopt -s --strip always --define MEDIAPIPE_DISABLE_GPU=1 \
# //mediapipe_custom/tasks/c/vision/image_classifier:libimage_classifier.so
cc_binary(
    name = "libimage_classifier.so",
    linkopts = [
        "-Wl,-soname=libimage_classifier.so",
        "-fvisibility=hidden",
    ],
    linkshared = True,
    tags = [
        "manual",
        "nobuilder",
        "notap",
    ],
    deps = [":image_classifier_lib"],
)

# bazel build --config darwin_arm64 -c opt --strip always --define MEDIAPIPE_DISABLE_GPU=1 \
# //mediapipe_custom/tasks/c/vision/image_classifier:libimage_classifier.dylib
cc_binary(
    name = "libimage_classifier.dylib",
    linkopts = [
        "-Wl,-install_name,libimage_classifier.dylib",
        "-fvisibility=hidden",
    ],
    linkshared = True,
    tags = [
        "manual",
        "nobuilder",
        "notap",
    ],
    deps = [":image_classifier_lib"],
)
