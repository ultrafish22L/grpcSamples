# LiveLink gRPC-Web Client Implementation

## Overview

This is a complete, standalone gRPC-Web client implementation for connecting HTML applications to Octane Render's LiveLink service. The implementation has been designed to work without any external dependencies or generated protobuf files, making it compatible with any gRPC-Web setup.

## Problem Solved

The original implementation had compatibility issues between the CDN gRPC-Web library and the generated JavaScript files, causing errors like:
- `this.client_.rpcCall is not a function`
- `gRPC-Web generated classes not found`

This new implementation completely bypasses these issues by providing a custom HTTP-based gRPC-Web client.

## Features

### ✅ Core Functionality
- **Connection Management**: Connect/disconnect to Octane LiveLink service
- **Camera Control**: Get/set camera position, target, and FOV
- **Mesh Management**: Retrieve mesh lists and mesh data
- **Real-time Communication**: Event-driven architecture for real-time updates
- **Performance Tracking**: Call count, response times, and statistics
- **Error Handling**: Comprehensive error handling and reporting

### ✅ Technical Features
- **No External Dependencies**: Works without CDN libraries or generated files
- **HTTP-based gRPC-Web**: Uses standard fetch() API for gRPC-Web communication
- **Event System**: Built-in event emitter for connection state changes
- **Debug Support**: Comprehensive logging and debugging capabilities
- **Cross-browser Compatible**: Works in all modern browsers
- **Windows Build Compatible**: Maintains compatibility with existing Windows build system

## Files

### Core Implementation
- **`livelink.js`** - Main client implementation with LiveLinkClient and LiveLinkManager classes

### Main Application
- **`index.html`** - Complete WebGL 3D viewer with Octane LiveLink integration
  - Full-featured demo with camera control and real-time synchronization
  - Interactive 3D rendering with mouse controls
  - Professional OTOY-branded UI with activity logging
  - Comprehensive testing interface for all gRPC functionality

## Usage

### Basic Connection
```javascript
// Get the global LiveLink manager
const client = liveLinkManager.getClient('http://127.0.0.1:8080');

// Set up event listeners
client.on('connected', () => {
    console.log('Connected to Octane LiveLink');
});

client.on('error', (error) => {
    console.error('Connection error:', error);
});

// Connect to the server
await client.connect();
```

### Camera Control
```javascript
// Set camera position
await client.setCamera({
    position: { x: 0, y: 0, z: 5 },
    target: { x: 0, y: 0, z: 0 },
    fov: 45
});

// Get current camera state
const cameraState = await client.getCamera();
```

### Mesh Management
```javascript
// Get list of available meshes
const meshes = await client.getMeshes();

// Get specific mesh data
const meshData = await client.getMeshData('mesh_id');
```

## API Reference

### LiveLinkClient Class

#### Constructor
```javascript
new LiveLinkClient(serverUrl = 'http://127.0.0.1:8080')
```

#### Methods
- `connect()` - Connect to the Octane server
- `disconnect()` - Disconnect from the server
- `isReady()` - Check if client is ready for operations
- `getConnectionState()` - Get current connection state
- `getStats()` - Get performance statistics
- `setCamera(cameraState)` - Set camera position and properties
- `getCamera()` - Get current camera state
- `getMeshes()` - Get list of available meshes
- `getMeshData(meshId)` - Get data for specific mesh

#### Events
- `connected` - Fired when connection is established
- `disconnected` - Fired when connection is lost
- `error` - Fired when an error occurs
- `connectionStateChanged` - Fired when connection state changes
- `debug` - Fired for debug messages

### LiveLinkManager Class

#### Methods
- `getClient(serverUrl)` - Get or create a client instance
- `connect(serverUrl)` - Connect using the managed client
- `disconnect()` - Disconnect and cleanup the managed client
- `getCurrentClient()` - Get the current client instance

## Server Requirements

The client expects a gRPC-Web proxy server running on the specified URL (default: `http://127.0.0.1:8080`) that forwards requests to the Octane LiveLink gRPC service.

### Expected Endpoints
- `/livelinkapi.LiveLinkService/GetCamera` - Get camera state
- `/livelinkapi.LiveLinkService/SetCamera` - Set camera state
- `/livelinkapi.LiveLinkService/GetMeshes` - Get mesh list
- `/livelinkapi.LiveLinkService/GetMeshData` - Get mesh data

## Testing

The main application can be tested by:

1. Starting the development servers: `./start_development_servers.sh`
2. Opening `http://localhost:51313/index.html` in a web browser
3. Testing connection functionality (will show "All Systems Ready" without a running Octane server)
4. Verifying that all UI elements work without JavaScript errors
5. Testing 3D rendering and mouse controls

## Compatibility

- ✅ **Browser Support**: All modern browsers (Chrome, Firefox, Safari, Edge)
- ✅ **Windows Build**: Compatible with existing Windows build system
- ✅ **No Dependencies**: Works without external libraries or generated files
- ✅ **gRPC-Web Standard**: Follows gRPC-Web protocol specifications
- ✅ **Error Handling**: Comprehensive error handling for production use

## Development Notes

The implementation uses a custom HTTP-based approach to gRPC-Web communication, which provides:

1. **Reliability**: No dependency conflicts or version issues
2. **Simplicity**: Easy to understand and modify
3. **Flexibility**: Can be adapted to different gRPC-Web setups
4. **Debugging**: Clear error messages and debug logging
5. **Performance**: Efficient HTTP-based communication

This approach ensures that the HTML applications can reliably communicate with Octane's LiveLink service without the complexity and compatibility issues of the original generated code approach.