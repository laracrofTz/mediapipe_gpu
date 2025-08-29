load("@rules_cc//cc:objc_library.bzl", "objc_library")

package(default_visibility = ["//mediapipe_custom/tasks:internal"])

licenses(["notice"])

objc_library(
    name = "MPPImageUtils",
    srcs = ["sources/MPPImage+Utils.mm"],
    hdrs = ["sources/MPPImage+Utils.h"],
    copts = [
        "-ObjC++",
        "-std=c++20",
        "-Xclang=-fno-cxx-modules",
    ],
    module_name = "MPPImageUtils",
    deps = [
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:image_format_cc_proto",
        "//mediapipe_custom/framework/formats:image_frame",
        "//mediapipe_custom/tasks/ios/common:MPPCommon",
        "//mediapipe_custom/tasks/ios/common/utils:MPPCommonUtils",
        "//mediapipe_custom/tasks/ios/vision/core:MPPImage",
        "//third_party/apple_frameworks:Accelerate",
        "//third_party/apple_frameworks:CoreGraphics",
        "//third_party/apple_frameworks:CoreImage",
        "//third_party/apple_frameworks:CoreVideo",
        "//third_party/apple_frameworks:Foundation",
    ],
)
