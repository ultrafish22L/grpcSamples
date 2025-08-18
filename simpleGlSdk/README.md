# simpleGlSdk - OpenGL with Octane SDK Integration

## Overview
simpleGlSdk is a specialized OpenGL application that provides direct integration with the Octane Render SDK. It enables real-time camera synchronization between OpenGL viewports and Octane Render instances across Windows, Linux, and macOS platforms.

## Key Features

### Octane SDK Integration
- **Real-time Camera Sync**: Bidirectional camera synchronization with Octane Render
- **Cross-platform Support**: Windows (.lib), Linux (.a), and macOS (.a) SDK libraries
- **Direct API Access**: Uses Octane::ApiRenderEngine and Octane::ApiNode for camera control
- **Matrix Conversion**: GLM ↔ Octane matrix/vector type conversion utilities

### OpenGL Rendering
- **3D Scene Rendering**: Basic OpenGL scene with camera controls
- **Interactive Camera**: Mouse-controlled camera with position/orientation tracking
- **Real-time Updates**: Live camera parameter extraction and synchronization

### gRPC Communication (Optional)
- **Camera Control Service**: gRPC server for remote camera manipulation
- **Protocol Buffers**: Structured camera data exchange
- **Network Synchronization**: Multi-client camera state sharing

## Requirements

### Mandatory Dependencies
- **Octane SDK**: Complete SDK installation with headers and libraries
- **OpenGL**: GLFW, GLEW for rendering context
- **GLM**: Mathematics library for 3D transformations
- **C++17**: Modern C++ standard support

### SDK Directory Structure
```
grpcSamples/
├── sdk/                                    # Required SDK headers
│   ├── apirender.h
│   ├── apinodesystem.h
│   ├── octanevectypes.h
│   ├── octanematrix.h
│   └── octaneids.h
└── third_party/octane/                     # Required SDK libraries
    ├── windows/octane_standalone.lib       # Windows
    ├── linux/liboctane_standalone.a        # Linux
    └── macos/liboctane_standalone.a        # macOS
```

### Optional Dependencies
- **gRPC**: For network camera synchronization
- **Protocol Buffers**: For structured data exchange

## Build Instructions

### Prerequisites Check
The build system will verify SDK availability and fail if requirements are not met:
```bash
# Check for required files
ls sdk/apirender.h                          # SDK headers
ls third_party/octane/linux/liboctane_standalone.a  # Linux library
```

### Linux Build
```bash
cd simpleGlSdk
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

### Windows Build (Visual Studio)
```bash
cd simpleGlSdk
mkdir build && cd build
cmake .. -G "Visual Studio 16 2019" -A x64
cmake --build . --config Release
```

### macOS Build (Xcode)
```bash
cd simpleGlSdk
mkdir build && cd build
cmake .. -G Xcode
cmake --build . --config Release
```

## Usage

### Basic SDK Integration
```cpp
#include "../shared/camera_sync_sdk.h"

// Initialize SDK connection
CameraSyncSdk cameraSync;
if (cameraSync.connectToServer("127.0.0.1:51022")) {
    // Update Octane camera from OpenGL view matrix
    cameraSync.updateCameraFromViewMatrix(viewMatrix);
    
    // Get camera state from Octane
    glm::vec3 position, forward, up;
    cameraSync.getCameraPosition(position);
    cameraSync.getCameraOrientation(forward, up);
}
```

### Camera Synchronization
The application automatically synchronizes camera parameters:
- **Position**: 3D world coordinates
- **Orientation**: Forward and up vectors
- **Transform Matrix**: Complete 4x4 transformation

### gRPC Server (Optional)
If gRPC is available, the application provides network camera control:
```bash
# Start with gRPC server
./simpleGlSdk
# Server listens on default port for camera control commands
```

## Architecture

### Core Components
- **CameraSyncSdk**: Main SDK integration class
- **Camera Control**: OpenGL camera manipulation
- **Matrix Conversion**: GLM ↔ Octane type conversion
- **SDK Service**: Direct Octane SDK integration

### SDK Integration Flow
1. **Initialization**: Connect to Octane render engine
2. **Camera Detection**: Locate active render camera node
3. **Synchronization**: Bidirectional camera parameter exchange
4. **Real-time Updates**: Continuous camera state monitoring

### Error Handling
- **SDK Availability**: Graceful handling of missing SDK
- **Camera Access**: Fallback when camera node unavailable
- **Network Issues**: gRPC connection error recovery

## Differences from simpleGlGrpc

### simpleGlSdk (This Project)
- **Requires Octane SDK**: Mandatory SDK installation
- **Direct SDK Integration**: Real Octane API calls
- **Production Ready**: Full camera synchronization
- **Platform Specific**: Requires platform-specific SDK libraries

### simpleGlGrpc (Sibling Project)
- **No SDK Dependencies**: Pure gRPC implementation
- **Development Friendly**: Builds without SDK
- **Network Focus**: Emphasizes gRPC communication
- **Cross-platform**: No platform-specific requirements

## Troubleshooting

### Build Failures
```bash
# Missing SDK headers
FATAL_ERROR: Octane SDK headers not found! simpleGlSdk requires SDK headers in sdk/ directory

# Missing SDK libraries
FATAL_ERROR: Octane Linux library not found! Required: third_party/octane/linux/liboctane_standalone.a
```

### Runtime Issues
```bash
# SDK initialization failure
[SDK] Failed to initialize Octane SDK connection
[SDK] ERROR: Real Octane connection required - no fallback mode

# Camera access issues
[SDK] Camera node not available - using cached data
```

### Platform-Specific Notes
- **Windows**: Requires Visual Studio 2019+ for C++17 support
- **Linux**: Needs development packages for OpenGL and gRPC
- **macOS**: Requires Xcode command line tools

## Development

### Adding New Features
1. Extend `OctaneCameraSync` class for new SDK functionality
2. Update CMakeLists.txt for additional dependencies
3. Test across all supported platforms

### SDK Version Updates
1. Update SDK headers in `sdk/` directory
2. Replace platform-specific libraries in `third_party/octane/`
3. Verify API compatibility in `octane_camera_sync.cpp`

## License
This project follows the same license as the parent grpcSamples repository.

## Related Projects
- **simpleGlGrpc**: Pure gRPC implementation without SDK dependencies
- **simpleGL**: Basic OpenGL rendering with shared helper system
- **Web Viewers**: Browser-based 3D model viewers with gRPC integration