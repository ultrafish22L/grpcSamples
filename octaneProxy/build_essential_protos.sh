#!/bin/bash

# 🚀 Essential Octane Protobuf Build Script
# Generates only the essential Python protobuf files needed by octane_proxy.py

# Don't exit on errors - handle them gracefully

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}🚀 Essential Octane Protobuf Build Script${NC}"
echo -e "${BLUE}=========================================${NC}"

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# Define paths
PROTO_SOURCE_DIR="$PROJECT_ROOT/sdk/src/api/grpc/protodef"
OUTPUT_DIR="$SCRIPT_DIR/generated"

echo -e "${YELLOW}📁 Source directory: $PROTO_SOURCE_DIR${NC}"
echo -e "${YELLOW}📁 Output directory: $OUTPUT_DIR${NC}"

# Create output directory and clean SDK files (preserve shared files)
mkdir -p "$OUTPUT_DIR"
echo -e "${BLUE}🧹 Cleaning existing SDK protobuf files (preserving shared files)...${NC}"
find "$OUTPUT_DIR" -name "*.py" ! -name "*livelink*" ! -name "*camera_control*" ! -name "__init__.py" -delete 2>/dev/null || true

# Essential files needed by octane_proxy.py
ESSENTIAL_FILES=(
    "common.proto"
    "octaneenums.proto"
    "octaneids.proto"
    "octanevectypes.proto"
    "octanetime.proto"
    "octanereferenceexport.proto"
    "apitimesampling.proto"
    "apiprojectmanager.proto"
    "apinodesystem.proto"
    "apiitemarray.proto"
    "apinodegrapheditor.proto"
    "apisceneoutliner.proto"
    "apirender.proto"
    "apirenderview.proto"
)

echo -e "${BLUE}⚙️  Processing essential protobuf files...${NC}"

GENERATED_COUNT=0
FAILED_COUNT=0

for proto_file in "${ESSENTIAL_FILES[@]}"; do
    if [ -f "$PROTO_SOURCE_DIR/$proto_file" ]; then
        echo -e "${YELLOW}   Processing: $proto_file${NC}"
        
        if python -m grpc_tools.protoc \
            --proto_path="$PROTO_SOURCE_DIR" \
            --python_out="$OUTPUT_DIR" \
            --grpc_python_out="$OUTPUT_DIR" \
            "$PROTO_SOURCE_DIR/$proto_file"; then
            ((GENERATED_COUNT++))
            echo -e "${GREEN}   ✅ Success: $proto_file${NC}"
        else
            echo -e "${RED}   ❌ Failed: $proto_file${NC}"
            ((FAILED_COUNT++))
        fi
    else
        echo -e "${RED}   ❌ Not found: $proto_file${NC}"
        ((FAILED_COUNT++))
    fi
done

# Create __init__.py
echo "# Generated protobuf package" > "$OUTPUT_DIR/__init__.py"

# Summary
echo -e "${BLUE}📊 Build Summary${NC}"
echo -e "${BLUE}================${NC}"
echo -e "${GREEN}✅ Successfully generated: $GENERATED_COUNT files${NC}"
if [ $FAILED_COUNT -gt 0 ]; then
    echo -e "${RED}❌ Failed to generate: $FAILED_COUNT files${NC}"
fi

# List generated files
GENERATED_FILES=$(find "$OUTPUT_DIR" -name "*.py" | wc -l)
echo -e "${GREEN}📁 Total Python files: $GENERATED_FILES${NC}"

if [ $FAILED_COUNT -eq 0 ]; then
    echo -e "${GREEN}🎉 Essential protobuf files generated successfully!${NC}"
    exit 0
else
    echo -e "${YELLOW}⚠️  Some files failed, but essential ones may be available${NC}"
    exit 1
fi