// Copyright 2019 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "mediapipe_custom/calculators/core/end_loop_calculator.h"

#include <array>
#include <utility>
#include <vector>

#include "mediapipe_custom/framework/formats/classification.pb.h"
#include "mediapipe_custom/framework/formats/detection.pb.h"
#include "mediapipe_custom/framework/formats/image.h"
#include "mediapipe_custom/framework/formats/image_frame.h"
#include "mediapipe_custom/framework/formats/landmark.pb.h"
#include "mediapipe_custom/framework/formats/matrix.h"
#include "mediapipe_custom/framework/formats/rect.pb.h"
#include "mediapipe_custom/framework/formats/tensor.h"
#include "mediapipe_custom/gpu/gpu_buffer.h"
#include "mediapipe_custom/util/render_data.pb.h"
#include "tensorflow/lite/interpreter.h"

namespace mediapipe_custom {

typedef EndLoopCalculator<std::vector<::mediapipe_custom::NormalizedRect>>
    EndLoopNormalizedRectCalculator;
REGISTER_CALCULATOR(EndLoopNormalizedRectCalculator);

typedef EndLoopCalculator<std::vector<::mediapipe_custom::LandmarkList>>
    EndLoopLandmarkListVectorCalculator;
REGISTER_CALCULATOR(EndLoopLandmarkListVectorCalculator);

typedef EndLoopCalculator<std::vector<::mediapipe_custom::NormalizedLandmarkList>>
    EndLoopNormalizedLandmarkListVectorCalculator;
REGISTER_CALCULATOR(EndLoopNormalizedLandmarkListVectorCalculator);

typedef EndLoopCalculator<std::vector<bool>> EndLoopBooleanCalculator;
REGISTER_CALCULATOR(EndLoopBooleanCalculator);

typedef EndLoopCalculator<std::vector<float>> EndLoopFloatCalculator;
REGISTER_CALCULATOR(EndLoopFloatCalculator);

typedef EndLoopCalculator<std::vector<::mediapipe_custom::RenderData>>
    EndLoopRenderDataCalculator;
REGISTER_CALCULATOR(EndLoopRenderDataCalculator);

typedef EndLoopCalculator<std::vector<::mediapipe_custom::ClassificationList>>
    EndLoopClassificationListCalculator;
REGISTER_CALCULATOR(EndLoopClassificationListCalculator);

typedef EndLoopCalculator<std::vector<TfLiteTensor>>
    EndLoopTfLiteTensorCalculator;
REGISTER_CALCULATOR(EndLoopTfLiteTensorCalculator);

typedef EndLoopCalculator<std::vector<::mediapipe_custom::Detection>>
    EndLoopDetectionCalculator;
REGISTER_CALCULATOR(EndLoopDetectionCalculator);

typedef EndLoopCalculator<std::vector<Matrix>> EndLoopMatrixCalculator;
REGISTER_CALCULATOR(EndLoopMatrixCalculator);

typedef EndLoopCalculator<std::vector<Tensor>> EndLoopTensorCalculator;
REGISTER_CALCULATOR(EndLoopTensorCalculator);

typedef EndLoopCalculator<std::vector<ImageFrame>> EndLoopImageFrameCalculator;
REGISTER_CALCULATOR(EndLoopImageFrameCalculator);

typedef EndLoopCalculator<std::vector<GpuBuffer>> EndLoopGpuBufferCalculator;
REGISTER_CALCULATOR(EndLoopGpuBufferCalculator);

typedef EndLoopCalculator<std::vector<::mediapipe_custom::Image>>
    EndLoopImageCalculator;
REGISTER_CALCULATOR(EndLoopImageCalculator);

typedef EndLoopCalculator<std::vector<std::array<float, 16>>>
    EndLoopAffineMatrixCalculator;
REGISTER_CALCULATOR(EndLoopAffineMatrixCalculator);

typedef EndLoopCalculator<std::vector<std::pair<int, int>>>
    EndLoopImageSizeCalculator;
REGISTER_CALCULATOR(EndLoopImageSizeCalculator);

}  // namespace mediapipe_custom
