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

package(default_visibility = [
    "//mediapipe_custom/tasks:internal",
])

licenses(["notice"])

objc_library(
    name = "MPPTextClassifierOptions",
    srcs = ["sources/MPPTextClassifierOptions.m"],
    hdrs = ["sources/MPPTextClassifierOptions.h"],
    deps = [
        "//mediapipe_custom/tasks/ios/core:MPPTaskOptions",
        "//third_party/apple_frameworks:Foundation",
    ],
)

objc_library(
    name = "MPPTextClassifierResult",
    srcs = ["sources/MPPTextClassifierResult.m"],
    hdrs = ["sources/MPPTextClassifierResult.h"],
    deps = [
        "//mediapipe_custom/tasks/ios/components/containers:MPPClassificationResult",
        "//mediapipe_custom/tasks/ios/core:MPPTaskResult",
        "//third_party/apple_frameworks:Foundation",
    ],
)

objc_library(
    name = "MPPTextClassifier",
    srcs = ["sources/MPPTextClassifier.mm"],
    hdrs = ["sources/MPPTextClassifier.h"],
    copts = [
        "-ObjC++",
        "-std=c++20",
        "-Xclang=-fno-cxx-modules",
        "-x objective-c++",
    ],
    module_name = "MPPTextClassifier",
    deps = [
        ":MPPTextClassifierOptions",
        ":MPPTextClassifierResult",
        "//mediapipe_custom/tasks/cc/components/containers/proto:classifications_cc_proto",
        "//mediapipe_custom/tasks/cc/text/text_classifier:text_classifier_graph",
        "//mediapipe_custom/tasks/ios/common/utils:MPPCommonUtils",
        "//mediapipe_custom/tasks/ios/common/utils:NSStringHelpers",
        "//mediapipe_custom/tasks/ios/core:MPPTaskInfo",
        "//mediapipe_custom/tasks/ios/core:MPPTaskOptions",
        "//mediapipe_custom/tasks/ios/core:MPPTextPacketCreator",
        "//mediapipe_custom/tasks/ios/text/core:MPPTextTaskRunner",
        "//mediapipe_custom/tasks/ios/text/text_classifier/utils:MPPTextClassifierOptionsHelpers",
        "//mediapipe_custom/tasks/ios/text/text_classifier/utils:MPPTextClassifierResultHelpers",
        "//third_party/apple_frameworks:Foundation",
    ],
)
