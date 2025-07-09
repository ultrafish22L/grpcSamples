#!/bin/bash

# Script to regenerate simpleGlGrpc protobuf files using the correct protoc version

PROTOC_BIN="/workspace/grpcSamples/third_party/protobuf/tools/bin/protoc"
GRPC_PLUGIN="/workspace/grpcSamples/third_party/protobuf/tools/bin/grpc_cpp_plugin"
PROTO_FILE="/workspace/grpcSamples/simpleGlGrpc/camera_control.proto"
OUTPUT_DIR="/workspace/grpcSamples/simpleGlGrpc/generated"

echo "Regenerating simpleGlGrpc protobuf files..."
echo "Using protoc: $($PROTOC_BIN --version)"
echo "Proto file: $PROTO_FILE"
echo "Output dir: $OUTPUT_DIR"

# Remove old generated files
echo "Cleaning old generated files..."
rm -f $OUTPUT_DIR/*.pb.cc
rm -f $OUTPUT_DIR/*.pb.h
rm -f $OUTPUT_DIR/*.grpc.pb.cc
rm -f $OUTPUT_DIR/*.grpc.pb.h

# Generate new files
echo "Generating new protobuf files..."
$PROTOC_BIN \
    --proto_path=$(dirname $PROTO_FILE) \
    --cpp_out=$OUTPUT_DIR \
    --grpc_out=$OUTPUT_DIR \
    --plugin=protoc-gen-grpc=$GRPC_PLUGIN \
    "$PROTO_FILE"

if [ $? -eq 0 ]; then
    echo "simpleGlGrpc protobuf regeneration complete!"
    echo "Generated files:"
    ls -la $OUTPUT_DIR/
else
    echo "Error regenerating simpleGlGrpc protobuf files"
    exit 1
fi