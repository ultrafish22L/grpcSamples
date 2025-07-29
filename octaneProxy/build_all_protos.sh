#!/bin/bash

# 🚀 Complete Octane Protobuf Build Script
# Generates both shared and SDK Python protobuf files for octaneProxy

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}🚀 Complete Octane Protobuf Build Script${NC}"
echo -e "${BLUE}=======================================${NC}"

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo -e "${BLUE}📋 This script will generate:${NC}"
echo -e "${YELLOW}   1. Shared protobuf files (livelink.proto, camera_control.proto)${NC}"
echo -e "${YELLOW}   2. Essential SDK protobuf files (Octane API)${NC}"
echo -e "${YELLOW}   3. Combined generated/ directory for octaneProxy${NC}"

# Step 1: Generate shared protobuf files
echo -e "\n${BLUE}🔄 Step 1: Generating shared protobuf files...${NC}"
if ./build_shared_protos.sh; then
    echo -e "${GREEN}✅ Shared protobuf files generated successfully${NC}"
else
    echo -e "${RED}❌ Failed to generate shared protobuf files${NC}"
    exit 1
fi

# Step 2: Generate essential SDK protobuf files
echo -e "\n${BLUE}🔄 Step 2: Generating essential SDK protobuf files...${NC}"
if ./build_essential_protos.sh; then
    echo -e "${GREEN}✅ Essential SDK protobuf files generated successfully${NC}"
else
    echo -e "${RED}❌ Failed to generate essential SDK protobuf files${NC}"
    exit 1
fi

# Summary
echo -e "\n${BLUE}📊 Complete Build Summary${NC}"
echo -e "${BLUE}=========================${NC}"

TOTAL_FILES=$(find generated/ -name "*.py" | wc -l)
SHARED_FILES=$(find generated/ -name "*livelink*" -o -name "*camera_control*" | wc -l)
SDK_FILES=$((TOTAL_FILES - SHARED_FILES - 1)) # -1 for __init__.py

echo -e "${GREEN}📁 Total Python files generated: $TOTAL_FILES${NC}"
echo -e "${GREEN}📁 Shared protobuf files: $SHARED_FILES${NC}"
echo -e "${GREEN}📁 SDK protobuf files: $SDK_FILES${NC}"

echo -e "\n${BLUE}📋 Key generated files:${NC}"
echo -e "${YELLOW}   Shared LiveLink API:${NC}"
echo -e "${YELLOW}     - livelink_pb2.py / livelink_pb2_grpc.py${NC}"
echo -e "${YELLOW}     - camera_control_pb2.py / camera_control_pb2_grpc.py${NC}"
echo -e "${YELLOW}   Essential Octane SDK:${NC}"
echo -e "${YELLOW}     - apinodesystem_pb2.py / apinodesystem_pb2_grpc.py${NC}"
echo -e "${YELLOW}     - apiprojectmanager_pb2.py / apiprojectmanager_pb2_grpc.py${NC}"
echo -e "${YELLOW}     - apirender_pb2.py / apirender_pb2_grpc.py${NC}"
echo -e "${YELLOW}     - common_pb2.py and core dependencies${NC}"

echo -e "\n${GREEN}🎉 All protobuf files generated successfully!${NC}"
echo -e "${BLUE}💡 octaneProxy now has access to both shared LiveLink API and full Octane SDK${NC}"
echo -e "${BLUE}🚀 Ready to run: python octane_proxy.py${NC}"