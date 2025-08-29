#include "mediapipe_custom/framework/api2/stream/tensor_to_joints.h"

#include <vector>

#include "mediapipe_custom/framework/api2/builder.h"
#include "mediapipe_custom/framework/calculator_framework.h"
#include "mediapipe_custom/framework/formats/body_rig.pb.h"
#include "mediapipe_custom/framework/formats/tensor.h"
#include "mediapipe_custom/framework/port/gmock.h"
#include "mediapipe_custom/framework/port/gtest.h"
#include "mediapipe_custom/framework/port/parse_text_proto.h"
#include "mediapipe_custom/framework/port/status_matchers.h"

namespace mediapipe_custom::api2::builder {
namespace {

TEST(ConvertTensorToJoints, ConvertTensorToJoints) {
  Graph graph;

  Stream<Tensor> tensor = graph.In("TENSOR").Cast<Tensor>();
  Stream<JointList> joint_list =
      ConvertTensorToJoints(tensor, /*num_joints=*/56, graph);
  joint_list.SetName("joints");

  EXPECT_THAT(graph.GetConfig(),
              EqualsProto(ParseTextProtoOrDie<CalculatorGraphConfig>(R"pb(
                node {
                  calculator: "TensorToJointsCalculator"
                  input_stream: "TENSOR:__stream_0"
                  output_stream: "JOINTS:joints"
                  options {
                    [mediapipe.TensorToJointsCalculatorOptions.ext] {
                      num_joints: 56
                      start_index: 0
                    }
                  }
                }
                input_stream: "TENSOR:__stream_0"
              )pb")));

  CalculatorGraph calcualtor_graph;
  MP_EXPECT_OK(calcualtor_graph.Initialize(graph.GetConfig()));
}

TEST(ConvertTensorToJointsAtIndex, ConvertTensorToJointsAtIndex) {
  Graph graph;

  Stream<Tensor> tensor = graph.In("TENSOR").Cast<Tensor>();
  Stream<JointList> joint_list = ConvertTensorToJointsAtIndex(
      tensor, /*num_joints=*/56, /*start_index=*/3, graph);
  joint_list.SetName("joints");

  EXPECT_THAT(graph.GetConfig(),
              EqualsProto(ParseTextProtoOrDie<CalculatorGraphConfig>(R"pb(
                node {
                  calculator: "TensorToJointsCalculator"
                  input_stream: "TENSOR:__stream_0"
                  output_stream: "JOINTS:joints"
                  options {
                    [mediapipe.TensorToJointsCalculatorOptions.ext] {
                      num_joints: 56
                      start_index: 3
                    }
                  }
                }
                input_stream: "TENSOR:__stream_0"
              )pb")));

  CalculatorGraph calcualtor_graph;
  MP_EXPECT_OK(calcualtor_graph.Initialize(graph.GetConfig()));
}

}  // namespace
}  // namespace mediapipe_custom::api2::builder
