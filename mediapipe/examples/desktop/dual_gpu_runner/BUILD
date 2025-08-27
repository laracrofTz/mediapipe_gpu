load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "dual_gpu_runner",
    srcs = ["dual_gpu_runner.cc"],
    deps = [
        "//mediapipe/framework:calculator_graph",
        "//mediapipe/framework/port:logging",
        "//mediapipe/framework/port:parse_text_proto",
        "//mediapipe/framework/port:status",
        "//mediapipe/framework/port:statusor",
        "//mediapipe/gpu:gl_context",
        "//mediapipe/gpu:gpu_service",
        "//mediapipe/calculators/core:pass_through_calculator",
        "@com_google_absl//absl/status:status",
        "@com_google_absl//absl/status:statusor",
    ],
    copts = [
        "-DEGL_EGLEXT_PROTOTYPES",
        "-DGL_GLEXT_PROTOTYPES",
        "-DMEDIAPIPE_OMIT_EGL_WINDOW_BIT",
    ],
    linkopts = [
        "-lEGL",
        "-lGLESv2",  # libGLESv2 usually contains ES3 entry points
    ],
    visibility = ["//visibility:public"],
)