# Octane gRPC Samples Repository

## Purpose
This repository provides comprehensive code samples and implementations for connecting to Octane Render via gRPC. It demonstrates real-time camera synchronization, 3D model loading, and web-based integration with Octane's LiveLink service. The repository serves as both a learning resource and production-ready foundation for building applications that integrate with Octane Render.

The main goal is to enable both **desktop applications** (C++/OpenGL) and **browser-based applications** (HTML/JavaScript/WebGL) to seamlessly integrate with Octane's professional 3D rendering pipeline for camera control, mesh discovery, geometry access, and real-time rendering workflows.

## General Setup

### Core Components
- **C++ Applications**: Native desktop applications using OpenGL for 3D rendering with gRPC connectivity to Octane
- **Web Applications**: Browser-based HTML/JavaScript clients using custom gRPC-Web implementation
- **Proxy Server**: Python-based HTTP-to-gRPC proxy server for web client connectivity with comprehensive logging
- **Shared Libraries**: Common helper libraries for file dialogs, model loading, and camera controls
- **Build System**: Cross-platform CMake configuration supporting Windows, Linux, and macOS

### Architecture Patterns
**Desktop Applications**: C++ Application ↔ gRPC ↔ Octane LiveLink Service
**Web Applications**: JavaScript Client ↔ HTTP Proxy Server ↔ gRPC ↔ Octane LiveLink Service

### Key Technologies
- **Desktop**: C++17, OpenGL 3.3+, gRPC, Protocol Buffers, CMake
- **Web Frontend**: Vanilla JavaScript, WebGL, custom gRPC-Web implementation, real-time 3D rendering
- **Proxy Server**: Python with aiohttp, grpcio, comprehensive CORS middleware, and enhanced logging
- **Protocol**: HTTP/JSON for browser-to-proxy, native gRPC for all Octane communication
- **Development**: Simulation modes and graceful degradation when Octane unavailable

## Repository Structure

```
grpcSamples/
├── shared/                    # 🔧 Common helper libraries
│   ├── camera_system.h        # Camera controls and input handling
│   ├── model_loader.h         # 3D model loading (OBJ/PLY/STL)
│   ├── file_dialog.h          # Cross-platform file dialogs
│   └── generated/             # Generated protobuf files
├── simpleGL/                  # 🎯 Standalone 3D model viewer
│   └── main.cpp               # Interactive viewer with file loading
├── simpleGlGrpc/              # 🌐 Pure gRPC network synchronization
│   └── main.cpp               # Network-based camera sync (no SDK)
├── simpleGlSdk/               # 🚀 Direct Octane SDK integration
│   └── main.cpp               # Real-time SDK-based synchronization
├── html/                      # 🌐 Web-based applications
│   ├── livelink.js            # Custom gRPC-Web client implementation
│   ├── grpc_test.html         # gRPC functionality testing interface
│   ├── web3d_octane_sync.html # WebGL viewer with Octane sync
│   └── README_LIVELINK.md     # Web client documentation
├── proxy/                     # 🔄 HTTP-to-gRPC proxy server
│   ├── grpc_proxy.py          # Python proxy with comprehensive logging
│   ├── livelink_pb2.py        # Generated protobuf Python bindings
│   └── livelink_pb2_grpc.py   # Generated gRPC Python stubs
├── sdk/                       # 📚 Octane SDK wrapper library
│   ├── octane*.h              # Core SDK headers
│   ├── octanewrap*.h/.cpp     # SDK wrapper classes
│   └── grpc-examples/         # gRPC integration examples
├── third_party/               # 📦 External dependencies
│   ├── grpc/                  # gRPC framework
│   ├── protobuf/              # Protocol buffers
│   ├── glfw/                  # Window management
│   ├── glew/                  # OpenGL extensions
│   └── glm/                   # Mathematics library
├── test_models/               # 🎲 Sample 3D models for testing
├── ORBX/                      # 🎨 Octane scene files
└── cmake/                     # 🔨 Build system configuration
```

### Application Types

**Desktop Applications (C++)**:
- `simpleGL`: Standalone 3D viewer with file loading and camera controls
- `simpleGlGrpc`: Network-based camera synchronization without SDK dependencies
- `simpleGlSdk`: Full SDK integration with real-time Octane synchronization

**Web Applications (HTML/JavaScript)**:
- `grpc_test.html`: gRPC connectivity testing and debugging interface
- `web3d_octane_sync.html`: WebGL 3D viewer with live Octane synchronization
- Custom gRPC-Web client implementation without external dependencies

**Infrastructure**:
- Python proxy server for HTTP-to-gRPC translation with comprehensive logging
- Cross-platform build system supporting multiple development environments
- Shared helper libraries for common functionality across applications

### Key Features
- **Real-time Camera Synchronization**: Bidirectional camera sync between applications and Octane
- **Multi-format 3D Model Loading**: Support for OBJ, PLY, and STL file formats
- **Cross-platform Compatibility**: Windows, Linux, and macOS support
- **Web Integration**: Browser-based clients with custom gRPC-Web implementation
- **Comprehensive Logging**: Detailed request/response logging with emoji indicators (📤 outgoing, 📥 incoming, ❌ errors)
- **Development-friendly**: Simulation modes and graceful degradation when Octane unavailable
- **Enhanced Error Handling**: Comprehensive error reporting with detailed debug information
- **Performance Monitoring**: Real-time FPS, call statistics, and connection health tracking
- **CORS-compliant**: Enhanced cross-origin support with X-Call-Id and gRPC-Web headers
- **Event-driven Architecture**: Asynchronous client with proper connection state management
- **Activity Log System**: Complete detailed operation logging in HTML applications with timestamps and emoji indicators
- **Zero External Dependencies**: Custom gRPC-Web implementation without CDN libraries or generated protobuf files