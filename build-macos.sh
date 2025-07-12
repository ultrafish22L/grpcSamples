#!/bin/bash

echo "Building GrpcSamples for macOS..."
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
mkdir -p build/macos
cd build/macos

# Generate makefiles or Xcode project
echo "Generating build files..."
if command -v xcodebuild >/dev/null 2>&1; then
    echo "Generating Xcode project..."
    cmake -G Xcode -DCMAKE_BUILD_TYPE=Release ../../
    
    if [ $? -eq 0 ]; then
        echo
        echo "Success! Xcode project generated at:"
        echo "$(pwd)/GrpcSamples.xcodeproj"
        echo
        echo "To build from command line:"
        echo "  xcodebuild -project GrpcSamples.xcodeproj -configuration Release"
        echo
        echo "Or open the project in Xcode and build there."
    else
        echo "Error: Failed to generate Xcode project."
        exit 1
    fi
else
    echo "Xcode not found, generating makefiles..."
    cmake -DCMAKE_BUILD_TYPE=Release ../../
    
    if [ $? -eq 0 ]; then
        echo
        echo "Success! Makefiles generated."
        echo "Build directory: $(pwd)"
        echo
        echo "To build the project, run:"
        echo "  make -j$(sysctl -n hw.ncpu)"
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
fi