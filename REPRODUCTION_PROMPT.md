# Octane gRPC Samples - Complete Reproduction Guide

## Overview

This guide provides complete instructions for reproducing the Octane gRPC Samples repository from scratch. The system demonstrates Octane Render integration via gRPC with both web and desktop applications.

## System Architecture

**Web Application**: Professional WebGL 3D viewer with Octane LiveLink integration
- Custom gRPC-Web client with zero external dependencies
- OTOY-branded professional UI with full-height layout
- Real-time camera synchronization and activity logging

**Desktop Applications**: C++ OpenGL viewers with varying integration levels
- Standalone viewer, network sync, and full SDK integration
- Cross-platform support (Windows, Linux, macOS)

**Development Infrastructure**: Complete development environment
- Python HTTP-to-gRPC proxy server
- Mock Octane server for development without Octane installation

## Quick Start

### Web Application
```bash
# Start development servers
./start_development_servers.sh

# Open web application
http://localhost:51313/html/index.html
```

### Desktop Applications  
```bash
# Build C++ applications
mkdir build && cd build
cmake .. && make

# Run applications
./simpleGL        # Standalone viewer
./simpleGlGrpc    # Network sync viewer
./simpleGlSdk     # SDK integrated viewer
```

## Key Implementation Requirements

### Web Application (html/index.html)
**Visual Standards:**
- Professional OTOY-branded dark theme with red accents
- Full-height layout with canvas and activity log both utilizing vertical space
- WebGL 2.0 rendering with interactive 3D cube
- Mouse controls: left drag (orbit), right drag (pan), scroll (zoom)

**Technical Requirements:**
- Custom gRPC-Web client using native fetch() API only
- Zero external dependencies (no CDN libraries or generated protobuf)
- Real-time activity logging with timestamps and status indicators
- Performance monitoring with FPS and connection health tracking

### Desktop Applications (C++)
**Common Features:**
- OpenGL 3.3+ rendering with 1200x800 window
- Interactive 3D cube with mouse controls (orbit, pan, zoom)
- Professional lighting with Phong shading
- Cross-platform file dialogs for model loading (OBJ, PLY, STL)

**Application Variants:**
1. **simpleGL**: Standalone 3D viewer with file loading
2. **simpleGlGrpc**: Network camera sync without SDK dependencies  
3. **simpleGlSdk**: Full SDK integration with real-time synchronization

### Development Infrastructure
**Python Proxy Server (proxy/grpc_proxy.py):**
- HTTP-to-gRPC translation with comprehensive logging
- CORS support for web client connectivity
- Emoji-based status indicators (📤 outgoing, 📥 incoming, ❌ errors)

**Mock Octane Server (mock_octane/mock_octane_server.py):**
- Simulates Octane responses for development without Octane installation
- Statistics tracking and performance monitoring
- Configurable response delays and error simulation

## Repository Structure

```
grpcSamples/
├── html/                      # 🌐 Web applications
│   ├── index.html             # Main WebGL 3D viewer with Octane sync
│   ├── livelink.js            # Custom gRPC-Web client implementation
│   ├── shared.js              # Common utilities and helper functions
│   ├── webgl-utils.js         # WebGL rendering and 3D utilities
│   ├── otoy-theme.css         # Professional OTOY branding and styling
│   └── README_LIVELINK.md     # Web client documentation
├── proxy/                     # 🔄 HTTP-to-gRPC proxy server
│   ├── grpc_proxy.py          # Python proxy with comprehensive logging
│   ├── livelink_pb2.py        # Generated protobuf Python bindings
│   └── livelink_pb2_grpc.py   # Generated gRPC Python stubs
├── mock_octane/               # 🎭 Mock Octane server for development
│   ├── mock_octane_server.py  # Python mock server implementation
│   └── README.md              # Mock server documentation
├── shared/                    # 🔧 Common helper libraries (C++)
│   ├── camera_system.h        # Camera controls and input handling
│   ├── model_loader.h         # 3D model loading (OBJ/PLY/STL)
│   └── file_dialog.h          # Cross-platform file dialogs
├── simpleGL/                  # 🎯 Standalone 3D model viewer (C++)
├── simpleGlGrpc/              # 🌐 Pure gRPC network synchronization (C++)
├── simpleGlSdk/               # 🚀 Direct Octane SDK integration (C++)
├── sdk/                       # 📚 Octane SDK wrapper library
├── third_party/               # 📦 External dependencies
├── test_models/               # 🎲 Sample 3D models for testing
└── ORBX/                      # 🎨 Octane scene files
```

