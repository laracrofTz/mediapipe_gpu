# Copyright 2023 The MediaPipe Authors.
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

load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_cc//cc:cc_test.bzl", "cc_test")

package(default_visibility = ["//visibility:public"])

licenses(["notice"])

cc_library(
    name = "pose_landmarker",
    srcs = ["pose_landmarker.cc"],
    hdrs = ["pose_landmarker.h"],
    deps = [
        ":pose_landmarker_graph",
        ":pose_landmarker_result",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:landmark_cc_proto",
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/core:base_options",
        "//mediapipe_custom/tasks/cc/core:base_task_api",
        "//mediapipe_custom/tasks/cc/core:model_resources",
        "//mediapipe_custom/tasks/cc/core:task_runner",
        "//mediapipe_custom/tasks/cc/core:utils",
        "//mediapipe_custom/tasks/cc/core/proto:inference_subgraph_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/core:base_vision_task_api",
        "//mediapipe_custom/tasks/cc/vision/core:image_processing_options",
        "//mediapipe_custom/tasks/cc/vision/core:running_mode",
        "//mediapipe_custom/tasks/cc/vision/core:vision_task_api_factory",
        "//mediapipe_custom/tasks/cc/vision/pose_detector/proto:pose_detector_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/pose_landmarker/proto:pose_landmarker_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/pose_landmarker/proto:pose_landmarks_detector_graph_options_cc_proto",
        "@com_google_absl//absl/status:statusor",
    ],
)

cc_library(
    name = "pose_landmarks_detector_graph",
    srcs = ["pose_landmarks_detector_graph.cc"],
    deps = [
        "//mediapipe_custom/calculators/core:begin_loop_calculator",
        "//mediapipe_custom/calculators/core:concatenate_vector_calculator",
        "//mediapipe_custom/calculators/core:constant_side_packet_calculator",
        "//mediapipe_custom/calculators/core:constant_side_packet_calculator_cc_proto",
        "//mediapipe_custom/calculators/core:end_loop_calculator",
        "//mediapipe_custom/calculators/core:gate_calculator",
        "//mediapipe_custom/calculators/core:side_packet_to_stream_calculator",
        "//mediapipe_custom/calculators/core:split_proto_list_calculator",
        "//mediapipe_custom/calculators/core:split_vector_calculator",
        "//mediapipe_custom/calculators/core:split_vector_calculator_cc_proto",
        "//mediapipe_custom/calculators/image:warp_affine_calculator",
        "//mediapipe_custom/calculators/image:warp_affine_calculator_cc_proto",
        "//mediapipe_custom/calculators/tensor:image_to_tensor_calculator_cc_proto",
        "//mediapipe_custom/calculators/tensor:inference_calculator",
        "//mediapipe_custom/calculators/tensor:tensors_to_floats_calculator",
        "//mediapipe_custom/calculators/tensor:tensors_to_landmarks_calculator",
        "//mediapipe_custom/calculators/tensor:tensors_to_landmarks_calculator_cc_proto",
        "//mediapipe_custom/calculators/tensor:tensors_to_segmentation_calculator",
        "//mediapipe_custom/calculators/tensor:tensors_to_segmentation_calculator_cc_proto",
        "//mediapipe_custom/calculators/util:alignment_points_to_rects_calculator",
        "//mediapipe_custom/calculators/util:detections_to_rects_calculator",
        "//mediapipe_custom/calculators/util:detections_to_rects_calculator_cc_proto",
        "//mediapipe_custom/calculators/util:inverse_matrix_calculator",
        "//mediapipe_custom/calculators/util:landmark_letterbox_removal_calculator",
        "//mediapipe_custom/calculators/util:landmark_projection_calculator",
        "//mediapipe_custom/calculators/util:landmarks_to_detection_calculator",
        "//mediapipe_custom/calculators/util:rect_transformation_calculator",
        "//mediapipe_custom/calculators/util:rect_transformation_calculator_cc_proto",
        "//mediapipe_custom/calculators/util:refine_landmarks_from_heatmap_calculator",
        "//mediapipe_custom/calculators/util:refine_landmarks_from_heatmap_calculator_cc_proto",
        "//mediapipe_custom/calculators/util:thresholding_calculator",
        "//mediapipe_custom/calculators/util:thresholding_calculator_cc_proto",
        "//mediapipe_custom/calculators/util:visibility_copy_calculator",
        "//mediapipe_custom/calculators/util:visibility_copy_calculator_cc_proto",
        "//mediapipe_custom/calculators/util:world_landmark_projection_calculator",
        "//mediapipe_custom/framework:subgraph",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/api2/stream:get_vector_item",
        "//mediapipe_custom/framework/api2/stream:image_size",
        "//mediapipe_custom/framework/api2/stream:smoothing",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:landmark_cc_proto",
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/gpu:gpu_origin_cc_proto",
        "//mediapipe_custom/tasks/cc:common",
        "//mediapipe_custom/tasks/cc/components/processors:image_preprocessing_graph",
        "//mediapipe_custom/tasks/cc/core:model_resources",
        "//mediapipe_custom/tasks/cc/core:model_task_graph",
        "//mediapipe_custom/tasks/cc/vision/pose_landmarker/proto:pose_landmarks_detector_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/utils:image_tensor_specs",
        "//mediapipe_custom/util:graph_builder_utils",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ],
    alwayslink = 1,
)

