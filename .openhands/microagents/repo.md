# grpcSamples Repository

## Purpose
This repository provides sample applications demonstrating gRPC communication with Octane Render's LiveLink API. It includes C++ desktop applications, HTML/JavaScript web demos, and a Python proxy server for bridging web browsers to gRPC services.

## General Setup
- **Build System**: CMake 3.10+ with cross-platform support (Windows MSVC, Linux GCC/Clang)
- **Dependencies**: OpenGL, GLFW, GLEW, GLM, gRPC, Protocol Buffers, Python 3.7+
- **Third-party Libraries**: Included in `third_party/` directory with pre-built Windows binaries
- **Target Platforms**: Windows (Visual Studio 2019/2022), Linux (system packages)
- **Architecture**: Browser → HTTP → Python Proxy → gRPC → Octane Render

## Repository Structure

### Core Applications
- **`simpleGL/`**: Basic OpenGL rendering demo
- **`simpleGlGrpc/`**: OpenGL + gRPC LiveLink integration (C++)
- **`simpleGlSdk/`**: OpenGL + Octane SDK integration (Windows only)

### Web Demos
- **`html/`**: Browser-based gRPC-Web demos
  - `grpc_test.html`: Connection debugging and API testing tool
  - `web3d_octane_sync.html`: 3D WebGL viewer with real-time Octane camera sync
  - `livelink.js`: Custom gRPC-Web client implementation

### Proxy Server
- **`proxy/`**: Python HTTP-to-gRPC proxy server
  - `grpc_proxy.py`: Translates browser HTTP requests to Octane gRPC calls
  - `CMakeLists.txt`: Build integration for protobuf generation

### Shared Components
- **`shared/`**: Common code and protocol definitions
  - `protos/definitions/`: Protocol buffer definitions (livelink.proto, camera_control.proto)
  - `generated/`: Auto-generated protobuf files (Python, JavaScript)
  - Camera synchronization classes and utilities

### SDK Integration
- **`sdk/`**: Octane SDK headers and wrapper classes (Windows only)
- **`third_party/`**: Pre-built dependencies (gRPC, protobuf, OpenGL libraries)

### Build Configuration
- **Root `CMakeLists.txt`**: Main build configuration with MSVC optimizations
- **`cmake/`**: Build utilities and protobuf generation scripts
- **Platform scripts**: `win-vs2022.bat`, `regenerate_*.sh` for development workflow

The repository demonstrates three approaches to Octane LiveLink integration: direct C++ gRPC, SDK-based (Windows), and web-based via proxy server.