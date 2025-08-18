# OctaneProxy - HTTP-to-gRPC Proxy Server

HTTP-to-gRPC proxy server for web client connectivity with comprehensive logging and callback streaming support.

## Quick Start

### Install Dependencies

```bash
# Install core dependencies
pip install -r requirements.txt

# Or install manually:
pip install aiohttp grpcio protobuf numpy

# Optional: Install Pillow for PNG export functionality
pip install Pillow
```

### Run the Proxy Server

```bash
python octane_proxy.py
```

The server will start on `http://localhost:51023` by default.

## Features

- **HTTP-to-gRPC Translation**: Converts HTTP/JSON requests to native gRPC calls
- **Server-Sent Events (SSE)**: Real-time callback streaming for render updates
- **Comprehensive Logging**: Detailed request/response logging with emoji indicators
- **PNG Export**: Optional PNG saving of render callbacks (requires Pillow)
- **CORS Support**: Enhanced cross-origin support for web clients
- **Graceful Degradation**: Handles missing dependencies gracefully

## Dependencies

### Core Dependencies (Required)
- `aiohttp>=3.8.0` - HTTP server framework
- `grpcio>=1.50.0` - gRPC client library
- `protobuf>=4.21.0` - Protocol buffer support
- `numpy>=1.21.0` - Array processing for image data

### Optional Dependencies
- `Pillow>=9.0.0` - PNG export functionality in callback system

If Pillow is not installed, the proxy will still work but PNG export will be disabled.

## Configuration

The proxy server connects to Octane LiveLink service at:
- **Host**: `127.0.0.1` (localhost)
- **Port**: `51022` (default Octane LiveLink port)

## Troubleshooting

### Missing PIL/Pillow Error
```
ModuleNotFoundError: No module named 'PIL'
```

**Solution**: Install Pillow:
```bash
pip install Pillow
```

Or the proxy will run without PNG export functionality.

### Connection Refused
```
Connection refused (10061)
```

**Solution**: 
1. Ensure Octane is running
2. Enable LiveLink in Octane: Help → LiveLink
3. Check that port 51022 is not blocked by firewall

## Architecture

```
Web Client → HTTP/JSON → Proxy Server → gRPC → Octane LiveLink
          ← SSE Stream ←              ← Callbacks ←
```

The proxy translates between web-friendly HTTP/JSON and Octane's native gRPC protocol.