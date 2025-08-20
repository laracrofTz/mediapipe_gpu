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
#include <GLES3/gl3.h>

// --- Helpers to load extension entry points ---
static PFNEGLQUERYDEVICESEXTPROC eglQueryDevicesEXT = nullptr;
static PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT = nullptr;

// dont link the zink vulkan
static PFNEGLQUERYDEVICESTRINGEXTPROC eglQueryDeviceStringEXT = nullptr;

bool LoadEGLExtensions() {
  eglQueryDevicesEXT = // gives list of physical GPUs exposed to EGL
      (PFNEGLQUERYDEVICESEXTPROC)eglGetProcAddress("eglQueryDevicesEXT");
  eglGetPlatformDisplayEXT = // open eglld display on specific GPU instead of default
      (PFNEGLGETPLATFORMDISPLAYEXTPROC)eglGetProcAddress("eglGetPlatformDisplayEXT");
  eglQueryDeviceStringEXT = (PFNEGLQUERYDEVICESTRINGEXTPROC)eglGetProcAddress("eglQueryDeviceStringEXT");
  return eglQueryDevicesEXT && eglGetPlatformDisplayEXT;
}

// helper function
auto is_hw_device = [](EGLDeviceEXT d) -> bool {
  if (!eglQueryDeviceStringEXT) return true;
  const char* vendor = eglQueryDeviceStringEXT(d, EGL_VENDOR);
  const char* exts = eglQueryDeviceStringEXT(d, EGL_EXTENSIONS);
  auto has = [](const char* s, const char* sub){
    return s && std::string(s).find(sub) != std::string::npos;
  };
  // reject zink paths
  if (has(vendor, "zink") || has(exts, "ZINK")) {
    return false;
  }
  return true;
};

struct GpuCtx { // representing 1 GPU context
  EGLDeviceEXT dev = nullptr; //physical GPU handle
  EGLDisplay dpy = EGL_NO_DISPLAY; // egld display object bound to that GPU
  EGLContext ctx = EGL_NO_CONTEXT; //opengl es context
  EGLSurface surf = EGL_NO_SURFACE; // tiny pbuffer surface used to make context current
};

absl::StatusOr<GpuCtx> MakeHeadlessES3Context(EGLDeviceEXT dev) {
  GpuCtx gc; gc.dev = dev;
  
  // open display on that device
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

absl::Status RunGraphOn(const GpuCtx& gc, const mediapipe::CalculatorGraphConfig& cfg) {
  // bind the context to this thread
  if (!eglMakeCurrent(gc.dpy, gc.surf, gc.surf, gc.ctx)){
    return absl::UnknownError("eglMakeCurrent failed.");
  }

  // verify that we have opengl es and >= 3.1
  const char* ver_c = reinterpret_cast<const char*>(glGetString(GL_VERSION));
  if(!ver_c) return absl::UnknownError("glGetString version is null.");
  std::string ver = ver_c;
  if(ver.find("OpenGL ES") == std::string::npos) {
    return absl::InvalidArgumentError("Not an OpenGL ES context. " + ver);
  }
  int max = 0, min = 0;
  sscanf(ver.c_str(), "OpenGL ES %d.%d", &max, &min);
  if(!(max >3 || (max == 3 && min >= 1))){
    return absl::InvalidArgumentError("Need ES 3.1+, got: " + ver);
  }
  
  // Construct GpuResources from an external EGLContext and install it
  // as the graph's GPU service (kGpuService).
  auto gpu_res_or = mediapipe::GpuResources::Create(
    static_cast<mediapipe::PlatformGlContext>(gc.ctx)
  );

  if (!gpu_res_or.ok()) return gpu_res_or.status();
  std::shared_ptr<mediapipe::GpuResources> gpu_res = *gpu_res_or;

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
  if (!eglQueryDevicesEXT(8, devices, &ndev) || ndev < 1) {
    std::cerr << "No EGL devices found\n";
    return 1;
  }

  std::vector<EGLDeviceEXT> hw;
  for (int i = 0; i < ndev; ++i){
    if (is_hw_device(devices[i])){
      hw.push_back(devices[i]);
    }
  }
  if (hw.empty()) {
    std::cerr << "No usable hardware egl devices.\n";
    return 1;
  }

  // fallback for testing, if only 1 GPU is availble, it will run both on it
  EGLDeviceEXT dev0 = hw[0];
  EGLDeviceEXT dev1 = (hw.size() >=2 ? hw[1] : hw[0]);

  // 2) Create one context per GPU
  auto gc0_or = MakeHeadlessES3Context(dev0);
  auto gc1_or = MakeHeadlessES3Context(dev1);
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
