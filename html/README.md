# HTML LiveLink Demos

This folder contains HTML demos for connecting to Octane Render via gRPC-Web protocol. These demos require a **gRPC proxy server** to translate HTTP requests to gRPC calls.

## 🚀 Windows Quick Start (Batch Files)

For Windows users, we provide convenient batch files that handle all setup automatically:

### Automated Setup (Recommended)

**Option A: One-Click Setup (Easiest)**
```cmd
cd html
start_both_servers.bat    # Starts both servers automatically in separate windows
```

**Option B: Proxy Only (file:// protocol)**
```cmd
cd html
start_proxy_only.bat      # Only starts proxy server, double-click HTML files
```

**Option C: Manual Two-Terminal Setup**
```cmd
# Terminal 1: Start the gRPC proxy server
cd html
start_proxy_server.bat

# Terminal 2: Start the HTTP server for HTML files  
cd html
start_http_server.bat
```

**⚠️ Server Requirements**:
- **Option A & C**: Both servers must be running simultaneously
  - **Proxy Server**: Translates browser HTTP → Octane gRPC (port 51023)
  - **HTTP Server**: Serves HTML files to your browser (port 8000)
- **Option B**: Only proxy server needed (HTML files opened via file://)

**What the batch files do**:
- ✅ Install Python dependencies (`grpcio`, `grpcio-tools`, `aiohttp`)
- ✅ Generate protobuf files using CMake or fallback methods
- ✅ Start gRPC proxy server on `http://127.0.0.1:51023`
- ✅ Start HTTP server on `http://localhost:8000`
- ✅ Provide clear error messages and troubleshooting

**Then open in browser**:
- 🧪 **Debug Tool**: http://localhost:8000/grpc_test.html
- 🎮 **3D Demo**: http://localhost:8000/web3d_octane_sync.html

### Visual Studio IDE Workflow

For developers using Visual Studio IDE, the proxy components are organized in the **"Proxy"** solution folder:

1. **Build `proxy_setup_and_run`**: 
   - Right-click → Build
   - Installs Python dependencies and generates protobuf files
   - Shows setup completion message with next steps

2. **Build `run_proxy_server`**:
   - Right-click → Build  
   - Starts the gRPC proxy server on port 51023
   - Connects to Octane on port 51022

3. **Alternative**: Use `grpc_proxy_server` target for the original proxy behavior

## 🏗️ Manual Building and Setup

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
# Linux/Command Line
cmake --build . --target grpc_proxy_server

# Windows Visual Studio: Multiple options available
cmake --build . --target proxy_setup_and_run      # Installs deps + generates files
cmake --build . --target run_proxy_server          # Runs proxy server
cmake --build . --target grpc_proxy_server         # Original proxy target
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

**Visual Studio specific issues**:
1. ✅ If "grpc_proxy_server" is skipped: Build `python_protobuf_builder` first
2. ✅ Check that Python is found by CMake (`find_package(Python3)`)
3. ✅ Ensure protoc.exe exists in `third_party/protobuf/windows/bin/`
4. ✅ Use "Build Solution" to generate all protobuf files automatically

**Batch file issues (Windows)**:
1. ✅ **"This script must be run from the html/ directory"**: Navigate to `html/` folder first
2. ✅ **Python not found**: Install Python and add to PATH, or use full path in batch file
3. ✅ **CMake protobuf generation failed**: Batch file will try manual generation as fallback
4. ✅ **Port already in use**: Stop existing servers with Ctrl+C before restarting
5. ✅ **Permission denied**: Run Command Prompt as Administrator if needed

**Connection errors in browser**:
1. ✅ **`net::ERR_CONNECTION_REFUSED` on port 51023**: Proxy server not running
   - Run `start_proxy_server.bat` or `start_both_servers.bat`
   - Check that proxy server window shows "Server running on port 51023"
2. ✅ **`net::ERR_CONNECTION_REFUSED` on port 8000**: HTTP server not running
   - Run `start_http_server.bat` or `start_both_servers.bat`
   - Access demos via `http://localhost:8000/` not `file://`
3. ✅ **Proxy connects but gRPC calls fail**: Octane LiveLink not enabled
   - Enable LiveLink in Octane Render settings
   - Verify Octane is listening on port 51022

**Can I skip the HTTP server and use file:// protocol?**

✅ **YES!** You can run `grpc_test.html` directly by double-clicking it (uses `file://` protocol):

```cmd
# Only need the proxy server running
cd html
start_proxy_server.bat

# Then double-click grpc_test.html or web3d_octane_sync.html
```

**Why this works:**
- The gRPC proxy server has CORS configured to allow `file://` origins
- Modern browsers allow `file://` → `http://localhost` requests
- You only need the proxy server (port 51023), not the HTTP server (port 8000)

**Browser compatibility:**
- ✅ Chrome/Edge: Works perfectly
- ✅ Firefox: Works with default settings  
- ⚠️ Safari: May require "Develop" menu → "Disable Cross-Origin Restrictions"

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