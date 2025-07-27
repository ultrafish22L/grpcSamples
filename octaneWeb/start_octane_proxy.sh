#!/bin/bash
# ========================================
# OctaneWeb Complete Server Launcher
# ========================================
# Starts both the HTTP-to-gRPC proxy server
# and the web server for octaneWeb
# ========================================

echo
echo "========================================"
echo "  OctaneWeb Complete Server Launcher"
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

# Check if working proxy exists
if [ ! -f "working_proxy.py" ]; then
    echo "❌ ERROR: Working proxy server not found"
    echo "Expected location: working_proxy.py"
    echo "Please ensure the working proxy is in the octaneWeb directory"
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
echo "  Starting Servers..."
echo "========================================"
echo
echo "🚀 Proxy Server: http://localhost:51998"
echo "🌐 Web Server:   http://localhost:8080"
echo "🎯 Octane Target: 127.0.0.1:51022"
echo
echo "🧪 Test Endpoints:"
echo "- Proxy Health: http://localhost:51998/test"
echo "- Web App:      http://localhost:8080/"
echo "- Minimal Test: http://localhost:8080/minimal_test.html"
echo
echo "🎯 IMPORTANT:"
echo "1. Make sure Octane Render is running with LiveLink enabled"
echo "2. Both servers will start automatically"
echo "3. Open http://localhost:8080/ in your browser"
echo "4. Press Ctrl+C to stop servers"
echo

# Function to cleanup on exit
cleanup() {
    echo
    echo "🛑 Stopping servers..."
    kill $PROXY_PID 2>/dev/null
    kill $WEB_PID 2>/dev/null
    echo "✅ All servers stopped"
    exit 0
}

# Set up signal handlers
trap cleanup SIGINT SIGTERM

# Start the proxy server in background
echo "🚀 Starting proxy server..."
python3 working_proxy.py > proxy.log 2>&1 &
PROXY_PID=$!

# Wait a moment for proxy to start
sleep 3

# Start the web server in background
echo "🌐 Starting web server..."
python3 -m http.server 8080 > server.log 2>&1 &
WEB_PID=$!

echo
echo "========================================"
echo "  Both Servers Running!"
echo "========================================"
echo
echo "🌐 Open in browser: http://localhost:8080/"
echo "📊 Proxy logs: tail -f proxy.log"
echo "📊 Web logs: tail -f server.log"
echo
echo "Press Ctrl+C to stop all servers..."
echo

# Wait for user to stop
wait

# If we get here, something went wrong
echo
echo "========================================"
echo "  Servers Stopped Unexpectedly"
echo "========================================"
echo
cleanup