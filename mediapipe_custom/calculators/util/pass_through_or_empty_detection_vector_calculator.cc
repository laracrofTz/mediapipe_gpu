#include "mediapipe_custom/calculators/util/pass_through_or_empty_detection_vector_calculator.h"

#include <vector>

#include "absl/status/status.h"
#include "mediapipe_custom/framework/api2/node.h"
#include "mediapipe_custom/framework/calculator_context.h"
#include "mediapipe_custom/framework/formats/detection.pb.h"

namespace mediapipe_custom {

class PassThroughOrEmptyDetectionVectorCalculatorImpl
    : public mediapipe_custom::api2::NodeImpl<
          PassThroughOrEmptyDetectionVectorCalculator> {
 public:
  absl::Status Process(CalculatorContext* cc) override {
    if (kInputVector(cc).IsEmpty()) {
      kOutputVector(cc).Send(std::vector<mediapipe_custom::Detection>{});
      return absl::OkStatus();
    }
    kOutputVector(cc).Send(kInputVector(cc));
    return absl::OkStatus();
  }
};
MEDIAPIPE_NODE_IMPLEMENTATION(PassThroughOrEmptyDetectionVectorCalculatorImpl);

}  // namespace mediapipe_custom
