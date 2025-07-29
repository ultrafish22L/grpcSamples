#!/bin/bash

# 🚀 Octane Protobuf Build Script (Unix/Linux/macOS)
# Generates Python protobuf files from Octane SDK proto definitions
# 
# Usage: ./build_protos.sh
# Output: octaneProxy/generated/*.py files

# Handle errors gracefully instead of exiting

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}🚀 Octane Protobuf Build Script${NC}"
echo -e "${BLUE}=================================${NC}"

# Get script directory (works even when called from other directories)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# Define paths
PROTO_SOURCE_DIR="$PROJECT_ROOT/sdk/src/api/grpc/protodef"
OUTPUT_DIR="$SCRIPT_DIR/generated"

echo -e "${YELLOW}📁 Source directory: $PROTO_SOURCE_DIR${NC}"
echo -e "${YELLOW}📁 Output directory: $OUTPUT_DIR${NC}"

# Verify source directory exists
if [ ! -d "$PROTO_SOURCE_DIR" ]; then
    echo -e "${RED}❌ Error: Proto source directory not found: $PROTO_SOURCE_DIR${NC}"
    exit 1
fi

# Create output directory
echo -e "${BLUE}📂 Creating output directory...${NC}"
mkdir -p "$OUTPUT_DIR"

# Clean existing generated files
echo -e "${BLUE}🧹 Cleaning existing generated files...${NC}"
rm -f "$OUTPUT_DIR"/*.py

# Check if protoc is available
if ! command -v python &> /dev/null; then
    echo -e "${RED}❌ Error: Python not found${NC}"
    exit 1
fi

# Test grpc_tools availability
if ! python -c "import grpc_tools.protoc" 2>/dev/null; then
    echo -e "${RED}❌ Error: grpc_tools not installed. Run: pip install grpcio-tools${NC}"
    exit 1
fi

echo -e "${GREEN}✅ Tools verified${NC}"

# Count proto files
PROTO_COUNT=$(find "$PROTO_SOURCE_DIR" -name "*.proto" | wc -l)
echo -e "${BLUE}📊 Found $PROTO_COUNT proto files to process${NC}"

# Generate Python files from proto files
echo -e "${BLUE}⚙️  Generating Python protobuf files...${NC}"

# Define core files that should be processed first (dependencies)
CORE_FILES=(
    "common.proto"
    "octaneenums.proto" 
    "octaneids.proto"
    "octanevectypes.proto"
    "octanetime.proto"
    "octaneinfos.proto"
    "octanenet.proto"
    "octaneimageexport.proto"
    "octanereferenceexport.proto"
    "octanerenderpasses.proto"
    "octanevolume.proto"
)

# Files with known conflicts to skip
SKIP_FILES=(
    "apinodesystem_1.proto"
    "apinodesystem_2.proto" 
    "apinodesystem_3.proto"
    "apinodesystem_4.proto"
    "apinodesystem_5.proto"
    "apinodesystem_6.proto"
    "apinodesystem_7.proto"
    "apinodesystem_8.proto"
)

GENERATED_COUNT=0
FAILED_COUNT=0

# Process core files first
echo -e "${YELLOW}   Step 1: Processing core dependency files...${NC}"
for core_file in "${CORE_FILES[@]}"; do
    if [ -f "$PROTO_SOURCE_DIR/$core_file" ]; then
        echo -e "${YELLOW}      Processing: $core_file${NC}"
        if python -m grpc_tools.protoc \
            --proto_path="$PROTO_SOURCE_DIR" \
            --python_out="$OUTPUT_DIR" \
            --grpc_python_out="$OUTPUT_DIR" \
            "$PROTO_SOURCE_DIR/$core_file" 2>&1; then
            ((GENERATED_COUNT++))
        else
            echo -e "${RED}      ❌ Failed: $core_file${NC}"
            ((FAILED_COUNT++))
        fi
    fi
done

# Process remaining files (excluding problematic ones)
echo -e "${YELLOW}   Step 2: Processing remaining API files...${NC}"
for proto_file in "$PROTO_SOURCE_DIR"/*.proto; do
    if [ -f "$proto_file" ]; then
        filename=$(basename "$proto_file")
        
        # Skip if it's a core file (already processed)
        skip_core=false
        for core_file in "${CORE_FILES[@]}"; do
            if [ "$filename" = "$core_file" ]; then
                skip_core=true
                break
            fi
        done
        
        # Skip if it's in the skip list
        skip_problem=false
        for skip_file in "${SKIP_FILES[@]}"; do
            if [ "$filename" = "$skip_file" ]; then
                skip_problem=true
                echo -e "${YELLOW}      Skipping problematic: $filename${NC}"
                break
            fi
        done
        
        if [ "$skip_core" = false ] && [ "$skip_problem" = false ]; then
            echo -e "${YELLOW}      Processing: $filename${NC}"
            if python -m grpc_tools.protoc \
                --proto_path="$PROTO_SOURCE_DIR" \
                --python_out="$OUTPUT_DIR" \
                --grpc_python_out="$OUTPUT_DIR" \
                "$proto_file" 2>&1; then
                ((GENERATED_COUNT++))
            else
                echo -e "${RED}      ❌ Failed: $filename${NC}"
                ((FAILED_COUNT++))
            fi
        fi
    fi
done

# Create __init__.py to make it a Python package
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
echo -e "${GREEN}📁 Total Python files in output: $GENERATED_FILES${NC}"

# Show some example files
echo -e "${BLUE}📋 Sample generated files:${NC}"
ls "$OUTPUT_DIR"/*.py | head -5 | while read file; do
    echo -e "${YELLOW}   $(basename "$file")${NC}"
done

if [ $GENERATED_FILES -gt 5 ]; then
    echo -e "${YELLOW}   ... and $((GENERATED_FILES - 5)) more files${NC}"
fi

if [ $FAILED_COUNT -eq 0 ]; then
    echo -e "${GREEN}🎉 Build completed successfully!${NC}"
    echo -e "${GREEN}   Generated files are ready in: $OUTPUT_DIR${NC}"
    exit 0
else
    echo -e "${RED}⚠️  Build completed with errors${NC}"
    exit 1
fi