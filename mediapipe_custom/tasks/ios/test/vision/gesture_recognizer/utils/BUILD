load("@rules_cc//cc:objc_library.bzl", "objc_library")

package(default_visibility = ["//mediapipe_custom/tasks:internal"])

licenses(["notice"])

objc_library(
    name = "MPPGestureRecognizerResultProtobufHelpers",
    srcs = ["sources/MPPGestureRecognizerResult+ProtobufHelpers.mm"],
    hdrs = ["sources/MPPGestureRecognizerResult+ProtobufHelpers.h"],
    copts = [
        "-ObjC++",
        "-std=c++20",
        "-Xclang=-fno-cxx-modules",
        "-x objective-c++",
    ],
    deps = [
        "//mediapipe_custom/framework/formats:classification_cc_proto",
        "//mediapipe_custom/tasks/cc/components/containers/proto:landmarks_detection_result_cc_proto",
        "//mediapipe_custom/tasks/ios/common/utils:NSStringHelpers",
        "//mediapipe_custom/tasks/ios/test/vision/utils:parse_proto_utils",
        "//mediapipe_custom/tasks/ios/vision/gesture_recognizer:MPPGestureRecognizerResult",
        "//mediapipe_custom/tasks/ios/vision/gesture_recognizer/utils:MPPGestureRecognizerResultHelpers",
        "//third_party/apple_frameworks:Foundation",
    ],
)
