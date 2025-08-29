# Copyright 2019 The MediaPipe Authors.
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

load(
    "//mediapipe_custom/framework/tool:mediapipe_graph.bzl",
    "mediapipe_simple_subgraph",
)

licenses(["notice"])

package(default_visibility = ["//visibility:public"])

mediapipe_simple_subgraph(
    name = "box_tracking_gpu",
    graph = "box_tracking_gpu.pbtxt",
    register_as = "BoxTrackingSubgraphGpu",
    deps = [
        "//mediapipe_custom/calculators/image:image_transformation_calculator",
        "//mediapipe_custom/calculators/video:box_tracker_calculator",
        "//mediapipe_custom/calculators/video:flow_packager_calculator",
        "//mediapipe_custom/calculators/video:motion_analysis_calculator",
        "//mediapipe_custom/framework/stream_handler:immediate_input_stream_handler",
        "//mediapipe_custom/framework/stream_handler:sync_set_input_stream_handler",
        "//mediapipe_custom/gpu:gpu_buffer_to_image_frame_calculator",
    ],
)

mediapipe_simple_subgraph(
    name = "box_tracking_cpu",
    graph = "box_tracking_cpu.pbtxt",
    register_as = "BoxTrackingSubgraphCpu",
    deps = [
        "//mediapipe_custom/calculators/image:image_transformation_calculator",
        "//mediapipe_custom/calculators/video:box_tracker_calculator",
        "//mediapipe_custom/calculators/video:flow_packager_calculator",
        "//mediapipe_custom/calculators/video:motion_analysis_calculator",
        "//mediapipe_custom/framework/stream_handler:immediate_input_stream_handler",
        "//mediapipe_custom/framework/stream_handler:sync_set_input_stream_handler",
    ],
)

mediapipe_simple_subgraph(
    name = "object_tracking_gpu",
    graph = "object_tracking_gpu.pbtxt",
    register_as = "ObjectTrackingSubgraphGpu",
    deps = [
        "//mediapipe_custom/calculators/util:detection_unique_id_calculator",
        "//mediapipe_custom/calculators/util:detections_to_timed_box_list_calculator",
        "//mediapipe_custom/calculators/video:tracked_detection_manager_calculator",
        "//mediapipe_custom/framework/stream_handler:sync_set_input_stream_handler",
        "//mediapipe_custom/graphs/tracking/subgraphs:box_tracking_gpu",
    ],
)

mediapipe_simple_subgraph(
    name = "object_tracking_cpu",
    graph = "object_tracking_cpu.pbtxt",
    register_as = "ObjectTrackingSubgraphCpu",
    deps = [
        "//mediapipe_custom/calculators/util:detection_unique_id_calculator",
        "//mediapipe_custom/calculators/util:detections_to_timed_box_list_calculator",
        "//mediapipe_custom/calculators/video:tracked_detection_manager_calculator",
        "//mediapipe_custom/framework/stream_handler:sync_set_input_stream_handler",
        "//mediapipe_custom/graphs/tracking/subgraphs:box_tracking_cpu",
    ],
)

mediapipe_simple_subgraph(
    name = "object_detection_gpu",
    graph = "object_detection_gpu.pbtxt",
    register_as = "ObjectDetectionSubgraphGpu",
    deps = [
        "//mediapipe_custom/calculators/image:image_transformation_calculator",
        "//mediapipe_custom/calculators/tflite:ssd_anchors_calculator",
        "//mediapipe_custom/calculators/tflite:tflite_converter_calculator",
        "//mediapipe_custom/calculators/tflite:tflite_inference_calculator",
        "//mediapipe_custom/calculators/tflite:tflite_tensors_to_detections_calculator",
        "//mediapipe_custom/calculators/util:detection_label_id_to_text_calculator",
        "//mediapipe_custom/calculators/util:non_max_suppression_calculator",
    ],
)

mediapipe_simple_subgraph(
    name = "object_detection_cpu",
    graph = "object_detection_cpu.pbtxt",
    register_as = "ObjectDetectionSubgraphCpu",
    deps = [
        "//mediapipe_custom/calculators/image:image_transformation_calculator",
        "//mediapipe_custom/calculators/tflite:ssd_anchors_calculator",
        "//mediapipe_custom/calculators/tflite:tflite_converter_calculator",
        "//mediapipe_custom/calculators/tflite:tflite_inference_calculator",
        "//mediapipe_custom/calculators/tflite:tflite_tensors_to_detections_calculator",
        "//mediapipe_custom/calculators/util:detection_label_id_to_text_calculator",
        "//mediapipe_custom/calculators/util:non_max_suppression_calculator",
    ],
)

mediapipe_simple_subgraph(
    name = "renderer_gpu",
    graph = "renderer_gpu.pbtxt",
    register_as = "RendererSubgraphGpu",
    deps = [
        "//mediapipe_custom/calculators/util:annotation_overlay_calculator",
        "//mediapipe_custom/calculators/util:detections_to_render_data_calculator",
        "//mediapipe_custom/calculators/util:rect_to_render_data_calculator",
    ],
)

mediapipe_simple_subgraph(
    name = "renderer_cpu",
    graph = "renderer_cpu.pbtxt",
    register_as = "RendererSubgraphCpu",
    deps = [
        "//mediapipe_custom/calculators/util:annotation_overlay_calculator",
        "//mediapipe_custom/calculators/util:detections_to_render_data_calculator",
        "//mediapipe_custom/calculators/util:rect_to_render_data_calculator",
    ],
)
