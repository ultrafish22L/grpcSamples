#!/bin/bash
# Simple Test Proxy Server Launcher for Linux/macOS
# Tests ObjectPtr passing between Octane gRPC APIs

echo ""
echo "========================================"
echo "  Simple Test Proxy Server Launcher"
echo "========================================"
echo ""
echo "This proxy tests ObjectPtr passing with real Octane:"
echo "- Connects to Octane at host.docker.internal:51022"
echo "- Runs on http://localhost:51024"
echo "- Tests rootNodeGraph -> name API chain"
echo ""

# Check if Python is available
if ! command -v python3 &> /dev/null; then
    echo "❌ ERROR: python3 not found"
    echo "Please install Python 3.7+ and ensure python3 is in your PATH"
    exit 1
fi

# Check if we're in the correct directory
if [ ! -f "simple_test_proxy.py" ]; then
    echo "❌ ERROR: simple_test_proxy.py not found"
    echo "Please run this script from the grpcSamples directory"
    exit 1
fi

# Check if protobuf files exist
if [ ! -f "proxy/apiprojectmanager_pb2.py" ]; then
    echo "❌ ERROR: Protobuf files not found in proxy/ directory"
    echo "Please ensure the protobuf files are generated"
    exit 1
fi

echo "✅ Python3 found"
echo "✅ simple_test_proxy.py found"
echo "✅ Protobuf files found"
echo ""

echo "🚀 Starting Simple Test Proxy Server..."
echo ""
echo "Server will run on: http://localhost:51024"
echo "Octane connection: host.docker.internal:51022"
echo ""
echo "Available endpoints:"
echo "  POST /octaneapi.ApiProjectManagerService/rootNodeGraph"
echo "  POST /octaneapi.ApiItemService/name"
echo ""
echo "Press Ctrl+C to stop the server"
echo ""

# Start the proxy server
python3 simple_test_proxy.py