#include "mediapipe_custom/framework/api2/stream/merge.h"

#include "mediapipe_custom/framework/api2/builder.h"
#include "mediapipe_custom/framework/calculator_framework.h"
#include "mediapipe_custom/framework/port/gmock.h"
#include "mediapipe_custom/framework/port/gtest.h"
#include "mediapipe_custom/framework/port/parse_text_proto.h"

namespace mediapipe_custom::api2::builder {
namespace {

TEST(Merge, VerifyConfig) {
  mediapipe_custom::api2::builder::Graph graph;

  Stream<int> input_a = graph.In("INPUT_A").Cast<int>();
  Stream<int> input_b = graph.In("INPUT_B").Cast<int>();
  Stream<int> input = Merge(input_a, input_b, graph);
  input.SetName("input");

  EXPECT_THAT(
      graph.GetConfig(),
      EqualsProto(mediapipe_custom::ParseTextProtoOrDie<CalculatorGraphConfig>(R"pb(
        node {
          calculator: "MergeCalculator"
          input_stream: "__stream_0"
          input_stream: "__stream_1"
          output_stream: "input"
        }
        input_stream: "INPUT_A:__stream_0"
        input_stream: "INPUT_B:__stream_1"
      )pb")));
}

}  // namespace
}  // namespace mediapipe_custom::api2::builder
