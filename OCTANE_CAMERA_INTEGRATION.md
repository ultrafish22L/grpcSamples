# Octane Camera Integration

This document describes the integration between the simpleGL application and the Octane SDK for camera synchronization.

## Overview

The integration allows the simpleGL application to synchronize its OpenGL camera with Octane's render camera, enabling real-time camera updates as the user manipulates the view.

## Architecture

### Components

1. **OctaneCameraSync Class** (`octane_camera_sync.h/cpp`)
   - Manages the connection between OpenGL and Octane cameras
   - Handles coordinate system conversions
   - Provides simulation mode when gRPC is unavailable

2. **Camera Integration** (`main.cpp`)
   - Integrates camera sync into the main application
   - Updates Octane camera on mouse interactions
   - Initializes SDK connection

3. **Demo Application** (`demo.cpp`)
   - Demonstrates camera sync functionality
   - Shows coordinate transformations
   - Provides testing without OpenGL context

## Key Features

### Camera Synchronization
- **Real-time Updates**: Camera position and orientation are synchronized whenever the user interacts with the view
- **Mouse Integration**: Updates occur on mouse drag (orbit) and scroll (zoom) events
- **Coordinate Conversion**: Automatic conversion between GLM and Octane vector/matrix types

### SDK Integration
- **getRenderCameraNode()**: Retrieves the current render camera from Octane
- **Transform Updates**: Sets camera position and orientation using transformation matrices
- **Error Handling**: Graceful fallback when SDK functionality is unavailable

### Simulation Mode
- **Development Support**: Works without full gRPC connectivity
- **Logging**: Detailed output showing what operations would be performed
- **Testing**: Allows development and testing of camera logic

## Implementation Details

### Camera Coordinate System
The application uses a spherical coordinate system for camera control:
- **Radius**: Distance from the center point
- **Theta**: Horizontal angle (azimuth)
- **Phi**: Vertical angle (elevation)

### Coordinate Conversion
```cpp
// GLM to Octane vector conversion
OctaneVec::float3 glmToOctane(const glm::vec3& v) const {
    OctaneVec::float3 result;
    result.x = v.x; result.y = v.y; result.z = v.z;
    return result;
}

// GLM to Octane matrix conversion (column-major to row-major)
OctaneVec::float4x4 glmToOctane(const glm::mat4& m) const {
    OctaneVec::float4x4 result;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 4; ++col) {
            result.m[row][col] = m[col][row];
        }
    }
    return result;
}
```

### Camera Update Flow
1. User interacts with mouse (drag/scroll)
2. OpenGL camera parameters updated (theta, phi, radius)
3. New camera position calculated using spherical coordinates
4. `octaneSync.updateCamera()` called with new position/target/up vectors
5. Coordinates converted to Octane format
6. Camera transform applied to Octane render camera node

## Usage

### Connection to Octane Server

The camera sync system requires a connection to the Octane server before initialization. The connection uses Unix domain sockets for communication:

```cpp
// Default connection to standard Octane server socket
octaneSync.connectToServer("/tmp/octane_server.sock");

// Custom server address
octaneSync.connectToServer("/path/to/custom/octane.sock");
```

**Connection Modes:**
- **gRPC Enabled**: Establishes actual connection to Octane server via Unix socket
- **Simulation Mode**: When gRPC is disabled, connection returns success but operates in simulation mode

### Initialization
```cpp
OctaneCameraSync octaneSync;

// Connect to Octane server (required before initialization)
if (!octaneSync.connectToServer("/tmp/octane_server.sock")) {
    std::cerr << "Warning: Failed to connect to Octane server" << std::endl;
}

// Initialize the camera sync system
if (!octaneSync.initialize()) {
    std::cerr << "Warning: Failed to initialize Octane camera sync" << std::endl;
}
```

### Camera Updates
```cpp
// On mouse interaction
glm::vec3 position = camera.getPosition();
octaneSync.updateCamera(position, camera.center, glm::vec3(0.0f, 1.0f, 0.0f));
```

### Status Checking
```cpp
if (octaneSync.isCameraControlAvailable()) {
    // Full SDK functionality available
} else {
    // Running in simulation mode
}
```

## Current Status

### Working Features
- ✅ Camera sync class implementation
- ✅ Integration with simpleGL application
- ✅ Mouse interaction updates
- ✅ Coordinate system conversion
- ✅ Simulation mode for development
- ✅ Comprehensive logging and debugging

### Build Configuration

The SDK supports both gRPC-enabled and simulation modes:

```bash
# Enable gRPC functionality (requires gRPC libraries)
cmake .. -DENABLE_OCTANE_GRPC=ON

# Disable gRPC (simulation mode only)
cmake .. -DENABLE_OCTANE_GRPC=OFF
```

### Current Limitations
- ⚠️ gRPC functionality disabled by default (missing libraries)
- ⚠️ Running in simulation mode
- ⚠️ Cannot actually communicate with Octane render engine

### Future Enhancements
When gRPC libraries are available:
1. **Full SDK Integration**: Enable actual communication with Octane
2. **Bidirectional Sync**: Read camera state from Octane
3. **Advanced Features**: Support for camera animation, keyframes
4. **Performance Optimization**: Reduce update frequency, batch operations

## Testing

### Demo Application
Run the demo to see camera sync in action:
```bash
cd bin
./simpleGL_demo
```

Expected output shows:
- SDK initialization
- Camera position calculations
- Coordinate transformations
- Simulation mode operations

### Main Application
The main application integrates camera sync with OpenGL rendering:
```bash
cd bin
./simpleGL
```

Camera updates occur automatically during mouse interactions.

## Build Integration

The camera sync functionality is integrated into the CMake build system:
- Source files added to simpleGL and simpleGL_demo targets
- SDK headers included in build path
- Links against octane_sdk library

## Error Handling

The implementation includes comprehensive error handling:
- Graceful degradation when SDK unavailable
- Detailed logging for debugging
- Simulation mode for development
- Exception handling for SDK calls

## Conclusion

This integration provides a solid foundation for camera synchronization between OpenGL and Octane. While currently running in simulation mode due to missing gRPC libraries, the architecture is ready for full SDK integration once the required libraries are available.

The implementation demonstrates:
- Clean separation of concerns
- Robust error handling
- Comprehensive testing capabilities
- Production-ready code structure