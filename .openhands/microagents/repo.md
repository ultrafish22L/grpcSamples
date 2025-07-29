# Octane gRPC Samples Repository

## 🚨 CRITICAL OPENHANDS NETWORKING SETUP

**Docker Container Isolation**: OpenHands cannot access host localhost services by default. For gRPC proxy connectivity:

```bash
export SANDBOX_USE_HOST_NETWORK=true
```

**Docker-in-Docker Alternative:**
```bash
export SANDBOX_LOCAL_RUNTIME_URL="http://host.docker.internal"
```

**Troubleshooting Keywords**: `Connection refused`, `localhost:8080`, `gRPC timeout`, `Network unreachable`

**Complete Guide**: See `OPENHANDS_LOCALHOST_NETWORKING.md` for detailed networking configuration.

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
- **Mock Server**: Development-time Octane simulation for testing without live Octane instance

### Architecture Patterns
**Desktop Applications**: C++ Application ↔ gRPC ↔ Octane LiveLink Service
**Web Applications**: JavaScript Client ↔ HTTP Proxy Server ↔ gRPC ↔ Octane LiveLink Service
**Development Mode**: Applications ↔ Mock Octane Server (for testing without live Octane)

### Key Technologies
- **Desktop**: C++17, OpenGL 3.3+, gRPC, Protocol Buffers, CMake, ImGui
- **Web Frontend**: Vanilla JavaScript, WebGL 2.0/1.0, custom gRPC-Web implementation, real-time 3D rendering
- **Proxy Server**: Python with aiohttp, grpcio, comprehensive CORS middleware, and enhanced logging
- **Protocol**: HTTP/JSON for browser-to-proxy, native gRPC for all Octane communication
- **Development**: Mock server simulation and graceful degradation when Octane unavailable

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
├── octaneWeb/                 # 🚀 Modern web application suite
│   ├── index.html             # Main web application
│   ├── js/                    # JavaScript modules
│   │   ├── OctaneWebClient.js # gRPC-Web client implementation
│   │   ├── SceneOutliner.js   # Hierarchical scene tree viewer
│   │   ├── NodeGraphEditor.js # Visual node graph editor
│   │   ├── DebugConsole.js    # Development debug console
│   │   └── CacheBuster.js     # Development cache management
│   ├── css/                   # Styling and themes
│   │   ├── main.css           # Core application styles
│   │   └── otoy-theme.css     # Professional OTOY branding
│   ├── shared/                # Shared web utilities
│   │   ├── webgl-utils.js     # WebGL rendering classes
│   │   └── shared.js          # Common helper functions
│   └── assets/                # Static assets and icons
├── octaneProxy/                     # 🔄 HTTP-to-gRPC proxy server
│   ├── octane_proxy.py          # Main proxy server with comprehensive logging
│   ├── livelink_pb2.py        # Generated protobuf Python bindings
│   └── *_pb2.py               # Complete Octane API protobuf bindings
├── mock_octane/               # 🎭 Development mock server
│   ├── mock_octane_server.py  # Simulates Octane LiveLink for development
│   └── start_mock_octane.sh/.bat # Mock server launchers
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
- `octaneWeb/`: Modern web application suite with comprehensive Octane integration
  - Scene outliner with hierarchical tree view and visibility controls
  - Node graph editor with right-click context menus and node creation
  - Real-time 3D WebGL rendering with camera synchronization
  - Professional OTOY branding and responsive design
- `html/`: Legacy web applications (deprecated but functional)
  - Basic LiveLink connectivity testing
  - Simple 3D viewer with Octane sync

**Infrastructure**:
- Python proxy server for HTTP-to-gRPC translation with comprehensive logging
- Mock Octane server for development without live Octane instance
- Cross-platform build system supporting multiple development environments
- Shared helper libraries for common functionality across applications

### Key Features
- **Real-time Camera Synchronization**: Bidirectional camera sync between applications and Octane
- **Scene Outliner**: Hierarchical tree view of Octane scene with expand/collapse and visibility controls
- **Node Graph Editor**: Visual node creation and editing with right-click context menus
- **Multi-format 3D Model Loading**: Support for OBJ, PLY, and STL file formats
- **Cross-platform Compatibility**: Windows, Linux, and macOS support
- **Web Integration**: Browser-based clients with custom gRPC-Web implementation
- **Comprehensive Logging**: Detailed request/response logging with emoji indicators (📤 outgoing, 📥 incoming, ❌ errors)
- **Development-friendly**: Mock server simulation and graceful degradation when Octane unavailable
- **Enhanced Error Handling**: Comprehensive error reporting with detailed debug information
- **Performance Monitoring**: Real-time FPS, call statistics, and connection health tracking
- **CORS-compliant**: Enhanced cross-origin support with X-Call-Id and gRPC-Web headers
- **Event-driven Architecture**: Asynchronous client with proper connection state management
- **Activity Log System**: Complete detailed operation logging in HTML applications with timestamps and emoji indicators
- **Zero External Dependencies**: Custom gRPC-Web implementation without CDN libraries or generated protobuf files
- **Professional OTOY Branding**: OTOY-themed versions with professional dark UI matching Octane UX standards
- **Shared Code Architecture**: Common utilities and WebGL classes to eliminate code duplication
- **WebGL 2.0/1.0 Compatibility**: Enhanced 3D rendering with backward compatibility for older browsers
- **Modular Design**: Separate utility files for shared functionality across all web applications
- **Cache Busting System**: Development-time cache management with visual indicators
- **Debug Console**: Ctrl-D toggleable debug console for development

