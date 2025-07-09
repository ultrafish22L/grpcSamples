#!/bin/bash
# Test script to verify repository can be cloned and built from scratch
# This simulates what a new user would experience

set -e  # Exit on any error

echo "=== Testing Repository Clone and Build ==="

# Create temporary directory
TEST_DIR="/tmp/grpcSamples_test_$(date +%s)"
echo "Creating test directory: $TEST_DIR"
mkdir -p "$TEST_DIR"
cd "$TEST_DIR"

# Clone repository (simulating fresh clone)
echo "Cloning repository..."
git clone /workspace/grpcSamples grpcSamples_test
cd grpcSamples_test

# Initialize submodules
echo "Initializing submodules..."
git submodule update --init --recursive

# Check submodule status
echo "Submodule status:"
git submodule status

# Create build directory and configure
echo "Configuring build..."
mkdir build
cd build
cmake ..

# Build protoc-gen-grpc-web target
echo "Building protoc-gen-grpc-web..."
cmake --build . --target protoc-gen-grpc-web

# Verify executable was created
if [ -f "../html/protoc-gen-grpc-web" ]; then
    echo "✅ SUCCESS: protoc-gen-grpc-web executable created"
    ls -la ../html/protoc-gen-grpc-web
else
    echo "❌ FAILED: protoc-gen-grpc-web executable not found"
    exit 1
fi

# Clean up
cd /
rm -rf "$TEST_DIR"

echo "=== Test completed successfully! ==="
echo "Repository can be cloned and built from scratch."