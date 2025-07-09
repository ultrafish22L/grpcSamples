# HTML LiveLink Demos

This folder contains two essential HTML demos for connecting to Octane Render via gRPC-Web.

## Demos

### 1. 🔧 Debug Test (`grpc_test.html`)
**Purpose**: Connection debugging and troubleshooting tool

**Features**:
- Server address configuration (default: `http://127.0.0.1:51022`)
- Connection status monitoring
- LiveLink operation testing (GetCamera, SetCamera, GetMeshes, GetMesh)
- Performance statistics and response time tracking
- Detailed activity logging
- Debug information display

**Use this when**:
- Testing connection to Octane server
- Debugging gRPC-Web communication issues
- Verifying server configuration
- Troubleshooting network problems

### 2. 🚀 3D Octane Sync Viewer (`web3d_octane_sync.html`)
**Purpose**: Full 3D model viewer with real-time Octane camera synchronization

**Features**:
- Interactive 3D WebGL cube rendering
- Real-time camera synchronization with Octane Render
- Mouse controls (orbit, pan, zoom) that sync to Octane
- LiveLink mesh discovery and management
- Performance monitoring (FPS, frame time, sync rate)
- Activity logging and status display

**Controls**:
- **Left Mouse Drag**: Orbit camera (syncs to Octane)
- **Right Mouse Drag**: Pan camera (syncs to Octane)
- **Mouse Wheel**: Zoom in/out (syncs to Octane)
- **ESC**: Reset camera position
- **Space**: Toggle auto-rotation
- **S**: Force sync camera to Octane

## Quick Start

1. **Start web server**:
   ```bash
   python3 serve.py
   # Or: python3 -m http.server 8000
   ```

2. **Open demos**:
   - Debug: `http://localhost:8000/grpc_test.html`
   - 3D Viewer: `http://localhost:8000/web3d_octane_sync.html`

3. **Configure server address** in the input field (default: `http://127.0.0.1:51022`)

4. **Click Connect** to establish connection to Octane

## Support Files

- **`livelink.js`**: Custom HTTP-based gRPC-Web client implementation
- **`module-loader.js`**: Dynamic module loading utility
- **`generated/`**: Protocol buffer generated JavaScript files
- **`README_LIVELINK.md`**: Detailed technical documentation

## Troubleshooting

If connection fails:
1. Verify Octane server is running and listening on the configured port
2. Check if you need a gRPC-Web proxy (see main repository documentation)
3. Try different server addresses (8080, 9090, 50051)
4. Use the debug test to diagnose specific connection issues