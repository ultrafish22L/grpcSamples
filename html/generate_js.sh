#!/bin/bash
# Generate JavaScript gRPC-Web files from proto definitions
# This script generates the JavaScript files needed for HTML demos to communicate with Octane

echo "Generating JavaScript gRPC-Web files..."

# Create generated directory if it doesn't exist
mkdir -p generated

# Set paths
PROTO_DIR="../shared/protos"
THIRD_PARTY_DIR="../third_party"
OUTPUT_DIR="generated"
PROTOC_GEN_GRPC_WEB="./protoc-gen-grpc-web"

# Check if protoc-gen-grpc-web exists
if [ ! -f "$PROTOC_GEN_GRPC_WEB" ]; then
    echo "Error: protoc-gen-grpc-web not found. Please build it first with CMake."
    exit 1
fi

# Check if protoc is available
if ! command -v protoc &> /dev/null; then
    echo "Error: protoc not found. Please install protobuf-compiler."
    exit 1
fi

# Generate JavaScript files for each proto file
echo "Generating from livelink.proto..."
protoc \
    --proto_path="$PROTO_DIR" \
    --proto_path="$THIRD_PARTY_DIR" \
    --js_out="$OUTPUT_DIR" \
    --grpc-web_out=mode=grpcwebtext:"$OUTPUT_DIR" \
    --plugin=protoc-gen-grpc-web="$PROTOC_GEN_GRPC_WEB" \
    "$PROTO_DIR/livelink.proto"

if [ $? -eq 0 ]; then
    echo "Successfully generated JavaScript files in $OUTPUT_DIR/"
    echo "Files generated:"
    ls -la "$OUTPUT_DIR/"
else
    echo "Error: Failed to generate JavaScript files"
    exit 1
fi

echo "JavaScript generation complete!"
echo ""
echo "You can now use these files in your HTML demos:"
echo "- Import the generated *_pb.js files for message types"
echo "- Import the generated *_grpc_web_pb.js files for service clients"
echo "- Use with livelink.js for easy integration"