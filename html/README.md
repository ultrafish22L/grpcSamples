# HTML LiveLink Demos

This folder contains HTML demos for connecting to Octane Render via gRPC-Web protocol. These demos require a **gRPC proxy server** to translate HTTP requests to gRPC calls.

## 🏗️ Building and Setup

### Prerequisites

**Windows (MSVC)**:
- Visual Studio 2019/2022 with C++ support
- CMake 3.10+
- Python 3.7+ with pip

**Linux**:
- GCC/Clang with C++17 support
- CMake 3.10+
- Python 3.7+ with pip
- System packages: `protobuf-compiler`, `libgrpc++-dev`, `libprotobuf-dev`

### 1. Build the Project

**Windows**:
```cmd
# Open Visual Studio Developer Command Prompt
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019" -A x64
cmake --build . --config Release

# This builds:
# - protoc-gen-grpc-web.exe (for JavaScript generation)
# - Python protobuf files (for proxy server)
```

**Linux**:
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)

# This builds:
# - protoc-gen-grpc-web (for JavaScript generation)  
# - Python protobuf files (for proxy server)
```

### 2. Install Python Dependencies

```bash
pip install grpcio grpcio-tools aiohttp
```

### 3. Generate Protocol Buffer Files

The CMake build automatically generates:
- **JavaScript files**: `html/generated/*.js` (for browser)
- **Python files**: `shared/generated/*.py` (for proxy server)

Manual generation (if needed):
```bash
# JavaScript (requires protoc-gen-grpc-web)
cd html
../bin/protoc-gen-grpc-web --js_out=import_style=commonjs:generated --grpc-web_out=import_style=commonjs,mode=grpcwebtext:generated ../shared/protos/definitions/*.proto

# Python
python -m grpc_tools.protoc --python_out=../shared/generated --grpc_python_out=../shared/generated --proto_path=../shared/protos/definitions ../shared/protos/definitions/*.proto
```

## 🚀 Running the Demos

### Step 1: Start Octane Render
- Launch Octane Render
- Enable LiveLink server (default port: 51022)
- Verify server is listening: `netstat -an | grep 51022`

### Step 2: Start the gRPC Proxy Server
The HTML demos cannot connect directly to Octane's gRPC server. You need a proxy:

```bash
# From project root
cd proxy
python grpc_proxy.py

# Output should show:
# ✅ Proxy server started on http://127.0.0.1:51023
# Browser requests will be forwarded to Octane at 127.0.0.1:51022
```

**Alternative: Use CMake target**:
```bash
# From build directory
cmake --build . --target grpc_proxy_server
```

### Step 3: Start Web Server
```bash
cd html
python serve.py
# Or: python -m http.server 8000
```

### Step 4: Open Demos
- **Debug Tool**: `http://localhost:8000/grpc_test.html`
- **3D Viewer**: `http://localhost:8000/web3d_octane_sync.html`

**Important**: Use proxy address `http://127.0.0.1:51023` (not 51022)

## 📱 Demo Applications

### 1. 🔧 gRPC Test Tool (`grpc_test.html`)
**Purpose**: Connection debugging and API testing

**Features**:
- ✅ Comprehensive connection diagnostics
- ✅ LiveLink API testing (GetCamera, SetCamera, GetMeshes, GetMesh)
- ✅ Performance metrics and response time tracking
- ✅ Detailed error analysis with troubleshooting suggestions
- ✅ System information collection
- ✅ Debug information export

**Debugging Features**:
- Color-coded console logging
- Network request/response inspection
- Error classification and analysis
- Browser compatibility checks
- Connection retry mechanisms

### 2. 🎮 3D Octane Sync Viewer (`web3d_octane_sync.html`)
**Purpose**: Interactive 3D viewer with real-time Octane synchronization

**Features**:
- ✅ WebGL-based 3D cube rendering
- ✅ Real-time camera synchronization with Octane
- ✅ Interactive mouse controls (orbit, pan, zoom)
- ✅ LiveLink mesh discovery and loading
- ✅ Performance monitoring (FPS, frame time)
- ✅ Enhanced logging and error reporting

**Controls**:
- **Left Mouse**: Orbit camera (syncs to Octane)
- **Right Mouse**: Pan camera (syncs to Octane)  
- **Mouse Wheel**: Zoom in/out (syncs to Octane)
- **ESC**: Reset camera position
- **Space**: Toggle auto-rotation
- **S**: Force sync camera to Octane

## 🔧 Architecture

```
Browser (HTML/JS) → HTTP → gRPC Proxy → gRPC → Octane Render
                           (Port 51023)         (Port 51022)
```

**Why a proxy?**
- Browsers cannot make direct gRPC calls
- gRPC-Web requires HTTP/1.1 or HTTP/2 transport
- Octane's gRPC server only supports binary gRPC protocol
- Proxy translates between HTTP and gRPC protocols

## 📁 File Structure

```
html/
├── grpc_test.html          # Debug and testing tool
├── web3d_octane_sync.html  # 3D viewer with sync
├── livelink.js             # gRPC-Web client implementation
├── module-loader.js        # Dynamic module loading
├── serve.py                # Development web server
├── generated/              # Generated JavaScript protobuf files
│   ├── livelink_pb.js
│   └── livelink_grpc_web_pb.js
└── README.md               # This file

proxy/
├── grpc_proxy.py           # HTTP-to-gRPC proxy server
└── CMakeLists.txt          # Build configuration

shared/generated/           # Generated Python protobuf files
├── livelink_pb2.py
└── livelink_pb2_grpc.py
```

## 🐛 Troubleshooting

### Connection Issues

**"Failed to fetch" errors**:
1. ✅ Verify proxy server is running on port 51023
2. ✅ Check Octane is running and LiveLink enabled
3. ✅ Ensure firewall allows connections
4. ✅ Try different browser (Chrome/Firefox/Edge)

**Proxy connection errors**:
1. ✅ Verify Octane LiveLink server port (default: 51022)
2. ✅ Check `netstat -an | grep 51022` shows LISTENING
3. ✅ Restart Octane and re-enable LiveLink
4. ✅ Check proxy logs for detailed error messages

**Build issues**:
1. ✅ Ensure all dependencies installed
2. ✅ Check CMake finds protobuf and grpc
3. ✅ Verify Python has grpcio-tools installed
4. ✅ Run `cmake --build . --target python_protobuf_generation`

### Debug Tools

**Use the gRPC Test Tool**:
- Detailed connection diagnostics
- System information collection
- Error analysis with suggestions
- Network request inspection

**Check Console Logs**:
- Open browser Developer Tools (F12)
- Look for color-coded log messages
- Check Network tab for HTTP requests
- Examine error stack traces

**Proxy Server Logs**:
```bash
# Check proxy logs
tail -f proxy.log

# Look for:
# ✅ "Proxy server started on http://127.0.0.1:51023"
# ❌ Connection errors to Octane
# 📡 HTTP request handling
```

## 🔗 Related Documentation

- **`README_LIVELINK.md`**: Detailed technical implementation
- **`../README.md`**: Main project documentation
- **`../GRPC_WEB_BUILD.md`**: gRPC-Web build instructions