# Copyright 2020 The MediaPipe Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

load("@org_tensorflow//tensorflow:tensorflow.bzl", "pybind_extension")

licenses(["notice"])  # Apache 2.0

package(default_visibility = ["//visibility:public"])

pybind_extension(
    name = "_framework_bindings",
    srcs = ["framework_bindings.cc"],
    linkopts = select({
        "//third_party:opencv_source_build": [],
        "//conditions:default": [
            "-lopencv_core",
            "-lopencv_imgproc",
            "-lopencv_highgui",
            "-lopencv_video",
            "-lopencv_features2d",
            "-lopencv_calib3d",
            "-lopencv_imgcodecs",
        ],
    }),
    module_name = "_framework_bindings",
    deps = [
        ":builtin_calculators",
        ":builtin_task_graphs",
        "//mediapipe_custom/python/pybind:calculator_graph",
        "//mediapipe_custom/python/pybind:image",
        "//mediapipe_custom/python/pybind:image_frame",
        "//mediapipe_custom/python/pybind:matrix",
        "//mediapipe_custom/python/pybind:model_ckpt_util",
        "//mediapipe_custom/python/pybind:packet",
        "//mediapipe_custom/python/pybind:packet_creator",
        "//mediapipe_custom/python/pybind:packet_getter",
        "//mediapipe_custom/python/pybind:resource_util",
        "//mediapipe_custom/python/pybind:timestamp",
        "//mediapipe_custom/python/pybind:validated_graph_config",
        "//mediapipe_custom/tasks/python/core/pybind:task_runner",
        "@com_google_absl//absl/strings:str_format",
        "@stblib//:stb_image",
        # Type registration.
        "//mediapipe_custom/framework:basic_types_registration",
        "//mediapipe_custom/framework/formats:body_rig_registration",
        "//mediapipe_custom/framework/formats:classification_registration",
        "//mediapipe_custom/framework/formats:detection_registration",
        "//mediapipe_custom/framework/formats:landmark_registration",
        "//mediapipe_custom/framework/formats:rect_registration",
        "//mediapipe_custom/modules/objectron/calculators:annotation_registration",
        "//mediapipe_custom/tasks/cc/vision/face_geometry/proto:face_geometry_registration",
    ],
)

cc_library(
    name = "builtin_calculators",
    deps = [
        "//mediapipe_custom/calculators/core:gate_calculator",
        "//mediapipe_custom/calculators/core:pass_through_calculator",
        "//mediapipe_custom/calculators/core:side_packet_to_stream_calculator",
        "//mediapipe_custom/calculators/core:split_proto_list_calculator",
        "//mediapipe_custom/calculators/core:string_to_int_calculator",
        "//mediapipe_custom/calculators/image:image_transformation_calculator",
        "//mediapipe_custom/calculators/util:detection_unique_id_calculator",
        "//mediapipe_custom/modules/face_detection:face_detection_full_range_cpu",
        "//mediapipe_custom/modules/face_detection:face_detection_short_range_cpu",
        "//mediapipe_custom/modules/face_landmark:face_landmark_front_cpu",
        "//mediapipe_custom/modules/hand_landmark:hand_landmark_tracking_cpu",
        "//mediapipe_custom/modules/holistic_landmark:holistic_landmark_cpu",
        "//mediapipe_custom/modules/objectron:objectron_cpu",
        "//mediapipe_custom/modules/palm_detection:palm_detection_cpu",
        "//mediapipe_custom/modules/pose_detection:pose_detection_cpu",
        "//mediapipe_custom/modules/pose_landmark:pose_landmark_by_roi_cpu",
        "//mediapipe_custom/modules/pose_landmark:pose_landmark_cpu",
        "//mediapipe_custom/modules/selfie_segmentation:selfie_segmentation_cpu",
    ],
)

cc_library(
    name = "builtin_task_graphs",
    deps = [
        "//mediapipe_custom/tasks/cc/audio/audio_classifier:audio_classifier_graph",
        "//mediapipe_custom/tasks/cc/audio/audio_embedder:audio_embedder_graph",
        "//mediapipe_custom/tasks/cc/text/text_classifier:text_classifier_graph",
        "//mediapipe_custom/tasks/cc/text/text_embedder:text_embedder_graph",
        "//mediapipe_custom/tasks/cc/vision/face_detector:face_detector_graph",
        "//mediapipe_custom/tasks/cc/vision/face_landmarker:face_landmarker_graph",
        "//mediapipe_custom/tasks/cc/vision/face_stylizer:face_stylizer_graph",
        "//mediapipe_custom/tasks/cc/vision/gesture_recognizer:gesture_recognizer_graph",
        "//mediapipe_custom/tasks/cc/vision/holistic_landmarker:holistic_landmarker_graph",
        "//mediapipe_custom/tasks/cc/vision/image_classifier:image_classifier_graph",
        "//mediapipe_custom/tasks/cc/vision/image_embedder:image_embedder_graph",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter:image_segmenter_graph",
        "//mediapipe_custom/tasks/cc/vision/interactive_segmenter:interactive_segmenter_graph",
        "//mediapipe_custom/tasks/cc/vision/object_detector:object_detector_graph",
        "//mediapipe_custom/tasks/cc/vision/pose_landmarker:pose_landmarker_graph",
    ],
)

