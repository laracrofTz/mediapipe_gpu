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

load("@rules_cc//cc:objc_library.bzl", "objc_library")

package(default_visibility = ["//mediapipe_custom/tasks:internal"])

licenses(["notice"])

objc_library(
    name = "MPPImage",
    srcs = ["sources/MPPImage.m"],
    hdrs = ["sources/MPPImage.h"],
    copts = [
        "-ObjC++",
        "-std=c++20",
        "-Xclang=-fno-cxx-modules",
    ],
    module_name = "MPPImage",
    deps = [
        "//mediapipe_custom/tasks/ios/common:MPPCommon",
        "//mediapipe_custom/tasks/ios/common/utils:MPPCommonUtils",
        "//third_party/apple_frameworks:CoreMedia",
        "//third_party/apple_frameworks:CoreVideo",
        "//third_party/apple_frameworks:Foundation",
        "//third_party/apple_frameworks:UIKit",
    ],
)

objc_library(
    name = "MPPRunningMode",
    hdrs = ["sources/MPPRunningMode.h"],
    module_name = "MPPRunningMode",
    deps = ["//third_party/apple_frameworks:Foundation"],
)

objc_library(
    name = "MPPVisionPacketCreator",
    srcs = ["sources/MPPVisionPacketCreator.mm"],
    hdrs = ["sources/MPPVisionPacketCreator.h"],
    copts = [
        "-ObjC++",
        "-std=c++20",
        "-Xclang=-fno-cxx-modules",
    ],
    deps = [
        ":MPPImage",
        "//mediapipe_custom/framework:packet",
        "//mediapipe_custom/framework:timestamp",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/tasks/ios/components/containers:MPPRegionOfInterest",
        "//mediapipe_custom/tasks/ios/components/containers/utils:MPPRegionOfInterestHelpers",
        "//mediapipe_custom/tasks/ios/vision/core/utils:MPPImageUtils",
        "//third_party/apple_frameworks:Foundation",
    ],
)

objc_library(
    name = "MPPVisionTaskRunner",
    srcs = ["sources/MPPVisionTaskRunner.mm"],
    hdrs = ["sources/MPPVisionTaskRunner.h"],
    copts = [
        "-ObjC++",
        "-std=c++20",
        "-Xclang=-fno-cxx-modules",
    ],
    deps = [
        ":MPPImage",
        ":MPPRunningMode",
        ":MPPVisionPacketCreator",
        "//mediapipe_custom/calculators/core:flow_limiter_calculator",
        "//mediapipe_custom/framework:packet",
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/tasks/ios/common:MPPCommon",
        "//mediapipe_custom/tasks/ios/common/utils:MPPCommonUtils",
        "//mediapipe_custom/tasks/ios/common/utils:NSStringHelpers",
        "//mediapipe_custom/tasks/ios/core:MPPTaskInfo",
        "//mediapipe_custom/tasks/ios/core:MPPTaskRunner",
        "//third_party/apple_frameworks:Foundation",
        "//third_party/apple_frameworks:UIKit",
        "@com_google_absl//absl/status:statusor",
    ],
)

objc_library(
    name = "MPPMask",
    srcs = ["sources/MPPMask.mm"],
    hdrs = ["sources/MPPMask.h"],
    copts = [
        "-ObjC++",
        "-std=c++20",
        "-Xclang=-fno-cxx-modules",
    ],
    deps = [
        "//mediapipe_custom/tasks/ios/common:MPPCommon",
        "//mediapipe_custom/tasks/ios/common/utils:MPPCommonUtils",
        "//third_party/apple_frameworks:Foundation",
    ],
)
