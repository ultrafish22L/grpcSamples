# Octane gRPC Samples Repository - Production-Ready System

## 🚨 **CRITICAL REQUIREMENT: REAL OCTANE ONLY**

**⚠️ NEVER EVER use mock or simulated data - only real live connection with Octane LiveLink service.**

## 🎯 Repository Status: PRODUCTION-READY REAL-TIME SYSTEM ✅

**ACHIEVEMENT**: Complete production-ready real-time rendering system with optimized performance, clean UI, and robust callback streaming.

## 🚨 CRITICAL WARNINGS FOR DEVELOPERS

### 🛑 DO NOT BREAK PRODUCTION-READY CODE
The system is now **PRODUCTION-READY** with all core functionality working. The most dangerous pattern is **breaking working functionality**:

**⚠️ CRITICAL SYSTEMS - DO NOT MODIFY**:
- **Buffer Processing**: convertHDRRGBA buffer isolation prevents garbage frames
- **Performance Settings**: PNG saves disabled, logging minimized for production
- **Camera Sync**: setCameraPosition/setCameraTarget methods enable live camera updates
- **UI Debug Mode**: Default uiDebugMode = false keeps production UI clean
- **Callback System**: callback_streamer.py and registration logic optimized and stable

**✅ PRODUCTION FEATURES WORKING**:
- Real-time callback system with consistent frame display
- Mouse drag camera synchronization with live Octane updates
- Performance optimized with minimal logging and clean UI
- Configurable debug mode via toggleUIDebugMode() in browser console
- Robust error handling and memory management

### 🔍 Error Analysis Guidelines

**Connection Errors ≠ Code Bugs**:
- `Connection refused (10061)`: Octane not running or LiveLink disabled
- `Connection reset (10054)`: Network issue or Octane restart
- `Socket closed`: Octane disconnected (often normal)

**These are NOT indicators of code bugs** - the system is production-ready.

**Before assuming code bugs**:
1. Is Octane running?
2. Is LiveLink enabled (Help → LiveLink in Octane)?
3. Is port 51022 accessible?
4. Try restarting Octane LiveLink service
5. Test with minimal API calls first

## General Setup

### Core Components
- **C++ Applications**: Native desktop applications using OpenGL for 3D rendering with gRPC connectivity to Octane
- **octaneWeb**: **PRODUCTION-READY** browser-based real-time rendering system with callback streaming
- **Proxy Server**: Optimized Python HTTP-to-gRPC proxy with performance enhancements and minimal logging
- **Shared Libraries**: Common helper libraries for file dialogs, model loading, and camera controls
- **Build System**: Cross-platform CMake configuration supporting Windows, Linux, and macOS

### 🚨 **CRITICAL REQUIREMENT: REAL OCTANE ONLY**
**⚠️ NEVER EVER use mock or simulated data - only real live connection with Octane LiveLink service.**

### Production Architecture
**Desktop Applications**: C++ Application ↔ gRPC ↔ Octane LiveLink Service
**octaneWeb (PRODUCTION)**: Browser ↔ Clean UI ↔ Optimized Proxy ↔ Callback Streaming ↔ gRPC ↔ Octane LiveLink Service

