# HTML Applications

## Overview
Professional WebGL 3D viewer with Octane LiveLink integration featuring real-time camera synchronization, interactive 3D rendering, and OTOY-branded professional UI.

## Main Application
- **index.html**: Complete WebGL 3D viewer with Octane LiveLink integration
  - Interactive 3D rendering with mouse controls (orbit, pan, zoom)
  - Real-time camera synchronization with Octane Render
  - Professional OTOY-branded UI with activity logging
  - Custom gRPC-Web client with zero external dependencies

## Key Features
- **Interactive 3D Rendering**: WebGL 2.0 cube with mouse controls
- **Real-time Octane Sync**: Live camera synchronization with Octane Render
- **Professional UI**: OTOY-branded dark theme with full-height layout
- **Activity Logging**: Real-time operation logging with timestamps and status indicators
- **Custom gRPC-Web**: Zero external dependencies, reliable cross-browser support
- **Performance Monitoring**: Real-time FPS, call statistics, and connection health

## Supporting Files
- **livelink.js**: Custom gRPC-Web client implementation
- **shared.js**: Common utilities and helper functions
- **webgl-utils.js**: WebGL rendering and 3D utilities
- **otoy-theme.css**: Professional OTOY branding and styling

## Quick Start
1. Start development servers: `./start_development_servers.sh`
2. Open application: `http://localhost:51313/index.html`
3. Click the connection toggle to connect to Octane LiveLink
4. Use mouse to interact with the 3D scene

## Testing
The application shows:
- ✅ Rotating 3D cube with proper WebGL 2.0 shaders
- ✅ Mouse interaction for camera control
- ✅ Auto-rotate toggle functionality
- ✅ Reset camera button
- ✅ All UI controls working
- ✅ Smooth 60fps performance
- ✅ Real-time connection status with LED indicators