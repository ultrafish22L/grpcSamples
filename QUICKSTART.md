# 🚀 OctaneWeb v1.0 - Professional 3D Web Application QUICKSTART

**🎉 MAJOR MILESTONE**: Complete professional 3D web application suite with full-height Scene Outliner, auto-fitting Node Graph Editor, and comprehensive Octane Render integration!

## 🔥 CRITICAL OBJECTPTR TYPE CONVERSION REQUIREMENT

**⚠️ BEFORE YOU START**: If you're developing with Octane's gRPC API, you MUST understand ObjectPtr type conversion to avoid "invalid pointer type" errors.

**Quick Reference**:
```python
# ❌ WRONG - Copying original type fails
request.objectPtr.type = source_object.type

# ✅ CORRECT - Convert to target service type
request.objectPtr.type = 16  # ApiItem for ApiItemService calls
```

**See `OBJECTPTR_TYPE_CONVERSION_GUIDE.md` for complete details.**

## ⚡ QUICKSTART - Zero-to-Professional in 60 Seconds

**🎯 GOAL**: Experience professional 3D web application with full Octane integration in under one minute.

### 🚀 Instant Launch Sequence

**⏱️ 15 seconds - Environment Setup**:
```bash
# Terminal 1: Start proxy server
cd grpcSamples && python proxy/grpc_proxy.py

# Terminal 2: Launch Octane (if available)
# Octane → Preferences → LiveLink → Enable gRPC Server (port 51023)
```

**⏱️ 15 seconds - Application Launch**:
```bash
# Navigate and launch
cd octaneWeb && open index.html
# OR drag index.html to browser
```

**⏱️ 15 seconds - Connection & Verification**:
1. **Auto-Connect**: Application attempts connection automatically
2. **Visual Confirmation**: Green "connected" status in footer
3. **Feature Verification**: Scene Outliner populated, Node Graph auto-fitted

**⏱️ 15 seconds - Experience Core Features**:
- **Scene Outliner**: Expand/collapse hierarchical tree
- **Node Graph**: Auto-fitted nodes with professional rendering
- **Debug Console**: Press `Ctrl-D` for comprehensive testing suite
- **3D Viewport**: Mouse controls (orbit/pan/zoom) with real-time sync

### 🎯 Immediate Value Demonstration

**🔍 Visual Verification Checklist**:
- ✅ Scene Outliner spans full height (menu to footer)
- ✅ Node Graph Editor shows auto-fitted nodes
- ✅ Professional OTOY dark theme active
- ✅ Real-time connection status in footer
- ✅ Debug console accessible via Ctrl-D

### 🎯 What You'll Experience in v1.0
**🎨 Professional Interface**:
- **Scene Outliner**: Full-height hierarchical tree view with expand/collapse and visibility controls
- **Node Graph Editor**: Auto-fitting nodes with perfect positioning and right-click context menus
- **Node Inspector**: Complete property panels with camera parameters and render settings
- **Professional Layout**: Industry-standard 3D software aesthetic with OTOY dark theme

**🔧 Advanced Features**:
- **Debug Console**: Press Ctrl-D to access comprehensive testing suite (🧑‍🚒 button)
- **Cache Busting**: Automatic development-time cache management
- **Real-time Sync**: Bidirectional camera synchronization with Octane Render
- **Interactive 3D**: WebGL rendering with mouse controls (orbit, pan, zoom)
- **Activity Logging**: Live operation tracking with emoji indicators and timestamps

**🌐 Professional Experience**:
- **Zero Dependencies**: Custom gRPC-Web implementation without external libraries
- **Responsive Design**: Adapts to all screen sizes with mobile-friendly controls
- **Performance Monitoring**: FPS, connection health, and operation statistics
- **Error Handling**: Comprehensive error reporting with graceful degradation

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