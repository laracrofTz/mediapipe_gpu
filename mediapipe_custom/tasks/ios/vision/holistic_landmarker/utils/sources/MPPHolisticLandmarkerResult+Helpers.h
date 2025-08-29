// Copyright 2024 The MediaPipe Authors.
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

#ifndef __cplusplus
#error "This file requires Objective-C++."
#endif  // __cplusplus

#include "mediapipe_custom/framework/formats/classification.pb.h"
#include "mediapipe_custom/framework/formats/image.h"
#include "mediapipe_custom/framework/formats/landmark.pb.h"
#include "mediapipe_custom/framework/packet.h"

#import "mediapipe/tasks/ios/vision/holistic_landmarker/sources/MPPHolisticLandmarkerResult.h"

NS_ASSUME_NONNULL_BEGIN

@interface MPPHolisticLandmarkerResult (Helpers)

/**
 * Creates a `MPPHolisticLandmarkerResult` from face landmarks, face blend shapes, pose landmarks,
 * pose world landmarks, pose segmentation mask, left hand landmarks, left hand world landmarks,
 * right hand landmarks and right hand world landmarks packets.
 *
 * @param faceLandmarksPacket A MediaPipe packet wrapping a
 * `std::vector<mediapipe_custom::NormalizedLandmarkList>`.
 * @param faceBlendShapesPacket A MediaPipe packet wrapping a
 * `std::vector<mediapipe_custom::ClassificationList>`.
 * @param poseLandmarksPacket a MediaPipe packet wrapping a
 * `std::vector<mediapipe_custom::NormalizedlandmarkList>`.
 * @param poseWorldLandmarksPacket a MediaPipe packet wrapping a
 * `std::vector<mediapipe_custom::LandmarkList>`.
 * @param poseSegmentationMaskPacket a MediaPipe packet wrapping a `mediapipe_custom::Image`.
 * @param leftHandLandmarksPacket a MediaPipe packet wrapping a
 * `std::vector<mediapipe_custom::NormalizedlandmarkList>`.
 * @param leftHandWorldLandmarksPacket a MediaPipe packet wrapping a
 * `std::vector<mediapipe_custom::LandmarkList>`.
 * @param rightHandLandmarksPacket a MediaPipe packet wrapping a
 * `std::vector<mediapipe_custom::NormalizedlandmarkList>`.
 * @param rightHandWorldLandmarksPacket a MediaPipe packet wrapping a
 * `std::vector<mediapipe_custom::LandmarkList>`.
 *
 * @return  An `MPPHolisticLandmarkerResult` object that contains the holistic landmark detection
 * results.
 */
+ (MPPHolisticLandmarkerResult *)
    holisticLandmarkerResultWithFaceLandmarksPacket:(const mediapipe_custom::Packet &)faceLandmarksPacket
                              faceBlendshapesPacket:(const mediapipe_custom::Packet &)faceBlendShapesPacket
                                poseLandmarksPacket:(const mediapipe_custom::Packet &)poseLandmarksPacket
                           poseWorldLandmarksPacket:
                               (const mediapipe_custom::Packet &)poseWorldLandmarksPacket
                         poseSegmentationMaskPacket:
                             (const mediapipe_custom::Packet &)poseSegmentationMaskPacket
                            leftHandLandmarksPacket:
                                (const mediapipe_custom::Packet &)leftHandLandmarksPacket
                       leftHandWorldLandmarksPacket:
                           (const mediapipe_custom::Packet &)leftHandWorldLandmarksPacket
                           rightHandLandmarksPacket:
                               (const mediapipe_custom::Packet &)rightHandLandmarksPacket
                      rightHandWorldLandmarksPacket:
                          (const mediapipe_custom::Packet &)rightHandWorldLandmarksPacket;

/**
 * Creates a `MPPHolisticLandmarkerResult` from face landmarks, face blend shapes, pose landmarks,
 * pose world landmarks, pose segmentation mask, left hand landmarks, left hand world landmarks,
 * right hand landmarks, right hand world landmarks and timestamp in milliseconds.
 *
 * @param faceLandmarksProto A proto of type `mediapipe_custom::NormalizedlandmarkList`.
 * @param faceBlendshapesProto A proto of type `mediapipe_custom::ClassificationList`.
 * @param poseLandmarksProto A proto of type `mediapipe_custom::NormalizedlandmarkList`.
 * @param poseWorldLandmarksProto A proto of type `mediapipe_custom::LandmarkList`.
 * @param poseSegmentationMaskProto A proto of type `mediapipe_custom::Image`.
 * @param leftHandLandmarksProto A proto of type `mediapipe_custom::NormalizedlandmarkList`.
 * @param leftHandWorldLandmarksProto A proto of type `mediapipe_custom::LandmarkList`.
 * @param rightHandLandmarksProto A proto of type `mediapipe_custom::NormalizedlandmarkList`.
 * @param rightHandWorldLandmarksProto A proto of type `mediapipe_custom::LandmarkList`.
 * @param timestampInMilliseconds The timestamp of the result.
 *
 * @return  A `MPPHolisticLandmarkerResult` object created from the given protos and timestamp in
 * milliseconds.
 */
+ (MPPHolisticLandmarkerResult *)
    holisticLandmarkerResultWithFaceLandmarksProto:
        (const mediapipe_custom::NormalizedLandmarkList &)faceLandmarksProto
                              faceBlendshapesProto:
                                  (const mediapipe_custom::ClassificationList *)faceBlendshapesProto
                                poseLandmarksProto:
                                    (const mediapipe_custom::NormalizedLandmarkList &)poseLandmarksProto
                           poseWorldLandmarksProto:
                               (const mediapipe_custom::LandmarkList &)poseWorldLandmarksProto
                         poseSegmentationMaskProto:
                             (const ::mediapipe_custom::Image *)poseSegmentationMaskProto
                            leftHandLandmarksProto:
                                (const mediapipe_custom::NormalizedLandmarkList &)leftHandLandmarksProto
                       leftHandWorldLandmarksProto:
                           (const mediapipe_custom::LandmarkList &)leftHandWorldLandmarksProto
                           rightHandLandmarksProto:
                               (const mediapipe_custom::NormalizedLandmarkList &)rightHandLandmarksProto
                      rightHandWorldLandmarksProto:
                          (const mediapipe_custom::LandmarkList &)rightHandWorldLandmarksProto
                           timestampInMilliseconds:(NSInteger)timestampInMilliseconds;

@end

NS_ASSUME_NONNULL_END
