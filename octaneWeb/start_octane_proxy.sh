#!/bin/bash
# ========================================
# OctaneWeb Custom Proxy Server Launcher
# ========================================
# Starts the custom HTTP-to-gRPC proxy server
# optimized specifically for octaneWeb
# ========================================

echo
echo "========================================"
echo "  OctaneWeb Custom Proxy Server"
echo "========================================"
echo

# Check if we're in the correct directory
if [ ! -f "index.html" ]; then
    echo "❌ ERROR: This script must be run from the octaneWeb folder"
    echo "Current directory: $(pwd)"
    echo "Expected files: index.html, js/, css/"
    echo
    exit 1
fi

# Check if custom proxy exists
if [ ! -f "octane_proxy.py" ]; then
    echo "❌ ERROR: Custom proxy server not found"
    echo "Expected location: octane_proxy.py"
    echo "Please ensure the custom proxy is in the octaneWeb directory"
    echo
    exit 1
fi

echo "🔍 Checking Python installation..."
if ! command -v python3 &> /dev/null; then
    echo "❌ ERROR: Python 3 not found in PATH"
    echo "Please install Python 3.7+ and add it to your PATH"
    echo "Download from: https://python.org/downloads/"
    echo
    exit 1
fi

echo "✅ Python found: $(python3 --version)"

echo
echo "🔍 Checking required Python packages..."
if ! python3 -c "import grpcio, aiohttp" 2>/dev/null; then
    echo "⚠️  WARNING: Required packages not found"
    echo "Installing grpcio and aiohttp..."
    pip3 install grpcio aiohttp protobuf
    if [ $? -ne 0 ]; then
        echo "❌ ERROR: Failed to install required packages"
        echo "Please run manually: pip3 install grpcio aiohttp protobuf"
        echo
        exit 1
    fi
fi

echo "✅ Required packages found"

echo
echo "========================================"
echo "  Starting Custom Proxy Server..."
echo "========================================"
echo
echo "🚀 Custom Proxy: http://localhost:51024"
echo "🎯 Octane Target: 127.0.0.1:51022"
echo "📊 Health Check:  http://localhost:51024/health"
echo "🧪 Test Suite:    http://localhost:51024/test"
echo
echo "🎯 IMPORTANT:"
echo "1. Make sure Octane Render is running with LiveLink enabled"
echo "2. Open octaneWeb in browser: file://$(pwd)/index.html"
echo "3. Press Ctrl+C to stop the proxy server"
echo

# Start the custom proxy server
python3 octane_proxy.py

# If we get here, the server stopped
echo
echo "========================================"
echo "  Custom Proxy Server Stopped"
echo "========================================"
echo