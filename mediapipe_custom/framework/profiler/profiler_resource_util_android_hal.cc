#include "mediapipe_custom/framework/port/statusor.h"

namespace mediapipe_custom {

StatusOr<std::string> GetDefaultTraceLogDirectory() {
  return "/data/local/tmp";
}

}  // namespace mediapipe_custom
