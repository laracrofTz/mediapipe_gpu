# This contains the MediaPipe Image Segmenter Task.

load("@npm//@bazel/jasmine:index.bzl", "jasmine_node_test")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("//mediapipe_custom/framework/port:build_config.bzl", "mediapipe_ts_declaration", "mediapipe_ts_library")

package(default_visibility = ["//mediapipe_custom/tasks:internal"])

licenses(["notice"])

mediapipe_ts_library(
    name = "image_segmenter",
    srcs = [
        "image_segmenter.ts",
        "image_segmenter_result.ts",
    ],
    deps = [
        ":image_segmenter_types",
        "//mediapipe_custom/framework:calculator_jspb_proto",
        "//mediapipe_custom/framework:calculator_options_jspb_proto",
        "//mediapipe_custom/tasks/cc/core/proto:base_options_jspb_proto",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter/calculators:tensors_to_segmentation_calculator_jspb_proto",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter/proto:image_segmenter_graph_options_jspb_proto",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter/proto:segmenter_options_jspb_proto",
        "//mediapipe_custom/tasks/web/core",
        "//mediapipe_custom/tasks/web/core:classifier_options",
        "//mediapipe_custom/tasks/web/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/web/vision/core:mask",
        "//mediapipe_custom/tasks/web/vision/core:vision_task_runner",
        "//mediapipe_custom/util:label_map_jspb_proto",
        "//mediapipe_custom/web/graph_runner:graph_runner_ts",
    ],
)

mediapipe_ts_declaration(
    name = "image_segmenter_types",
    srcs = ["image_segmenter_options.d.ts"],
    deps = ["//mediapipe_custom/tasks/web/vision/core:vision_task_options"],
)

mediapipe_ts_library(
    name = "image_segmenter_test_lib",
    testonly = True,
    srcs = [
        "image_segmenter_test.ts",
    ],
    deps = [
        ":image_segmenter",
        ":image_segmenter_types",
        "//mediapipe_custom/framework:calculator_jspb_proto",
        "//mediapipe_custom/tasks/web/core",
        "//mediapipe_custom/tasks/web/core:task_runner_test_utils",
        "//mediapipe_custom/tasks/web/vision/core:mask",
        "//mediapipe_custom/web/graph_runner:graph_runner_image_lib_ts",
    ],
)

jasmine_node_test(
    name = "image_segmenter_test",
    srcs = [":image_segmenter_test_lib"],
    tags = ["nomsan"],
)
