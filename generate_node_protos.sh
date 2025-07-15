#!/bin/bash
set -e

# Generate protobuf files for node system
PROTODEFS="sdk/src/api/grpc/protodef/"
OUTPUT_DIR="proxy/"

echo "Generating protobuf files for node system..."

# Generate required dependencies first
echo "Generating dependencies..."
protoc -I "$PROTODEFS" --python_out="$OUTPUT_DIR" --grpc_out="$OUTPUT_DIR" --plugin=protoc-gen-grpc=`which grpc_python_plugin` "$PROTODEFS"apitimesampling.proto 2>/dev/null || echo "Warning: apitimesampling.proto not found"
protoc -I "$PROTODEFS" --python_out="$OUTPUT_DIR" --grpc_out="$OUTPUT_DIR" --plugin=protoc-gen-grpc=`which grpc_python_plugin` "$PROTODEFS"apioutputcolorspaceinfo.proto 2>/dev/null || echo "Warning: apioutputcolorspaceinfo.proto not found"
protoc -I "$PROTODEFS" --python_out="$OUTPUT_DIR" --grpc_out="$OUTPUT_DIR" --plugin=protoc-gen-grpc=`which grpc_python_plugin` "$PROTODEFS"octanerenderpasses.proto 2>/dev/null || echo "Warning: octanerenderpasses.proto not found"
protoc -I "$PROTODEFS" --python_out="$OUTPUT_DIR" --grpc_out="$OUTPUT_DIR" --plugin=protoc-gen-grpc=`which grpc_python_plugin` "$PROTODEFS"octaneimageexport.proto 2>/dev/null || echo "Warning: octaneimageexport.proto not found"
protoc -I "$PROTODEFS" --python_out="$OUTPUT_DIR" --grpc_out="$OUTPUT_DIR" --plugin=protoc-gen-grpc=`which grpc_python_plugin` "$PROTODEFS"apianimationtimetransform.proto 2>/dev/null || echo "Warning: apianimationtimetransform.proto not found"
protoc -I "$PROTODEFS" --python_out="$OUTPUT_DIR" --grpc_out="$OUTPUT_DIR" --plugin=protoc-gen-grpc=`which grpc_python_plugin` "$PROTODEFS"apiarray.proto 2>/dev/null || echo "Warning: apiarray.proto not found"
protoc -I "$PROTODEFS" --python_out="$OUTPUT_DIR" --grpc_out="$OUTPUT_DIR" --plugin=protoc-gen-grpc=`which grpc_python_plugin` "$PROTODEFS"octaneenums.proto 2>/dev/null || echo "Warning: octaneenums.proto not found"
protoc -I "$PROTODEFS" --python_out="$OUTPUT_DIR" --grpc_out="$OUTPUT_DIR" --plugin=protoc-gen-grpc=`which grpc_python_plugin` "$PROTODEFS"octaneids.proto 2>/dev/null || echo "Warning: octaneids.proto not found"
protoc -I "$PROTODEFS" --python_out="$OUTPUT_DIR" --grpc_out="$OUTPUT_DIR" --plugin=protoc-gen-grpc=`which grpc_python_plugin` "$PROTODEFS"octaneinfos.proto 2>/dev/null || echo "Warning: octaneinfos.proto not found"

# Generate the main node system protobuf
echo "Generating apinodesystem.proto..."
protoc -I "$PROTODEFS" --python_out="$OUTPUT_DIR" --grpc_out="$OUTPUT_DIR" --plugin=protoc-gen-grpc=`which grpc_python_plugin` "$PROTODEFS"apinodesystem.proto

echo "✅ Generated apinodesystem protobuf files"