cc_library(
    name = "pose_landmarker_graph",
    srcs = ["pose_landmarker_graph.cc"],
    deps = [
        ":pose_landmarks_detector_graph",
        "//mediapipe_custom/calculators/core:clip_vector_size_calculator",
        "//mediapipe_custom/calculators/core:clip_vector_size_calculator_cc_proto",
        "//mediapipe_custom/calculators/core:gate_calculator",
        "//mediapipe_custom/calculators/core:gate_calculator_cc_proto",
        "//mediapipe_custom/calculators/core:pass_through_calculator",
        "//mediapipe_custom/calculators/core:previous_loopback_calculator",
        "//mediapipe_custom/calculators/image:image_properties_calculator",
        "//mediapipe_custom/calculators/util:association_calculator_cc_proto",
        "//mediapipe_custom/calculators/util:association_norm_rect_calculator",
        "//mediapipe_custom/calculators/util:collection_has_min_size_calculator",
        "//mediapipe_custom/calculators/util:collection_has_min_size_calculator_cc_proto",
        "//mediapipe_custom/framework/api2:builder",
        "//mediapipe_custom/framework/api2:port",
        "//mediapipe_custom/framework/formats:detection_cc_proto",
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:landmark_cc_proto",
        "//mediapipe_custom/framework/formats:rect_cc_proto",
        "//mediapipe_custom/framework/port:status",
        "//mediapipe_custom/tasks/cc/components/utils:gate",
        "//mediapipe_custom/tasks/cc/core:model_asset_bundle_resources",
        "//mediapipe_custom/tasks/cc/core:model_resources_cache",
        "//mediapipe_custom/tasks/cc/core:model_task_graph",
        "//mediapipe_custom/tasks/cc/core:utils",
        "//mediapipe_custom/tasks/cc/metadata/utils:zip_utils",
        "//mediapipe_custom/tasks/cc/vision/pose_detector:pose_detector_graph",
        "//mediapipe_custom/tasks/cc/vision/pose_detector/proto:pose_detector_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/pose_landmarker/proto:pose_landmarker_graph_options_cc_proto",
        "//mediapipe_custom/tasks/cc/vision/pose_landmarker/proto:pose_landmarks_detector_graph_options_cc_proto",
        "//mediapipe_custom/util:graph_builder_utils",
        "@com_google_absl//absl/status",
    ],
    alwayslink = 1,
)

cc_library(
    name = "pose_landmarker_result",
    srcs = ["pose_landmarker_result.cc"],
    hdrs = ["pose_landmarker_result.h"],
    deps = [
        "//mediapipe_custom/framework/formats:image",
        "//mediapipe_custom/framework/formats:landmark_cc_proto",
        "//mediapipe_custom/tasks/cc/components/containers:landmark",
    ],
)

cc_library(
    name = "pose_landmarks_connections",
    hdrs = ["pose_landmarks_connections.h"],
)

cc_library(
    name = "pose_topology",
    hdrs = ["pose_topology.h"],
)
