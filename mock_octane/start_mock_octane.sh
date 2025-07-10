#!/bin/bash
# Mock Octane gRPC Server Launcher for Linux/Mac
# Simulates Octane Render's LiveLink service for development and testing

echo "========================================"
echo "Mock Octane gRPC Server"
echo "========================================"
echo

# Check if we're in the correct directory
if [ ! -f "mock_octane_server.py" ]; then
    echo "ERROR: This script must be run from the mock_octane/ directory"
    echo "Current directory: $(pwd)"
    echo "Expected file: mock_octane_server.py"
    echo
    exit 1
fi

echo "This script starts a mock Octane gRPC server for development and testing."
echo "Use this when you don't have Octane Render available but want to test"
echo "the HTML applications and gRPC connectivity."
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
python3 -m pip install grpcio grpcio-tools asyncio
if [ $? -ne 0 ]; then
    echo "WARNING: Failed to install some Python packages"
    echo "Continuing anyway - packages might already be installed"
fi

echo
echo "Step 2: Checking protobuf files..."
echo "---------------------------------"
if [ ! -f "../proxy/livelink_pb2.py" ]; then
    echo "ERROR: Protobuf files not found!"
    echo "Please run the build process first to generate protobuf files."
    echo "Expected location: ../proxy/livelink_pb2.py"
    echo
    exit 1
fi
echo "✓ Protobuf files found"

echo
echo "Step 3: Starting Mock Octane gRPC server..."
echo "------------------------------------------"
echo "Server will run on: 127.0.0.1:51022 (same as real Octane)"
echo
echo "🎭 MOCK SERVER FEATURES:"
echo "  - Simulates GetCamera/SetCamera operations"
echo "  - Provides mock mesh data (Cube, Sphere, Teapot)"
echo "  - Realistic camera state management"
echo "  - Statistics and logging"
echo
echo "🔧 USAGE:"
echo "  1. Start this mock server (replaces Octane Render)"
echo "  2. Start the proxy server: ../html/start_proxy.sh"
echo "  3. Open HTML applications: grpc_test.html, web3d_octane_sync.html"
echo
echo "Press Ctrl+C to stop the server"
echo

# Start the mock server
python3 mock_octane_server.py

# If we get here, the server stopped
echo
echo "Mock Octane server stopped."