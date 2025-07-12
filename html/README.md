# OTOY WebGL-Octane LiveLink Sync

## 🚀 QUICKSTART - Get Running in 2 Minutes

### Windows
```cmd
cd path\to\grpcSamples\html
python -m http.server 8000
```
Open browser: `http://localhost:8000`

### Linux/macOS
```bash
cd /path/to/grpcSamples/html
python3 -m http.server 8000
```
Open browser: `http://localhost:8000`

### What You'll See
- **Professional 3D Viewer**: Interactive WebGL cube with mouse controls
- **Octane Render Branding**: Official Octane logo and OTOY styling
- **Real-time Activity Log**: Live operation tracking with emoji indicators
- **Connection Controls**: Toggle to connect to Octane LiveLink service
- **Performance Stats**: FPS, frame time, and connection metrics

### Basic Usage
1. **Interact with 3D**: Drag to rotate, scroll to zoom, right-drag to pan
2. **Toggle Auto-Rotate**: Use the 🧊 switch to enable/disable rotation
3. **Connect to Octane**: Toggle the 🔌 switch (requires proxy server)
4. **Test Functions**: Use toolbar buttons (📷 📸 🔄 🎬 📂 🫖)

---

## 📋 Complete Documentation

### Overview
Professional WebGL 3D viewer with Octane LiveLink integration featuring real-time camera synchronization, interactive 3D rendering, and authentic OTOY branding.

### Main Application
- **index.html**: Complete WebGL 3D viewer with Octane LiveLink integration
  - Interactive 3D rendering with mouse controls (orbit, pan, zoom)
  - Real-time camera synchronization with Octane Render
  - Professional OTOY-branded UI with activity logging
  - Custom gRPC-Web client with zero external dependencies

### Key Features
- **Interactive 3D Rendering**: WebGL 2.0 cube with mouse controls
- **Real-time Octane Sync**: Live camera synchronization with Octane Render
- **Professional UI**: OTOY-branded light theme with responsive layout
- **Activity Logging**: Real-time operation logging with timestamps and status indicators
- **Custom gRPC-Web**: Zero external dependencies, reliable cross-browser support
- **Performance Monitoring**: Real-time FPS, call statistics, and connection health
- **Authentic Branding**: Official Octane Render logo and OTOY.com styling

### Supporting Files
- **livelink.js**: Custom gRPC-Web client implementation
- **shared.js**: Common utilities and helper functions
- **webgl-utils.js**: WebGL rendering and 3D utilities
- **otoy-theme.css**: Professional OTOY branding and styling

### Advanced Setup (Optional)
For full Octane connectivity, also run the proxy server:

#### Windows
```cmd
cd path\to\grpcSamples\proxy
pip install grpcio aiohttp aiohttp-cors
python grpc_proxy.py
```

#### Linux/macOS
```bash
cd /path/to/grpcSamples/proxy
pip3 install grpcio aiohttp aiohttp-cors
python3 grpc_proxy.py
```

### Testing & Verification
The application demonstrates:
- ✅ Rotating 3D cube with proper WebGL 2.0 shaders
- ✅ Mouse interaction for camera control (drag, zoom, pan)
- ✅ Auto-rotate toggle functionality
- ✅ Reset camera button
- ✅ All UI controls working
- ✅ Smooth 60fps performance
- ✅ Real-time connection status with LED indicators
- ✅ Professional OTOY.com styling and branding
- ✅ Official Octane Render logo with working link

### Browser Requirements
- **Modern Browser**: Chrome, Firefox, Safari, Edge (2020+)
- **WebGL Support**: WebGL 2.0 preferred, WebGL 1.0 fallback
- **JavaScript**: ES6+ support required

### Troubleshooting
- **Port conflicts**: Change `8000` to another port (e.g., `8001`, `3000`)
- **Python not found**: Install from [python.org](https://python.org)
- **WebGL issues**: Update graphics drivers, try different browser
- **Connection errors**: Check proxy server is running on port 8080