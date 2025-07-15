#!/bin/bash

# Generate protobuf and gRPC files for Linux
# This script generates the protobuf files that the shared components expect

set -e

echo "Generating protobuf files for Linux..."

# Create output directory if it doesn't exist
mkdir -p .

# Generate livelink protobuf files
echo "Generating livelink.proto..."
protoc --grpc_out=. --cpp_out=. \
    -I../protos/definitions \
    --plugin=protoc-gen-grpc=/usr/bin/grpc_cpp_plugin \
    ../protos/definitions/livelink.proto

# Generate camera_control protobuf files
echo "Generating camera_control.proto..."
protoc --grpc_out=. --cpp_out=. \
    -I../protos/definitions \
    --plugin=protoc-gen-grpc=/usr/bin/grpc_cpp_plugin \
    ../protos/definitions/camera_control.proto

echo "Protobuf generation complete!"
echo "Generated files:"
ls -la *.pb.h *.pb.cc 2>/dev/null || echo "No files generated"