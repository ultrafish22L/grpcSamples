# grpcSamples Repository

## Purpose
This repository demonstrates **gRPC-Web client integration** with **Octane Render's LiveLink API**. It provides a complete web-based interface for real-time camera synchronization and mesh data exchange between web browsers and Octane Render through gRPC protocol communication.

The main goal is to enable **browser-based applications** to seamlessly integrate with Octane's professional 3D rendering pipeline for camera control, mesh discovery, geometry access, and real-time rendering workflows.

## General Setup
The repository implements a **proxy-based architecture** to bridge the gap between web browsers (which cannot directly communicate with gRPC servers) and Octane Render's native gRPC LiveLink service:

**Web Client** (JavaScript/HTML) ↔ **HTTP Proxy Server** (Python/aiohttp) ↔ **Octane LiveLink gRPC Service**

### Architecture Components:
1. **HTML/JavaScript Client** - Browser-based interface with WebGL 3D rendering and LiveLink integration
2. **HTTP-to-gRPC Proxy** - Python aiohttp server that converts HTTP/JSON requests to native gRPC calls
3. **Octane gRPC Server** - Octane Render's LiveLink service (external dependency)

### Key Technologies:
- **Frontend**: Vanilla JavaScript with WebGL, custom gRPC-Web implementation, real-time 3D rendering
- **Proxy**: Python with aiohttp, grpcio, comprehensive CORS middleware, and protobuf handling
- **Protocol**: HTTP/JSON for browser-to-proxy, native gRPC for proxy-to-Octane communication
- **CORS**: Enhanced cross-origin support including X-Call-Id and gRPC-Web headers
- **Demo Mode**: Fallback simulation when Octane is not available for development/testing

## Repository Structure

```
grpcSamples/
├── .openhands/microagents/     # Repository documentation
├── html/                       # Web client applications
│   ├── grpc_test.html         # Interactive testing interface for LiveLink operations
│   ├── web3d_octane_sync.html # Real-time 3D WebGL viewer with camera synchronization
│   ├── livelink.js            # JavaScript client library for LiveLink protocol
│   └── *.bat                  # Windows batch scripts for easy testing
├── proxy/                      # HTTP-to-gRPC proxy server
│   ├── grpc_proxy.py          # Python aiohttp server with CORS and dual routing
│   ├── livelink_pb2.py        # Generated protobuf message classes
│   ├── livelink_pb2_grpc.py   # Generated gRPC service stubs
│   └── *.bat                  # Windows batch scripts for proxy management
├── shared/                     # Protocol definitions and generated code
│   ├── protos/definitions/    # LiveLink service protobuf definitions
│   └── generated/             # Generated protobuf Python bindings
├── sdk/                        # Octane SDK integration and API definitions
├── third_party/               # External dependencies (gRPC-Web, protobuf libraries)
├── batch/                     # Windows batch scripts for building and running
└── README.md                  # Main repository documentation
```

### Core Components:
- **grpc_test.html**: Interactive testing interface with comprehensive LiveLink operation testing
- **web3d_octane_sync.html**: Real-time 3D WebGL viewer with camera synchronization and demo mode
- **livelink.js**: JavaScript client library with event-driven architecture and error handling
- **grpc_proxy.py**: HTTP-to-gRPC proxy server with enhanced CORS support and protobuf handling
- **livelink.proto**: Complete service definitions for camera, mesh, and geometry operations

### Key Features:
- ✅ **Camera Control** - Real-time camera position, target, up vector, and FOV synchronization
- ✅ **Mesh Discovery** - Query available meshes in Octane scenes via GetMeshes
- ✅ **Geometry Access** - Retrieve full mesh data including vertices, normals, and polygons
- ✅ **CORS-compliant** - Enhanced cross-origin support with X-Call-Id and gRPC-Web headers
- ✅ **Dual URL routing** - Supports both `/LiveLinkService/` and `/livelinkapi.LiveLinkService/` patterns
- ✅ **Error Handling** - Comprehensive error reporting with detailed debug information
- ✅ **Demo Mode** - Fallback simulation when Octane is not available
- ✅ **Performance Monitoring** - Real-time FPS, call statistics, and connection health tracking
- ✅ **WebGL Integration** - 3D rendering with real-time camera synchronization
- ✅ **Event-driven Architecture** - Asynchronous client with proper connection state management