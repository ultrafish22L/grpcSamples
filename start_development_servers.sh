#!/bin/bash
# Development Environment Launcher
# Starts both Mock Octane server and Proxy server for HTML development

echo "========================================"
echo "Development Environment Launcher"
echo "========================================"
echo

echo "This script starts both servers needed for HTML development:"
echo "  1. Mock Octane gRPC Server (replaces Octane Render)"
echo "  2. Proxy Server (translates HTTP to gRPC)"
echo
echo "After both servers start, you can open:"
echo "  - index.html (WebGL viewer with Octane sync)"
echo

# Check if we're in the project root
if [ ! -f "CMakeLists.txt" ]; then
    echo "ERROR: This script must be run from the project root directory"
    echo "Current directory: $(pwd)"
    echo "Expected file: CMakeLists.txt"
    echo
    exit 1
fi

echo "Step 1: Starting Mock Octane gRPC Server..."
echo "-------------------------------------------"

# Start mock server in background
cd mock_octane
./start_mock_octane.sh &
MOCK_PID=$!
cd ..

# Wait a moment for the mock server to start
sleep 3

echo "Step 2: Starting Proxy Server..."
echo "--------------------------------"

# Start proxy server in background
cd html
./start_proxy.sh &
PROXY_PID=$!
cd ..

echo
echo "✅ Both servers are starting:"
echo "  📭 Mock Octane Server: 127.0.0.1:51022 (PID: $MOCK_PID)"
echo "  🔄 Proxy Server: 127.0.0.1:51023 (PID: $PROXY_PID)"
echo
echo "🎮 Next steps:"
echo "  1. Wait for both servers to fully start"
echo "  2. Open html/index.html in your browser"
echo "  3. Test connectivity and explore mock data"
echo "  4. Open html/index.html for 3D viewer"
echo
echo "Press Ctrl+C to stop both servers"

# Function to cleanup on exit
cleanup() {
    echo
    echo "🛑 Stopping development servers..."
    kill $MOCK_PID 2>/dev/null
    kill $PROXY_PID 2>/dev/null
    echo "✅ Development servers stopped"
    exit 0
}

# Set trap to cleanup on Ctrl+C
trap cleanup SIGINT SIGTERM

# Wait for user to stop
while true; do
    sleep 1
done