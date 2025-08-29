load("@rules_cc//cc:cc_test.bzl", "cc_test")

package(
    default_visibility = ["//visibility:private"],
    licenses = ["notice"],  # Apache 2.0
)

cc_test(
    name = "metadata_extractor_test",
    srcs = ["metadata_extractor_test.cc"],
    data = [
        "//mediapipe_custom/tasks/testdata/metadata:data_files",
        "//mediapipe_custom/tasks/testdata/metadata:model_files",
    ],
    deps = [
        "//mediapipe_custom/framework/port:file_helpers",
        "//mediapipe_custom/framework/port:gtest",
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/core:utils",
        "//mediapipe_custom/tasks/cc/metadata:metadata_extractor",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:cord",
        "@com_google_absl//absl/strings:str_format",
    ],
)

cc_test(
    name = "metadata_version_test",
    srcs = ["metadata_version_test.cc"],
    deps = [
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/tasks/cc/metadata:metadata_version",
        "//mediapipe_custom/tasks/metadata:metadata_schema_cc",
        "@flatbuffers//:runtime_cc",
    ],
)

cc_test(
    name = "metadata_parser_test",
    srcs = ["metadata_parser_test.cc"],
    deps = [
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/tasks/cc/metadata:metadata_version",
    ],
)

cc_test(
    name = "metadata_version_utils_test",
    srcs = ["metadata_version_utils_test.cc"],
    deps = [
        "//mediapipe_custom/framework/port:gtest_main",
        "//mediapipe_custom/tasks/cc/metadata:metadata_version_utils",
    ],
)
