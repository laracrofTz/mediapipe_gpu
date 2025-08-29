# Placeholder: load py_test

package(
    default_visibility = [
        "//visibility:public",
    ],
    licenses = ["notice"],  # Apache 2.0
)

py_test(
    name = "metadata_test",
    srcs = ["metadata_test.py"],
    data = ["//mediapipe_custom/tasks/testdata/metadata:data_files"],
    deps = [
        "//mediapipe_custom/tasks/metadata:metadata_schema_py",
        "//mediapipe_custom/tasks/metadata:schema_py",
        "//mediapipe_custom/tasks/python/metadata",
        "//mediapipe_custom/tasks/python/test:test_utils",
        "@flatbuffers//:runtime_py",
        "@mediapipe_pip_deps//:absl_py",
        "@mediapipe_pip_deps//:six",
    ],
)

py_test(
    name = "metadata_parser_test",
    srcs = ["metadata_parser_test.py"],
    deps = [
        "//mediapipe_custom/tasks/python/metadata",
        "@mediapipe_pip_deps//:absl_py",
    ],
)
