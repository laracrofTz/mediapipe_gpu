#ifndef MEDIAPIPE_FRAMEWORK_API2_STREAM_LANDMARKS_TO_DETECTION_H_
#define MEDIAPIPE_FRAMEWORK_API2_STREAM_LANDMARKS_TO_DETECTION_H_

#include "mediapipe_custom/framework/api2/builder.h"
#include "mediapipe_custom/framework/formats/detection.pb.h"
#include "mediapipe_custom/framework/formats/landmark.pb.h"

namespace mediapipe_custom::api2::builder {

// Updates @graph to convert @landmarks to a detection.
Stream<mediapipe_custom::Detection> ConvertLandmarksToDetection(
    Stream<mediapipe_custom::NormalizedLandmarkList> landmarks, Graph& graph);

}  // namespace mediapipe_custom::api2::builder

#endif  // MEDIAPIPE_FRAMEWORK_API2_STREAM_LANDMARKS_TO_DETECTION_H_
