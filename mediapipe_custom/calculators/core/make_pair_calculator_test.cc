// Copyright 2021 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "mediapipe_custom/framework/calculator_framework.h"
#include "mediapipe_custom/framework/calculator_runner.h"
#include "mediapipe_custom/framework/port/canonical_errors.h"
#include "mediapipe_custom/framework/port/gmock.h"
#include "mediapipe_custom/framework/port/gtest.h"
#include "mediapipe_custom/framework/port/status.h"
#include "mediapipe_custom/framework/port/status_matchers.h"
#include "mediapipe_custom/framework/timestamp.h"
#include "mediapipe_custom/framework/tool/validate_type.h"
#include "mediapipe_custom/util/packet_test_util.h"
#include "mediapipe_custom/util/time_series_test_util.h"

namespace mediapipe_custom {

class MakePairCalculatorTest
    : public mediapipe_custom::TimeSeriesCalculatorTest<mediapipe_custom::NoOptions> {
 protected:
  void SetUp() override {
    calculator_name_ = "MakePairCalculator";
    num_input_streams_ = 2;
  }
};

TEST_F(MakePairCalculatorTest, ProducesExpectedPairs) {
  InitializeGraph();
  AppendInputPacket(new std::string("first packet"), Timestamp(1),
                    /* input_index= */ 0);
  AppendInputPacket(new std::string("second packet"), Timestamp(5),
                    /* input_index= */ 0);
  AppendInputPacket(new int(10), Timestamp(1), /* input_index= */ 1);
  AppendInputPacket(new int(20), Timestamp(5), /* input_index= */ 1);

  MP_ASSERT_OK(RunGraph());

  EXPECT_THAT(
      output().packets,
      ::testing::ElementsAre(
          mediapipe_custom::PacketContainsTimestampAndPayload<
              std::pair<Packet, Packet>>(
              Timestamp(1),
              ::testing::Pair(
                  mediapipe_custom::PacketContainsTimestampAndPayload<std::string>(
                      Timestamp(1), std::string("first packet")),
                  mediapipe_custom::PacketContainsTimestampAndPayload<int>(
                      Timestamp(1), 10))),
          mediapipe_custom::PacketContainsTimestampAndPayload<
              std::pair<Packet, Packet>>(
              Timestamp(5),
              ::testing::Pair(
                  mediapipe_custom::PacketContainsTimestampAndPayload<std::string>(
                      Timestamp(5), std::string("second packet")),
                  mediapipe_custom::PacketContainsTimestampAndPayload<int>(
                      Timestamp(5), 20)))));
}

}  // namespace mediapipe_custom