### Key Technologies
- **Desktop**: C++17, OpenGL 3.3+, gRPC, Protocol Buffers, CMake, ImGui
- **octaneWeb**: Vanilla JavaScript, real-time callback streaming, optimized buffer processing, configurable debug UI
- **Proxy Server**: Python with aiohttp, grpcio, performance optimizations, minimal logging for production
- **Protocol**: HTTP/JSON for browser-to-proxy, native gRPC for all Octane communication
- **Real-time Rendering**: OnNewImage callbacks, HDR/LDR support, consistent frame display

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
├── testGrpcApi/               # 🔬 Advanced gRPC testing application
│   ├── main.cpp               # ImGui-based gRPC API testing interface
│   ├── ActivityLogger.h/.cpp  # Comprehensive logging system
│   └── PerformanceTracker.h/.cpp # Performance monitoring
├── html/                      # 🌐 Legacy web applications (DEPRECATED)
│   ├── index.html             # Original LiveLink web interface
│   ├── start_proxy.sh/.bat    # Proxy server launchers
│   └── README_LIVELINK.md     # Legacy documentation
├── octaneWeb/                 # 🚀 PRODUCTION-READY web application suite
│   ├── index.html             # Main production web application
│   ├── js/                    # Optimized JavaScript modules
│   │   ├── core/
│   │   │   └── OctaneWebClient.js # Complete gRPC-Web client with camera sync
│   │   ├── components/
│   │   │   ├── CallbackRenderViewport.js # Real-time callback rendering (FIXED buffer corruption)
│   │   │   ├── RenderViewport.js # Standard rendering viewport
│   │   │   ├── SceneOutliner.js  # Hierarchical scene tree viewer
│   │   │   └── NodeGraphEditor.js # Visual node graph editor
│   │   ├── utils/
│   │   │   ├── DebugConsole.js   # Development debug console
│   │   │   └── CacheBuster.js    # Development cache management
│   │   └── app.js             # Main application with toggleUIDebugMode()
│   ├── css/                   # Professional styling
│   │   ├── octane-theme.css   # Clean production OTOY theme
│   │   └── components.css     # Component-specific styles
│   ├── shared/js/             # Shared web utilities
│   │   ├── webgl-utils.js     # WebGL rendering classes
│   │   └── shared.js          # Common helper functions
│   ├── assets/                # Static assets and icons
│   ├── start_servers.bat      # Production server startup (auto-installs dependencies)
│   └── REPRO_PROMPT.md        # Production status documentation
├── octaneProxy/               # 🔄 OPTIMIZED HTTP-to-gRPC proxy server
│   ├── octane_proxy.py        # Production proxy (minimal logging, PNG saves disabled)
│   ├── callback_streamer.py   # Real-time callback streaming (optimized performance)
│   ├── livelink_pb2.py        # Generated protobuf Python bindings
│   └── *_pb2.py               # Complete Octane API protobuf bindings

