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
    name = "MPPFaceDetectorResult",
    srcs = ["sources/MPPFaceDetectorResult.m"],
    hdrs = ["sources/MPPFaceDetectorResult.h"],
    deps = [
        "//mediapipe_custom/tasks/ios/components/containers:MPPDetection",
        "//mediapipe_custom/tasks/ios/core:MPPTaskResult",
    ],
)

objc_library(
    name = "MPPFaceDetectorOptions",
    srcs = ["sources/MPPFaceDetectorOptions.m"],
    hdrs = ["sources/MPPFaceDetectorOptions.h"],
    deps = [
        ":MPPFaceDetectorResult",
        "//mediapipe_custom/tasks/ios/core:MPPTaskOptions",
        "//mediapipe_custom/tasks/ios/vision/core:MPPRunningMode",
        "//third_party/apple_frameworks:Foundation",
    ],
)

objc_library(
    name = "MPPFaceDetector",
    srcs = ["sources/MPPFaceDetector.mm"],
    hdrs = ["sources/MPPFaceDetector.h"],
    copts = [
        "-ObjC++",
        "-std=c++20",
        "-Xclang=-fno-cxx-modules",
        "-x objective-c++",
    ],
    deps = [
        ":MPPFaceDetectorOptions",
        ":MPPFaceDetectorResult",
        "//mediapipe_custom/tasks/cc/vision/face_detector:face_detector_graph",
        "//mediapipe_custom/tasks/ios/common/utils:MPPCommonUtils",
        "//mediapipe_custom/tasks/ios/common/utils:NSStringHelpers",
        "//mediapipe_custom/tasks/ios/core:MPPTaskInfo",
        "//mediapipe_custom/tasks/ios/vision/core:MPPImage",
        "//mediapipe_custom/tasks/ios/vision/core:MPPVisionPacketCreator",
        "//mediapipe_custom/tasks/ios/vision/core:MPPVisionTaskRunner",
        "//mediapipe_custom/tasks/ios/vision/face_detector/utils:MPPFaceDetectorOptionsHelpers",
        "//mediapipe_custom/tasks/ios/vision/face_detector/utils:MPPFaceDetectorResultHelpers",
        "//third_party/apple_frameworks:Foundation",
    ],
)
