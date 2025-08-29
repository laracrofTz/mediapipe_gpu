bazel_dep(name = "rules_python", version = "0.34.0")

use_extension("@rules_python//python/extensions:pip.bzl", "pip")

pip.parse(
    name = "mediapipe_pip_deps",
    requirements = "requirements.txt",
)

use_repo(
    pip,
    "mediapipe_pip_deps_numpy",
    "mediapipe_pip_deps_absl_py",
    "mediapipe_pip_deps_protobuf",
    "mediapipe_pip_deps_attrs",
    "mediapipe_pip_deps_pyyaml",
    "mediapipe_pip_deps_six",
)
