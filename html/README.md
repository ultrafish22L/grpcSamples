# OTOY WebGL-Octane LiveLink Sync

## 🚀 QUICKSTART - Get Running in 2 Minutes

### Step 1: Start Octane Render
1. **Launch Octane Render** on your system
2. **Enable gRPC Server**: Go to Preferences → LiveLink → Enable gRPC Server
3. **Note the Port**: Default is usually 51023 (check Preferences → LiveLink → Port)

### Step 2: Start the Proxy Server

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

### Step 3: Open the Web Application
Simply **double-click `index.html`** or drag it into your browser.

### Step 4: Configure Connection
1. **Check Server Address**: Should match your Octane gRPC port (default: `http://127.0.0.1:51023`)
2. **Toggle Connection**: Click the 🔌 switch to connect to Octane LiveLink
3. **Verify Connection**: Look for green status indicators and successful connection messages

### What You'll See
- **Professional 3D Viewer**: Interactive WebGL cube with mouse controls
- **Octane Render Branding**: Official Octane logo and OTOY styling
- **Real-time Activity Log**: Live operation tracking with emoji indicators
- **Connection Controls**: Toggle to connect to Octane LiveLink service
- **Performance Stats**: FPS, frame time, and connection metrics

### Basic Usage
1. **Interact with 3D**: Drag to rotate, scroll to zoom, right-drag to pan
2. **Toggle Auto-Rotate**: Use the 🧊 switch to enable/disable rotation
3. **Connect to Octane**: Toggle the 🔌 switch (requires Octane + proxy)
4. **Test Functions**: Use toolbar buttons (📷 📸 🔄 🎬 📂 🫖)

### ⚠️ Important Notes
- **Octane Must Be Running**: The application requires Octane Render to be launched
- **gRPC Server Enabled**: Check Octane Preferences → LiveLink → Enable gRPC Server
- **Port Matching**: Server address in web app must match Octane's gRPC port
- **Proxy Required**: The proxy server translates HTTP requests to gRPC for Octane

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

### Development Mode (Optional)
For development without Octane Render, you can use the mock server:

#### Start Mock Octane Server
```bash
cd /path/to/grpcSamples/mock_octane
python3 mock_octane_server.py
```

#### Start Proxy Server (pointing to mock)
```bash
cd /path/to/grpcSamples/proxy
python3 grpc_proxy.py --target localhost:51023
```

This allows testing the web application without requiring Octane Render installation.

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
- **Connection Failed**: 
  - Verify Octane Render is running
  - Check Octane Preferences → LiveLink → Enable gRPC Server is checked
  - Ensure proxy server is running (`python3 grpc_proxy.py`)
  - Verify port numbers match between Octane and web app
- **Python Dependencies**: Install missing packages with `pip install grpcio aiohttp aiohttp-cors`
- **WebGL Issues**: Update graphics drivers, try different browser
- **Port Conflicts**: 
  - Octane gRPC port (default 51023) - change in Octane Preferences
  - Proxy server port (default 8080) - change in grpc_proxy.py
  - Update server address in web app to match