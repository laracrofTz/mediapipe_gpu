# Copyright 2022 The MediaPipe Authors.
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

# Placeholder for internal Python strict library and test compatibility macro.

package(default_visibility = ["//visibility:public"])

licenses(["notice"])

py_library(
    name = "object_detector",
    srcs = [
        "object_detector.py",
    ],
    deps = [
        "//mediapipe_custom/python:_framework_bindings",
        "//mediapipe_custom/python:packet_creator",
        "//mediapipe_custom/python:packet_getter",
        "//mediapipe_custom/tasks/cc/vision/object_detector/proto:object_detector_options_py_pb2",
        "//mediapipe_custom/tasks/python/components/containers:detections",
        "//mediapipe_custom/tasks/python/components/containers:rect",
        "//mediapipe_custom/tasks/python/core:base_options",
        "//mediapipe_custom/tasks/python/core:optional_dependencies",
        "//mediapipe_custom/tasks/python/core:task_info",
        "//mediapipe_custom/tasks/python/vision/core:base_vision_task_api",
        "//mediapipe_custom/tasks/python/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/python/vision/core:vision_task_running_mode",
    ],
)

py_library(
    name = "image_classifier",
    srcs = [
        "image_classifier.py",
    ],
    deps = [
        "//mediapipe_custom/python:_framework_bindings",
        "//mediapipe_custom/python:packet_creator",
        "//mediapipe_custom/python:packet_getter",
        "//mediapipe_custom/tasks/cc/components/containers/proto:classifications_py_pb2",
        "//mediapipe_custom/tasks/cc/components/processors/proto:classifier_options_py_pb2",
        "//mediapipe_custom/tasks/cc/vision/image_classifier/proto:image_classifier_graph_options_py_pb2",
        "//mediapipe_custom/tasks/python/components/containers:classification_result",
        "//mediapipe_custom/tasks/python/components/containers:rect",
        "//mediapipe_custom/tasks/python/core:base_options",
        "//mediapipe_custom/tasks/python/core:optional_dependencies",
        "//mediapipe_custom/tasks/python/core:task_info",
        "//mediapipe_custom/tasks/python/vision/core:base_vision_task_api",
        "//mediapipe_custom/tasks/python/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/python/vision/core:vision_task_running_mode",
    ],
)

py_library(
    name = "image_segmenter",
    srcs = [
        "image_segmenter.py",
    ],
    deps = [
        "//mediapipe_custom/python:_framework_bindings",
        "//mediapipe_custom/python:packet_creator",
        "//mediapipe_custom/python:packet_getter",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter/calculators:tensors_to_segmentation_calculator_py_pb2",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter/proto:image_segmenter_graph_options_py_pb2",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter/proto:segmenter_options_py_pb2",
        "//mediapipe_custom/tasks/python/components/containers:rect",
        "//mediapipe_custom/tasks/python/core:base_options",
        "//mediapipe_custom/tasks/python/core:optional_dependencies",
        "//mediapipe_custom/tasks/python/core:task_info",
        "//mediapipe_custom/tasks/python/vision/core:base_vision_task_api",
        "//mediapipe_custom/tasks/python/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/python/vision/core:vision_task_running_mode",
    ],
)

py_library(
    name = "image_embedder",
    srcs = [
        "image_embedder.py",
    ],
    deps = [
        "//mediapipe_custom/python:_framework_bindings",
        "//mediapipe_custom/python:packet_creator",
        "//mediapipe_custom/python:packet_getter",
        "//mediapipe_custom/tasks/cc/components/containers/proto:embeddings_py_pb2",
        "//mediapipe_custom/tasks/cc/components/processors/proto:embedder_options_py_pb2",
        "//mediapipe_custom/tasks/cc/vision/image_embedder/proto:image_embedder_graph_options_py_pb2",
        "//mediapipe_custom/tasks/python/components/containers:embedding_result",
        "//mediapipe_custom/tasks/python/components/utils:cosine_similarity",
        "//mediapipe_custom/tasks/python/core:base_options",
        "//mediapipe_custom/tasks/python/core:optional_dependencies",
        "//mediapipe_custom/tasks/python/core:task_info",
        "//mediapipe_custom/tasks/python/vision/core:base_vision_task_api",
        "//mediapipe_custom/tasks/python/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/python/vision/core:vision_task_running_mode",
    ],
)

