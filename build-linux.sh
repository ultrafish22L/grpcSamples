#!/bin/bash

echo "Building GrpcSamples for Linux..."
echo

# Generate GLEW extensions and source files
echo "Generating GLEW extensions and source files..."
cd third_party/glew
if [ -f auto/Makefile ]; then
    echo "Running GLEW auto-generation..."
    if make -C auto; then
        echo "GLEW files generated successfully"
    else
        echo "Warning: GLEW auto-generation failed, using existing files"
    fi
else
    echo "GLEW auto directory not found, using existing files"
fi
cd ../..

# Create build directory
mkdir -p build/linux
cd build/linux

# Generate makefiles
echo "Generating makefiles..."
cmake -DCMAKE_BUILD_TYPE=Release ../../

if [ $? -eq 0 ]; then
    echo
    echo "Success! Makefiles generated."
    echo "Build directory: $(pwd)"
    echo
    echo "To build the project, run:"
    echo "  make -j$(nproc)"
    echo
    echo "Or to build a specific target:"
    echo "  make simpleGlGrpc"
    echo "  make simpleGL"
    echo "  make simpleGlSdk"
else
    echo
    echo "Error: Failed to generate makefiles."
    echo "Please check that CMake and required dependencies are installed."
    exit 1
fi