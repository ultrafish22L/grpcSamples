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
cmake -G "Visual Studio 17 2022" -A x64 ../../
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

The SDK is built as a static library (`liboctane_sdk.a` / `octane_sdk.lib`) and linked with simpleGL applications. The gRPC functionality is disabled by default and can be enabled by setting the CMake option `ENABLE_OCTANE_GRPC=ON`.

### Windows MSVC Optimizations

The build system has been optimized for Windows MSVC with the following features:

**Compiler Optimizations:**
- Parallel compilation enabled (`/MP`)
- Appropriate warning levels and disabled common third-party warnings
- Proper exception handling (`/EHsc`)
- Dynamic runtime library linking for better compatibility

**Library Configuration:**
- Static linking for all third-party libraries (GLEW, GLFW, GLM)
- Proper Windows system library linking (user32, gdi32, shell32)
- WIN32_LEAN_AND_MEAN and NOMINMAX definitions for cleaner Windows builds

### Enabling gRPC Libraries (Optional)

To enable the full SDK functionality, set `ENABLE_OCTANE_GRPC=ON` and ensure the following gRPC libraries are available:

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

To enable gRPC functionality:
```cmd
cmake -G "Visual Studio 17 2022" -A x64 -DENABLE_OCTANE_GRPC=ON ../../
```

## Notes

- The project is configured to use C++17 standard
- All third-party libraries are built from source to ensure MSVC compatibility
- The solution uses proper folder organization for Visual Studio
- Debug working directory is set to the bin folder for easy asset loading
- MSVC-specific optimizations include parallel compilation and proper runtime library linking
- SDK currently builds 31 wrapper files; gRPC functionality is disabled by default
- Console subsystem is used for all executables to ensure proper debugging experience
- Windows system libraries are automatically linked when building on Windows