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
    name = "MPPFaceDetectorOptionsHelpers",
    srcs = ["sources/MPPFaceDetectorOptions+Helpers.mm"],
    hdrs = ["sources/MPPFaceDetectorOptions+Helpers.h"],
    deps = [
        "//mediapipe_custom/framework:calculator_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/face_detector/proto:face_detector_graph_options_cc_proto",
        "//mediapipe_custom/tasks/ios/common/utils:NSStringHelpers",
        "//mediapipe_custom/tasks/ios/core:MPPTaskOptionsProtocol",
        "//mediapipe_custom/tasks/ios/core/utils:MPPBaseOptionsHelpers",
        "//mediapipe_custom/tasks/ios/vision/face_detector:MPPFaceDetectorOptions",
    ],
)

objc_library(
    name = "MPPFaceDetectorResultHelpers",
    srcs = ["sources/MPPFaceDetectorResult+Helpers.mm"],
    hdrs = ["sources/MPPFaceDetectorResult+Helpers.h"],
    deps = [
        "//mediapipe_custom/framework:packet",
        "//mediapipe_custom/tasks/ios/components/containers/utils:MPPDetectionHelpers",
        "//mediapipe_custom/tasks/ios/vision/face_detector:MPPFaceDetectorResult",
    ],
)
