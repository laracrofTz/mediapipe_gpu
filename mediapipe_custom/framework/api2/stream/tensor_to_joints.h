#ifndef MEDIAPIPE_FRAMEWORK_API2_STREAM_TENSOR_TO_JOINTS_H_
#define MEDIAPIPE_FRAMEWORK_API2_STREAM_TENSOR_TO_JOINTS_H_

#include "mediapipe_custom/framework/api2/builder.h"
#include "mediapipe_custom/framework/formats/body_rig.pb.h"
#include "mediapipe_custom/framework/formats/tensor.h"

namespace mediapipe_custom::api2::builder {

// Updates @graph to convert @tensor to a JointList skipping first @start_index
// values of a @tensor.
Stream<mediapipe_custom::JointList> ConvertTensorToJointsAtIndex(Stream<Tensor> tensor,
                                                          const int num_joints,
                                                          const int start_index,
                                                          Graph& graph);

// Updates @graph to convert @tensor to a JointList.
inline Stream<::mediapipe_custom::JointList> ConvertTensorToJoints(
    Stream<Tensor> tensor, const int num_joints, Graph& graph) {
  return ConvertTensorToJointsAtIndex(tensor, num_joints, /*start_index=*/0,
                                      graph);
}

}  // namespace mediapipe_custom::api2::builder

#endif  // MEDIAPIPE_FRAMEWORK_API2_STREAM_TENSOR_TO_JOINTS_H_
