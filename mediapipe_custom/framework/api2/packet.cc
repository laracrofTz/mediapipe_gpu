#include "mediapipe_custom/framework/api2/packet.h"

namespace mediapipe_custom {
namespace api2 {

PacketBase FromOldPacket(const mediapipe_custom::Packet& op) {
  return PacketBase(packet_internal::GetHolderShared(op)).At(op.Timestamp());
}

PacketBase FromOldPacket(mediapipe_custom::Packet&& op) {
  Timestamp t = op.Timestamp();
  return PacketBase(packet_internal::GetHolderShared(std::move(op))).At(t);
}

mediapipe_custom::Packet ToOldPacket(const PacketBase& p) {
  return mediapipe_custom::packet_internal::Create(p.payload_, p.timestamp_);
}

mediapipe_custom::Packet ToOldPacket(PacketBase&& p) {
  return mediapipe_custom::packet_internal::Create(std::move(p.payload_),
                                            p.timestamp_);
}

}  // namespace api2
}  // namespace mediapipe_custom
