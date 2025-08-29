#include "mediapipe_custom/gpu/gpu_origin_utils.h"

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"

namespace mediapipe_custom {

absl::StatusOr<bool> IsGpuOriginAtBottom(mediapipe_custom::GpuOrigin::Mode origin) {
  switch (origin) {
    case mediapipe_custom::GpuOrigin::TOP_LEFT:
      return false;
    case mediapipe_custom::GpuOrigin::DEFAULT:
    case mediapipe_custom::GpuOrigin::CONVENTIONAL:
      // TOP_LEFT on Metal, BOTTOM_LEFT on OpenGL.
#ifdef __APPLE__
      return false;
#else
      return true;
#endif
    default:
      return absl::InvalidArgumentError(
          absl::StrFormat("Unhandled GPU origin %i", origin));
  }
}

}  // namespace mediapipe_custom
