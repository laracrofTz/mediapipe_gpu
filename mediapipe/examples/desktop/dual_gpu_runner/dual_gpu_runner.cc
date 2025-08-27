#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>

// #include <atomic>
// #include <chrono>
#include <cstdarg>
// #include <cstdlib>
// #include <cstring>
// #include <functional>
// #include <iostream>
#include <memory>
#include <mutex>
// #include <string>
// #include <thread>
// #include <tuple>
#include <vector>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "mediapipe/framework/calculator_graph.h"
#include "mediapipe/framework/port/logging.h"
#include "mediapipe/framework/port/status.h"
#include "mediapipe/framework/port/statusor.h"
#include "mediapipe/examples/desktop/dual_gpu_runner/dual_gpu_runner.h"
#include "mediapipe/framework/deps/status_macros.h"
#include "mediapipe/framework/port/parse_text_proto.h"
#include "mediapipe/gpu/gpu_service.h"
#include "mediapipe/gpu/gl_context.h"
#include "mediapipe/gpu/share"

// namespace mpgpu{
//   absl::StatusOr<std::shared_ptr<mediapipe::GpuResources>>CreateGpuResourcesForDevice(int device_index);
// }

// helpers 
static void Logf(const char* fmt, ...) {
  va_list ap; va_start(ap, fmt);
  char buf[2048]; vsnprintf(buf, sizeof(buf), fmt, ap); va_end(ap);
  std::cout << buf << std::endl;
}

static void LogE(const char* fmt, ...) {
  va_list ap; va_start(ap, fmt);
  char buf[2048]; vsnprintf(buf, sizeof(buf), fmt, ap); va_end(ap);
  std::cerr << buf << std::endl;
}

// Load EGL extension entry points 
static PFNEGLQUERYDEVICESEXTPROC pfn_eglQueryDevicesEXT = nullptr;
static PFNEGLQUERYDEVICESTRINGEXTPROC pfn_eglQueryDeviceStringEXT = nullptr;
static PFNEGLGETPLATFORMDISPLAYEXTPROC pfn_eglGetPlatformDisplayEXT = nullptr;

static bool LoadEglExts() {
  pfn_eglQueryDevicesEXT = (PFNEGLQUERYDEVICESEXTPROC)eglGetProcAddress("eglQueryDevicesEXT");
  pfn_eglQueryDeviceStringEXT = (PFNEGLQUERYDEVICESTRINGEXTPROC)eglGetProcAddress("eglQueryDeviceStringEXT");
  pfn_eglGetPlatformDisplayEXT = (PFNEGLGETPLATFORMDISPLAYEXTPROC)eglGetProcAddress("eglGetPlatformDisplayEXT");
  return pfn_eglQueryDevicesEXT && pfn_eglQueryDeviceStringEXT && pfn_eglGetPlatformDisplayEXT;
}

struct EglObjects {
  EGLDisplay dpy = EGL_NO_DISPLAY;
  EGLContext ctx = EGL_NO_CONTEXT;
  EGLSurface surf = EGL_NO_SURFACE;
  EGLConfig cfg = nullptr;

  void Destroy() {
    if (dpy != EGL_NO_DISPLAY) {
      eglMakeCurrent(dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
      if (surf != EGL_NO_SURFACE) { eglDestroySurface(dpy, surf); surf = EGL_NO_SURFACE; }
      if (ctx != EGL_NO_CONTEXT)   { eglDestroyContext(dpy, ctx); ctx = EGL_NO_CONTEXT; }
      eglTerminate(dpy);
      dpy = EGL_NO_DISPLAY;
    }
  }
  ~EglObjects() { Destroy(); }
};

static bool ChooseConfig(EGLDisplay dpy, EGLConfig* out_cfg, bool es3) {
  const EGLint cfg_attribs_es3[] = {
    EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
    EGL_RED_SIZE,8, EGL_GREEN_SIZE,8, EGL_BLUE_SIZE,8, EGL_ALPHA_SIZE,8,
    EGL_DEPTH_SIZE,16,
    EGL_NONE
  };
  const EGLint cfg_attribs_es2[] = {
    EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
    EGL_RED_SIZE,8, EGL_GREEN_SIZE,8, EGL_BLUE_SIZE,8, EGL_ALPHA_SIZE,8,
    EGL_DEPTH_SIZE,16,
    EGL_NONE
  };
  const EGLint* cfg_attribs = es3 ? cfg_attribs_es3 : cfg_attribs_es2;

  EGLConfig cfg; EGLint n=0;
  if (!eglChooseConfig(dpy, cfg_attribs, &cfg, 1, &n) || n == 0) return false;
  *out_cfg = cfg;
  return true;
}

static bool CreateEglOnDevice(int dev_index, EglObjects* out, int* out_es_major) {
  if (!LoadEglExts()) {
    LogE("Required EGL device extensions are not present.");
    return false;
  }

  EGLDeviceEXT devices[16]; EGLint num=0;
  if (!pfn_eglQueryDevicesEXT(16, devices, &num) || num <= dev_index) {
    LogE("eglQueryDevicesEXT failed or dev_index out of range (have %d, want %d).", num, dev_index);
    return false;
  }

  const char* dev_str = pfn_eglQueryDeviceStringEXT(devices[dev_index], EGL_VENDOR);
  Logf("EGL Device %d vendor: %s", dev_index, dev_str ? dev_str : "(unknown)");

  out->dpy = pfn_eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, (void*)devices[dev_index], nullptr);
  if (out->dpy == EGL_NO_DISPLAY) { LogE("eglGetPlatformDisplayEXT failed."); return false; }
  if (!eglInitialize(out->dpy, nullptr, nullptr)) { LogE("eglInitialize failed."); return false; }

