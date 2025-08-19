#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <memory>
#include <thread>
#include <vector>
#include <iostream>

#include "absl/status/statusor.h"
#include "mediapipe/framework/calculator_graph.h"
#include "mediapipe/framework/port/status.h"
#include "mediapipe/gpu/gpu_service.h"
#include "mediapipe/gpu/gl_context.h"
#include "mediapipe/framework/port/logging.h"

// --- Helpers to load extension entry points ---
static PFNEGLQUERYDEVICESEXTPROC eglQueryDevicesEXT = nullptr;
static PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT = nullptr;

bool LoadEGLExtensions() {
  eglQueryDevicesEXT =
      (PFNEGLQUERYDEVICESEXTPROC)eglGetProcAddress("eglQueryDevicesEXT");
  eglGetPlatformDisplayEXT =
      (PFNEGLGETPLATFORMDISPLAYEXTPROC)eglGetProcAddress("eglGetPlatformDisplayEXT");
  return eglQueryDevicesEXT && eglGetPlatformDisplayEXT;
}

struct GpuCtx {
  EGLDeviceEXT dev = nullptr;
  EGLDisplay dpy = EGL_NO_DISPLAY;
  EGLContext ctx = EGL_NO_CONTEXT;
  EGLSurface surf = EGL_NO_SURFACE;
};

absl::StatusOr<GpuCtx> MakeHeadlessES3Context(EGLDeviceEXT dev) {
  GpuCtx gc; gc.dev = dev;

  gc.dpy = eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, dev, nullptr);
  if (gc.dpy == EGL_NO_DISPLAY) return absl::UnknownError("No EGLDisplay");

  if (!eglInitialize(gc.dpy, nullptr, nullptr))
    return absl::UnknownError("eglInitialize failed");

  const EGLint cfg_attrs[] = {
    EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
    EGL_RED_SIZE,8, EGL_GREEN_SIZE,8, EGL_BLUE_SIZE,8, EGL_ALPHA_SIZE,8,
    EGL_NONE
  };
  EGLConfig cfg; EGLint n=0;
  if (!eglChooseConfig(gc.dpy, cfg_attrs, &cfg, 1, &n) || n < 1)
    return absl::UnknownError("eglChooseConfig failed");

  const EGLint pb[] = {EGL_WIDTH,16, EGL_HEIGHT,16, EGL_NONE};
  gc.surf = eglCreatePbufferSurface(gc.dpy, cfg, pb);
  if (gc.surf == EGL_NO_SURFACE)
    return absl::UnknownError("eglCreatePbufferSurface failed");

  eglBindAPI(EGL_OPENGL_ES_API);
  const EGLint ctx_attrs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
  gc.ctx = eglCreateContext(gc.dpy, cfg, EGL_NO_CONTEXT, ctx_attrs);
  if (gc.ctx == EGL_NO_CONTEXT)
    return absl::UnknownError("eglCreateContext failed");

  return gc;
}

absl::Status RunGraphOn(const GpuCtx& gc,
                        const mediapipe::CalculatorGraphConfig& cfg) {
  // Make this context current on *this* thread.
  if (!eglMakeCurrent(gc.dpy, gc.surf, gc.surf, gc.ctx))
    return absl::UnknownError("eglMakeCurrent failed");

  using PlatformGlContext = mediapipe::GlContext::PlatformGlContext;

  // Construct GpuResources from an *external* EGLContext and install it
  // as the graph's GPU service (kGpuService).
  auto gpu_res = std::make_shared<mediapipe::GpuResources>(
      (PlatformGlContext)gc.ctx);

  mediapipe::CalculatorGraph graph;
  // Either SetServiceObject(kGpuService, ...) or SetGpuResources(...) depending on version.
  // Preferred public service API:
  MP_RETURN_IF_ERROR(graph.SetServiceObject(mediapipe::kGpuService, gpu_res));

  MP_RETURN_IF_ERROR(graph.Initialize(cfg));
  MP_RETURN_IF_ERROR(graph.StartRun({}));

  // TODO: feed inputs / poll outputs as your application needs.
  // For a smoke test you can just stop immediately:
  MP_RETURN_IF_ERROR(graph.CloseAllPacketSources());
  return graph.WaitUntilDone();
}

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);

  if (!LoadEGLExtensions()) {
    std::cerr << "EGL_EXT_device/platform_device not available\n";
    return 1;
  }

  // 1) Enumerate devices
  EGLDeviceEXT devices[8]; EGLint ndev = 0;
  if (!eglQueryDevicesEXT(8, devices, &ndev) || ndev < 2) {
    std::cerr << "Need >= 2 EGL devices (found " << ndev << ")\n";
    return 1;
  }

  // 2) Create one context per GPU
  auto gc0_or = MakeHeadlessES3Context(devices[0]);
  auto gc1_or = MakeHeadlessES3Context(devices[1]);
  if (!gc0_or.ok() || !gc1_or.ok()) {
    std::cerr << "Context creation failed\n";
    return 1;
  }
  GpuCtx gc0 = *gc0_or; GpuCtx gc1 = *gc1_or;

  // Optional: print renderer strings for sanity
  eglMakeCurrent(gc0.dpy, gc0.surf, gc0.surf, gc0.ctx);
  std::cerr << "GPU0 GL_RENDERER: " << glGetString(GL_RENDERER) << "\n";
  eglMakeCurrent(gc1.dpy, gc1.surf, gc1.surf, gc1.ctx);
  std::cerr << "GPU1 GL_RENDERER: " << glGetString(GL_RENDERER) << "\n";

  // 3) Load or build your CalculatorGraphConfig objects (cfg0, cfg1).
  // For brevity, you'd parse from .pbtxt or build in code.
  mediapipe::CalculatorGraphConfig cfg0; // TODO: fill
  mediapipe::CalculatorGraphConfig cfg1; // TODO: fill

  // 4) Run each graph on its own thread (each with its own current context)
  absl::Status s0, s1;
  std::thread t0([&]{ s0 = RunGraphOn(gc0, cfg0); });
  std::thread t1([&]{ s1 = RunGraphOn(gc1, cfg1); });
  t0.join(); t1.join();

  if (!s0.ok()) { std::cerr << s0.message() << "\n"; return 1; }
  if (!s1.ok()) { std::cerr << s1.message() << "\n"; return 1; }
  return 0;
}
