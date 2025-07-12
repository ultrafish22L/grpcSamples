# Octane gRPC Samples

Comprehensive code samples demonstrating Octane Render integration via gRPC. Features real-time camera synchronization, 3D visualization, and web-based LiveLink connectivity.

## Overview

**Web Application**: Professional WebGL 3D viewer with Octane LiveLink integration
- Interactive 3D rendering with mouse controls (orbit, pan, zoom)
- Real-time camera synchronization with Octane Render
- OTOY-branded professional UI with activity logging
- Custom gRPC-Web client with zero external dependencies

**Desktop Applications**: C++ OpenGL viewers with varying integration levels
- **simpleGL**: Standalone 3D viewer with file loading
- **simpleGlGrpc**: Network camera sync without SDK dependencies  
- **simpleGlSdk**: Full SDK integration with real-time synchronization

**Development Infrastructure**: Complete development environment
- Python HTTP-to-gRPC proxy server
- Mock Octane server for development without Octane installation
- Cross-platform build system (Windows, Linux, macOS)

## Quick Start

### Web Application
```bash
# Start development servers
./start_development_servers.sh

# Open web application  
http://localhost:51313/index.html
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
Professional WebGL 3D viewer with Octane LiveLink integration:
- **Interactive 3D Rendering**: WebGL 2.0 cube with mouse controls (orbit, pan, zoom)
- **Real-time Octane Sync**: Live camera synchronization with Octane Render
- **Professional UI**: OTOY-branded dark theme with full-height layout
- **Activity Logging**: Real-time operation logging with timestamps and status indicators
- **Custom gRPC-Web**: Zero external dependencies, reliable cross-browser support
- **Performance Monitoring**: Real-time FPS, call statistics, and connection health

### Desktop Applications (C++)
Three C++ applications demonstrating different integration approaches:

**simpleGL**: Standalone 3D viewer
- Interactive OpenGL 3D rendering with file loading capabilities
- Cross-platform file dialogs for OBJ, PLY, STL model loading
- Mouse/keyboard camera controls (orbit, pan, zoom)

**simpleGlGrpc**: Network camera synchronization  
- Pure gRPC implementation without SDK dependencies
- Real-time camera sync with external Octane server
- Development-friendly with graceful degradation

**simpleGlSdk**: Full SDK integration
- Direct Octane SDK integration with real-time synchronization
- Production-ready implementation with complete API access
- Platform-specific SDK library requirements

### Development Infrastructure
Complete development environment for testing without Octane:
- **Python Proxy Server**: HTTP-to-gRPC translation with comprehensive logging
- **Mock Octane Server**: Simulates Octane responses for development
- **Cross-platform Build**: CMake configuration for Windows, Linux, macOS

## Recent Updates (2025)

### ✅ Complete Web Application Rewrite
- **Professional OTOY UI**: Dark theme with red accents matching Octane branding
- **Full-height Layout**: Both canvas and activity log utilize full vertical space
- **Enhanced WebGL Rendering**: Improved 3D cube with better lighting and mouse controls
- **Streamlined CSS**: Eliminated redundant wrapper classes for cleaner code structure

### ✅ Custom gRPC-Web Implementation
- **Zero External Dependencies**: No CDN libraries or generated protobuf files required
- **Reliable Cross-browser Support**: Works consistently across all modern browsers
- **HTTP-based Protocol**: Uses native fetch() API for robust connectivity
- **Comprehensive Error Handling**: User-friendly error messages and status indicators

### ✅ Complete Development Environment
- **Mock Octane Server**: Full development without Octane installation required
- **Python Proxy Server**: HTTP-to-gRPC translation with detailed logging
- **Automated Startup**: Single script starts all development servers

## Requirements

**For Web Application:**
- Modern web browser with WebGL 2.0 support
- Python 3.7+ (for development servers)

**For C++ Applications:**
- CMake 3.10+
- C++17 compatible compiler  
- OpenGL 3.3+ support
- gRPC libraries (optional, for full functionality)

**For Octane Integration:**
- Octane Render (for actual server connection)
- Octane SDK (for simpleGlSdk only)

## Documentation

- **repo.md**: Concise repository overview and architecture
- **html/README_LIVELINK.md**: Detailed web client implementation guide
- **REPRODUCTION_PROMPT.md**: Complete system reproduction instructions

## License

Sample code for demonstration purposes. See individual component licenses in third_party directory.