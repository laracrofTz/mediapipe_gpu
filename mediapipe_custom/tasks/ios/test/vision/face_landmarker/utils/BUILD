load("@build_bazel_rules_apple//apple:ios.bzl", "ios_unit_test")
load(
    "@org_tensorflow//tensorflow/lite:special_rules.bzl",
    "tflite_ios_lab_runner",
)
load("@rules_cc//cc:objc_library.bzl", "objc_library")
load(
    "//mediapipe_custom/framework/tool:ios.bzl",
    "MPP_TASK_MINIMUM_OS_VERSION",
)

licenses(["notice"])

# Default tags for filtering iOS targets. Targets are restricted to Apple platforms.
TFL_DEFAULT_TAGS = [
    "apple",
]

# Following sanitizer tests are not supported by iOS test targets.
TFL_DISABLED_SANITIZER_TAGS = [
    "noasan",
    "nomsan",
    "notsan",
]

objc_library(
    name = "MPPFaceLandmarkeResultHelpersTestLibrary",
    testonly = True,
    srcs = ["sources/MPPFaceLandmarkerResult+HelpersTests.mm"],
    copts = [
        "-ObjC++",
        "-std=c++20",
        "-Xclang=-fno-cxx-modules",
        "-x objective-c++",
    ],
    deps = [
        "//mediapipe_custom/framework:packet",
        "//mediapipe_custom/framework/formats:classification_cc_proto",
        "//mediapipe_custom/framework/formats:landmark_cc_proto",
        "//mediapipe_custom/framework/formats:matrix_data_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/face_geometry/proto:face_geometry_cc_proto",
        "//mediapipe_custom/tasks/ios/vision/face_landmarker:MPPFaceLandmarkerResult",
        "//mediapipe_custom/tasks/ios/vision/face_landmarker/utils:MPPFaceLandmarkerResultHelpers",
        "//third_party/apple_frameworks:XCTest",
    ],
)

ios_unit_test(
    name = "MPPFaceLandmarkeResultHelpersTest",
    minimum_os_version = MPP_TASK_MINIMUM_OS_VERSION,
    runner = tflite_ios_lab_runner("IOS_LATEST"),
    tags = TFL_DEFAULT_TAGS + TFL_DISABLED_SANITIZER_TAGS,
    deps = [
        ":MPPFaceLandmarkeResultHelpersTestLibrary",
    ],
)