### Recent Major Updates (2025)
- **✅ OCTANEWEB SUITE CREATED**: Complete modern web application replacing legacy html/ applications
- **✅ SCENE OUTLINER IMPLEMENTED**: Hierarchical tree view with expand/collapse, node icons, and visibility toggles
- **✅ NODE GRAPH EDITOR COMPLETE**: Right-click context menus, hierarchical node types, and node creation system
- **✅ REAL API INTEGRATION**: Connected to live Octane APIs including buildSceneTree, GetMeshes, and camera sync
- **✅ MOCK SERVER DEVELOPMENT**: Complete mock Octane server for development without live Octane instance
- **✅ ENHANCED PROXY SERVER**: Comprehensive logging, error handling, and API coverage
- **✅ PROFESSIONAL UX**: Applied OTOY.com styling with red accents, dark panels, and responsive design
- **✅ DEVELOPMENT TOOLS**: Cache busting system, debug console, and comprehensive error reporting
- **✅ TESTGRPCAPI ENHANCED**: ImGui-based desktop application for advanced gRPC API testing
- **✅ CROSS-PLATFORM BUILDS**: Successful Linux, Windows, and macOS build configurations
- **✅ COMPREHENSIVE DOCUMENTATION**: Updated documentation, setup guides, and reproduction prompts

## User Experience Design Patterns

### Visual Design Philosophy
The application interfaces follow a **professional dark theme** approach that prioritizes clarity and reduces eye strain during extended 3D rendering sessions. The design language emphasizes **immediate visual feedback** and **status transparency**, ensuring users always understand the current system state and connection health.

### Interface Layout Strategies
**Adaptive Content Hierarchy**: The interface dynamically reorganizes based on available screen space, with critical controls always remaining accessible. Activity logs and status information scale proportionally to screen size, ensuring optimal information density without overwhelming smaller displays.

**Progressive Information Disclosure**: Complex technical details are layered behind primary actions, allowing both novice and expert users to operate at their preferred level of detail. Connection diagnostics and debug information appear contextually when needed.

### Multi-Device Experience Patterns
**Mobile-First Responsive Design**: The interface gracefully adapts from large desktop displays down to mobile phones, with touch-optimized controls and reorganized layouts that prioritize the most important functions on smaller screens.

**Context-Aware Layout Switching**: On mobile devices, the activity log moves above the 3D viewport for better readability, while desktop users see a side-by-side layout that maximizes both 3D workspace and logging visibility.

**Touch-Friendly Interactions**: All interactive elements meet accessibility standards for touch targets, with generous spacing and clear visual feedback for touch interactions.

### Status Communication Design
**Three-State Visual Feedback System**: The interface uses a color-coded LED system that immediately communicates system health:
- **Ready State**: Warm yellow indicating system is prepared and waiting
- **Operational State**: Green indicating active connection and successful operations  
- **Error State**: Red indicating system dependencies are unavailable or errors occurred

**Real-Time Activity Transparency**: All system operations are logged with timestamps and visual indicators, creating a sense of system reliability and allowing users to understand exactly what's happening during complex operations.

### Professional Branding Integration
**Industry-Standard Aesthetics**: The interface matches professional 3D rendering software conventions, using familiar dark themes, red accent colors, and clean typography that 3D artists and developers expect.

**Contextual Branding**: Professional logos and branding elements are integrated without overwhelming the functional interface, maintaining credibility while keeping focus on the tools.

### Accessibility and Inclusion Patterns
**Reduced Motion Support**: Users with motion sensitivity preferences see static interfaces without animations or pulsing effects, while maintaining all functional capabilities.

**High Contrast Compatibility**: The interface automatically adapts to high contrast system preferences, ensuring visibility for users with visual impairments.

**Keyboard Navigation**: All functions remain accessible via keyboard navigation, supporting users who cannot or prefer not to use pointing devices.

### Error Communication Strategy
**Contextual Error Messaging**: Instead of generic error messages, the system provides specific, actionable feedback about what went wrong and what the user can do to resolve issues.

**Graceful Degradation**: When connections fail or services become unavailable, the interface clearly communicates the limitation while maintaining access to offline functionality.

**Progressive Error Recovery**: The system guides users through connection troubleshooting with clear visual cues about which components are working and which need attention.

### Performance Feedback Patterns
**Real-Time Performance Metrics**: Connection speed, response times, and system health are continuously displayed in an unobtrusive footer, allowing users to monitor system performance without interrupting their workflow.

**Activity Logging with Context**: Every operation is logged with clear success/failure indicators and timing information, helping users understand system behavior and troubleshoot issues independently.

### Cross-Platform Consistency
**Unified Experience**: Whether accessed on desktop browsers, mobile devices, or tablets, users encounter consistent functionality and visual design, reducing learning curve when switching between devices.

**Platform-Optimized Interactions**: While maintaining visual consistency, interactions are optimized for each platform - touch gestures on mobile, mouse interactions on desktop, with appropriate feedback for each input method.

## Development Environment

### Sandbox Limitations
**Network Isolation**: Development environments (like OpenHands) may have network isolation that prevents direct connection to localhost services running on the host machine. This affects:
- Connection to live Octane LiveLink service at 127.0.0.1:51022
- Proxy server binding to specific ports
- Real-time testing of live Octane integration

**Workarounds**:
- Mock server provides full Octane API simulation for development
- Proxy server includes graceful degradation and retry logic
- Applications detect connection failures and provide appropriate fallbacks

### Development Workflow
1. **Mock Development**: Use mock_octane_server.py for initial development and testing
2. **Proxy Testing**: Test HTTP-to-gRPC translation with comprehensive logging
3. **Live Integration**: Connect to real Octane LiveLink service for production testing
4. **Cross-platform Validation**: Build and test on multiple operating systems