load("//mediapipe_custom/framework/tool:mediapipe_graph.bzl", "mediapipe_binary_graph")

package(default_visibility = ["//visibility:private"])

licenses(["notice"])

cc_library(
    name = "CFHolder",
    # Header is excluded on non-ios so you can still build :all.
    hdrs = select({
        "//mediapipe_custom:apple": ["CFHolder.h"],
        "//conditions:default": [],
    }),
    features = ["layering_check"],
    visibility = ["//mediapipe_custom/framework:mediapipe_internal"],
)

cc_library(
    name = "util",
    srcs = ["util.cc"],
    hdrs = ["util.h"],
    features = [
        "-parse_headers",
        "layering_check",
    ],
    linkopts = [
        "-framework Accelerate",
        "-framework CoreFoundation",
        "-framework CoreGraphics",
        "-framework CoreVideo",
    ],
    visibility = ["//mediapipe_custom/framework:mediapipe_internal"],
    deps = [
        ":CFHolder",
        "//mediapipe_custom/framework:packet",
        "//mediapipe_custom/framework/formats:image_frame",
        "//mediapipe_custom/framework/port:logging",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:source_location",
        "//mediapipe_custom/framework/port:status",
        "@com_google_absl//absl/base:core_headers",
        "@com_google_absl//absl/log:absl_check",
        "@com_google_absl//absl/log:absl_log",
        "@com_google_absl//absl/memory",
    ],
)

objc_library(
    name = "Weakify",
    hdrs = ["Weakify.h"],
    visibility = ["//mediapipe_custom/framework:mediapipe_internal"],
)

MEDIAPIPE_IOS_SRCS = [
    "MPPGraph.cc",
    "MPPTimestampConverter.cc",
    "NSError+util_status.cc",
]

MEDIAPIPE_IOS_HDRS = [
    "MPPGraph.h",
    "MPPTimestampConverter.h",
    "NSError+util_status.h",
]

cc_library(
    name = "mediapipe_framework_ios",
    srcs = MEDIAPIPE_IOS_SRCS,
    hdrs = MEDIAPIPE_IOS_HDRS,
    copts = [
        "-x objective-c++",
        "-fobjc-arc",  # enable reference-counting
        "-Wno-shorten-64-to-32",
    ],
    # This build rule is public to allow external customers to build their own iOS apps.
    visibility = ["//visibility:public"],
    deps = [
        ":CFHolder",
        ":util",
        "//mediapipe_custom/framework:calculator_framework",
        "//mediapipe_custom/framework:mediapipe_profiling",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/port:map_util",
        "//mediapipe_custom/framework/port:ret_check",
        "//mediapipe_custom/framework/port:source_location",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/framework/port:statusor",
        "//mediapipe_custom/framework/port:threadpool",
        "//mediapipe_custom/gpu:gl_base",
        "//mediapipe_custom/gpu:gpu_buffer",
        "//mediapipe_custom/gpu:gpu_shared_data_internal",
        "//mediapipe_custom/gpu:graph_support",
        "//mediapipe_custom/gpu:metal_shared_resources",
        "//mediapipe_custom/gpu:pixel_buffer_pool_util",
        "//mediapipe_custom/util:cpu_util",
        "//third_party/apple_frameworks:AVFoundation",
        "//third_party/apple_frameworks:Accelerate",
        "@com_google_absl//absl/base:core_headers",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/synchronization",
        "@google_toolbox_for_mac//:GTM_Defines",
    ],
    alwayslink = 1,
)

objc_library(
    name = "mediapipe_input_sources_ios",
    srcs = [
        "MPPInputSource.m",
        "MPPPlayerInputSource.m",
    ] + select({
        "//mediapipe_custom:ios": [
            "MPPCameraInputSource.m",
            "MPPDisplayLinkWeakTarget.m",
        ],
        "//conditions:default": [],
    }),
    hdrs = [
        "MPPInputSource.h",
        "MPPPlayerInputSource.h",
    ] + select({
        "//mediapipe_custom:ios": [
            "MPPCameraInputSource.h",
            "MPPDisplayLinkWeakTarget.h",
        ],
        "//conditions:default": [],
    }),
    # This build rule is public to allow external customers to build their own iOS apps.
    visibility = ["//visibility:public"],
    deps = [
        "//third_party/apple_frameworks:AVFoundation",
        "//third_party/apple_frameworks:CoreAudio",
        "//third_party/apple_frameworks:CoreVideo",
        "//third_party/apple_frameworks:Foundation",
        "//third_party/apple_frameworks:MediaToolbox",
    ],
)

objc_library(
    name = "mediapipe_gl_view_renderer",
    srcs = [
        "MPPGLViewRenderer.mm",
    ],
    hdrs = [
        "MPPGLViewRenderer.h",
    ],
    copts = [
        "-Wno-shorten-64-to-32",
    ],
    visibility = ["//mediapipe_custom/framework:mediapipe_internal"],
    deps = [
        ":mediapipe_framework_ios",
        "//mediapipe_custom/gpu:gl_calculator_helper",
        "//mediapipe_custom/gpu:gl_quad_renderer",
        "//mediapipe_custom/gpu:gl_simple_shaders",
        "//third_party/apple_frameworks:Foundation",
        "//third_party/apple_frameworks:GLKit",
    ],
)

