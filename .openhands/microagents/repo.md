# grpcSamples Repository

## Purpose
This repository provides **gRPC-Web client samples** for connecting to **Octane LiveLink** services. It demonstrates how to build web-based clients that can communicate with Octane's gRPC server through HTTP/CORS-compatible proxy layers.

The main goal is to enable **browser-based applications** to interact with Octane's LiveLink API for camera control, mesh operations, and real-time 3D rendering workflows.

## General Setup
The repository implements a **client-proxy-server architecture**:

1. **HTML/JavaScript Client** - Browser-based gRPC-Web client with interactive UI
2. **HTTP-to-gRPC Proxy** - Python aiohttp server that translates HTTP requests to gRPC calls
3. **Octane gRPC Server** - Target server running LiveLink services (external dependency)

### Key Technologies:
- **Frontend**: Vanilla JavaScript with custom gRPC-Web implementation
- **Proxy**: Python with aiohttp, grpcio, and CORS middleware  
- **Protocol**: gRPC-Web over HTTP with protobuf serialization
- **CORS**: Full cross-origin support for file:// and http:// protocols

## Repository Structure

```
grpcSamples/
├── .openhands/microagents/     # Repository documentation
├── html/                       # Web client implementation
│   ├── grpc_test.html         # Main test interface with connection status
│   ├── livelink.js            # LiveLink client library with gRPC-Web support
│   ├── *.bat                  # Windows batch scripts for easy testing
│   └── README.md              # HTML client documentation
├── proxy/                      # HTTP-to-gRPC proxy server
│   ├── grpc_proxy.py          # Main proxy server with CORS and dual routing
│   ├── livelink_pb2.py        # Generated protobuf message classes
│   ├── livelink_pb2_grpc.py   # Generated gRPC service stubs
│   └── *.bat                  # Windows batch scripts for proxy management
├── proto/                      # Protocol buffer definitions
│   └── livelink.proto         # LiveLink service definitions
└── README.md                  # Main repository documentation
```

### Core Components:
- **grpc_test.html**: Interactive web interface for testing LiveLink connections
- **livelink.js**: Custom gRPC-Web client with event-driven architecture
- **grpc_proxy.py**: Bidirectional HTTP↔gRPC proxy with enhanced CORS support
- **livelink.proto**: Service definitions for camera, mesh, and rendering operations

### Key Features:
- ✅ **CORS-compliant** - Works from file:// and http:// origins
- ✅ **Dual URL routing** - Supports both `/LiveLinkService/` and `/livelinkapi.LiveLinkService/` patterns
- ✅ **Real-time status** - Live connection monitoring with proper error handling
- ✅ **Cross-platform** - Windows batch files and Python scripts for easy setup
- ✅ **Event-driven** - Asynchronous client with connection state management