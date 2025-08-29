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

load("@rules_cc//cc:cc_library.bzl", "cc_library")
load(
    "//mediapipe_custom/framework/tool:mediapipe_graph.bzl",
    "mediapipe_binary_graph",
)

licenses(["notice"])

package(default_visibility = ["//visibility:public"])

exports_files(glob([
    "*.pbtxt",
]))

cc_library(
    name = "mobile_calculators",
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/calculators/core:flow_limiter_calculator",
        "//mediapipe_custom/calculators/image:image_cropping_calculator",
        "//mediapipe_custom/graphs/object_detection_3d/calculators:annotations_to_model_matrices_calculator",
        "//mediapipe_custom/graphs/object_detection_3d/calculators:gl_animation_overlay_calculator",
        "//mediapipe_custom/modules/objectron:objectron_gpu",
    ],
)

cc_library(
    name = "mobile_calculators_1stage",
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/calculators/core:packet_resampler_calculator",
        "//mediapipe_custom/calculators/image:image_cropping_calculator",
        "//mediapipe_custom/gpu:gl_scaler_calculator",
        "//mediapipe_custom/graphs/object_detection_3d/calculators:annotations_to_model_matrices_calculator",
        "//mediapipe_custom/graphs/object_detection_3d/calculators:gl_animation_overlay_calculator",
        "//mediapipe_custom/modules/objectron:objectron_detection_1stage_gpu",
        "//mediapipe_custom/modules/objectron:objectron_tracking_1stage_gpu",
    ],
)

cc_library(
    name = "desktop_cpu_calculators",
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe_custom/calculators/core:constant_side_packet_calculator",
        "//mediapipe_custom/calculators/video:opencv_video_decoder_calculator",
        "//mediapipe_custom/calculators/video:opencv_video_encoder_calculator",
        "//mediapipe_custom/graphs/object_detection_3d/subgraphs:renderer_cpu",
        "//mediapipe_custom/modules/objectron:objectron_cpu",
    ],
)

mediapipe_binary_graph(
    name = "mobile_gpu_binary_graph",
    graph = "object_occlusion_tracking.pbtxt",
    output_name = "mobile_gpu_binary_graph.binarypb",
    visibility = ["//visibility:public"],
    deps = [":mobile_calculators"],
)

mediapipe_binary_graph(
    name = "mobile_gpu_1stage_binary_graph",
    graph = "object_occlusion_tracking_1stage.pbtxt",
    output_name = "mobile_gpu_1stage_binary_graph.binarypb",
    visibility = ["//visibility:public"],
    deps = [":mobile_calculators_1stage"],
)
