load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("//mediapipe_custom/tasks/metadata:build_defs.bzl", "stamp_metadata_parser_version")

package(
    default_visibility = ["//mediapipe_custom/tasks:internal"],
    licenses = ["notice"],  # Apache 2.0
)

stamp_metadata_parser_version(
    name = "metadata_parser_h",
    srcs = ["metadata_parser.h.template"],
    outs = ["metadata_parser.h"],
)

cc_library(
    name = "metadata_extractor",
    srcs = ["metadata_extractor.cc"],
    hdrs = [
        "metadata_extractor.h",
        "metadata_parser_h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":metadata_version_utils",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/metadata/utils:zip_utils",
        "//mediapipe_custom/tasks/metadata:metadata_schema_cc",
        "@com_google_absl//absl/cleanup",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
        "@flatbuffers//:runtime_cc",
        "@org_tensorflow//tensorflow/lite/schema:schema_fbs",
    ],
)

cc_library(
    name = "metadata_version",
    srcs = ["metadata_version.cc"],
    hdrs = [
        "metadata_version.h",
        ":metadata_parser_h",
    ],
    deps = [
        "//mediapipe_custom/tasks/metadata:metadata_schema_cc",
        "@com_google_absl//absl/strings",
        "@flatbuffers//:runtime_cc",
        "@org_tensorflow//tensorflow/lite/c:common",
        "@org_tensorflow//tensorflow/lite/kernels/internal:compatibility",
        "@org_tensorflow//tensorflow/lite/tools:logging",
    ],
)

cc_library(
    name = "metadata_populator",
    srcs = ["metadata_populator.cc"],
    hdrs = ["metadata_populator.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/metadata/utils:zip_writable_mem_file",
        "//mediapipe_custom/tasks/metadata:metadata_schema_cc",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@flatbuffers//:runtime_cc",
        "@org_tensorflow//tensorflow/lite/schema:schema_fbs",
        "@zlib//:zlib_minizip",
    ],
)

cc_library(
    name = "metadata_version_utils",
    srcs = ["metadata_version_utils.cc"],
    hdrs = ["metadata_version_utils.h"],
    deps = ["@com_google_absl//absl/strings"],
)
