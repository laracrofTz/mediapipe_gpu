# This contains the MediaPipe Hand Landmarker Task.
#
# This task takes video frames and outputs synchronized frames along with
# the detection results for one or more holistic categories, using Hand Landmarker.

load("@npm//@bazel/jasmine:index.bzl", "jasmine_node_test")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("//mediapipe_custom/framework/port:build_config.bzl", "mediapipe_ts_declaration", "mediapipe_ts_library")

package(default_visibility = ["//mediapipe_custom/tasks:internal"])

licenses(["notice"])

mediapipe_ts_library(
    name = "holistic_landmarker",
    srcs = [
        "holistic_landmarker.ts",
        "holistic_landmarker_result.ts",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":holistic_landmarker_connections",
        ":holistic_landmarker_types",
        "//mediapipe_custom/framework:calculator_jspb_proto",
        "//mediapipe_custom/framework:calculator_options_jspb_proto",
        "//mediapipe_custom/framework/formats:classification_jspb_proto",
        "//mediapipe_custom/framework/formats:landmark_jspb_proto",
        "//mediapipe_custom/tasks/cc/core/proto:base_options_jspb_proto",
        "//mediapipe_custom/tasks/cc/vision/face_detector/proto:face_detector_graph_options_jspb_proto",
        "//mediapipe_custom/tasks/cc/vision/face_landmarker/proto:face_landmarks_detector_graph_options_jspb_proto",
        "//mediapipe_custom/tasks/cc/vision/hand_landmarker/proto:hand_landmarks_detector_graph_options_jspb_proto",
        "//mediapipe_custom/tasks/cc/vision/hand_landmarker/proto:hand_roi_refinement_graph_options_jspb_proto",
        "//mediapipe_custom/tasks/cc/vision/holistic_landmarker/proto:holistic_landmarker_graph_options_jspb_proto",
        "//mediapipe_custom/tasks/cc/vision/pose_detector/proto:pose_detector_graph_options_jspb_proto",
        "//mediapipe_custom/tasks/cc/vision/pose_landmarker/proto:pose_landmarks_detector_graph_options_jspb_proto",
        "//mediapipe_custom/tasks/web/components/containers:category",
        "//mediapipe_custom/tasks/web/components/containers:classification_result",
        "//mediapipe_custom/tasks/web/components/containers:landmark",
        "//mediapipe_custom/tasks/web/components/processors:classifier_result",
        "//mediapipe_custom/tasks/web/components/processors:landmark_result",
        "//mediapipe_custom/tasks/web/core",
        "//mediapipe_custom/tasks/web/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/web/vision/core:mask",
        "//mediapipe_custom/tasks/web/vision/core:vision_task_runner",
        "//mediapipe_custom/web/graph_runner:graph_runner_ts",
    ],
)

mediapipe_ts_declaration(
    name = "holistic_landmarker_types",
    srcs = ["holistic_landmarker_options.d.ts"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/tasks/web/components/containers:category",
        "//mediapipe_custom/tasks/web/components/containers:classification_result",
        "//mediapipe_custom/tasks/web/components/containers:landmark",
        "//mediapipe_custom/tasks/web/components/containers:matrix",
        "//mediapipe_custom/tasks/web/core",
        "//mediapipe_custom/tasks/web/vision/core:vision_task_options",
    ],
)

mediapipe_ts_library(
    name = "holistic_landmarker_test_lib",
    testonly = True,
    srcs = [
        "holistic_landmarker_test.ts",
    ],
    deps = [
        ":holistic_landmarker",
        ":holistic_landmarker_types",
        "//mediapipe_custom/framework:calculator_jspb_proto",
        "//mediapipe_custom/framework/formats:classification_jspb_proto",
        "//mediapipe_custom/tasks/cc/vision/holistic_landmarker/proto:holistic_landmarker_graph_options_jspb_proto",
        "//mediapipe_custom/tasks/web/components/processors:landmark_result",
        "//mediapipe_custom/tasks/web/core",
        "//mediapipe_custom/tasks/web/core:task_runner_test_utils",
        "//mediapipe_custom/tasks/web/vision/core:vision_task_runner",
    ],
)

jasmine_node_test(
    name = "holistic_landmarker_test",
    srcs = [":holistic_landmarker_test_lib"],
    tags = ["nomsan"],
)

mediapipe_ts_library(
    name = "holistic_landmarker_connections",
    deps = [
        "//mediapipe_custom/tasks/web/vision/face_landmarker:face_landmarks_connections",
        "//mediapipe_custom/tasks/web/vision/hand_landmarker:hand_landmarks_connections",
        "//mediapipe_custom/tasks/web/vision/pose_landmarker:pose_landmarks_connections",
    ],
)
