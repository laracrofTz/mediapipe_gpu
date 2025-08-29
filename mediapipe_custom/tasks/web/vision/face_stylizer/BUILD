# This contains the MediaPipe Face Stylizer Task.

load("@npm//@bazel/jasmine:index.bzl", "jasmine_node_test")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("//mediapipe_custom/framework/port:build_config.bzl", "mediapipe_ts_declaration", "mediapipe_ts_library")

package(default_visibility = ["//mediapipe_custom/tasks:internal"])

licenses(["notice"])

mediapipe_ts_library(
    name = "face_stylizer",
    srcs = ["face_stylizer.ts"],
    deps = [
        ":face_stylizer_types",
        "//mediapipe_custom/framework:calculator_jspb_proto",
        "//mediapipe_custom/framework:calculator_options_jspb_proto",
        "//mediapipe_custom/tasks/cc/core/proto:base_options_jspb_proto",
        "//mediapipe_custom/tasks/cc/vision/face_stylizer/proto:face_stylizer_graph_options_jspb_proto",
        "//mediapipe_custom/tasks/web/core",
        "//mediapipe_custom/tasks/web/vision/core:image",
        "//mediapipe_custom/tasks/web/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/web/vision/core:types",
        "//mediapipe_custom/tasks/web/vision/core:vision_task_runner",
        "//mediapipe_custom/web/graph_runner:graph_runner_ts",
    ],
)

mediapipe_ts_declaration(
    name = "face_stylizer_types",
    srcs = ["face_stylizer_options.d.ts"],
    deps = [
        "//mediapipe_custom/tasks/web/core",
        "//mediapipe_custom/tasks/web/core:classifier_options",
        "//mediapipe_custom/tasks/web/vision/core:vision_task_options",
    ],
)

mediapipe_ts_library(
    name = "face_stylizer_test_lib",
    testonly = True,
    srcs = [
        "face_stylizer_test.ts",
    ],
    deps = [
        ":face_stylizer",
        ":face_stylizer_types",
        "//mediapipe_custom/framework:calculator_jspb_proto",
        "//mediapipe_custom/tasks/web/core",
        "//mediapipe_custom/tasks/web/core:task_runner_test_utils",
        "//mediapipe_custom/web/graph_runner:graph_runner_image_lib_ts",
    ],
)

jasmine_node_test(
    name = "face_stylizer_test",
    srcs = [":face_stylizer_test_lib"],
    tags = ["nomsan"],
)
