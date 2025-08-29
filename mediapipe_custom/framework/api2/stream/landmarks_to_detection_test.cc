#include "mediapipe_custom/framework/api2/stream/landmarks_to_detection.h"

#include "mediapipe_custom/framework/api2/builder.h"
#include "mediapipe_custom/framework/formats/detection.pb.h"
#include "mediapipe_custom/framework/formats/landmark.pb.h"
#include "mediapipe_custom/framework/port/gmock.h"
#include "mediapipe_custom/framework/port/gtest.h"
#include "mediapipe_custom/framework/port/parse_text_proto.h"
#include "mediapipe_custom/framework/port/status_matchers.h"

namespace mediapipe_custom::api2::builder {
namespace {

TEST(LandmarksToDetection, VerifyConfig) {
  mediapipe_custom::api2::builder::Graph graph;

  Stream<NormalizedLandmarkList> landmarks =
      graph.In("LANDMARKS").Cast<NormalizedLandmarkList>();
  Stream<Detection> detection = ConvertLandmarksToDetection(landmarks, graph);
  detection.SetName("detection");

  EXPECT_THAT(
      graph.GetConfig(),
      EqualsProto(mediapipe_custom::ParseTextProtoOrDie<CalculatorGraphConfig>(R"pb(
        node {
          calculator: "LandmarksToDetectionCalculator"
          input_stream: "NORM_LANDMARKS:__stream_0"
          output_stream: "DETECTION:detection"
        }
        input_stream: "LANDMARKS:__stream_0"
      )pb")));
}

}  // namespace
}  // namespace mediapipe_custom::api2::builder
