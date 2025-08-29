#include "mediapipe_custom/framework/api2/stream/landmarks_to_detection.h"

#include "mediapipe_custom/framework/api2/builder.h"
#include "mediapipe_custom/framework/formats/detection.pb.h"
#include "mediapipe_custom/framework/formats/landmark.pb.h"

namespace mediapipe_custom::api2::builder {

Stream<mediapipe_custom::Detection> ConvertLandmarksToDetection(
    Stream<mediapipe_custom::NormalizedLandmarkList> landmarks, Graph& graph) {
  auto& landmarks_to_detection =
      graph.AddNode("LandmarksToDetectionCalculator");
  landmarks.ConnectTo(landmarks_to_detection.In("NORM_LANDMARKS"));
  return landmarks_to_detection.Out("DETECTION").Cast<mediapipe_custom::Detection>();
}

}  // namespace mediapipe_custom::api2::builder
