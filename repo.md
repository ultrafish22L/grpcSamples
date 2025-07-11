# Octane gRPC Samples Repository

## Purpose
This repository provides comprehensive code samples and implementations for connecting to Octane Render via gRPC. It demonstrates real-time camera synchronization, 3D model loading, and web-based integration with Octane's LiveLink service.

## Architecture
- **Desktop Applications**: C++ applications using OpenGL for 3D rendering with gRPC connectivity to Octane
- **Web Applications**: Browser-based HTML/JavaScript clients using custom gRPC-Web implementation
- **Proxy Server**: Python-based HTTP-to-gRPC proxy server for web client connectivity
- **Mock Server**: Python mock Octane server for development and testing

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

## Key Features

### Web Application (html/index.html)
- **WebGL 3D Rendering**: Interactive 3D cube with mouse controls
- **Real-time Octane Sync**: Live camera synchronization with Octane Render
- **Professional UI**: OTOY-branded dark theme with activity logging
- **Full-height Layout**: Canvas and activity log both utilize full vertical space
- **Custom gRPC-Web**: Zero external dependencies, works in all modern browsers
- **Performance Monitoring**: Real-time FPS, call statistics, and connection health

### Desktop Applications (C++)
- **simpleGL**: Standalone 3D viewer with file loading capabilities
- **simpleGlGrpc**: Network-based camera sync without SDK dependencies
- **simpleGlSdk**: Full SDK integration with real-time Octane synchronization

### Infrastructure
- **Python Proxy**: HTTP-to-gRPC translation with comprehensive logging
- **Mock Server**: Development server that simulates Octane responses
- **Cross-platform Build**: CMake configuration for Windows, Linux, and macOS

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

## Recent Updates (2025)
- ✅ **Complete Web UI Rewrite**: Professional OTOY-branded interface
- ✅ **Full-height Layout**: Both canvas and activity log utilize full vertical space
- ✅ **Enhanced WebGL Rendering**: Improved 3D cube with better lighting and colors
- ✅ **Streamlined CSS**: Eliminated redundant wrapper classes for cleaner code
- ✅ **Custom gRPC-Web Client**: Zero external dependencies, reliable cross-browser support
- ✅ **Mock Server Integration**: Complete development environment without Octane

## Development Environment
- **Languages**: C++17, Python 3.7+, JavaScript ES6+
- **Graphics**: OpenGL 3.3+, WebGL 2.0
- **Networking**: gRPC, HTTP/JSON proxy
- **Build System**: CMake 3.10+
- **Platforms**: Windows, Linux, macOS, Web browsers

## Documentation
- **README.md**: Complete system overview and setup instructions
- **html/README_LIVELINK.md**: Detailed web client implementation guide
- **REPRODUCTION_PROMPT.md**: Comprehensive reproduction instructions