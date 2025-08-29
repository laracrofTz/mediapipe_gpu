load("//mediapipe_custom/framework/port:build_config.bzl", "mediapipe_proto_library")

package(default_visibility = ["//mediapipe_custom/framework/api3:__subpackages__"])

licenses(["notice"])

mediapipe_proto_library(
    name = "foo_proto",
    testonly = True,
    srcs = ["foo.proto"],
)

mediapipe_proto_library(
    name = "bar_proto",
    testonly = True,
    srcs = ["bar.proto"],
)

mediapipe_proto_library(
    name = "generator_proto",
    srcs = ["generator.proto"],
    visibility = ["//mediapipe_custom:__subpackages__"],
    deps = [
        "//mediapipe_custom/framework:packet_generator_proto",
    ],
)

mediapipe_proto_library(
    name = "multiplier_proto",
    testonly = True,
    srcs = ["multiplier.proto"],
)
