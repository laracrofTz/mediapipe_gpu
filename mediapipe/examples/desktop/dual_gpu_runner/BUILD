cc_binary(
    name = "dual_gpu_runner",
    srcs = ["dual_gpu_runner.cc"],
    deps = [
        "//mediapipe/framework:calculator_graph",
        "//mediapipe/gpu:gpu",
        "@com_google_absl//absl/status:statusor",
    ],
    copts = [
        "-DMESA_EGL_NO_X11_HEADERS",  
        "-DEGL_NO_X11",
    ],
    linkopts = ["-lEGL", "-lGLESv2"],
)
