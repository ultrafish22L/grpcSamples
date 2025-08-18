#!/bin/bash
# gRPC Proxy Server Launcher
# Starts the gRPC-Web proxy server for HTML applications

echo "========================================"
echo "gRPC Proxy Server for HTML Applications"
echo "========================================"
echo

# Check if we're in the correct directory
if [ ! -f "index.html" ]; then
    echo "ERROR: This script must be run from the html/ directory"
    echo "Current directory: $(pwd)"
    echo "Expected files: index.html"
    echo
    exit 1
fi

echo "This script starts the gRPC proxy server for HTML applications."
echo "The proxy translates HTTP requests from browsers to gRPC calls to Octane."
echo
echo "WARNING: Make sure Octane Render is running with LiveLink enabled!"
echo

# Check if Python is available
if ! command -v python3 &> /dev/null; then
    echo "ERROR: Python 3 not found"
    echo "Please install Python 3.7+ and make sure it's in your PATH"
    echo
    exit 1
fi

echo "Step 1: Installing Python dependencies..."
echo "-----------------------------------------"
echo "Installing core packages: grpcio, aiohttp, protobuf, numpy..."
python3 -m pip install grpcio grpcio-tools aiohttp aiohttp-cors protobuf numpy
if [ $? -ne 0 ]; then
    echo "WARNING: Failed to install some core packages"
    echo "Continuing anyway - packages might already be installed"
fi

echo "Installing optional packages for enhanced functionality..."
python3 -m pip install Pillow
if [ $? -ne 0 ]; then
    echo "WARNING: Failed to install Pillow (PNG export will be disabled)"
    echo "This is not critical - the proxy will work without it"
else
    echo "Pillow installed ✓ (PNG export enabled)"
fi

echo
echo "Step 2: Starting gRPC proxy server..."
echo "------------------------------------"
echo "Server will run on: http://127.0.0.1:51023"
echo "Octane connection: 127.0.0.1:51022"
echo
echo "🎮 Usage:"
echo "  1. Open index.html in your browser (any HTTP server or file://)"
echo
echo "Press Ctrl+C to stop the server"
echo

# Start the proxy server
cd ../octaneProxy
python3 octane_proxy.py

# If we get here, the server stopped
echo
echo "Proxy server stopped."