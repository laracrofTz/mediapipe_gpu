#include "mediapipe_custom/framework/api2/stream/landmarks_projection.h"

#include <array>

#include "mediapipe_custom/framework/api2/builder.h"
#include "mediapipe_custom/framework/formats/landmark.pb.h"

namespace mediapipe_custom::api2::builder {

Stream<mediapipe_custom::NormalizedLandmarkList> ProjectLandmarks(
    Stream<mediapipe_custom::NormalizedLandmarkList> landmarks,
    Stream<std::array<float, 16>> projection_matrix, Graph& graph) {
  auto& projector = graph.AddNode("LandmarkProjectionCalculator");
  landmarks.ConnectTo(projector.In("NORM_LANDMARKS"));
  projection_matrix.ConnectTo(projector.In("PROJECTION_MATRIX"));
  return projector.Out("NORM_LANDMARKS")
      .Cast<mediapipe_custom::NormalizedLandmarkList>();
}

}  // namespace mediapipe_custom::api2::builder
