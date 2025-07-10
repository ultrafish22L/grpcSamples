# Complete Development Setup Guide

## Overview

This repository now provides a complete development environment for Octane gRPC integration with both **real Octane Render** and a **mock server** for development without Octane.

## Architecture

```
HTML Applications ←→ Proxy Server ←→ Octane/Mock Server
(Browser)           (Port 51023)     (Port 51022)
```

## Quick Start Options

### Option 1: Development with Mock Server (No Octane Required)
```bash
# Start both mock server and proxy server
start_development_servers.bat    # Windows
./start_development_servers.sh   # Linux/Mac
```

### Option 2: Individual Server Control
```bash
# Start mock Octane server
cd mock_octane
start_mock_octane.bat    # Windows
./start_mock_octane.sh   # Linux/Mac

# Start proxy server (in another terminal)
cd html
start_proxy.bat         # Windows
./start_proxy.sh        # Linux/Mac
```

### Option 3: Real Octane Render
```bash
# 1. Start Octane Render with LiveLink enabled
# 2. Start only the proxy server
cd html
start_proxy.bat         # Windows
./start_proxy.sh        # Linux/Mac
```

## HTML Applications

### grpc_test.html
- **Purpose**: gRPC connectivity testing and debugging
- **Features**: All gRPC operations, connection testing, system info
- **Usage**: Open in browser after starting servers

### web3d_octane_sync.html
- **Purpose**: WebGL 3D viewer with live Octane synchronization
- **Features**: 3D rendering, camera sync, mesh loading
- **Usage**: Open in browser after starting servers

## File Structure

```
grpcSamples/
├── html/                          # 🌐 Web Applications
│   ├── grpc_test.html             # gRPC testing interface
│   ├── web3d_octane_sync.html     # WebGL viewer with sync
│   ├── styles.css                 # Shared modern styling
│   ├── shared.js                  # Consolidated utilities
│   ├── livelink.js                # Core gRPC-Web client
│   ├── webgl-utils.js             # WebGL utilities
│   ├── start_proxy.bat/.sh        # Proxy server launchers
│   └── SETUP.md                   # HTML setup guide
├── mock_octane/                   # 🎭 Mock Server
│   ├── mock_octane_server.py      # Complete mock implementation
│   ├── start_mock_octane.bat/.sh  # Mock server launchers
│   └── README.md                  # Mock server documentation
├── proxy/                         # 🔄 HTTP-to-gRPC Proxy
│   ├── grpc_proxy.py              # Proxy server implementation
│   ├── livelink_pb2.py            # Generated protobuf files
│   └── livelink_pb2_grpc.py       # Generated gRPC stubs
├── start_development_servers.*    # 🚀 Complete dev environment
└── DEVELOPMENT_SETUP.md           # This file
```

## Development Workflow

### 1. HTML Development (Recommended)
```bash
# Start complete development environment
./start_development_servers.sh

# Open applications
open html/grpc_test.html
open html/web3d_octane_sync.html
```

### 2. Testing with Real Octane
```bash
# 1. Start Octane Render with LiveLink
# 2. Start proxy server only
cd html && ./start_proxy.sh

# 3. Test applications
open html/grpc_test.html
```

### 3. Mock Server Features
- **3 Mock Meshes**: Cube, Sphere, Teapot with realistic geometry
- **Dynamic Camera**: Position variations to simulate movement
- **Full API**: GetCamera, SetCamera, GetMeshes, GetMesh
- **Statistics**: Call tracking and performance monitoring
- **Logging**: Detailed request/response logging

## Key Features

### 🎨 Unified Design System
- **Consistent styling** across both HTML applications
- **Modern UI** with gradients, animations, and responsive design
- **Shared utilities** for common functionality
- **Enhanced logging** with emoji indicators and timestamps

### 🔧 Development Tools
- **Mock server** for development without Octane
- **Proxy server** for HTTP-to-gRPC translation
- **Launch scripts** for easy server management
- **Comprehensive logging** and error handling

### 📊 Monitoring & Debugging
- **Activity logs** with detailed operation tracking
- **Performance statistics** with FPS and call metrics
- **Connection state management** with health monitoring
- **Debug utilities** for system information

## Requirements

### Software
- **Python 3.7+** with packages: `grpcio`, `grpcio-tools`, `aiohttp`, `aiohttp-cors`
- **Modern web browser** with WebGL support
- **Octane Render** (optional - use mock server for development)

### Network Ports
- **51022**: Octane LiveLink service (real or mock)
- **51023**: HTTP-to-gRPC proxy server

## Troubleshooting

### Common Issues

**"Connection refused"**
- Ensure servers are started in correct order
- Check that ports 51022 and 51023 are available
- Verify no firewall blocking connections

**"Protobuf version mismatch"**
- Update protobuf: `pip install --upgrade protobuf grpcio grpcio-tools`
- Regenerate protobuf files if needed

**"Mock server not responding"**
- Check Python version (3.7+ required)
- Verify protobuf files exist in proxy/ directory
- Look at server logs for specific errors

### Testing Connection
```bash
# Test mock server
telnet 127.0.0.1 51022

# Test proxy server
curl http://127.0.0.1:51023/health
```

## Next Steps

1. **Start development environment**: `./start_development_servers.sh`
2. **Open grpc_test.html** to verify connectivity
3. **Test camera operations** and mesh loading
4. **Open web3d_octane_sync.html** for 3D visualization
5. **Switch to real Octane** when ready for production testing

This setup provides a complete development environment for Octane gRPC integration with both mock and real server support.