# This package contains options shared by all MediaPipe Audio Tasks for Web.

load("//mediapipe_custom/framework/port:build_config.bzl", "mediapipe_ts_library")

package(default_visibility = ["//mediapipe_custom/tasks:internal"])

mediapipe_ts_library(
    name = "audio_task_runner",
    srcs = ["audio_task_runner.ts"],
    deps = [
        "//mediapipe_custom/tasks/web/core",
        "//mediapipe_custom/tasks/web/core:task_runner",
        "//mediapipe_custom/web/graph_runner:graph_runner_ts",
    ],
)
