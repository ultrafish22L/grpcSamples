# HTML Applications Setup Guide

## Quick Start

### 1. Start the Proxy Server
The gRPC proxy server is **required** for the HTML applications to communicate with Octane Render.

**Windows:**
```bash
start_proxy.bat
```

**Linux/Mac:**
```bash
./start_proxy.sh
```

### 2. Open HTML Application
Once the proxy server is running, you can open the main HTML application:

- **WebGL-Octane Sync**: `index.html` - Complete 3D viewer with live Octane synchronization and gRPC testing interface

You can open the application:
- **Via development servers**: `./start_development_servers.sh` then visit `http://localhost:51313/index.html`
- **Via HTTP server**: `python3 -m http.server 8000` then visit `http://localhost:8000/index.html`
- **Directly in browser**: Double-click the HTML file (file:// protocol)

## Architecture

```
Browser (HTML/JS) ←→ HTTP Proxy Server ←→ gRPC ←→ Octane Render
```

- **HTML Applications**: Run in browser, use custom gRPC-Web implementation
- **Proxy Server**: Translates HTTP requests to gRPC calls (`grpc_proxy.py`)
- **Octane Render**: Must be running with LiveLink enabled on port 51022

## Files Overview

### Main Application
- `index.html` - Complete WebGL 3D viewer with Octane synchronization and gRPC testing interface

### Supporting Libraries
- `otoy-theme.css` - Professional OTOY-branded stylesheet
- `shared.js` - Consolidated utility classes and functions
- `livelink.js` - Core gRPC-Web client implementation
- `webgl-utils.js` - WebGL utilities for 3D rendering

### Launch Scripts
- `start_proxy.bat` - Windows proxy server launcher
- `start_proxy.sh` - Linux/Mac proxy server launcher

## Requirements

### Software
- **Python 3.7+** with packages: `grpcio`, `grpcio-tools`, `aiohttp`, `aiohttp-cors`
- **Modern web browser** with WebGL support
- **Octane Render** with LiveLink enabled

### Network
- Proxy server runs on: `http://127.0.0.1:51023`
- Octane LiveLink service: `127.0.0.1:51022`

## Troubleshooting

### Proxy Server Issues
1. Make sure Python 3.7+ is installed
2. Install required packages: `pip install grpcio grpcio-tools aiohttp aiohttp-cors`
3. Check that Octane Render is running with LiveLink enabled
4. Verify no other service is using port 51023

### Browser Issues
1. Use a modern browser with WebGL support
2. Check browser console for JavaScript errors
3. Ensure the proxy server is running before opening the HTML application
4. Try both HTTP server and file:// protocol access

### Connection Issues
1. Verify Octane Render is running and LiveLink is enabled
2. Check that Octane LiveLink is listening on port 51022
3. Look at proxy server logs for connection errors
4. Use the connection toggle in `index.html` to test basic connectivity

## Development

The application uses a professional design system and utility library:
- **Professional styling** via `otoy-theme.css`
- **Shared functionality** via `shared.js`
- **Modular architecture** with separate concerns
- **Enhanced logging** with emoji indicators and timestamps