# This package contains options shared by all MediaPipe Tasks for Web.

load("@npm//@bazel/jasmine:index.bzl", "jasmine_node_test")
load("//mediapipe_custom/framework/port:build_config.bzl", "mediapipe_ts_library")

package(default_visibility = ["//mediapipe_custom/tasks:internal"])

mediapipe_ts_library(
    name = "classifier_options",
    srcs = ["classifier_options.ts"],
    deps = [
        "//mediapipe_custom/tasks/cc/components/processors/proto:classifier_options_jspb_proto",
        "//mediapipe_custom/tasks/web/core:classifier_options",
    ],
)

mediapipe_ts_library(
    name = "classifier_options_test_lib",
    testonly = True,
    srcs = ["classifier_options_test.ts"],
    deps = [
        ":classifier_options",
        "//mediapipe_custom/tasks/cc/components/processors/proto:classifier_options_jspb_proto",
        "//mediapipe_custom/tasks/web/core:classifier_options",
    ],
)

jasmine_node_test(
    name = "classifier_options_test",
    srcs = [":classifier_options_test_lib"],
)

mediapipe_ts_library(
    name = "classifier_result",
    srcs = ["classifier_result.ts"],
    deps = [
        "//mediapipe_custom/framework/formats:classification_jspb_proto",
        "//mediapipe_custom/tasks/cc/components/containers/proto:classifications_jspb_proto",
        "//mediapipe_custom/tasks/web/components/containers:classification_result",
        "//mediapipe_custom/tasks/web/components/utils:numeric_conversion",
    ],
)

mediapipe_ts_library(
    name = "classifier_result_test_lib",
    testonly = True,
    srcs = ["classifier_result_test.ts"],
    deps = [
        ":classifier_result",
        "//mediapipe_custom/framework/formats:classification_jspb_proto",
        "//mediapipe_custom/tasks/cc/components/containers/proto:classifications_jspb_proto",
    ],
)

jasmine_node_test(
    name = "classifier_result_test",
    srcs = [":classifier_result_test_lib"],
)

mediapipe_ts_library(
    name = "detection_result",
    srcs = ["detection_result.ts"],
    deps = [
        "//mediapipe_custom/framework/formats:detection_jspb_proto",
        "//mediapipe_custom/tasks/web/components/containers:detection_result",
    ],
)

mediapipe_ts_library(
    name = "detection_result_test_lib",
    testonly = True,
    srcs = ["detection_result_test.ts"],
    deps = [
        ":detection_result",
        "//mediapipe_custom/framework/formats:detection_jspb_proto",
        "//mediapipe_custom/framework/formats:location_data_jspb_proto",
        "//mediapipe_custom/tasks/web/components/containers:detection_result",
    ],
)

mediapipe_ts_library(
    name = "embedder_result",
    srcs = ["embedder_result.ts"],
    deps = [
        "//mediapipe_custom/tasks/cc/components/containers/proto:embeddings_jspb_proto",
        "//mediapipe_custom/tasks/web/components/containers:embedding_result",
        "//mediapipe_custom/tasks/web/components/utils:numeric_conversion",
    ],
)

mediapipe_ts_library(
    name = "embedder_result_test_lib",
    testonly = True,
    srcs = ["embedder_result_test.ts"],
    deps = [
        ":embedder_result",
        "//mediapipe_custom/tasks/cc/components/containers/proto:embeddings_jspb_proto",
    ],
)

jasmine_node_test(
    name = "embedder_result_test",
    srcs = [":embedder_result_test_lib"],
)

mediapipe_ts_library(
    name = "embedder_options",
    srcs = ["embedder_options.ts"],
    deps = [
        "//mediapipe_custom/tasks/cc/components/processors/proto:embedder_options_jspb_proto",
        "//mediapipe_custom/tasks/web/core:embedder_options",
    ],
)

mediapipe_ts_library(
    name = "embedder_options_test_lib",
    testonly = True,
    srcs = ["embedder_options_test.ts"],
    deps = [
        ":embedder_options",
        "//mediapipe_custom/tasks/cc/components/processors/proto:embedder_options_jspb_proto",
        "//mediapipe_custom/tasks/web/core:embedder_options",
    ],
)

jasmine_node_test(
    name = "embedder_options_test",
    srcs = [":embedder_options_test_lib"],
)

mediapipe_ts_library(
    name = "landmark_result",
    srcs = [
        "landmark_result.ts",
        "landmark_result_test_lib.ts",
    ],
    deps = [
        "//mediapipe_custom/framework/formats:landmark_jspb_proto",
        "//mediapipe_custom/tasks/web/components/containers:landmark",
    ],
)

mediapipe_ts_library(
    name = "landmark_result_test_lib",
    testonly = True,
    srcs = ["landmark_result_test.ts"],
    deps = [":landmark_result"],
)

jasmine_node_test(
    name = "landmark_result_test",
    srcs = [":landmark_result_test_lib"],
)
