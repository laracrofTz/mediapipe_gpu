# Copyright 2024 The MediaPipe Authors.
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
    name = "MPPHolisticLandmarkerOptionsHelpers",
    srcs = ["sources/MPPHolisticLandmarkerOptions+Helpers.mm"],
    hdrs = ["sources/MPPHolisticLandmarkerOptions+Helpers.h"],
    deps = [
        "//mediapipe_custom/tasks/cc/vision/face_detector/proto:face_detector_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/face_landmarker/proto:face_landmarks_detector_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/hand_landmarker/proto:hand_landmarks_detector_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/holistic_landmarker/proto:holistic_landmarker_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/pose_detector/proto:pose_detector_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/pose_landmarker/proto:pose_landmarks_detector_graph_options_cc_proto",
        "//mediapipe_custom/tasks/ios/common/utils:NSStringHelpers",
        "//mediapipe_custom/tasks/ios/core:MPPTaskOptionsProtocol",
        "//mediapipe_custom/tasks/ios/core/utils:MPPBaseOptionsHelpers",
        "//mediapipe_custom/tasks/ios/vision/holistic_landmarker:MPPHolisticLandmarkerOptions",
        "@com_google_protobuf//:protobuf",
    ],
)

objc_library(
    name = "MPPHolisticLandmarkerResultHelpers",
    srcs = ["sources/MPPHolisticLandmarkerResult+Helpers.mm"],
    hdrs = ["sources/MPPHolisticLandmarkerResult+Helpers.h"],
    copts = [
        "-ObjC++",
        "-std=c++20",
        "-Xclang=-fno-cxx-modules",
        "-x objective-c++",
    ],
    deps = [
        "//mediapipe_custom/framework:packet",
        "//mediapipe_custom/framework/formats:classification_cc_proto",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:landmark_cc_proto",
        "//mediapipe_custom/tasks/ios/components/containers/utils:MPPClassificationResultHelpers",
        "//mediapipe_custom/tasks/ios/components/containers/utils:MPPLandmarkHelpers",
        "//mediapipe_custom/tasks/ios/vision/holistic_landmarker:MPPHolisticLandmarkerResult",
    ],
)
