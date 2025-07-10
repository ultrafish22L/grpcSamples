#!/bin/bash
# gRPC Proxy Server Launcher
# Starts the gRPC-Web proxy server for HTML applications

echo "========================================"
echo "gRPC Proxy Server for HTML Applications"
echo "========================================"
echo

# Check if we're in the correct directory
if [ ! -f "grpc_test.html" ]; then
    echo "ERROR: This script must be run from the html/ directory"
    echo "Current directory: $(pwd)"
    echo "Expected files: grpc_test.html, web3d_octane_sync.html"
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
python3 -m pip install grpcio grpcio-tools aiohttp aiohttp-cors
if [ $? -ne 0 ]; then
    echo "WARNING: Failed to install some Python packages"
    echo "Continuing anyway - packages might already be installed"
fi

echo
echo "Step 2: Starting gRPC proxy server..."
echo "------------------------------------"
echo "Server will run on: http://127.0.0.1:51023"
echo "Octane connection: 127.0.0.1:51022"
echo
echo "🎮 Usage:"
echo "  1. Open grpc_test.html in your browser (any HTTP server or file://)"
echo "  2. Open web3d_octane_sync.html in your browser"
echo "  3. Both applications will connect through this proxy to Octane"
echo
echo "Press Ctrl+C to stop the server"
echo

# Start the proxy server
cd ../proxy
python3 grpc_proxy.py

# If we get here, the server stopped
echo
echo "Proxy server stopped."