py_library(
    name = "interactive_segmenter",
    srcs = [
        "interactive_segmenter.py",
    ],
    deps = [
        "//mediapipe_custom/python:_framework_bindings",
        "//mediapipe_custom/python:packet_creator",
        "//mediapipe_custom/python:packet_getter",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter/proto:image_segmenter_graph_options_py_pb2",
        "//mediapipe_custom/tasks/cc/vision/image_segmenter/proto:segmenter_options_py_pb2",
        "//mediapipe_custom/tasks/python/components/containers:keypoint",
        "//mediapipe_custom/tasks/python/core:base_options",
        "//mediapipe_custom/tasks/python/core:optional_dependencies",
        "//mediapipe_custom/tasks/python/core:task_info",
        "//mediapipe_custom/tasks/python/vision/core:base_vision_task_api",
        "//mediapipe_custom/tasks/python/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/python/vision/core:vision_task_running_mode",
        "//mediapipe_custom/util:render_data_py_pb2",
    ],
)

py_library(
    name = "gesture_recognizer",
    srcs = [
        "gesture_recognizer.py",
    ],
    deps = [
        "//mediapipe_custom/framework/formats:classification_py_pb2",
        "//mediapipe_custom/framework/formats:landmark_py_pb2",
        "//mediapipe_custom/python:_framework_bindings",
        "//mediapipe_custom/python:packet_creator",
        "//mediapipe_custom/python:packet_getter",
        "//mediapipe_custom/tasks/cc/vision/gesture_recognizer/proto:gesture_recognizer_graph_options_py_pb2",
        "//mediapipe_custom/tasks/python/components/containers:category",
        "//mediapipe_custom/tasks/python/components/containers:landmark",
        "//mediapipe_custom/tasks/python/components/processors:classifier_options",
        "//mediapipe_custom/tasks/python/core:base_options",
        "//mediapipe_custom/tasks/python/core:optional_dependencies",
        "//mediapipe_custom/tasks/python/core:task_info",
        "//mediapipe_custom/tasks/python/vision/core:base_vision_task_api",
        "//mediapipe_custom/tasks/python/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/python/vision/core:vision_task_running_mode",
    ],
)

py_library(
    name = "hand_landmarker",
    srcs = [
        "hand_landmarker.py",
    ],
    deps = [
        "//mediapipe_custom/framework/formats:classification_py_pb2",
        "//mediapipe_custom/framework/formats:landmark_py_pb2",
        "//mediapipe_custom/python:_framework_bindings",
        "//mediapipe_custom/python:packet_creator",
        "//mediapipe_custom/python:packet_getter",
        "//mediapipe_custom/tasks/cc/vision/hand_landmarker/proto:hand_landmarker_graph_options_py_pb2",
        "//mediapipe_custom/tasks/python/components/containers:category",
        "//mediapipe_custom/tasks/python/components/containers:landmark",
        "//mediapipe_custom/tasks/python/core:base_options",
        "//mediapipe_custom/tasks/python/core:optional_dependencies",
        "//mediapipe_custom/tasks/python/core:task_info",
        "//mediapipe_custom/tasks/python/vision/core:base_vision_task_api",
        "//mediapipe_custom/tasks/python/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/python/vision/core:vision_task_running_mode",
    ],
)

py_library(
    name = "pose_landmarker",
    srcs = [
        "pose_landmarker.py",
    ],
    deps = [
        "//mediapipe_custom/framework/formats:landmark_py_pb2",
        "//mediapipe_custom/python:_framework_bindings",
        "//mediapipe_custom/python:packet_creator",
        "//mediapipe_custom/python:packet_getter",
        "//mediapipe_custom/tasks/cc/vision/pose_landmarker/proto:pose_landmarker_graph_options_py_pb2",
        "//mediapipe_custom/tasks/python/components/containers:landmark",
        "//mediapipe_custom/tasks/python/core:base_options",
        "//mediapipe_custom/tasks/python/core:optional_dependencies",
        "//mediapipe_custom/tasks/python/core:task_info",
        "//mediapipe_custom/tasks/python/vision/core:base_vision_task_api",
        "//mediapipe_custom/tasks/python/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/python/vision/core:vision_task_running_mode",
        "@mediapipe_pip_deps//:numpy",
    ],
)

py_library(
    name = "face_detector",
    srcs = [
        "face_detector.py",
    ],
    deps = [
        "//mediapipe_custom/python:_framework_bindings",
        "//mediapipe_custom/python:packet_creator",
        "//mediapipe_custom/python:packet_getter",
        "//mediapipe_custom/tasks/cc/vision/face_detector/proto:face_detector_graph_options_py_pb2",
        "//mediapipe_custom/tasks/python/components/containers:detections",
        "//mediapipe_custom/tasks/python/core:base_options",
        "//mediapipe_custom/tasks/python/core:optional_dependencies",
        "//mediapipe_custom/tasks/python/core:task_info",
        "//mediapipe_custom/tasks/python/vision/core:base_vision_task_api",
        "//mediapipe_custom/tasks/python/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/python/vision/core:vision_task_running_mode",
    ],
)

