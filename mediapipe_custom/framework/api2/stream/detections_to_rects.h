#ifndef MEDIAPIPE_FRAMEWORK_API2_STREAM_DETECTIONS_TO_RECTS_H_
#define MEDIAPIPE_FRAMEWORK_API2_STREAM_DETECTIONS_TO_RECTS_H_

#include <utility>
#include <vector>

#include "mediapipe_custom/framework/api2/builder.h"
#include "mediapipe_custom/framework/formats/detection.pb.h"
#include "mediapipe_custom/framework/formats/rect.pb.h"

namespace mediapipe_custom::api2::builder {

// Updates @graph to convert @detection into a `NormalizedRect` according to
// passed parameters.
Stream<mediapipe_custom::NormalizedRect> ConvertAlignmentPointsDetectionToRect(
    Stream<mediapipe_custom::Detection> detection,
    Stream<std::pair<int, int>> image_size, int start_keypoint_index,
    int end_keypoint_index, float target_angle,
    mediapipe_custom::api2::builder::Graph& graph);

// Updates @graph to convert first detection from @detections into a
// `NormalizedRect` according to passed parameters.
Stream<mediapipe_custom::NormalizedRect> ConvertAlignmentPointsDetectionsToRect(
    Stream<std::vector<mediapipe_custom::Detection>> detections,
    Stream<std::pair<int, int>> image_size, int start_keypoint_index,
    int end_keypoint_index, float target_angle,
    mediapipe_custom::api2::builder::Graph& graph);

// Updates @graph to convert @detection into a `NormalizedRect` according to
// passed parameters.
Stream<mediapipe_custom::NormalizedRect> ConvertDetectionToRect(
    Stream<mediapipe_custom::Detection> detections,
    Stream<std::pair<int, int>> image_size, int start_keypoint_index,
    int end_keypoint_index, float target_angle,
    mediapipe_custom::api2::builder::Graph& graph);

// Updates @graph to convert @detections into a stream holding vector of
// `NormalizedRect` according to passed parameters.
Stream<std::vector<mediapipe_custom::NormalizedRect>> ConvertDetectionsToRects(
    Stream<std::vector<mediapipe_custom::Detection>> detections,
    Stream<std::pair<int, int>> image_size, int start_keypoint_index,
    int end_keypoint_index, float target_angle,
    mediapipe_custom::api2::builder::Graph& graph);

// Updates @graph to convert @detections into a stream holding vector of
// `NormalizedRect` according to passed parameters and using keypoints.
Stream<mediapipe_custom::NormalizedRect> ConvertDetectionsToRectUsingKeypoints(
    Stream<std::vector<mediapipe_custom::Detection>> detections,
    Stream<std::pair<int, int>> image_size, int start_keypoint_index,
    int end_keypoint_index, float target_angle,
    mediapipe_custom::api2::builder::Graph& graph);

}  // namespace mediapipe_custom::api2::builder

#endif  // MEDIAPIPE_FRAMEWORK_API2_STREAM_DETECTIONS_TO_RECTS_H_
