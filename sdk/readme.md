# Octane SDK Headers and gRPC API

## 🚨 **CRITICAL REQUIREMENT: REAL OCTANE ONLY**

**⚠️ NEVER EVER use mock or simulated data - only real live connection with Octane LiveLink service.**

## Overview

This directory contains Octane SDK headers and gRPC API examples for direct integration with Octane Render. The gRPC API allows remote connections to octane.exe and must be enabled via Help → LiveLink in Octane.

## SDK Headers

Core Octane SDK headers for direct API integration:
- `apirender.h` - Render engine and callback system
- `apinodesystem.h` - Node graph manipulation
- `octanevectypes.h` - Vector and matrix types
- `octanematrix.h` - Matrix operations
- `octaneids.h` - Node and object identifiers
- `octaneenums.h` - Enumeration definitions

## Applications Using SDK

### simpleGlSdk
Production-ready OpenGL application with direct SDK integration:
- Real-time camera synchronization with Octane
- Callback-based rendering system
- Shared surface rendering (Windows D3D11/OpenGL interop)
- Cross-platform support (Windows, Linux, macOS)

### gRPC API Examples
The `grpc-api-examples/` directory contains demonstration applications:
- **render-example**: Complete rendering pipeline demonstration
  - Create new projects
  - Build node graphs
  - Render images
  - Receive events and stream images

## Setup Requirements

### SDK Libraries (Required for simpleGlSdk)
Platform-specific SDK libraries must be placed in `third_party/octane/`:
```
third_party/octane/
├── windows/octane_standalone.lib
├── linux/liboctane_standalone.a
└── macos/liboctane_standalone.a
```

### gRPC Dependencies (For API examples)
Third-party dependencies for gRPC examples:
```
thirdparty/
├── absl/
├── cares/
├── curl/
├── grpc/
├── openssl/
├── protobuf/
├── re2/
└── zlib/
```

## Usage

### Enable Octane LiveLink
1. Launch Octane Render
2. Go to **Help → LiveLink** (enable gRPC server)
3. Default port: 51022

### Build Applications
```bash
# Build simpleGlSdk (requires SDK libraries)
cd simpleGlSdk && mkdir build && cd build
cmake .. && make

# Build gRPC examples (requires thirdparty dependencies)
cd grpc-api-examples && mkdir build && cd build
cmake .. && make
```

### Run Examples
```bash
# SDK integration example
./simpleGlSdk

# gRPC API example
./render-example 127.0.0.1:51022 /path/to/output/images
```

## Production Applications

For web-based production applications, see:
- **octaneWeb**: Modern web application with real-time rendering
- **octaneProxy**: HTTP-to-gRPC proxy server for web clients