py_library(
    name = "packet_creator",
    srcs = ["packet_creator.py"],
    srcs_version = "PY3",
    deps = [
        ":_framework_bindings",
    ],
)

py_library(
    name = "packet_getter",
    srcs = ["packet_getter.py"],
    srcs_version = "PY3",
    deps = [
        ":_framework_bindings",
    ],
)

py_library(
    name = "solution_base",
    srcs = ["solution_base.py"],
    srcs_version = "PY3",
    visibility = [
        "//mediapipe_custom/python:__subpackages__",
    ],
    deps = [
        ":_framework_bindings",
        ":packet_creator",
        ":packet_getter",
        "//mediapipe_custom/calculators/core:constant_side_packet_calculator_py_pb2",
        "//mediapipe_custom/calculators/image:image_transformation_calculator_py_pb2",
        "//mediapipe_custom/calculators/tensor:tensors_to_detections_calculator_py_pb2",
        "//mediapipe_custom/calculators/util:landmarks_smoothing_calculator_py_pb2",
        "//mediapipe_custom/calculators/util:logic_calculator_py_pb2",
        "//mediapipe_custom/calculators/util:thresholding_calculator_py_pb2",
        "//mediapipe_custom/framework:calculator_py_pb2",
        "//mediapipe_custom/framework/formats:classification_py_pb2",
        "//mediapipe_custom/framework/formats:detection_py_pb2",
        "//mediapipe_custom/framework/formats:landmark_py_pb2",
        "//mediapipe_custom/framework/formats:rect_py_pb2",
        "//mediapipe_custom/modules/objectron/calculators:annotation_py_pb2",
        "//mediapipe_custom/modules/objectron/calculators:lift_2d_frame_annotation_to_3d_calculator_py_pb2",
        "@com_google_protobuf//:protobuf_python",
    ],
)

py_test(
    name = "calculator_graph_test",
    srcs = ["calculator_graph_test.py"],
    python_version = "PY3",
    srcs_version = "PY3",
    deps = [
        ":_framework_bindings",
        ":packet_creator",
        ":packet_getter",
        "//mediapipe_custom/framework:calculator_py_pb2",
    ],
)

py_test(
    name = "image_test",
    srcs = ["image_test.py"],
    python_version = "PY3",
    srcs_version = "PY3",
    deps = [
        ":_framework_bindings",
    ],
)

py_test(
    name = "image_frame_test",
    srcs = ["image_frame_test.py"],
    python_version = "PY3",
    srcs_version = "PY3",
    deps = [
        ":_framework_bindings",
    ],
)

py_test(
    name = "packet_test",
    srcs = ["packet_test.py"],
    python_version = "PY3",
    srcs_version = "PY3",
    deps = [
        ":_framework_bindings",
        ":packet_creator",
        ":packet_getter",
        "//mediapipe_custom/framework/formats:detection_py_pb2",
    ],
)

py_test(
    name = "timestamp_test",
    srcs = ["timestamp_test.py"],
    python_version = "PY3",
    srcs_version = "PY3",
    deps = [
        ":_framework_bindings",
    ],
)

py_test(
    name = "solution_base_test",
    srcs = ["solution_base_test.py"],
    python_version = "PY3",
    srcs_version = "PY3",
    deps = [
        ":solution_base",
        "//file/google_src",
        "//file/localfile",
        "//mediapipe_custom/calculators/core:gate_calculator",
        "//mediapipe_custom/calculators/core:pass_through_calculator",
        "//mediapipe_custom/calculators/core:side_packet_to_stream_calculator",
        "//mediapipe_custom/calculators/image:image_transformation_calculator",
        "//mediapipe_custom/calculators/util:detection_unique_id_calculator",
        "//mediapipe_custom/calculators/util:to_image_calculator",
        "//mediapipe_custom/framework:calculator_py_pb2",
        "//mediapipe_custom/framework/formats:detection_py_pb2",
        "@com_google_protobuf//:protobuf_python",
    ],
)
