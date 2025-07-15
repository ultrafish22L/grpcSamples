#!/bin/bash

# Generate protobuf and gRPC files for Windows
# This script generates the protobuf files that the shared components expect
# Assumes protoc.exe and grpc_cpp_plugin.exe are in PATH or third_party directories

set -e

echo "Generating protobuf files for Windows..."

# Try to find protoc and grpc_cpp_plugin
PROTOC_EXECUTABLE=""
GRPC_CPP_PLUGIN=""

# Check third_party directories first
if [ -f "../../third_party/protobuf/windows/bin/protoc.exe" ]; then
    PROTOC_EXECUTABLE="../../third_party/protobuf/windows/bin/protoc.exe"
fi

if [ -f "../../third_party/grpc/windows/bin/grpc_cpp_plugin.exe" ]; then
    GRPC_CPP_PLUGIN="../../third_party/grpc/windows/bin/grpc_cpp_plugin.exe"
fi

# Fall back to system PATH
if [ -z "$PROTOC_EXECUTABLE" ]; then
    PROTOC_EXECUTABLE="protoc"
fi

if [ -z "$GRPC_CPP_PLUGIN" ]; then
    GRPC_CPP_PLUGIN="grpc_cpp_plugin"
fi

echo "Using protoc: $PROTOC_EXECUTABLE"
echo "Using grpc_cpp_plugin: $GRPC_CPP_PLUGIN"

# Create output directory if it doesn't exist
mkdir -p .

# Generate livelink protobuf files
echo "Generating livelink.proto..."
$PROTOC_EXECUTABLE --grpc_out=. --cpp_out=. \
    -I../protos/definitions \
    -I../../third_party/protobuf/windows/include \
    --plugin=protoc-gen-grpc=$GRPC_CPP_PLUGIN \
    ../protos/definitions/livelink.proto

# Generate camera_control protobuf files
echo "Generating camera_control.proto..."
$PROTOC_EXECUTABLE --grpc_out=. --cpp_out=. \
    -I../protos/definitions \
    -I../../third_party/protobuf/windows/include \
    --plugin=protoc-gen-grpc=$GRPC_CPP_PLUGIN \
    ../protos/definitions/camera_control.proto

echo "Protobuf generation complete!"
echo "Generated files:"
ls -la *.pb.h *.pb.cc 2>/dev/null || echo "No files generated"