#ifndef MEDIAPIPE_EXAMPLES_DESKTOP_DUAL_GPU_RUNNER_DUAL_GPU_RUNNER_H_
#define MEDIAPIPE_EXAMPLES_DESKTOP_DUAL_GPU_RUNNER_DUAL_GPU_RUNNER_H_

#include <memory>
#include "absl/status/statusor.h"

namespace mediapipe { class GpuResources; }

namespace mpgpu {
// Create MediaPipe GpuResources bound to EGL device `device_index`.
absl::StatusOr<std::shared_ptr<mediapipe::GpuResources>>
CreateGpuResourcesForDevice(int device_index);
}  // namespace mpgpu

#endif
