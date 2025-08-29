# Copyright 2019 - 2022 The MediaPipe Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from mediapipe_custom.python import *
import mediapipe_custom.python.solutions as solutions 
import mediapipe_custom.tasks.python as tasks

# Re-export the native bindings at the top level.
from .python import _framework_bindings as _framework_bindings
import sys as _sys, importlib as _importlib

# Make "mediapipe_custom._framework_bindings" refer to the same module object
_sys.modules[__name__ + "._framework_bindings"] = _framework_bindings

# Safety: route pb2-heavy subpackages to the official mediapipe to avoid duplicate descriptors.
for _sub in [
    "framework.formats",
    "calculators.util",
    "util",
    # add more if you ever see a pb2 import error from another sub-tree
]:
    try:
        _mod = _importlib.import_module(f"mediapipe.{_sub}")
        _sys.modules[f"{__name__}.{_sub}"] = _mod
    except Exception:
        pass

del framework
del gpu
del modules
del python
del mediapipe_custom
del util
__version__ = '0.10.21'
