# HTML Demos for Octane LiveLink

This directory contains HTML demos and tools for gRPC-Web connectivity to Octane's LiveLink service.

## Quick Start

1. **Start a web server** from the parent directory (`grpcSamples/`):
   ```bash
   # From grpcSamples/ directory
   python -m http.server 8000
   ```

2. **Open demos** in your browser:
   - `http://localhost:8000/html/livelink_demo.html` - Main LiveLink demo with connection status
   - `http://localhost:8000/html/grpc_test.html` - Technical testing interface for debugging
   - `http://localhost:8000/html/web3d_octane_sync.html` - 3D visualization demo

## Files

### HTML Demos
- **`livelink_demo.html`** - Main demonstration page with connection status and server info
- **`grpc_test.html`** - Technical testing interface for gRPC-Web connection debugging
- **`web3d_octane_sync.html`** - Advanced demo with 3D visualization and camera synchronization
- **Other HTML files** - Various test and development demos

### JavaScript Libraries
- **`livelink.js`** - Main JavaScript library providing LiveLink client functionality
- **Other JS files** - Supporting libraries and test implementations

### Tools
- **`protoc-gen-grpc-web`** - gRPC-Web plugin for generating JavaScript from proto files (built by CMake)
- **`generate_js.bat`** / **`generate_js.sh`** - Scripts for easy JavaScript file generation (Windows/Linux)
- **`generated/`** - Directory for generated JavaScript files from proto definitions

## Usage

### Running the Demos

The demos connect to Octane's gRPC server via gRPC-Web proxy at `http://127.0.0.1:8080`. If no server is available, they display appropriate error messages.

### Generating JavaScript Files

If you need to regenerate JavaScript files from proto definitions:

1. **Build the project** (from `grpcSamples/`):
   ```bash
   mkdir build && cd build
   cmake .. && cmake --build . --config Release
   ```

2. **Generate JavaScript files** (from `html/`):
   ```bash
   cd html
   # Windows:
   generate_js.bat
   # Linux:
   ./generate_js.sh
   ```

## Features

### LiveLink Client (`livelink.js`)
- **Custom gRPC-Web implementation**: Standalone HTTP-based client bypassing compatibility issues
- **No external dependencies**: Works without CDN libraries or generated protobuf files
- **Event-driven architecture**: Connection state notifications and real-time updates
- **Built-in statistics tracking**: Performance monitoring and call statistics
- **Camera synchronization support**: Real-time camera position and orientation sync
- **Mesh data retrieval**: Complete mesh management and data access
- **Cross-browser compatibility**: Works in all modern browsers without library conflicts
- **Windows build compatible**: Maintains compatibility with existing build system

### Test Interface (`grpc_test.html`)
- Connection testing and status monitoring
- Basic LiveLink functionality verification
- Performance statistics display
- Debug logging and error reporting

### 3D Visualization (`web3d_octane_sync.html`)
- Interactive 3D scene with Three.js
- Real-time camera synchronization with Octane
- Mesh data visualization
- Live connection status and controls

## Project Structure

This `html/` directory is completely separate from the C++ applications:

- **C++ executables**: Built to `../bin/` directory
- **HTML tools**: Built to this `html/` directory
- **Generated files**: Placed in `generated/` subdirectory
- **No interference**: HTML tools don't affect C++ builds or SDK integration

## Browser Compatibility

The demos require a modern browser with support for:
- ES6+ JavaScript features
- WebGL (for 3D visualization)
- gRPC-Web (for LiveLink connectivity)
- Fetch API and Promises

## Recent Updates

### ✅ Fixed gRPC-Web Client Issues (July 2025)
- **Resolved compatibility errors**: Fixed "this.client_.rpcCall is not a function" and protobuf class conflicts
- **Custom implementation**: Replaced CDN gRPC-Web libraries with standalone HTTP-based client
- **No external dependencies**: Eliminated all CDN libraries and generated file dependencies
- **All demos working**: livelink_demo.html, simple_test.html, and other HTML files now work without errors
- **Maintained functionality**: All original features preserved with improved reliability

## Troubleshooting

1. **Connection Issues**: Check that Octane gRPC server and gRPC-Web proxy are running on port 8080
2. **CORS Errors**: Ensure your web server allows cross-origin requests
3. **JavaScript Errors**: Check browser console for detailed error messages
4. **Error Handling**: If server is unavailable, demos display appropriate error states
5. **File Paths**: Make sure to serve from the parent `grpcSamples/` directory
6. **Library Conflicts**: If you encounter gRPC-Web errors, the custom implementation in `livelink.js` should resolve them
7. **Browser Cache**: Use hard refresh (Ctrl+F5) if you see old error messages