# This contains the MediaPipe RAG Pipeline

load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("//mediapipe_custom/framework/port:build_config.bzl", "mediapipe_ts_library")

licenses(["notice"])

mediapipe_ts_library(
    name = "rag_pipeline",
    srcs = ["rag_pipeline.ts"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/tasks/web/core",
        "//mediapipe_custom/tasks/web/genai/llm_inference",
        "//mediapipe_custom/web/graph_runner:graph_runner_ts",
        "//mediapipe_custom/web/graph_runner:graph_runner_wasm_file_reference_ts",
    ],
)