objc_library(
    name = "mediapipe_layer_renderer",
    srcs = [
        "MPPLayerRenderer.m",
    ],
    hdrs = [
        "MPPLayerRenderer.h",
    ],
    copts = [
        "-Wno-shorten-64-to-32",
    ],
    # This build rule is public to allow external customers to build their own iOS apps.
    visibility = ["//visibility:public"],
    deps = [
        ":mediapipe_framework_ios",
        ":mediapipe_gl_view_renderer",
        "//mediapipe_custom/gpu:gl_calculator_helper",
        "//third_party/apple_frameworks:Foundation",
        "//third_party/apple_frameworks:GLKit",
    ],
)

objc_library(
    name = "CGImageRefUtils",
    srcs = [
        "CGImageRefUtils.mm",
    ],
    hdrs = [
        "CGImageRefUtils.h",
    ],
    copts = [
        "-Wno-shorten-64-to-32",
    ],
    visibility = ["//mediapipe_custom/framework:mediapipe_internal"],
    deps = [
        ":mediapipe_framework_ios",
        "//third_party/apple_frameworks:CoreVideo",
        "//third_party/apple_frameworks:Foundation",
        "@com_google_absl//absl/strings",
    ],
)

objc_library(
    name = "mediapipe_audio_util",
    srcs = ["MediaPipeAudioUtil.mm"],
    hdrs = ["MediaPipeAudioUtil.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/framework/formats:matrix",
        "//mediapipe_custom/framework/port:statusor",
        "//third_party/apple_frameworks:AVFoundation",
        "//third_party/apple_frameworks:CoreAudio",
        "//third_party/apple_frameworks:CoreMedia",
        "@eigen//:eigen3",
    ],
)

objc_library(
    name = "MPPGraphTestBase",
    testonly = True,
    srcs = [
        "MPPGraphTestBase.mm",
    ],
    hdrs = [
        "MPPGraphTestBase.h",
    ],
    copts = [
        "-Wno-shorten-64-to-32",
    ],
    visibility = ["//mediapipe_custom/framework:mediapipe_internal"],
    deps = [
        ":CGImageRefUtils",
        ":Weakify",
        ":mediapipe_framework_ios",
        "//mediapipe_custom/framework:calculator_framework",
        "//third_party/apple_frameworks:AVFoundation",
        "//third_party/apple_frameworks:Accelerate",
        "//third_party/apple_frameworks:CoreGraphics",
        "//third_party/apple_frameworks:CoreMedia",
        "//third_party/apple_frameworks:CoreVideo",
        "//third_party/apple_frameworks:GLKit",
        "//third_party/apple_frameworks:OpenGLES",
        "//third_party/apple_frameworks:QuartzCore",
        "//third_party/apple_frameworks:UIKit",
    ],
)

objc_library(
    name = "mediapipe_framework_ios_testLib",
    testonly = True,
    srcs = [
        "CFHolderTests.mm",
        "MPPDisplayLinkWeakTargetTests.mm",
        "MPPGraphTests.mm",
        "MediaPipeAudioUtilTests.mm",
    ],
    copts = [
        "-Wno-shorten-64-to-32",
    ],
    data = [
        "testdata/googlelogo_color_272x92dp.png",
    ],
    visibility = ["//mediapipe_custom/framework:mediapipe_internal"],
    deps = [
        ":CGImageRefUtils",
        ":MPPGraphTestBase",
        ":Weakify",
        ":mediapipe_audio_util",
        ":mediapipe_framework_ios",
        ":mediapipe_input_sources_ios",
        "//mediapipe_custom/calculators/core:pass_through_calculator",
        "//third_party/apple_frameworks:AVFoundation",
        "//third_party/apple_frameworks:Accelerate",
        "//third_party/apple_frameworks:CoreAudio",
        "//third_party/apple_frameworks:CoreGraphics",
        "//third_party/apple_frameworks:CoreMedia",
        "//third_party/apple_frameworks:CoreVideo",
        "//third_party/apple_frameworks:GLKit",
        "//third_party/apple_frameworks:QuartzCore",
        "//third_party/apple_frameworks:UIKit",
    ],
)

[
    mediapipe_binary_graph(
        name = graph.split("/")[-1].rsplit(".", 1)[0] + "_graph",
        graph = graph,
        output_name = "%s.binarypb" % graph.split("/")[-1].rsplit(".", 1)[0],
        visibility = ["//mediapipe_custom/framework:mediapipe_internal"],
    )
    for graph in glob(["testdata/*.pbtxt"])
]

exports_files(
    [
        "testdata/googlelogo_color_272x92dp.png",
        "testdata/googlelogo_color_272x92dp_luminance.png",
        "testdata/sergey.png",
    ],
    visibility = [
        "//mediapipe_custom:__subpackages__",
    ],
)
