# This contains the MediaPipe Language Detector Task.

load("@npm//@bazel/jasmine:index.bzl", "jasmine_node_test")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("//mediapipe_custom/framework/port:build_config.bzl", "mediapipe_ts_declaration", "mediapipe_ts_library")

package(default_visibility = ["//mediapipe_custom/tasks:internal"])

licenses(["notice"])

mediapipe_ts_library(
    name = "language_detector",
    srcs = ["language_detector.ts"],
    visibility = ["//visibility:public"],
    deps = [
        ":language_detector_types",
        "//mediapipe_custom/framework:calculator_jspb_proto",
        "//mediapipe_custom/framework:calculator_options_jspb_proto",
        "//mediapipe_custom/tasks/cc/components/containers/proto:classifications_jspb_proto",
        "//mediapipe_custom/tasks/cc/core/proto:base_options_jspb_proto",
        "//mediapipe_custom/tasks/cc/text/text_classifier/proto:text_classifier_graph_options_jspb_proto",
        "//mediapipe_custom/tasks/web/components/containers:category",
        "//mediapipe_custom/tasks/web/components/containers:classification_result",
        "//mediapipe_custom/tasks/web/components/processors:classifier_options",
        "//mediapipe_custom/tasks/web/components/processors:classifier_result",
        "//mediapipe_custom/tasks/web/core",
        "//mediapipe_custom/tasks/web/core:classifier_options",
        "//mediapipe_custom/tasks/web/core:task_runner",
        "//mediapipe_custom/web/graph_runner:graph_runner_ts",
    ],
)

mediapipe_ts_declaration(
    name = "language_detector_types",
    srcs = [
        "language_detector_options.d.ts",
        "language_detector_result.d.ts",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/tasks/web/components/containers:category",
        "//mediapipe_custom/tasks/web/components/containers:classification_result",
        "//mediapipe_custom/tasks/web/core",
        "//mediapipe_custom/tasks/web/core:classifier_options",
    ],
)

mediapipe_ts_library(
    name = "language_detector_test_lib",
    testonly = True,
    srcs = [
        "language_detector_test.ts",
    ],
    deps = [
        ":language_detector",
        "//mediapipe_custom/framework:calculator_jspb_proto",
        "//mediapipe_custom/framework/formats:classification_jspb_proto",
        "//mediapipe_custom/tasks/cc/components/containers/proto:classifications_jspb_proto",
        "//mediapipe_custom/tasks/web/core",
        "//mediapipe_custom/tasks/web/core:task_runner_test_utils",
    ],
)

jasmine_node_test(
    name = "language_detector_test",
    srcs = [":language_detector_test_lib"],
)
