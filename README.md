# Octane gRPC Samples

Code samples demonstrating Octane's gRPC connection service and SDK integration. This repository provides practical examples of connecting to Octane Render via gRPC and implementing real-time camera synchronization between external applications and Octane's render engine.

## Overview

This repository contains:

- **simpleGL**: Interactive 3D OpenGL application with Octane camera synchronization
- **SDK**: Octane SDK wrapper library with gRPC connectivity
- **Third-party libraries**: OpenGL, gRPC, and supporting dependencies
- **Build system**: Cross-platform CMake configuration for Windows and Linux

## Key Features

### Camera Synchronization
- Real-time camera position/orientation sync between OpenGL and Octane
- Mouse-driven camera controls (orbit, zoom, pan)
- Coordinate system conversion (GLM ↔ Octane)
- Unix domain socket communication with Octane server

### gRPC Integration
- Connection management via `GRPCSettings` class
- Support for Unix socket and TCP connections
- Graceful fallback to simulation mode when gRPC unavailable
- Bidirectional communication capabilities

### Development Support
- Simulation mode for development without full Octane installation
- Comprehensive logging and debugging output
- Configurable build options for gRPC functionality
- Cross-platform compatibility (Windows/Linux)

## Repository Structure

```
grpcSamples/
├── simpleGL/              # Main OpenGL application with camera sync
│   ├── main.cpp           # Interactive 3D cube viewer
│   ├── demo.cpp           # Camera sync demonstration
│   ├── test_gl.cpp        # Basic OpenGL functionality test
│   ├── octane_camera_sync.h/.cpp  # Camera synchronization implementation
│   └── CMakeLists.txt     # Build configuration
├── sdk/                   # Octane SDK wrapper library
│   ├── src/api/grpc/      # gRPC client implementations
│   ├── octanewrap*.h/.cpp # SDK wrapper classes
│   ├── octane*.h          # Core SDK headers
│   └── CMakeLists.txt     # SDK build configuration
├── third_party/           # External dependencies
│   ├── glfw/              # Window management
│   ├── glew/              # OpenGL extensions
│   ├── glm/               # Mathematics library
│   ├── grpc/              # gRPC framework
│   └── protobuf/          # Protocol buffers
├── bin/                   # Built executables and libraries
├── build/                 # CMake build directory
└── win-vs2022.bat         # Windows Visual Studio build script
```

## Applications

### simpleGL
Interactive 3D application demonstrating camera synchronization:
- **Orbit controls**: Mouse drag to rotate camera around cube
- **Zoom**: Mouse wheel to adjust camera distance
- **Real-time sync**: Camera updates sent to Octane render engine
- **Visual feedback**: Colorful rotating cube with perspective projection

### simpleGL_demo
Command-line demonstration of camera sync functionality:
- Shows camera position calculations
- Demonstrates coordinate transformations
- Displays connection status and sync operations
- Useful for testing without GUI requirements

### simpleGL_test
Basic OpenGL functionality test:
- Verifies OpenGL context creation
- Tests rendering pipeline
- Validates third-party library integration

## Build Configuration

### gRPC Functionality
```bash
# Enable full gRPC connectivity (requires gRPC libraries)
cmake .. -DENABLE_OCTANE_GRPC=ON

# Simulation mode only (default)
cmake .. -DENABLE_OCTANE_GRPC=OFF
```

### Platform Support
- **Windows**: Visual Studio 2022 solution via `win-vs2022.bat`
- **Linux**: Standard CMake build with GCC/Clang
- **Dependencies**: Automatically managed via third_party directory

## Connection Methods

### Unix Domain Sockets (Recommended)
```cpp
octaneSync.connectToServer("/tmp/octane_server.sock");
```

### TCP Connections
```cpp
octaneSync.connectToServer("localhost:8080");
```

## Getting Started

1. **Clone repository**: `git clone <repository-url>`
2. **Build project**: See [BUILD_INSTRUCTIONS.md](BUILD_INSTRUCTIONS.md)
3. **Run demo**: `./bin/simpleGL_demo`
4. **Launch application**: `./bin/simpleGL`

For detailed integration examples and API documentation, see [OCTANE_CAMERA_INTEGRATION.md](OCTANE_CAMERA_INTEGRATION.md).

## Requirements

- **CMake 3.10+**
- **C++17 compatible compiler**
- **OpenGL 3.3+ support**
- **gRPC libraries** (optional, for full functionality)
- **Octane Render** (for actual server connection)

## License

This repository contains sample code for demonstration purposes. Please refer to individual component licenses in the third_party directory.