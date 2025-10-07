# Description:
#   ANGLE library to translate OpenGL ES calls into native Windows graphics call so that mediapipe can run on GPU on Windows OS.

# TODO: need to change the absolute path

filegroup( # use to group many source files together, but does not compile them
    name = "headers",
    srcs = glob(["include/**/*.h"]),
    visibility = ["//visibility:public"],
)

cc_import( # allows users to import pre compiled c/c++ libs
    name = "libEGL",
    interface_library = "out/Debug/libEGL.dll.lib", # for linking the shared library
    shared_library = "out/Debug/libEGL.dll", # single precompiled shared library, bazel ensures its available to the binary that depends on it during runtime
    visibility = ["//visibility:public"],
)

cc_import( # allows users to import pre compiled c/c++ libs for linking
    name = "libGLESv2",
    interface_library = "out/Debug/libGLESv2.dll.lib", # for linking the shared library
    shared_library = "out/Debug/libGLESv2.dll", # single precompiled shared library, bazel ensures its available to the binary that depends on it during runtime
    visibility = ["//visibility:public"],
)

cc_import(
    name = "d3dcompiler_47",
    shared_library = "out/Debug/d3dcompiler_47.dll",
    visibility = ["//visibility:public"],
)

cc_library( # compile source files into a library
    name = "angle",
    hdrs = [":headers"],
    includes = ["include"],
    deps = [":libEGL", ":libGLESv2", ":d3dcompiler_47"],
    visibility = ["//visibility:public"],
)