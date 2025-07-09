# Octane gRPC Samples

Code samples demonstrating Octane's gRPC connection service and SDK integration. This repository provides practical examples of connecting to Octane Render via gRPC and implementing real-time camera synchronization between external applications and Octane's render engine.

## Overview

This repository contains:

- **simpleGL**: Standalone interactive 3D model viewer with comprehensive file loading
- **simpleGlGrpc**: Pure gRPC implementation for network camera synchronization
- **simpleGlSdk**: Direct Octane SDK integration with real-time camera synchronization
- **shared/**: Common helper libraries for file dialogs, model loading, and camera controls
- **SDK**: Octane SDK wrapper library with gRPC connectivity
- **Web viewers**: Browser-based 3D viewers with WebGL and gRPC integration
- **Third-party libraries**: OpenGL, gRPC, and supporting dependencies
- **Build system**: Cross-platform CMake configuration for Windows, Linux, and macOS

## Key Features

### Camera Synchronization
- Real-time camera position/orientation sync between OpenGL and Octane
- Mouse-driven camera controls (orbit, zoom, pan with right-click)
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
├── shared/                # 🔧 Shared helper libraries
│   ├── file_dialog.h      # Cross-platform file dialogs (Win/Mac/Linux)
│   ├── model_loader.h     # 3D model loading (OBJ/PLY/STL)
│   ├── camera_system.h    # Camera controls and input handling
│   └── model_manager.h    # Model management with renderer integration
├── simpleGL/              # 🎯 Standalone 3D model viewer
│   ├── main.cpp           # Interactive viewer with file loading
│   ├── model_loader.h     # [DEPRECATED - use shared/]
│   ├── file_dialog.h      # [DEPRECATED - use shared/]
│   ├── test_model_loader.cpp # Unit tests for model loading
│   ├── demo.cpp           # Camera sync demonstration
│   ├── test_gl.cpp        # Basic OpenGL functionality test
│   ├── octane_camera_sync.h/.cpp  # Camera synchronization implementation
│   └── CMakeLists.txt     # Build configuration
├── simpleGlGrpc/          # 🌐 Pure gRPC network synchronization
│   ├── main.cpp           # 3D viewer with network camera sync
│   ├── grpc_camera_sync.h # gRPC-only camera sync implementation
│   └── CMakeLists.txt     # Build configuration (no SDK dependencies)
├── simpleGlSdk/           # 🚀 Direct Octane SDK integration
│   ├── main.cpp           # 3D viewer with real-time Octane sync
│   ├── octane_camera_sync.h # Direct SDK camera sync implementation
│   └── CMakeLists.txt     # Build configuration (requires SDK)
├── web3d_viewer.html      # 🌐 Standalone WebGL cube viewer
├── web3d_octane_sync.html # 🚀 WebGL viewer with Octane gRPC integration
├── grpc_web_proxy.py      # WebSocket-to-gRPC proxy server
├── WEB3D_VIEWER.md        # Web viewer documentation
├── OCTANE_SYNC_VIEWER.md  # Octane sync viewer documentation
├── MODEL_LOADER_GUIDE.md  # 3D model loading guide
├── shared_rendering.h     # Modern rendering system (shared)
├── test_models/           # Sample 3D models for testing
│   ├── teapot.obj         # Simple test model
│   └── pyramid.obj        # Complex test model
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

## Shared Helper System 🔧

The repository now includes a comprehensive shared library system that provides common functionality across all C++ applications:

- **Cross-platform file dialogs**: Native dialogs on Windows/macOS/Linux
- **Multi-format 3D model loading**: OBJ, PLY, and STL file support
- **Unified camera controls**: Consistent mouse/keyboard input handling
- **Model management**: High-level integration with rendering systems
- **Header-only design**: Easy integration with minimal dependencies
- **See**: [SHARED_HELPERS_GUIDE.md](SHARED_HELPERS_GUIDE.md) for complete documentation

## Applications

### simpleGL 🎯
Standalone interactive 3D model viewer:
- **Multi-format loading**: OBJ, PLY, STL files via file dialog (L key)
- **Model switching**: Reset to default cube (R key) 
- **Orbit controls**: Left mouse drag to rotate camera around model
- **Pan controls**: Right mouse drag to pan camera left/right/up/down
- **Zoom**: Mouse wheel to adjust camera distance
- **Cross-platform**: Windows/macOS/Linux file dialog support
- **Visual feedback**: Dynamic lighting with Phong shading and procedural colors
- **Uses shared helpers**: File dialogs, model loading, camera controls

## Two Octane Integration Approaches

This repository provides two distinct approaches for Octane Render integration:

### simpleGlGrpc 🌐 - Pure gRPC Network Synchronization
Network-focused implementation without SDK dependencies:
- **No SDK required**: Builds and runs without Octane SDK installation
- **gRPC-only communication**: Uses network protocols for camera sync
- **Development friendly**: Easy to build and test on any platform
- **Network architecture**: Designed for distributed rendering setups
- **Cross-platform**: No platform-specific library dependencies
- **Graceful degradation**: Works standalone when gRPC unavailable

### simpleGlSdk 🚀 - Direct SDK Integration
Production-ready implementation with full SDK integration:
- **Requires Octane SDK**: Mandatory SDK installation with headers/libraries
- **Direct API access**: Real-time camera sync via Octane::ApiRenderEngine
- **Platform-specific**: Windows (.lib), Linux (.a), macOS (.a) libraries
- **Production performance**: Optimized for real-time rendering workflows
- **Full SDK features**: Access to complete Octane API functionality
- **Multiplatform support**: Windows/Linux/macOS with proper SDK setup
- **Uses shared helpers**: Same UI/UX as simpleGL with added SDK integration

### Web3D Viewer 🌐
Standalone HTML file replicating simpleGL using WebGL:
- **Cross-platform**: Runs in any modern web browser
- **Identical rendering**: Matches C++ version pixel-for-pixel
- **No installation**: Direct browser access
- **Touch support**: Works on mobile devices
- **Performance metrics**: Real-time FPS and frame time display
- **See**: [WEB3D_VIEWER.md](WEB3D_VIEWER.md) for details

### WebGL-Octane Sync Viewer 🚀
Advanced WebGL viewer with real-time Octane gRPC integration:
- **gRPC Integration**: Real-time communication with Octane Render
- **Scene Loading**: Load teapot.orbx into Octane via gRPC calls
- **Camera Synchronization**: Bidirectional camera sync between WebGL and Octane
- **Live Monitoring**: Real-time status updates and performance metrics
- **Interactive Controls**: Mouse/keyboard controls (orbit, pan, zoom) with live Octane sync
- **See**: [OCTANE_SYNC_VIEWER.md](OCTANE_SYNC_VIEWER.md) for details

### 🚀 Web3D Octane Model Viewer
Complete 3D model viewer with full Octane gRPC integration:
- **Multi-format Model Loading**: OBJ, PLY, STL support with drag & drop
- **Real-time Octane Sync**: Live camera and model synchronization
- **Model Transformations**: Scale, rotate, translate with live updates
- **gRPC Communication**: Custom HTTP-based gRPC-Web client for reliable connectivity
- **Professional UI**: Comprehensive status monitoring and activity logging
- **Performance Metrics**: Real-time FPS, geometry stats, and gRPC call tracking
- **No Dependencies**: Works without external libraries or generated protobuf files
- **Cross-browser Compatible**: Reliable operation in all modern browsers
- **See**: [html/README_LIVELINK.md](html/README_LIVELINK.md) for complete documentation

#### Quick Start
```bash
# Start web server from grpcSamples directory
python3 -m http.server 8000

# Open HTML demos
http://localhost:8000/html/livelink_demo.html      # Main LiveLink demo
http://localhost:8000/html/simple_test.html        # Simple connection test
http://localhost:8000/html/web3d_octane_sync.html  # 3D visualization
```

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

## Recent Updates

### ✅ Fixed HTML gRPC-Web Client Issues (July 2025)
The HTML demos now feature a completely rewritten LiveLink client that resolves all previous compatibility issues:

- **Fixed "this.client_.rpcCall is not a function" error**: Eliminated CDN gRPC-Web library conflicts
- **Custom HTTP-based implementation**: Standalone gRPC-Web client using native fetch() API
- **Zero external dependencies**: No more CDN libraries or generated protobuf file requirements
- **All demos working**: livelink_demo.html, simple_test.html, and other HTML files work reliably
- **Maintained Windows compatibility**: Build system unchanged, all C++ functionality preserved
- **Cross-browser support**: Works consistently across Chrome, Firefox, Safari, and Edge

See [html/README_LIVELINK.md](html/README_LIVELINK.md) for complete technical details.

## Getting Started

### C++ Applications
1. **Clone repository**: `git clone <repository-url>`
2. **Build project**: See [BUILD_INSTRUCTIONS.md](BUILD_INSTRUCTIONS.md)
3. **Run demo**: `./bin/simpleGL_demo`
4. **Launch application**: `./bin/simpleGL`

### HTML Demos
1. **Start web server**: `python3 -m http.server 8000` (from grpcSamples directory)
2. **Open demos**: Navigate to `http://localhost:8000/html/livelink_demo.html`
3. **Test functionality**: All demos work without JavaScript errors

For detailed integration examples and API documentation, see [OCTANE_CAMERA_INTEGRATION.md](OCTANE_CAMERA_INTEGRATION.md).

## Requirements

- **CMake 3.10+**
- **C++17 compatible compiler**
- **OpenGL 3.3+ support**
- **gRPC libraries** (optional, for full functionality)
- **Octane Render** (for actual server connection)

## License

This repository contains sample code for demonstration purposes. Please refer to individual component licenses in the third_party directory.