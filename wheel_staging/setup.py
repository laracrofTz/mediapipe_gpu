from pathlib import Path
from setuptools import setup, find_packages
import os

packages = find_packages(where=".", include=["mediapipe_custom", "mediapipe_custom.*"])
if not packages:
    raise SystemExit("Could not find 'mediapipe_custom' package here.")

# Warn if the binding is missing
has_binding = any(Path(".").glob("mediapipe_custom/python/_framework_bindings*.so")) \
           or any(Path(".").glob("mediapipe_custom/python/_framework_bindings*.pyd"))
if not has_binding:
    print("Missing mediapipe_custom/python/_framework_bindings.*")

setup(
    name="mediapipe-custom",
    version=os.environ.get("MEDIAPIPE_CUSTOM_VERSION", "0.0.1+eglpatch"),
    description="MediaPipe fork with custom EGL changes",
    python_requires=">=3.9",
    packages=packages,
    include_package_data=True,
    package_data={
        "mediapipe_custom": [
            "**/*.pbtxt", "**/*.binarypb", "**/*.tflite", "**/*.json",
            "python/_framework_bindings*.so", "python/_framework_bindings*.pyd",
        ]
    },
    zip_safe=False,
)
