#include <cstdint>
#include <utility>

#include "absl/status/status.h"
#include "mediapipe_custom/framework/calculator_runner.h"
#include "mediapipe_custom/framework/formats/image_frame.h"
#include "mediapipe_custom/framework/packet.h"
#include "mediapipe_custom/framework/port/gtest.h"
#include "mediapipe_custom/framework/port/parse_text_proto.h"
#include "mediapipe_custom/framework/port/status_matchers.h"
#include "mediapipe_custom/framework/timestamp.h"

namespace mediapipe_custom {
namespace {

using ::testing::HasSubstr;
using ::testing::status::StatusIs;

mediapipe_custom::ImageFrame GetInputFrame(
    const int width, const int height, const int channel,
    const mediapipe_custom::ImageFormat::Format image_format) {
  const int total_size = width * height * channel;

  mediapipe_custom::ImageFrame input_frame(image_format, width, height,
                                    /*alignment_boundary =*/1);
  uint8_t* pixel_data = input_frame.MutablePixelData();
  for (int i = 0; i < total_size; ++i) {
    pixel_data[i] = i % 256;
  }

  return input_frame;
}

mediapipe_custom::CalculatorGraphConfig::Node GetTestingGraphNode() {
  return ParseTextProtoOrDie<mediapipe_custom::CalculatorGraphConfig::Node>(
      R"pb(
        calculator: "ScaleImageCalculator"
        input_stream: "input_frames"
        output_stream: "scaled_frames"
        options {
          [mediapipe.ScaleImageCalculatorOptions.ext] {
            input_format: SRGB
            output_format: SRGB
            target_width: 720
            target_height: 720
            preserve_aspect_ratio: true
          }
        }
      )pb");
}

TEST(ScaleImageCalculatorTest, ScaleRegualrSize) {
  auto calculator_node = GetTestingGraphNode();
  mediapipe_custom::CalculatorRunner runner(calculator_node);

  // Vertical 9:16 720P input frame
  auto input_frame = GetInputFrame(720, 1280, 3, mediapipe_custom::ImageFormat::SRGB);
  auto input_frame_packet =
      mediapipe_custom::MakePacket<mediapipe_custom::ImageFrame>(std::move(input_frame));
  runner.MutableInputs()->Index(0).packets.push_back(
      input_frame_packet.At(mediapipe_custom::Timestamp(1)));
  MP_ASSERT_OK(runner.Run());
}

TEST(ScaleImageCalculatorTest, ScaleOddSize) {
  auto calculator_node = GetTestingGraphNode();
  mediapipe_custom::CalculatorRunner runner(calculator_node);

  // 1 x 512 input frame
  auto input_frame = GetInputFrame(1, 512, 3, mediapipe_custom::ImageFormat::SRGB);
  auto input_frame_packet =
      mediapipe_custom::MakePacket<mediapipe_custom::ImageFrame>(std::move(input_frame));
  runner.MutableInputs()->Index(0).packets.push_back(
      input_frame_packet.At(mediapipe_custom::Timestamp(1)));
  ASSERT_THAT(runner.Run(),
              StatusIs(absl::StatusCode::kInvalidArgument,
                       HasSubstr("Image frame is empty before rescaling.")));
}

}  // namespace
}  // namespace mediapipe_custom
