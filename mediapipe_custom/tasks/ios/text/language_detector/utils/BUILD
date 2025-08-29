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
    name = "MPPLanguageDetectorOptionsHelpers",
    srcs = ["sources/MPPLanguageDetectorOptions+Helpers.mm"],
    hdrs = ["sources/MPPLanguageDetectorOptions+Helpers.h"],
    deps = [
        "//mediapipe_custom/framework:calculator_options_cc_proto",
        "//mediapipe_custom/tasks/cc/components/processors/proto:classifier_options_cc_proto",
        "//mediapipe_custom/tasks/cc/text/text_classifier/proto:text_classifier_graph_options_cc_proto",
        "//mediapipe_custom/tasks/ios/common/utils:NSStringHelpers",
        "//mediapipe_custom/tasks/ios/core:MPPTaskOptionsProtocol",
        "//mediapipe_custom/tasks/ios/core/utils:MPPBaseOptionsHelpers",
        "//mediapipe_custom/tasks/ios/text/language_detector:MPPLanguageDetectorOptions",
    ],
)

objc_library(
    name = "MPPLanguageDetectorResultHelpers",
    srcs = ["sources/MPPLanguageDetectorResult+Helpers.mm"],
    hdrs = ["sources/MPPLanguageDetectorResult+Helpers.h"],
    deps = [
        "//mediapipe_custom/framework:packet",
        "//mediapipe_custom/tasks/cc/components/containers/proto:classifications_cc_proto",
        "//mediapipe_custom/tasks/ios/components/containers/utils:MPPClassificationResultHelpers",
        "//mediapipe_custom/tasks/ios/text/language_detector:MPPLanguageDetectorResult",
    ],
)
