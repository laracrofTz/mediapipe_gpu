To build file: `bazel build -c opt   --copt=-DMESA_EGL_NO_X11_HEADERS --copt=-DEGL_NO_X11   //mediapipe/examples/desktop/dual_gpu_runner:dual_gpu_runner`

To run build: `GLOG_logtostderr=1 bazel-bin/mediapipe/examples/desktop/dual_gpu_runner/dual_gpu_runner`