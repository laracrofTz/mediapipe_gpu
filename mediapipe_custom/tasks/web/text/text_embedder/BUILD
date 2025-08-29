# This contains the MediaPipe Text Embedder Task.
#
# This task takes text input and performs embedding
#

load("@npm//@bazel/jasmine:index.bzl", "jasmine_node_test")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("//mediapipe_custom/framework/port:build_config.bzl", "mediapipe_ts_declaration", "mediapipe_ts_library")

package(default_visibility = ["//mediapipe_custom/tasks:internal"])

licenses(["notice"])

mediapipe_ts_library(
    name = "text_embedder",
    srcs = ["text_embedder.ts"],
    visibility = ["//visibility:public"],
    deps = [
        ":text_embedder_types",
        "//mediapipe_custom/framework:calculator_jspb_proto",
        "//mediapipe_custom/framework:calculator_options_jspb_proto",
        "//mediapipe_custom/tasks/cc/components/containers/proto:embeddings_jspb_proto",
        "//mediapipe_custom/tasks/cc/core/proto:base_options_jspb_proto",
        "//mediapipe_custom/tasks/cc/text/text_embedder/proto:text_embedder_graph_options_jspb_proto",
        "//mediapipe_custom/tasks/web/components/containers:embedding_result",
        "//mediapipe_custom/tasks/web/components/processors:embedder_options",
        "//mediapipe_custom/tasks/web/components/processors:embedder_result",
        "//mediapipe_custom/tasks/web/components/utils:cosine_similarity",
        "//mediapipe_custom/tasks/web/core",
        "//mediapipe_custom/tasks/web/core:embedder_options",
        "//mediapipe_custom/tasks/web/core:task_runner",
        "//mediapipe_custom/web/graph_runner:graph_runner_ts",
    ],
)

mediapipe_ts_declaration(
    name = "text_embedder_types",
    srcs = [
        "text_embedder_options.d.ts",
        "text_embedder_result.d.ts",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/tasks/web/components/containers:embedding_result",
        "//mediapipe_custom/tasks/web/core",
        "//mediapipe_custom/tasks/web/core:embedder_options",
    ],
)

mediapipe_ts_library(
    name = "text_embedder_test_lib",
    testonly = True,
    srcs = [
        "text_embedder_test.ts",
    ],
    deps = [
        ":text_embedder",
        "//mediapipe_custom/framework:calculator_jspb_proto",
        "//mediapipe_custom/tasks/cc/components/containers/proto:embeddings_jspb_proto",
        "//mediapipe_custom/tasks/web/core",
        "//mediapipe_custom/tasks/web/core:task_runner_test_utils",
    ],
)

jasmine_node_test(
    name = "text_embedder_test",
    srcs = [":text_embedder_test_lib"],
)
