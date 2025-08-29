#include "mediapipe_custom/framework/tool/packet_generator_wrapper_calculator.h"

#include "absl/status/status.h"
#include "mediapipe_custom/framework/calculator_base.h"
#include "mediapipe_custom/framework/calculator_registry.h"
#include "mediapipe_custom/framework/output_side_packet.h"
#include "mediapipe_custom/framework/packet_generator.h"
#include "mediapipe_custom/framework/packet_set.h"
#include "mediapipe_custom/framework/port/status_macros.h"
#include "mediapipe_custom/framework/tool/packet_generator_wrapper_calculator.pb.h"

namespace mediapipe_custom {

absl::Status PacketGeneratorWrapperCalculator::GetContract(
    CalculatorContract* cc) {
  const auto& options =
      cc->Options<::mediapipe_custom::PacketGeneratorWrapperCalculatorOptions>();
  MP_ASSIGN_OR_RETURN(auto static_access,
                      mediapipe_custom::internal::StaticAccessToGeneratorRegistry::
                          CreateByNameInNamespace(options.package(),
                                                  options.packet_generator()));
  MP_RETURN_IF_ERROR(static_access->FillExpectations(options.options(),
                                                     &cc->InputSidePackets(),
                                                     &cc->OutputSidePackets()))
          .SetPrepend()
      << options.packet_generator() << "::FillExpectations() failed: ";
  return absl::OkStatus();
}

absl::Status PacketGeneratorWrapperCalculator::Open(CalculatorContext* cc) {
  const auto& options =
      cc->Options<::mediapipe_custom::PacketGeneratorWrapperCalculatorOptions>();
  MP_ASSIGN_OR_RETURN(auto static_access,
                      mediapipe_custom::internal::StaticAccessToGeneratorRegistry::
                          CreateByNameInNamespace(options.package(),
                                                  options.packet_generator()));
  mediapipe_custom::PacketSet output_packets(cc->OutputSidePackets().TagMap());
  MP_RETURN_IF_ERROR(static_access->Generate(options.options(),
                                             cc->InputSidePackets(),
                                             &output_packets))
          .SetPrepend()
      << options.packet_generator() << "::Generate() failed: ";
  for (auto id = output_packets.BeginId(); id < output_packets.EndId(); ++id) {
    cc->OutputSidePackets().Get(id).Set(output_packets.Get(id));
  }
  return absl::OkStatus();
}

absl::Status PacketGeneratorWrapperCalculator::Process(CalculatorContext* cc) {
  return absl::OkStatus();
}

REGISTER_CALCULATOR(PacketGeneratorWrapperCalculator);

}  // namespace mediapipe_custom