  // Bind GLES API
  if (!eglBindAPI(EGL_OPENGL_ES_API)) { LogE("eglBindAPI(EGL_OPENGL_ES_API) failed."); return false; }

  // Prefer ES3, fall back to ES2 if needed
  EGLConfig cfg;
  bool ok = ChooseConfig(out->dpy, &cfg, /*es3=*/true);
  int es_major = 3;
  if (!ok) {
    Logf("Falling back to GLES2 config.");
    ok = ChooseConfig(out->dpy, &cfg, /*es3=*/false);
    es_major = 2;
  }
  if (!ok) { LogE("eglChooseConfig failed for both ES3 and ES2."); return false; }
  out->cfg = cfg;

  const EGLint ctx_attribs_es3[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
  const EGLint ctx_attribs_es2[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
  const EGLint* ctx_attribs = (es_major==3) ? ctx_attribs_es3 : ctx_attribs_es2;

  out->ctx = eglCreateContext(out->dpy, out->cfg, EGL_NO_CONTEXT, ctx_attribs);
  if (out->ctx == EGL_NO_CONTEXT) {
    LogE("eglCreateContext failed (maybe ES version mismatch).");
    return false;
  }

  const EGLint pb_attribs[] = {EGL_WIDTH, 1, EGL_HEIGHT, 1, EGL_NONE};
  out->surf = eglCreatePbufferSurface(out->dpy, out->cfg, pb_attribs);
  if (out->surf == EGL_NO_SURFACE) { LogE("eglCreatePbufferSurface failed."); return false; }

  if (!eglMakeCurrent(out->dpy, out->surf, out->surf, out->ctx)) {
    LogE("eglMakeCurrent failed."); return false;
  }

  *out_es_major = es_major;
  return true;
}

namespace mpgpu {
  absl::StatusOr<std::shared_ptr<mediapipe::GpuResources>>CreateGpuResourcesForDevice(int device_index) {
    int es = 0;
    auto egl = std::make_unique<EglObjects>();
    if (!CreateEglOnDevice(device_index, egl.get(), &es)){
      return absl::InternalError("CreateEglOnDevice failed.");
    }

    // create gpu resources while display/context is current
    MP_ASSIGN_OR_RETURN(auto gpu, mediapipe::GpuResources::Create())
  }
}

static void PrintRenderer() {
  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  const GLubyte* vendor  = glGetString(GL_VENDOR);
  Logf("GL_RENDERER : %s", renderer ? reinterpret_cast<const char*>(renderer) : "(null)");
  Logf("GL_VERSION  : %s", version ? reinterpret_cast<const char*>(version) : "(null)");
  Logf("GL_VENDOR   : %s", vendor  ? reinterpret_cast<const char*>(vendor)  : "(null)");
}

// --- Minimal MediaPipe graph ---------------------------------------------------------
// We'll build a tiny pass-through graph: input video frames (or any packets) go through
// PassThroughCalculator to an output. We only care about exercising graph startup
// and attaching GpuResources.

static mediapipe::CalculatorGraphConfig MakeTinyGraph() {
  // graph {
  //   input_stream: "in"
  //   node { calculator: "PassThroughCalculator" input_stream: "in" output_stream: "out" }
  //   output_stream: "out"
  // }
  mediapipe::CalculatorGraphConfig cfg =
      mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(R"pb(
        input_stream: "in"
        node {
          calculator: "PassThroughCalculator"
          input_stream: "in"
          output_stream: "out"
        }
        output_stream: "out"
      )pb");
  return cfg;
}

static absl::Status RunGraphOn(mediapipe::CalculatorGraph* graph,
                               std::shared_ptr<mediapipe::GpuResources> gpu,
                               int iters, const std::string& tag) {
  MP_RETURN_IF_ERROR(graph->SetGpuResources(gpu));
  auto cfg = MakeTinyGraph();
  MP_RETURN_IF_ERROR(graph->Initialize(cfg));

  // Output poller just to drain output
  MP_ASSIGN_OR_RETURN(auto poller, graph->AddOutputStreamPoller("out"));
  MP_RETURN_IF_ERROR(graph->StartRun({}));

  // Feed some dummy packets (timestamps 0..iters-1)
  for (int i = 0; i < iters; ++i) {
    MP_RETURN_IF_ERROR(graph->AddPacketToInputStream(
        "in", mediapipe::Adopt(new int(i)).At(mediapipe::Timestamp(i))));
  }

  MP_RETURN_IF_ERROR(graph->CloseInputStream("in"));

  mediapipe::Packet p;
  while (poller.Next(&p)) {
    // no-op, just draining
  }

  MP_RETURN_IF_ERROR(graph->WaitUntilDone());
  Logf("[%s] graph finished.", tag.c_str());
  return absl::OkStatus();
}

// Argument parsing

static int GetFlagInt(const char* name, int def, int argc, char** argv) {
  const std::string pref = std::string("--") + name + "=";
  for (int i = 1; i < argc; ++i) {
    if (strncmp(argv[i], pref.c_str(), pref.size()) == 0) {
      return atoi(argv[i] + pref.size());
    }
  }
  return def;
}

int main(int argc, char** argv) {
  int dev0 = GetFlagInt("dev0", 0, argc, argv);
  int dev1 = GetFlagInt("dev1", 1, argc, argv);
  int iters = GetFlagInt("iters", 120, argc, argv);

  Logf("Selecting devices: dev0=%d, dev1=%d (iters=%d)", dev0, dev1, iters);

  // Create EGL objects for both devices (in main thread)
  EglObjects egl0; int es0 = 0;
  if (!CreateEglOnDevice(dev0, &egl0, &es0)) {
    LogE("Failed to create EGL on device %d", dev0);
    return 1;
  }
  Logf("[GPU %d] Created EGL context (ES%d). Renderer strings:", dev0, es0);
  PrintRenderer();

  EglObjects egl1; int es1 = 0;
  if (!CreateEglOnDevice(dev1, &egl1, &es1)) {
    LogE("Failed to create EGL on device %d", dev1);
    return 1;
  }
  Logf("[GPU %d] Created EGL context (ES%d). Renderer strings:", dev1, es1);
  PrintRenderer();

  // Two graphs (one per GPU).
  mediapipe::CalculatorGraph g0, g1;

  absl::Status s0, s1;
  std::thread t0([&] {
    // Make device 0 context current in this thread
    eglMakeCurrent(egl0.dpy, egl0.surf, egl0.surf, egl0.ctx);

    assert(eglGetCurrentContext() == egl0.ctx && "External EGLContext must be current");

    // Create GpuResources bound to this current context (thread-local creation)
    auto gpu0_or = mediapipe::GpuResources::Create();
    if (!gpu0_or.ok()) {
      s0 = gpu0_or.status();
      return;
    }
    auto gpu0 = *gpu0_or;

    s0 = RunGraphOn(&g0, gpu0, iters, "GPU0");

    eglMakeCurrent(egl0.dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
  });

  std::thread t1([&] {
    eglMakeCurrent(egl1.dpy, egl1.surf, egl1.surf, egl1.ctx);

    assert(eglGetCurrentContext() == egl1.ctx && "External EGLContext must be current");

    auto gpu1_or = mediapipe::GpuResources::Create();
    if (!gpu1_or.ok()) {
      s1 = gpu1_or.status();
      return;
    }
    auto gpu1 = *gpu1_or;

    s1 = RunGraphOn(&g1, gpu1, iters, "GPU1");

    eglMakeCurrent(egl1.dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
  });

  t0.join();
  t1.join();

  if (!s0.ok()) { LogE("Graph 0 failed: %s", s0.ToString().c_str()); return 2; }
  if (!s1.ok()) { LogE("Graph 1 failed: %s", s1.ToString().c_str()); return 3; }

  Logf("All done.");
  return 0;
}