## Critical Implementation Details

### Web Application (html/index.html)
**Key Components:**
- **livelink.js**: Custom gRPC-Web client using native fetch() API
- **webgl-utils.js**: WebGL rendering utilities and 3D cube geometry
- **shared.js**: Common utilities and helper functions
- **otoy-theme.css**: Professional OTOY branding with full-height layout

**Core JavaScript Classes:**
```javascript
// Custom gRPC-Web client (livelink.js)
class LiveLinkClient extends SimpleEventEmitter {
    constructor(serverUrl = 'http://127.0.0.1:8080')
    async connect()
    async setCamera(cameraState)
    async getCamera()
    getStats()
}

// WebGL rendering (webgl-utils.js)  
class WebGLRenderer {
    constructor(canvas)
    render(camera)
    handleResize()
}

// 3D cube geometry
class CubeGeometry {
    constructor(gl)
    render(gl, program)
}
```

**Critical Requirements:**
- Zero external dependencies (no CDN libraries)
- Plain JavaScript objects (no protobuf classes)
- HTTP-based gRPC-Web protocol using fetch()
- Full-height layout with both canvas and activity log filling vertical space

### Desktop Applications (C++)
**Common Requirements:**
- OpenGL 3.3+ with 1200x800 window
- Header-only shared libraries (file_dialog.h, model_loader.h, camera_system.h)
- Cross-platform CMake build system
- Mouse/keyboard camera controls with smooth interpolation

**Application-Specific Features:**
- **simpleGL**: File loading with native dialogs (L key), model switching (R key)
- **simpleGlGrpc**: Network camera sync without SDK dependencies
- **simpleGlSdk**: Full SDK integration with real-time synchronization

### Development Infrastructure
**Python Servers:**
- **proxy/grpc_proxy.py**: HTTP-to-gRPC translation with CORS support
- **mock_octane/mock_octane_server.py**: Mock Octane server for development

**Build System:**
```cmake
# CMakeLists.txt structure
cmake_minimum_required(VERSION 3.10)
project(grpcSamples)

# Third-party dependencies
add_subdirectory(third_party/glfw)
add_subdirectory(third_party/glew)
add_subdirectory(third_party/grpc)

# Applications
add_subdirectory(simpleGL)
add_subdirectory(simpleGlGrpc) 
add_subdirectory(simpleGlSdk)
```

## Current Implementation Status (2025)

### ✅ Completed Features
- **Web Application**: Professional OTOY-branded UI with full-height layout
- **Custom gRPC-Web**: Zero external dependencies, reliable cross-browser support
- **WebGL Rendering**: Interactive 3D cube with mouse controls
- **Development Environment**: Complete mock server and proxy infrastructure
- **Activity Logging**: Real-time operation logging with timestamps and status indicators

### 🎯 Key Success Factors
1. **Zero External Dependencies**: Custom gRPC-Web client using only native browser APIs
2. **Full-height Layout**: Both canvas and activity log utilize complete vertical space
3. **Professional UI**: OTOY branding with dark theme and red accents
4. **Complete Development Environment**: Mock servers enable development without Octane
5. **Cross-platform Compatibility**: Works reliably across all modern browsers and operating systems

This reproduction guide provides the essential information needed to recreate the complete Octane gRPC Samples system with all current features and improvements.