py_library(
    name = "face_landmarker",
    srcs = [
        "face_landmarker.py",
    ],
    deps = [
        "//mediapipe_custom/framework/formats:classification_py_pb2",
        "//mediapipe_custom/framework/formats:landmark_py_pb2",
        "//mediapipe_custom/framework/formats:matrix_data_py_pb2",
        "//mediapipe_custom/python:_framework_bindings",
        "//mediapipe_custom/python:packet_creator",
        "//mediapipe_custom/python:packet_getter",
        "//mediapipe_custom/tasks/cc/vision/face_geometry/proto:face_geometry_py_pb2",
        "//mediapipe_custom/tasks/cc/vision/face_landmarker/proto:face_landmarker_graph_options_py_pb2",
        "//mediapipe_custom/tasks/python/components/containers:category",
        "//mediapipe_custom/tasks/python/components/containers:landmark",
        "//mediapipe_custom/tasks/python/core:base_options",
        "//mediapipe_custom/tasks/python/core:optional_dependencies",
        "//mediapipe_custom/tasks/python/core:task_info",
        "//mediapipe_custom/tasks/python/vision/core:base_vision_task_api",
        "//mediapipe_custom/tasks/python/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/python/vision/core:vision_task_running_mode",
        "@mediapipe_pip_deps//:numpy",
    ],
)

py_library(
    name = "holistic_landmarker",
    srcs = [
        "holistic_landmarker.py",
    ],
    deps = [
        "//mediapipe_custom/framework/formats:classification_py_pb2",
        "//mediapipe_custom/framework/formats:landmark_py_pb2",
        "//mediapipe_custom/python:_framework_bindings",
        "//mediapipe_custom/python:packet_creator",
        "//mediapipe_custom/python:packet_getter",
        "//mediapipe_custom/tasks/cc/vision/holistic_landmarker/proto:holistic_landmarker_graph_options_py_pb2",
        "//mediapipe_custom/tasks/cc/vision/holistic_landmarker/proto:holistic_result_py_pb2",
        "//mediapipe_custom/tasks/python/components/containers:category",
        "//mediapipe_custom/tasks/python/components/containers:landmark",
        "//mediapipe_custom/tasks/python/core:base_options",
        "//mediapipe_custom/tasks/python/core:optional_dependencies",
        "//mediapipe_custom/tasks/python/core:task_info",
        "//mediapipe_custom/tasks/python/vision/core:base_vision_task_api",
        "//mediapipe_custom/tasks/python/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/python/vision/core:vision_task_running_mode",
    ],
)

py_library(
    name = "face_stylizer",
    srcs = [
        "face_stylizer.py",
    ],
    deps = [
        "//mediapipe_custom/python:_framework_bindings",
        "//mediapipe_custom/python:packet_creator",
        "//mediapipe_custom/python:packet_getter",
        "//mediapipe_custom/tasks/cc/vision/face_stylizer/proto:face_stylizer_graph_options_py_pb2",
        "//mediapipe_custom/tasks/python/core:base_options",
        "//mediapipe_custom/tasks/python/core:optional_dependencies",
        "//mediapipe_custom/tasks/python/core:task_info",
        "//mediapipe_custom/tasks/python/vision/core:base_vision_task_api",
        "//mediapipe_custom/tasks/python/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/python/vision/core:vision_task_running_mode",
    ],
)

py_library(
    name = "face_aligner",
    srcs = [
        "face_aligner.py",
    ],
    deps = [
        "//mediapipe_custom/python:_framework_bindings",
        "//mediapipe_custom/python:packet_creator",
        "//mediapipe_custom/python:packet_getter",
        "//mediapipe_custom/tasks/cc/vision/face_stylizer/proto:face_stylizer_graph_options_py_pb2",
        "//mediapipe_custom/tasks/python/core:base_options",
        "//mediapipe_custom/tasks/python/core:optional_dependencies",
        "//mediapipe_custom/tasks/python/core:task_info",
        "//mediapipe_custom/tasks/python/vision/core:base_vision_task_api",
        "//mediapipe_custom/tasks/python/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/python/vision/core:vision_task_running_mode",
    ],
)
