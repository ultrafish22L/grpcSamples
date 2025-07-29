#!/bin/bash

# 🚀 Shared Protobuf Build Script for octaneProxy
# Generates Python protobuf files from shared/protos/definitions/

# Handle errors gracefully

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}🚀 Shared Protobuf Build Script${NC}"
echo -e "${BLUE}================================${NC}"

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# Define paths
SHARED_PROTO_DIR="$PROJECT_ROOT/shared/protos/definitions"
OUTPUT_DIR="$SCRIPT_DIR/generated"

echo -e "${YELLOW}📁 Source directory: $SHARED_PROTO_DIR${NC}"
echo -e "${YELLOW}📁 Output directory: $OUTPUT_DIR${NC}"

# Verify source directory exists
if [ ! -d "$SHARED_PROTO_DIR" ]; then
    echo -e "${RED}❌ Source directory not found: $SHARED_PROTO_DIR${NC}"
    exit 1
fi

# Create output directory
echo -e "${BLUE}📂 Creating output directory...${NC}"
mkdir -p "$OUTPUT_DIR"

# Clean existing files
echo -e "${BLUE}🧹 Cleaning existing shared protobuf files...${NC}"
rm -f "$OUTPUT_DIR"/livelink_pb2*.py
rm -f "$OUTPUT_DIR"/camera_control_pb2*.py

# Verify tools
echo -e "${BLUE}🔧 Verifying protobuf tools...${NC}"
if ! python -c "import grpc_tools.protoc" 2>/dev/null; then
    echo -e "${RED}❌ grpcio-tools not found. Install with: pip install grpcio-tools${NC}"
    exit 1
fi
echo -e "${GREEN}✅ Tools verified${NC}"

# Generate Python files from shared proto files
echo -e "${BLUE}⚙️  Generating shared protobuf files...${NC}"

GENERATED_COUNT=0
FAILED_COUNT=0

# Process livelink.proto
if [ -f "$SHARED_PROTO_DIR/livelink.proto" ]; then
    echo -e "${YELLOW}   Processing: livelink.proto${NC}"
    if python -m grpc_tools.protoc \
        --proto_path="$SHARED_PROTO_DIR" \
        --python_out="$OUTPUT_DIR" \
        --grpc_python_out="$OUTPUT_DIR" \
        "$SHARED_PROTO_DIR/livelink.proto"; then
        ((GENERATED_COUNT++))
        echo -e "${GREEN}   ✅ Success: livelink.proto${NC}"
    else
        echo -e "${RED}   ❌ Failed: livelink.proto${NC}"
        ((FAILED_COUNT++))
    fi
else
    echo -e "${RED}   ❌ Not found: livelink.proto${NC}"
    ((FAILED_COUNT++))
fi

# Process camera_control.proto
if [ -f "$SHARED_PROTO_DIR/camera_control.proto" ]; then
    echo -e "${YELLOW}   Processing: camera_control.proto${NC}"
    if python -m grpc_tools.protoc \
        --proto_path="$SHARED_PROTO_DIR" \
        --python_out="$OUTPUT_DIR" \
        --grpc_python_out="$OUTPUT_DIR" \
        "$SHARED_PROTO_DIR/camera_control.proto"; then
        ((GENERATED_COUNT++))
        echo -e "${GREEN}   ✅ Success: camera_control.proto${NC}"
    else
        echo -e "${RED}   ❌ Failed: camera_control.proto${NC}"
        ((FAILED_COUNT++))
    fi
else
    echo -e "${RED}   ❌ Not found: camera_control.proto${NC}"
    ((FAILED_COUNT++))
fi

# Update __init__.py
echo "# Generated protobuf package - includes both shared and SDK protobuf files" > "$OUTPUT_DIR/__init__.py"

# Summary
echo -e "${BLUE}📊 Build Summary${NC}"
echo -e "${BLUE}================${NC}"
echo -e "${GREEN}✅ Successfully generated: $GENERATED_COUNT shared protobuf files${NC}"
if [ $FAILED_COUNT -gt 0 ]; then
    echo -e "${RED}❌ Failed to generate: $FAILED_COUNT files${NC}"
fi

# List generated files
SHARED_FILES=$(find "$OUTPUT_DIR" -name "*livelink*" -o -name "*camera_control*" | wc -l)
echo -e "${GREEN}📁 Total shared protobuf files: $SHARED_FILES${NC}"

if [ $FAILED_COUNT -eq 0 ]; then
    echo -e "${GREEN}🎉 Shared protobuf files generated successfully!${NC}"
    echo -e "${BLUE}💡 These files provide the LiveLinkService for camera control and mesh access${NC}"
    exit 0
else
    echo -e "${YELLOW}⚠️  Some files failed, but others may be available${NC}"
    exit 1
fi