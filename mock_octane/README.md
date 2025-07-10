# Mock Octane gRPC Server

A comprehensive mock implementation of Octane Render's LiveLink gRPC service for development and testing purposes.

## Purpose

This mock server allows developers to:
- **Test HTML applications** without requiring Octane Render
- **Develop and debug** gRPC connectivity and camera synchronization
- **Validate functionality** of the proxy server and client applications
- **Simulate realistic scenarios** with mock mesh data and camera operations

## Features

### 🎭 Complete LiveLink Simulation
- **GetCamera/SetCamera**: Full camera state management with position, target, up vector, and FOV
- **GetMeshes**: Returns list of available mock meshes
- **GetMesh**: Provides detailed mesh geometry data
- **Realistic responses**: Includes proper gRPC status codes and error handling

### 📊 Mock Data
- **Mock Cube**: Simple cube geometry with proper normals and face data
- **Mock Sphere**: Procedurally generated sphere with configurable resolution
- **Mock Teapot**: Simplified teapot-like geometry for testing
- **Dynamic camera**: Slight position variations to simulate real camera movement

### 📈 Statistics & Monitoring
- **Call tracking**: Counts all gRPC method invocations
- **Performance metrics**: Uptime and request statistics
- **Detailed logging**: Request/response logging with emoji indicators
- **Periodic stats**: Automatic statistics reporting every 30 seconds

## Quick Start

### 1. Start Mock Octane Server

**Windows:**
```bash
cd mock_octane
start_mock_octane.bat
```

**Linux/Mac:**
```bash
cd mock_octane
./start_mock_octane.sh
```

### 2. Start Proxy Server
```bash
cd html
start_proxy.bat    # Windows
./start_proxy.sh   # Linux/Mac
```

### 3. Test HTML Applications
Open `grpc_test.html` or `web3d_octane_sync.html` in your browser and connect to test the mock server.

## Architecture

```
HTML Apps ←→ Proxy Server ←→ Mock Octane Server
(Browser)     (Port 51023)    (Port 51022)
```

The mock server runs on the same port (51022) as the real Octane LiveLink service, making it a drop-in replacement for development.

## Mock Data Details

### Camera State
- **Initial Position**: (5.0, 3.0, 8.0)
- **Target**: (0.0, 0.0, 0.0)
- **Up Vector**: (0.0, 1.0, 0.0)
- **FOV**: 45 degrees
- **Dynamic Variation**: Slight position changes to simulate movement

### Available Meshes

| ID   | Name        | Description                    | Vertices | Polygons |
|------|-------------|--------------------------------|----------|----------|
| 1001 | Mock Cube   | Simple cube with 6 faces      | 24       | 6 quads  |
| 1002 | Mock Sphere | Procedural sphere geometry     | 80       | 80 tris  |
| 1003 | Mock Teapot | Simplified teapot-like shape  | 100      | 100 tris |

### Mesh Data Format
- **Positions**: Float array of vertex coordinates (x, y, z)
- **Normals**: Float array of normal vectors
- **VertsPerPoly**: Integer array specifying vertices per polygon
- **WindingOrder**: Polygon winding order (0 = counter-clockwise)

## API Compatibility

The mock server implements the same gRPC interface as Octane Render:

### Methods
- `GetCamera() → CameraState`
- `SetCamera(CameraState) → Empty`
- `GetMeshes() → MeshList`
- `GetMesh(MeshRequest) → MeshData`

### Message Types
- `CameraState`: position, target, up, fov
- `Vec3`: x, y, z coordinates
- `Mesh`: id, name, objectHandle
- `MeshData`: name, positions, normals, vertsPerPoly, windingOrder

## Development Features

### Logging
```
📤 GetCamera request #1
📥 Returning camera: pos=(5.10, 3.00, 8.00)
📤 SetCamera request #1
📥 New camera: pos=(2.50, 4.20, 6.80)
```

### Statistics
```
📊 Mock Octane Server Statistics:
   Uptime: 120.5s
   GetCamera calls: 15
   SetCamera calls: 3
   GetMeshes calls: 2
   GetMesh calls: 1
   Total calls: 21
```

### Error Simulation
- **Mesh not found**: Returns proper gRPC NOT_FOUND status
- **Invalid requests**: Appropriate error responses
- **Connection handling**: Graceful startup and shutdown

## Configuration

### Server Settings
- **Address**: 127.0.0.1:51022 (matches real Octane)
- **Max Workers**: 10 concurrent connections
- **Stats Interval**: 30 seconds

### Customization
The mock server can be easily extended:
- Add new mesh types in `_create_mock_meshes()`
- Modify camera behavior in `GetCamera()`/`SetCamera()`
- Add new gRPC methods as needed
- Customize logging and statistics

## Requirements

### Software
- **Python 3.7+**
- **Required packages**: `grpcio`, `grpcio-tools`, `asyncio`
- **Protobuf files**: Generated from the main build process

### Dependencies
The mock server requires the same protobuf files as the proxy server:
- `livelink_pb2.py`
- `livelink_pb2_grpc.py`

These are generated during the main project build process.

## Troubleshooting

### Common Issues

**"Failed to import gRPC modules"**
- Run the main project build to generate protobuf files
- Check that `../shared/generated/livelink_pb2.py` exists

**"Address already in use"**
- Stop any running Octane Render instances
- Check if another mock server is already running
- Use `netstat -an | grep 51022` to check port usage

**Connection refused from proxy**
- Ensure mock server started successfully
- Check that it's listening on 127.0.0.1:51022
- Verify no firewall blocking the connection

### Testing Connection
```bash
# Test if mock server is responding
telnet 127.0.0.1 51022
```

## Integration with HTML Applications

The mock server works seamlessly with the HTML applications:

1. **grpc_test.html**: All test operations work with mock data
2. **web3d_octane_sync.html**: Camera sync and mesh loading functional
3. **Proxy server**: No changes needed - transparent operation

## Development Workflow

1. **Start mock server** (replaces Octane Render)
2. **Start proxy server** (translates HTTP to gRPC)
3. **Develop/test HTML apps** with full functionality
4. **Switch to real Octane** by stopping mock and starting Octane

This allows complete development and testing without requiring Octane Render installation.