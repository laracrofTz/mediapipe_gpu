#include "mediapipe_custom/framework/api3/function_runner_internal.h"

#include <utility>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "mediapipe_custom/framework/calculator_framework.h"
#include "mediapipe_custom/framework/output_stream_poller.h"

namespace mediapipe_custom::api3 {

absl::StatusOr<mediapipe_custom::Packet> GetOutputPacket(OutputStreamPoller& poller,
                                                  CalculatorGraph& graph) {
  mediapipe_custom::Packet packet;
  if (!poller.Next(&packet)) {
    if (graph.HasError()) {
      absl::Status status;
      (void)graph.GetCombinedErrors("Failed to poll the output", &status);
      return status;
    } else {
      return absl::InternalError("Failled to poll the output.");
    }
  }

  // NOTE: currently supporting timestamp-less execution only.
  return std::move(packet).At(Timestamp::Unset());
}

}  // namespace mediapipe_custom::api3
