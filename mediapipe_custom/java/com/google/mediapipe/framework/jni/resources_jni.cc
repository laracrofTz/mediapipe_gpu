// Copyright 2025 The MediaPipe Authors.
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

#include "mediapipe_custom/java/com/google/mediapipe/framework/jni/resources_jni.h"

#include <jni.h>

#include <memory>
#include <string>
#include <utility>

#include "absl/container/flat_hash_map.h"
#include "mediapipe_custom/framework/resources.h"
#include "mediapipe_custom/framework/resources_service.h"
#include "mediapipe_custom/java/com/google/mediapipe/framework/jni/graph_service_jni.h"
#include "mediapipe_custom/java/com/google/mediapipe/framework/jni/jni_util.h"

using HandleType = std::shared_ptr<mediapipe_custom::Resources>*;

JNIEXPORT void JNICALL MEDIAPIPE_RESOURCES_SERVICE_METHOD(
    nativeInstallServiceObject)(JNIEnv* env, jobject thiz, jlong context,
                                jobject resourcesMapping) {
  absl::flat_hash_map<std::string, std::string> mapping =
      mediapipe_custom::android::JMapToAbslStringMap(env, resourcesMapping);
  std::unique_ptr<mediapipe_custom::Resources> resources =
      mediapipe_custom::CreateDefaultResourcesWithMapping(mapping);
  HandleType handle =
      new std::shared_ptr<mediapipe_custom::Resources>(std::move(resources));

  mediapipe_custom::android::GraphServiceHelper::SetServiceObject(
      context, mediapipe_custom::kResourcesService, *handle);
}
