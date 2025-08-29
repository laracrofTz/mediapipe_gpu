#include "mediapipe_custom/framework/api2/stream/presence.h"

#include "mediapipe_custom/framework/api2/builder.h"
#include "mediapipe_custom/framework/calculator.pb.h"
#include "mediapipe_custom/framework/port/gmock.h"
#include "mediapipe_custom/framework/port/gtest.h"
#include "mediapipe_custom/framework/port/parse_text_proto.h"

namespace mediapipe_custom::api2::builder {
namespace {

TEST(Presence, VerifyConfig) {
  Graph graph;

  Stream<int> stream = graph.In("STREAM").Cast<int>();
  stream.SetName("stream_to_check");
  Stream<bool> is_present_stream = IsPresent(stream, graph);
  is_present_stream.SetName("is_present_stream");

  EXPECT_THAT(
      graph.GetConfig(),
      EqualsProto(mediapipe_custom::ParseTextProtoOrDie<CalculatorGraphConfig>(R"pb(
        node {
          calculator: "PacketPresenceCalculator"
          input_stream: "PACKET:stream_to_check"
          output_stream: "PRESENCE:is_present_stream"
        }
        input_stream: "STREAM:stream_to_check"
      )pb")));
}

}  // namespace
}  // namespace mediapipe_custom::api2::builder
