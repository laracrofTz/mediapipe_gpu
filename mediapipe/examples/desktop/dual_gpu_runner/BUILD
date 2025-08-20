cc_binary(
    name = "dual_gpu_runner",
    srcs = ["dual_gpu_runner.cc"],
    deps = [
        "//mediapipe/framework:calculator_graph", 
        "//mediapipe/framework/port:status",
        "//mediapipe/framework/port:logging",
        "//mediapipe/gpu:gl_context",
        "//mediapipe/gpu:gpu_service",
        "@com_google_absl//absl/status:statusor",
    ],
    linkopts = ["-lEGL", "-lGLESv2"],
)
