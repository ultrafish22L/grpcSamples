# GrpcSamples Build Instructions

This repository contains a CMake-based build system for the GrpcSamples solution with a simpleGL project that builds with MSVC on Windows.

## Project Structure

- `simpleGL/` - Contains the OpenGL application that orbits a camera around a cube
- `third_party/` - Contains third-party libraries (GLEW, GLFW, GLM)
- `sdk/` - SDK headers for future use
- `bin/` - Output directory for executables and libraries

## Building on Windows with Visual Studio 2022

1. Ensure you have Visual Studio 2022 with C++ development tools installed
2. Run the provided batch file:
   ```cmd
   win-vs2022.bat
   ```
3. This will create a Visual Studio solution in `build/win-vs2022/GrpcSamples.sln`
4. Open the solution in Visual Studio and build

## Manual CMake Build

Alternatively, you can build manually:

```cmd
mkdir build
mkdir build\win-vs2022
cd build\win-vs2022
cmake -G "Visual Studio 17 2022" ../../
cmake --build . --config Release
```

## Project Organization

The CMake configuration creates a well-organized Visual Studio solution:

### Solution: GrpcSamples
- **Applications** folder:
  - `simpleGL` - Main 3D cube viewer application
  - `simpleGL_demo` - Camera system demonstration
  - `simpleGL_test` - OpenGL setup test
- **ThirdParty** folder:
  - `glew` - OpenGL Extension Wrangler Library
  - `glfw` - OpenGL window and input handling
  - `glm` - OpenGL Mathematics library

## Applications

### simpleGL
The main application that displays a colorful 3D cube with interactive camera controls:
- **Mouse controls**: Left-click and drag to orbit the camera around the cube
- **Scroll wheel**: Zoom in/out
- **ESC key**: Exit the application

### simpleGL_demo
A console application that demonstrates the camera system mathematics without requiring OpenGL.

### simpleGL_test
A test application that verifies OpenGL setup and displays system information.

## Third-Party Libraries

All required third-party libraries are included and built from source:

- **GLEW**: Built as a static library with `GLEW_STATIC` definition
- **GLFW**: Configured to not build examples, tests, or documentation
- **GLM**: Header-only mathematics library for OpenGL

## Output

All executables and libraries are placed in the `bin/` directory for easy deployment and testing.

## Requirements

- Windows 10/11
- Visual Studio 2022 with C++ development tools
- CMake 3.10 or later (included with Visual Studio)

## SDK Library

The SDK is built as a static library (`liboctane_sdk.a` / `octane_sdk.lib`) and linked with simpleGL applications. Currently, the gRPC-dependent portions of the SDK are excluded from the build.

### Missing gRPC Libraries

To enable the full SDK functionality, the following gRPC libraries need to be added to `third_party/grpc/windows/release_64/`:

**Core gRPC Libraries:**
- grpc++.lib, grpc.lib, gpr.lib
- address_sorting.lib
- upb_base_lib.lib, upb_message_lib.lib, upb_json_lib.lib
- upb_textformat_lib.lib, upb_wire_lib.lib, upb_mem_lib.lib
- upb_mini_descriptor_lib.lib, utf8_range_lib.lib

**Protocol Buffers:**
- libprotobuf.lib, libprotobuf-lite.lib, libprotoc.lib

**Windows System Libraries:**
- ws2_32.lib, crypt32.lib, advapi32.lib

Once these libraries are added, remove the gRPC exclusion in `sdk/CMakeLists.txt` to build the complete SDK with all 268 source files.

## Notes

- The project is configured to use C++17 standard
- All third-party libraries are built from source to ensure compatibility
- The solution uses proper folder organization for Visual Studio
- Debug working directory is set to the bin folder for easy asset loading
- SDK currently builds 31 wrapper files; 236 gRPC client files and octanewrappers.cpp are excluded pending library availability