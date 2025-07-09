# Octane gRPC Samples Repository

## Purpose

This repository provides comprehensive code samples demonstrating Octane Render's gRPC connection service and SDK integration. It enables real-time camera synchronization and 3D model interaction between external applications (C++, HTML/WebGL) and Octane's render engine through various connection methods including gRPC, WebSocket, and direct SDK integration.

## General Setup

The repository is designed as a cross-platform development environment supporting:

- **Build System**: CMake-based configuration for Windows, Linux, and macOS
- **Dependencies**: Self-contained third-party libraries (OpenGL, gRPC, protobuf, etc.)
- **Development Modes**: 
  - Full gRPC connectivity (requires gRPC libraries)
  - Simulation mode (standalone development)
- **Connection Methods**: Unix domain sockets, TCP connections, HTTP-based gRPC-Web
- **Default Server**: `127.0.0.1:51022` for gRPC-Web HTML demos

### Key Components
- **C++ Applications**: Native desktop viewers with OpenGL rendering
- **HTML/WebGL Demos**: Browser-based 3D viewers with custom gRPC-Web client
- **Octane SDK Integration**: Direct API access for production workflows
- **Shared Libraries**: Common functionality for file dialogs, model loading, camera controls

## Repository Structure

```
grpcSamples/
├── html/                          # 🌐 Web-based demos and gRPC-Web client
│   ├── livelink.js               # Custom HTTP-based gRPC-Web implementation
│   ├── livelink_demo.html        # Main LiveLink demo with camera/mesh control
│   ├── simple_test.html          # Basic connection testing
│   ├── grpc_test.html           # gRPC functionality testing
│   ├── web3d_*.html             # 3D WebGL viewers with Octane sync
│   └── generated/               # Protobuf-generated JavaScript files
│
├── simpleGL/                      # 🎯 Standalone 3D model viewer
│   └── main.cpp                  # Interactive viewer with file loading
│
├── simpleGlGrpc/                  # 🌐 Pure gRPC network synchronization
│   └── main.cpp                  # Network-focused implementation (no SDK)
│
├── simpleGlSdk/                   # 🚀 Direct Octane SDK integration
│   └── main.cpp                  # Production-ready with full SDK access
│
├── shared/                        # 🔧 Common helper libraries
│   ├── camera_sync_*.h/.cpp      # Camera synchronization implementations
│   ├── file_dialog.h             # Cross-platform file dialogs
│   ├── model_loader.h            # 3D model loading (OBJ/PLY/STL)
│   └── protos/                   # Protocol buffer definitions
│
├── sdk/                           # Octane SDK wrapper library
│   ├── octanewrap*.h/.cpp        # SDK wrapper classes
│   ├── grpc-examples/            # gRPC integration examples
│   └── src/                      # Core SDK implementation
│
├── third_party/                   # External dependencies
│   ├── grpc/                     # gRPC framework
│   ├── protobuf/                 # Protocol buffers
│   ├── glfw/, glew/, glm/        # OpenGL libraries
│   └── openssl/, curl/, etc.     # Supporting libraries
│
├── test_models/                   # Sample 3D models for testing
├── ORBX/                         # Octane scene files
├── cmake/                        # Build system configuration
└── win-vs2022.bat               # Windows build script
```

### Application Types
1. **HTML Demos**: Browser-based with custom gRPC-Web client (no external dependencies)
2. **C++ Viewers**: Native applications with OpenGL rendering and mouse controls
3. **SDK Integration**: Direct Octane API access for production workflows
4. **Network Sync**: Pure gRPC implementations for distributed rendering

### Key Features
- Real-time camera synchronization between applications and Octane
- Multi-format 3D model loading (OBJ, PLY, STL)
- Cross-platform file dialogs and UI components
- Graceful fallback to simulation mode when Octane unavailable
- Comprehensive logging and debugging support with enhanced error analysis

### Recent Enhancements (Latest)
- **Comprehensive Debugging System**: Enhanced LiveLinkClient with detailed logging infrastructure
- **Error Analysis**: Automatic error type classification with specific troubleshooting suggestions
- **Connection Tracking**: Complete history of connection attempts, failures, and system information
- **Performance Monitoring**: Call timing, response analysis, and detailed performance metrics
- **Debug Utilities**: Exportable debug reports and comprehensive client state information
- **Enhanced HTML Demos**: Detailed error display, debugging controls, and system information collection
- **gRPC Call Logging**: Complete request/response tracking with call ID correlation and timeout handling