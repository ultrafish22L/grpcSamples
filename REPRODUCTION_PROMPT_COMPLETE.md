# Complete Octane gRPC Samples Repository Reproduction Prompt

## User Experience Requirements (Non-Technical)

### Visual Design and Branding
Create a professional 3D rendering application suite with **OTOY Octane Render branding** that matches industry standards for 3D software. The interface should use a **dark theme** with red accent colors (#e74c3c), professional typography, and the OTOY logo prominently displayed. All applications should feel cohesive and professional, suitable for 3D artists and developers working with Octane Render.

### Desktop Applications User Experience
Build **four distinct C++ desktop applications** that demonstrate different levels of Octane integration:

1. **Standalone 3D Viewer** (`simpleGL`): A basic OpenGL application that loads and displays 3D models (OBJ, PLY, STL) with mouse camera controls. No network connectivity required.

2. **Network-Synchronized Viewer** (`simpleGlGrpc`): Same 3D viewer but with real-time camera synchronization to Octane Render via gRPC. Camera movements should sync bidirectionally.

3. **SDK-Integrated Viewer** (`simpleGlSdk`): Full integration with Octane SDK for direct scene access and manipulation.

4. **Advanced API Testing Interface** (`testGrpcApi`): A comprehensive ImGui-based application for testing all Octane gRPC APIs with detailed logging, performance monitoring, and connection diagnostics.

### Web Application User Experience
Create a **modern web application suite** (`octaneWeb/`) that provides browser-based access to Octane functionality:

#### Main Interface Layout
- **Left Panel**: Hierarchical scene outliner showing the complete Octane scene tree
- **Center Panel**: 3D WebGL viewport with interactive camera controls
- **Right Panel**: Activity log with real-time operation feedback
- **Top Bar**: Connection controls, server address input, and status indicators
- **Bottom Bar**: Performance metrics (FPS, response times, connection health)

#### Scene Outliner Requirements
- **Hierarchical Tree View**: Display scene nodes in expandable tree structure
- **Node Icons**: Different icons for geometry, lights, cameras, materials
- **Expand/Collapse**: Click triangles (▼/▶) to expand/collapse node children
- **Visibility Controls**: Eye icons to toggle node visibility in Octane
- **Node Selection**: Click nodes to select them (highlight in blue)
- **Professional Styling**: Dark theme with proper indentation and hover effects

#### Node Graph Editor Requirements
- **Right-Click Context Menus**: Right-click on scene outliner nodes to show context menu
- **Hierarchical Node Creation**: Menu organized by node types (Geometry, Lights, Materials, etc.)
- **Popup Submenus**: Hover over menu items to show submenu popups with specific node types
- **Visual Feedback**: Proper menu backgrounds, hover effects, and selection indicators
- **Node Creation**: Successfully create new nodes in Octane scene via API calls

#### 3D Viewport Requirements
- **WebGL Rendering**: Support both WebGL 2.0 and 1.0 with automatic fallback
- **Interactive Camera**: Mouse controls for orbit, pan, zoom
- **Real-time Sync**: Camera movements sync with Octane in real-time
- **3D Model Display**: Show basic 3D geometry (cube, sphere, etc.)
- **Responsive Design**: Adapt to different screen sizes and orientations

#### Activity Logging Requirements
- **Real-time Updates**: Show all API calls and responses as they happen
- **Emoji Indicators**: Use 📤 for outgoing, 📥 for incoming, ❌ for errors, ✅ for success
- **Timestamps**: Show precise timestamps for all operations
- **Scrollable History**: Maintain complete log history with auto-scroll to latest
- **Clear/Export**: Buttons to clear log or export to file

#### Connection Management
- **Status LED**: Three-state indicator (yellow=ready, green=connected, red=error)
- **Server Address**: Editable input field for proxy server address
- **Connect/Disconnect**: Toggle switch for connection control
- **Auto-Reconnect**: Automatic retry logic with exponential backoff
- **Error Recovery**: Clear error messages and recovery suggestions

#### Responsive Design Requirements
- **Mobile Support**: Full functionality on phones and tablets
- **Touch Controls**: Touch-friendly 3D camera controls
- **Adaptive Layout**: Reorganize panels for smaller screens
- **Accessibility**: High contrast support, keyboard navigation, reduced motion options

### Development Tools Requirements
- **Cache Busting**: Visual indicators showing current version to prevent browser caching issues
- **Debug Console**: Ctrl-D toggleable debug window showing detailed technical information
- **Mock Server**: Development-time Octane simulation for testing without live Octane
- **Comprehensive Logging**: Detailed request/response logging with performance metrics

### Legacy Application Support
Maintain the existing `html/` applications as functional legacy examples, but mark them as deprecated in favor of the modern `octaneWeb/` suite.

## Technical Implementation Details

### Repository Structure
```
grpcSamples/
├── shared/                    # Common C++ helper libraries
│   ├── camera_system.h        # Camera controls and input handling
│   ├── model_loader.h         # 3D model loading (OBJ/PLY/STL)
│   ├── file_dialog.h          # Cross-platform file dialogs
│   ├── js/                    # Shared JavaScript utilities
│   └── generated/             # Generated protobuf files
├── simpleGL/                  # Standalone 3D model viewer
│   ├── main.cpp               # OpenGL viewer with file loading
│   └── CMakeLists.txt         # Build configuration
├── simpleGlGrpc/              # Network-synchronized viewer
│   ├── main.cpp               # gRPC camera sync implementation
│   └── CMakeLists.txt         # Build configuration
├── simpleGlSdk/               # SDK-integrated viewer
│   ├── main.cpp               # Direct SDK integration
│   └── CMakeLists.txt         # Build configuration
├── testGrpcApi/               # Advanced API testing interface
│   ├── main.cpp               # ImGui-based testing application
│   ├── ActivityLogger.h/.cpp  # Comprehensive logging system
│   ├── PerformanceTracker.h/.cpp # Performance monitoring
│   └── CMakeLists.txt         # Build configuration
├── octaneWeb/                 # Modern web application suite
│   ├── index.html             # Main application entry point
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
├── html/                      # Legacy web applications (DEPRECATED)
│   ├── index.html             # Original LiveLink web interface
│   ├── start_proxy.sh/.bat    # Proxy server launchers
│   └── README_LIVELINK.md     # Legacy documentation
├── proxy/                     # HTTP-to-gRPC proxy server
│   ├── grpc_proxy.py          # Main proxy server with comprehensive logging
│   ├── livelink_pb2.py        # Generated protobuf Python bindings
│   └── *_pb2.py               # Complete Octane API protobuf bindings
├── mock_octane/               # Development mock server
│   ├── mock_octane_server.py  # Simulates Octane LiveLink for development
│   └── start_mock_octane.sh/.bat # Mock server launchers
├── sdk/                       # Octane SDK wrapper library
│   ├── octane*.h              # Core SDK headers
│   ├── octanewrap*.h/.cpp     # SDK wrapper classes
│   └── grpc-examples/         # gRPC integration examples
├── third_party/               # External dependencies
│   ├── grpc/                  # gRPC framework
│   ├── protobuf/              # Protocol buffers
│   ├── glfw/                  # Window management
│   ├── glew/                  # OpenGL extensions
│   ├── glm/                   # Mathematics library
│   └── imgui/                 # Immediate mode GUI
├── test_models/               # Sample 3D models for testing
├── ORBX/                      # Octane scene files
└── cmake/                     # Build system configuration
```

### Core Technologies
- **Desktop**: C++17, OpenGL 3.3+, gRPC, Protocol Buffers, CMake, ImGui
- **Web Frontend**: Vanilla JavaScript, WebGL 2.0/1.0, custom gRPC-Web implementation
- **Proxy Server**: Python with aiohttp, grpcio, comprehensive CORS middleware
- **Protocol**: HTTP/JSON for browser-to-proxy, native gRPC for all Octane communication
- **Development**: Mock server simulation and graceful degradation

### Build System Requirements
Create a **cross-platform CMake build system** that supports:
- Windows (Visual Studio, MinGW)
- Linux (GCC, Clang)
- macOS (Xcode, Clang)

Include all necessary third-party dependencies as git submodules or embedded libraries.

### gRPC Implementation Details

#### Protobuf Files Required
Generate Python and C++ bindings for these Octane API protobuf files:
- `livelink.proto` - Basic LiveLink camera and mesh APIs
- `apiprojectmanager.proto` - Project and scene management
- `apinodesystem.proto` - Node graph and scene tree APIs
- `octaneids.proto` - Node type definitions and IDs
- `octaneenums.proto` - Enumeration definitions
- `common.proto` - Common data structures

#### Proxy Server Implementation (`proxy/grpc_proxy.py`)
Create a comprehensive HTTP-to-gRPC proxy server with:
- **CORS Support**: Full cross-origin request handling
- **Comprehensive Logging**: Emoji-based logging (📤 outgoing, 📥 incoming, ❌ errors)
- **Error Handling**: Graceful degradation and detailed error reporting
- **API Coverage**: Support for all major Octane APIs
- **Performance Monitoring**: Request timing and connection health tracking
- **Auto-Retry Logic**: Automatic reconnection with exponential backoff

#### Web Client Implementation (`octaneWeb/js/OctaneWebClient.js`)
Implement a custom gRPC-Web client with:
- **Zero Dependencies**: No external libraries or CDN dependencies
- **HTTP/JSON Protocol**: Convert gRPC calls to HTTP requests
- **Async/Await Pattern**: Modern JavaScript async patterns
- **Error Handling**: Comprehensive error reporting and recovery
- **Connection Management**: Automatic reconnection and health monitoring

### Scene Outliner Implementation (`octaneWeb/js/SceneOutliner.js`)
Create a hierarchical tree view component with:
- **Data Transformation**: Convert flat API responses to hierarchical tree structure
- **DOM Rendering**: Efficient DOM manipulation for large scene trees
- **Event Handling**: Click handlers for expand/collapse, selection, visibility
- **CSS Styling**: Professional tree view styling with proper indentation
- **API Integration**: Real-time updates from Octane scene changes

### Node Graph Editor Implementation (`octaneWeb/js/NodeGraphEditor.js`)
Implement a visual node creation system with:
- **Context Menu System**: Right-click menus with hierarchical organization
- **Node Type Hierarchy**: Organized by Geometry, Lights, Materials, Cameras, etc.
- **Popup Submenus**: Hover-triggered submenus for specific node types
- **API Integration**: Create nodes in Octane via gRPC calls
- **Visual Feedback**: Proper menu styling and interaction feedback

### WebGL Rendering Implementation (`octaneWeb/shared/webgl-utils.js`)
Create WebGL rendering classes with:
- **Version Detection**: Automatic WebGL 2.0/1.0 detection and fallback
- **Shader Management**: Vertex and fragment shader compilation and linking
- **Geometry Rendering**: Basic 3D shapes (cube, sphere, etc.)
- **Camera Controls**: Mouse-based orbit, pan, zoom controls
- **Matrix Math**: 3D transformation and projection matrices

### Mock Server Implementation (`mock_octane/mock_octane_server.py`)
Create a development mock server that:
- **Simulates Octane APIs**: Provides realistic responses for all major APIs
- **Scene Data**: Mock scene hierarchy with geometry, lights, cameras
- **Camera Sync**: Bidirectional camera synchronization simulation
- **Node Creation**: Simulated node creation and scene modification
- **Development Mode**: Runs on localhost:51022 to match real Octane

### Development Tools Implementation

#### Cache Busting System (`octaneWeb/js/CacheBuster.js`)
- **Version Timestamps**: Append timestamps to script URLs
- **Visual Indicators**: Show current version in top-left corner
- **Development Mode**: Automatic cache busting during development

#### Debug Console (`octaneWeb/js/DebugConsole.js`)
- **Ctrl-D Toggle**: Keyboard shortcut to show/hide debug window
- **Console Capture**: Capture all console.log, error, warn messages
- **API Monitoring**: Show detailed API call information
- **Performance Metrics**: Display timing and performance data

### Connection Architecture
```
Browser Application ↔ HTTP/JSON ↔ Python Proxy Server ↔ gRPC ↔ Octane LiveLink Service
                                                      ↔ gRPC ↔ Mock Octane Server (development)
```

### Error Handling Strategy
- **Graceful Degradation**: Applications work offline with limited functionality
- **Automatic Retry**: Exponential backoff for connection failures
- **User Feedback**: Clear error messages with actionable recovery steps
- **Fallback Data**: Mock data when live connections unavailable

### Performance Requirements
- **60 FPS Rendering**: Smooth 3D viewport performance
- **Sub-100ms API Response**: Fast API call response times
- **Efficient DOM Updates**: Minimal DOM manipulation for large scene trees
- **Memory Management**: Proper cleanup of WebGL resources and event listeners

### Testing Strategy
- **Mock Server Testing**: All development can proceed without live Octane
- **Cross-browser Testing**: Support for Chrome, Firefox, Safari, Edge
- **Mobile Testing**: Full functionality on iOS and Android browsers
- **Connection Testing**: Robust testing of connection failures and recovery

### Documentation Requirements
- **Setup Guides**: Clear instructions for building and running all applications
- **API Documentation**: Complete documentation of all gRPC APIs used
- **User Guides**: Step-by-step usage instructions for each application
- **Developer Guides**: Technical documentation for extending the applications

## Potential Improvements

### Advanced Features
- **Real-time Collaboration**: Multiple users editing the same scene
- **Undo/Redo System**: Complete operation history with rollback
- **Drag-and-Drop**: File loading and node manipulation via drag-and-drop
- **Keyboard Shortcuts**: Comprehensive keyboard shortcuts for power users
- **Plugin System**: Extensible architecture for custom functionality

### Performance Optimizations
- **WebGL 2.0 Features**: Advanced rendering techniques for better performance
- **Scene Culling**: Only render visible scene elements
- **Lazy Loading**: Load scene data on-demand for large scenes
- **Connection Pooling**: Reuse connections for better performance

### User Experience Enhancements
- **Themes**: Multiple color themes beyond the default dark theme
- **Customizable Layout**: User-configurable panel layouts
- **Search and Filter**: Search functionality in scene outliner
- **Bookmarks**: Save and restore camera positions and scene states
- **Export Functionality**: Export scene data and images

### Development Tools
- **Hot Reload**: Automatic reloading during development
- **Performance Profiler**: Built-in performance analysis tools
- **API Explorer**: Interactive API testing interface
- **Scene Debugger**: Visual debugging tools for scene hierarchy
- **Network Monitor**: Real-time network traffic analysis