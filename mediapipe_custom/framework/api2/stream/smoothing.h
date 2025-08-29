#ifndef MEDIAPIPE_FRAMEWORK_API2_STREAM_SMOOTHING_H_
#define MEDIAPIPE_FRAMEWORK_API2_STREAM_SMOOTHING_H_

#include <cstdint>
#include <optional>
#include <utility>
#include <vector>

#include "absl/types/optional.h"
#include "mediapipe_custom/calculators/util/landmarks_smoothing_calculator.pb.h"
#include "mediapipe_custom/framework/api2/builder.h"
#include "mediapipe_custom/framework/formats/landmark.pb.h"
#include "mediapipe_custom/framework/formats/rect.pb.h"

namespace mediapipe_custom::api2::builder {

struct OneEuroFilterConfig {
  float min_cutoff;
  float beta;
  float derivate_cutoff;
};

// Updates graph to smooth normalized landmarks and returns resulting stream.
//
// @landmarks - normalized landmarks.
// @image_size - size of image where landmarks were detected.
// @scale_roi - can be used to specify object scale.
// @config - filter config.
// @graph - graph to update.
//
// Returns: smoothed/filtered normalized landmarks.
//
// NOTE: one-euro filter is exposed only. Other filter options can be exposed
//   on demand.
Stream<mediapipe_custom::NormalizedLandmarkList> SmoothLandmarks(
    Stream<mediapipe_custom::NormalizedLandmarkList> landmarks,
    Stream<std::pair<int, int>> image_size,
    std::optional<Stream<NormalizedRect>> scale_roi,
    const OneEuroFilterConfig& config, Graph& graph);

// Updates graph to smooth absolute landmarks and returns resulting stream.
//
// @landmarks - absolute landmarks.
// @scale_roi - can be used to specify object scale.
// @config - filter config.
// @graph - graph to update.
//
// Returns: smoothed/filtered absolute landmarks.
//
// NOTE: one-euro filter is exposed only. Other filter options can be exposed
//   on demand.
Stream<mediapipe_custom::LandmarkList> SmoothLandmarks(
    Stream<mediapipe_custom::LandmarkList> landmarks,
    std::optional<Stream<NormalizedRect>> scale_roi,
    const OneEuroFilterConfig& config, Graph& graph);

// Updates graph to smooth normalized landmarks and returns resulting stream.
//
// @landmarks - normalized landmarks vector.
// @tracking_ids - tracking IDs associated with landmarks
// @image_size - size of image where landmarks were detected.
// @scale_roi - can be used to specify object scales.
// @config - filter config.
// @graph - graph to update.
//
// Returns: smoothed/filtered normalized landmarks.
//
// NOTE: one-euro filter is exposed only. Other filter options can be exposed
//   on demand.
Stream<std::vector<mediapipe_custom::NormalizedLandmarkList>> SmoothMultiLandmarks(
    Stream<std::vector<mediapipe_custom::NormalizedLandmarkList>> landmarks,
    Stream<std::vector<int64_t>> tracking_ids,
    Stream<std::pair<int, int>> image_size,
    std::optional<Stream<std::vector<NormalizedRect>>> scale_roi,
    const mediapipe_custom::LandmarksSmoothingCalculatorOptions& config, Graph& graph);

// Updates graph to smooth absolute landmarks and returns resulting stream.
//
// @landmarks - absolute landmarks vector.
// @tracking_ids - tracking IDs associated with landmarks
// @scale_roi - can be used to specify object scales.
// @config - filter config.
// @graph - graph to update.
//
// Returns: smoothed/filtered absolute landmarks.
//
// NOTE: one-euro filter is exposed only. Other filter options can be exposed
//   on demand.
Stream<std::vector<mediapipe_custom::LandmarkList>> SmoothMultiWorldLandmarks(
    Stream<std::vector<mediapipe_custom::LandmarkList>> landmarks,
    Stream<std::vector<int64_t>> tracking_ids,
    std::optional<Stream<std::vector<mediapipe_custom::Rect>>> scale_roi,
    const mediapipe_custom::LandmarksSmoothingCalculatorOptions& config, Graph& graph);

// Updates graph to smooth visibility of landmarks.
//
// @landmarks - normalized landmarks.
// @low_pass_filter_alpha - low pass filter alpha to use for smoothing.
// @graph - graph to update.
//
// Returns: normalized landmarks containing smoothed visibility.
Stream<mediapipe_custom::NormalizedLandmarkList> SmoothLandmarksVisibility(
    Stream<mediapipe_custom::NormalizedLandmarkList> landmarks,
    float low_pass_filter_alpha, Graph& graph);

// Updates graph to smooth visibility of landmarks.
//
// @landmarks - absolute landmarks.
// @low_pass_filter_alpha - low pass filter alpha to use for smoothing.
// @graph - graph to update.
//
// Returns: absolute landmarks containing smoothed visibility.
Stream<mediapipe_custom::LandmarkList> SmoothLandmarksVisibility(
    Stream<mediapipe_custom::LandmarkList> landmarks, float low_pass_filter_alpha,
    mediapipe_custom::api2::builder::Graph& graph);

}  // namespace mediapipe_custom::api2::builder

#endif  // MEDIAPIPE_FRAMEWORK_API2_STREAM_SMOOTHING_H_