├── sdk/                       # 📚 Octane SDK wrapper library
│   ├── octane*.h              # Core SDK headers
│   ├── octanewrap*.h/.cpp     # SDK wrapper classes
│   └── grpc-examples/         # gRPC integration examples
├── third_party/               # 📦 External dependencies
│   ├── grpc/                  # gRPC framework
│   ├── protobuf/              # Protocol buffers
│   ├── glfw/                  # Window management
│   ├── glew/                  # OpenGL extensions
│   ├── glm/                   # Mathematics library
│   └── imgui/                 # Immediate mode GUI
├── test_models/               # 🎲 Sample 3D models for testing
├── ORBX/                      # 🎨 Octane scene files
└── cmake/                     # 🔨 Build system configuration
```

### Application Types

**Desktop Applications (C++)**:
- `simpleGL`: Standalone 3D viewer with file loading and camera controls
- `simpleGlGrpc`: Network-based camera synchronization without SDK dependencies
- `simpleGlSdk`: Full SDK integration with real-time Octane synchronization
- `testGrpcApi`: Advanced ImGui-based gRPC API testing and debugging interface

**Web Applications (HTML/JavaScript)**:
- `octaneWeb/`: **PRODUCTION-READY** web application suite with complete Octane integration
  - Real-time callback rendering with consistent frame display (buffer corruption FIXED)
  - Mouse drag camera synchronization with live Octane updates (end-to-end working)
  - Scene outliner with hierarchical tree view and visibility controls
  - Node graph editor with right-click context menus and node creation
  - Configurable UI debug mode (toggleUIDebugMode() in browser console)
  - Performance optimized with clean production UI
  - Professional OTOY branding and responsive design
- `html/`: Legacy web applications (deprecated but functional)
  - Basic LiveLink connectivity testing
  - Simple 3D viewer with Octane sync

**Infrastructure**:
- **OPTIMIZED** Python proxy server with performance enhancements and minimal logging
- Real-time callback streaming system with dedicated thread-based asyncio
- Cross-platform build system supporting multiple development environments
- Shared helper libraries for common functionality across applications

### Key Features

#### **🚀 Production-Ready Core Features**
- **Real-time Callback Rendering**: OnNewImage callbacks with consistent frame display (buffer corruption FIXED)
- **Mouse Drag Camera Sync**: Live camera synchronization with Octane (end-to-end working)
- **Performance Optimized**: Minimal logging, PNG saves disabled, clean production UI
- **Configurable Debug UI**: toggleUIDebugMode() for development access without performance impact
- **Robust Memory Management**: Proper buffer isolation prevents garbage frames
- **Scene Integration**: Complete Scene Outliner, Node Inspector, Node Graph working

#### **🎛️ User Interface Features**
- **Clean Production UI**: Professional interface with debug overlays disabled by default
- **Scene Outliner**: Hierarchical tree view of Octane scene with expand/collapse and visibility controls
- **Node Graph Editor**: Visual node creation and editing with right-click context menus
- **Professional OTOY Branding**: Clean dark UI matching Octane UX standards
- **Responsive Design**: Mobile-friendly interface with touch-optimized controls
- **Debug Console**: Ctrl-D toggleable debug console for development

#### **🔧 Technical Features**
- **Real-time Streaming**: Dedicated thread-based callback streaming with proper asyncio management
- **Cross-platform Compatibility**: Windows, Linux, and macOS support
- **Multi-format 3D Model Loading**: Support for OBJ, PLY, and STL file formats
- **Enhanced Error Handling**: Comprehensive error reporting with graceful degradation
- **CORS-compliant**: Enhanced cross-origin support with X-Call-Id and gRPC-Web headers
- **Zero External Dependencies**: Custom gRPC-Web implementation without CDN libraries
- **Modular Architecture**: Separate utility files for shared functionality across applications
- **Cache Busting System**: Development-time cache management with visual indicators

### Recent Major Updates (2025)

#### **🚀 PRODUCTION-READY SYSTEM ACHIEVED**
- **✅ OCTANEWEB PRODUCTION-READY**: Complete real-time rendering system with optimized performance
- **✅ BUFFER CORRUPTION FIXED**: Critical HDR buffer processing fix - consistent frame display
- **✅ CAMERA SYNC COMPLETE**: End-to-end mouse drag camera synchronization with live Octane updates
- **✅ PERFORMANCE OPTIMIZED**: PNG saves disabled, logging minimized, clean production UI
- **✅ UI DEBUG MODE SYSTEM**: Configurable debug overlays with toggleUIDebugMode() runtime control

#### **🔧 Core System Implementations**
- **✅ REAL-TIME CALLBACK SYSTEM**: OnNewImage callbacks with dedicated thread-based streaming
- **✅ SCENE OUTLINER COMPLETE**: Hierarchical tree view with expand/collapse, node icons, and visibility toggles
- **✅ NODE GRAPH EDITOR COMPLETE**: Right-click context menus, hierarchical node types, and node creation system
- **✅ REAL API INTEGRATION**: Connected to live Octane APIs including buildSceneTree, GetMeshes, and camera sync

#### **⚡ Performance & Production Enhancements**
- **✅ OPTIMIZED PROXY SERVER**: Minimal logging, PNG saves disabled, enhanced error handling
- **✅ PROFESSIONAL PRODUCTION UX**: Clean OTOY styling with debug overlays disabled by default
- **✅ MEMORY MANAGEMENT**: Proper buffer isolation prevents garbage frames between renders
- **✅ DEVELOPMENT TOOLS**: Cache busting system, debug console, and comprehensive error reporting
- **✅ CROSS-PLATFORM BUILDS**: Successful Linux, Windows, and macOS build configurations
- **✅ COMPREHENSIVE DOCUMENTATION**: Updated production status documentation and setup guides

## Key Development Guidelines

### UI/UX Principles
- **Professional Dark Theme**: Clean OTOY-branded interface with minimal debug overlays in production
- **Responsive Design**: Mobile-friendly interface with touch-optimized controls
- **Status Transparency**: Color-coded LED system (yellow=ready, green=operational, red=error)
- **Debug Access**: Use `toggleUIDebugMode()` in browser console for development visibility

## Production Deployment

### 🚀 Production-Ready Status
**octaneWeb is PRODUCTION-READY** with all core functionality complete and optimized:
- Real-time callback rendering with consistent frame display
- Mouse drag camera synchronization with live Octane updates
- Performance optimized with minimal logging and clean UI
- Configurable debug mode for development needs
- Robust error handling and memory management

### Quick Start (Production)
1. **Start octaneWeb**: Run `octaneWeb/start_servers.bat` (auto-installs dependencies)
2. **Access Application**: Open http://localhost:43331 in browser
3. **Connect to Octane**: Ensure Octane LiveLink is enabled (Help → LiveLink)
4. **Debug Access**: Use `toggleUIDebugMode()` in browser console when needed

### Network Configuration
**Sandbox Environments**: Development environments (like OpenHands) may have network isolation:
- Use `host.docker.internal:51022` for Octane connection in sandboxed environments
- Proxy server includes graceful degradation and retry logic
- Applications detect connection failures and provide appropriate fallbacks

### Production Workflow
1. **Live Integration**: Connect to real Octane LiveLink service for all functionality
2. **Performance Monitoring**: System optimized for production with minimal logging
3. **Debug Access**: Use toggleUIDebugMode() for development visibility when needed
4. **Cross-platform Support**: Tested on Windows, Linux, and macOS

### 🚨 **CRITICAL REQUIREMENT: REAL OCTANE ONLY**
**⚠️ NEVER EVER use mock or simulated data - only real live connection with Octane LiveLink service.**