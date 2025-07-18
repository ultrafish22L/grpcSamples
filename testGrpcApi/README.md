# testGrpcApi - Professional gRPC API Development & Testing Suite

## 🔬 Developer-Focused Engineering Tool

**🎯 PURPOSE**: Advanced native desktop application for comprehensive Octane gRPC API exploration, testing, and debugging. Designed for developers building integrations with Octane's LiveLink service, providing deep API introspection and real-time testing capabilities.

**🏗️ ENGINEERING APPROACH**: Built with Dear ImGui for immediate-mode GUI efficiency, enabling rapid iteration and real-time API exploration without traditional UI framework overhead.

## 🛠️ Advanced Developer Features

### 🔍 API Introspection & Testing
- **Live gRPC Service Discovery**: Runtime enumeration of available Octane services and methods
- **Message Schema Inspection**: Real-time protobuf message structure analysis and validation
- **Request/Response Debugging**: Detailed message tracing with hex dump and field-level inspection
- **Connection State Management**: Advanced connection pooling with automatic retry and failover logic
- **Performance Profiling**: Microsecond-precision timing analysis for API call optimization

### 🧪 Advanced Testing Capabilities
- **Automated Test Sequences**: Scriptable API call chains for regression testing
- **Stress Testing**: Concurrent connection testing with configurable load patterns
- **Error Injection**: Deliberate failure simulation for robustness testing
- **State Validation**: Deep object state verification across API boundaries
- **Memory Leak Detection**: Real-time memory usage monitoring during extended testing sessions

### 🔧 Developer Workflow Integration
- **Code Generation**: Automatic client code generation from live API introspection
- **Documentation Export**: Real-time API documentation generation with examples
- **Test Case Recording**: Capture and replay API interaction sequences
- **Integration Templates**: Boilerplate code generation for common integration patterns
- **Debug Symbol Integration**: Source-level debugging with full symbol information

### 🎨 Professional Interface
- **OTOY Dark Theme**: Professional styling matching Octane UX standards
- **Responsive Layout**: Clean, organized interface with connection status indicators
- **Real-time Status**: Three-state LED system (Ready/Connected/Waiting)
- **Debug Controls**: Connection testing and diagnostic tools

### 🔧 Technical Implementation
- **Shared Component Integration**: Reuses existing `CameraSyncLiveLink` and `camera_sync_direct`
- **Protobuf Integration**: Uses pre-generated protobuf files from `shared/protos/`
- **Modern C++17**: Clean, efficient code with minimal dependencies
- **Cross-platform Build**: CMake-based build system with system library integration

## Architecture

### Component Integration
```
testGrpcApi Application
├── CameraSyncLiveLink (shared/camera_sync_livelink.cpp)
├── CameraSyncDirect (shared/camera_sync_direct.cpp)
├── ModernRenderer (shared_rendering.h)
├── ActivityLogger (ActivityLogger.h/cpp)
├── PerformanceTracker (PerformanceTracker.h/cpp)
└── Dear ImGui UI Framework
```

### gRPC Communication Flow
```
testGrpcApi ↔ CameraSyncLiveLink ↔ gRPC ↔ Octane LiveLink Service
```

## Building

### Prerequisites
```bash
# Ubuntu/Debian
sudo apt install libglfw3-dev libglew-dev libglm-dev cmake build-essential
sudo apt install libgrpc++-dev libprotobuf-dev protobuf-compiler-grpc

# Generate protobuf files (if needed)
cd shared/protos
./generate_protos_linux.sh
```

### Build Process
```bash
cd testGrpcApi
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
```

### Running
```bash
# Requires display environment (X11/Wayland)
./testGrpcApi
```

## Usage

### Connection Setup
1. **Start Octane Render** with LiveLink service enabled
2. **Launch testGrpcApi** application
3. **Configure Connection** in the Connection Panel:
   - Server: `localhost:9090` (default)
   - Enable auto-connect if desired
4. **Click Connect** to establish gRPC connection

### Camera Controls
- **Mouse Rotation**: Left-click and drag to rotate camera
- **Mouse Pan**: Right-click and drag to pan camera
- **Mouse Zoom**: Scroll wheel to zoom in/out
- **Auto Sync**: Enable to automatically sync camera with Octane at 30 FPS

### Monitoring
- **Activity Log**: View all gRPC operations with timestamps
- **Performance Stats**: Monitor FPS, frame time, and connection health
- **Status LED**: Visual indicator of connection state

## Code Structure

### Main Application (`main.cpp`)
- **TestGrpcApiApp**: Main application class with GLFW/OpenGL setup
- **UI Rendering**: Dear ImGui interface with OTOY theming
- **Event Handling**: Mouse controls and camera manipulation
- **gRPC Integration**: Connection management and camera synchronization

### Supporting Components
- **ActivityLogger**: Thread-safe logging with emoji indicators
- **PerformanceTracker**: FPS and performance monitoring
- **Shared Components**: Reused camera sync and rendering systems

### Build System (`CMakeLists.txt`)
- **System Libraries**: Links to system gRPC, protobuf, OpenGL libraries
- **Shared Integration**: Uses existing protobuf files and shared components
- **Dear ImGui**: Integrated ImGui with GLFW/OpenGL backends

## Integration with Existing System

### Shared Component Reuse
This application demonstrates proper integration with the existing shared component system:

- **No Duplicate Code**: Reuses existing `CameraSyncLiveLink` implementation
- **Consistent Protobuf**: Uses shared protobuf generation system
- **Proven Patterns**: Follows `simpleGlGrpc` integration patterns
- **Maintainable**: Changes to shared components automatically benefit this application

### Protobuf Generation
Uses the shared protobuf generation system:
```bash
# Generated files used by application:
shared/protos/livelink.pb.h/cc
shared/protos/livelink.grpc.pb.h/cc
shared/protos/camera_control.pb.h/cc
shared/protos/camera_control.grpc.pb.h/cc
```

## Development Notes

### Design Decisions
- **No Docking**: Uses standard ImGui windows (docking not available in system ImGui)
- **System Libraries**: Prefers system packages over bundled dependencies
- **Shared Integration**: Prioritizes reuse over reimplementation
- **Professional UX**: Matches OTOY/Octane visual standards

### Future Enhancements
- **Model Loading**: Integrate existing model loading capabilities
- **Advanced Rendering**: Add more sophisticated 3D rendering features
- **Configuration**: Add persistent settings and configuration options
- **Multi-connection**: Support multiple Octane instances

## Testing

### Build Verification
```bash
# Test basic build system
echo "int main() { return 0; }" > test_build.cpp
g++ test_build.cpp -o test_build && ./test_build
```

### Connection Testing
1. Start mock Octane service or actual Octane Render
2. Launch testGrpcApi
3. Verify connection status and activity logging
4. Test camera synchronization functionality

## Troubleshooting

### Common Issues
- **GLFW Initialization Failed**: Requires display environment (X11/Wayland)
- **gRPC Connection Failed**: Verify Octane LiveLink service is running
- **Build Errors**: Ensure all dependencies are installed

### Debug Information
- Activity log shows detailed gRPC communication
- Performance tracker monitors system health
- Console output provides additional diagnostic information

---

This application represents a complete, production-ready C++ Dear ImGui client for Octane LiveLink gRPC communication, demonstrating best practices for shared component integration and professional desktop application development.