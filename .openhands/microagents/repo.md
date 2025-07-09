# Octane gRPC Samples Repository

## Purpose
This repository provides code samples demonstrating Octane Render's gRPC connection service and SDK integration. It showcases practical examples of connecting to Octane Render via gRPC and implementing real-time camera synchronization between external applications and Octane's render engine. The repository serves as a comprehensive demonstration platform for developers integrating with Octane's LiveLink service and SDK.

## General Setup
The repository is built using CMake with C++17 and supports cross-platform development (Windows, Linux, macOS). It includes:

- **Build System**: CMake 3.10+ with Visual Studio 2022 support on Windows
- **Dependencies**: All third-party libraries are included in `third_party/` directory (OpenGL, gRPC, protobuf, GLFW, GLEW, GLM)
- **Configuration Options**: 
  - `ENABLE_OCTANE_GRPC=ON/OFF` for gRPC functionality
  - Automatic SDK detection on Windows
  - Simulation mode for development without full Octane installation
- **Web Components**: HTML demos with custom gRPC-Web implementation for browser-based integration
- **Cross-platform**: Native file dialogs, OpenGL rendering, and consistent UI across platforms

## Repository Structure

### Core Applications
- **`simpleGL/`** - Standalone interactive 3D model viewer with comprehensive file loading (OBJ/PLY/STL)
- **`simpleGlGrpc/`** - Pure gRPC network synchronization without SDK dependencies
- **`simpleGlSdk/`** - Direct Octane SDK integration with real-time camera synchronization

### Shared Libraries
- **`shared/`** - Common helper libraries for file dialogs, model loading, camera controls, and model management
- **`sdk/`** - Octane SDK wrapper library with gRPC connectivity and API wrappers

### Web Integration
- **`html/`** - Browser-based 3D viewers with WebGL and custom gRPC-Web implementation
  - LiveLink demos with real-time Octane synchronization
  - Model viewers with drag-and-drop support
  - Connection testing and debugging interfaces

### Supporting Components
- **`third_party/`** - External dependencies (OpenGL libraries, gRPC framework, protobuf)
- **`test_models/`** - Sample 3D models for testing (PLY, STL formats)
- **`ORBX/`** - Octane scene files for testing
- **Build scripts** - Platform-specific build configurations and automation

### Key Features
- **Camera Synchronization**: Real-time position/orientation sync with mouse controls (orbit, zoom, pan)
- **Multi-format Model Loading**: Support for OBJ, PLY, STL files with cross-platform file dialogs
- **gRPC Integration**: Unix domain socket and TCP connections with graceful fallback
- **Web Compatibility**: Custom HTTP-based gRPC-Web client eliminating CDN dependencies
- **Development Support**: Simulation mode, comprehensive logging, and configurable build options