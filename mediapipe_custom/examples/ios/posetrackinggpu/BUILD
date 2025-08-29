# Copyright 2020 The MediaPipe Authors.
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

load(
    "@build_bazel_rules_apple//apple:ios.bzl",
    "ios_application",
)
load("@rules_cc//cc:objc_library.bzl", "objc_library")
load(
    "//mediapipe_custom/examples/ios:bundle_id.bzl",
    "BUNDLE_ID_PREFIX",
    "example_provisioning",
)

licenses(["notice"])

MIN_IOS_VERSION = "12.0"

alias(
    name = "posetrackinggpu",
    actual = "PoseTrackingGpuApp",
)

ios_application(
    name = "PoseTrackingGpuApp",
    app_icons = ["//mediapipe_custom/examples/ios/common:AppIcon"],
    bundle_id = BUNDLE_ID_PREFIX + ".PoseTrackingGpu",
    families = [
        "iphone",
        "ipad",
    ],
    infoplists = [
        "//mediapipe_custom/examples/ios/common:Info.plist",
        "Info.plist",
    ],
    minimum_os_version = MIN_IOS_VERSION,
    provisioning_profile = example_provisioning(),
    deps = [
        ":PoseTrackingGpuAppLibrary",
        "@ios_opencv//:OpencvFramework",
    ],
)

objc_library(
    name = "PoseTrackingGpuAppLibrary",
    srcs = [
        "PoseTrackingViewController.mm",
    ],
    hdrs = [
        "PoseTrackingViewController.h",
    ],
    data = [
        "//mediapipe_custom/graphs/pose_tracking:pose_tracking_gpu.binarypb",
        "//mediapipe_custom/modules/pose_detection:pose_detection.tflite",
        "//mediapipe_custom/modules/pose_landmark:pose_landmark_full.tflite",
    ],
    deps = [
        "//mediapipe_custom/examples/ios/common:CommonMediaPipeAppLibrary",
        "//mediapipe_custom/framework/formats:landmark_cc_proto",
    ] + select({
        "//mediapipe_custom:ios_x86_64": [],
        "//conditions:default": [
            "//mediapipe_custom/graphs/pose_tracking:pose_tracking_gpu_deps",
        ],
    }),
)
