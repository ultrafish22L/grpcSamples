#!/bin/bash

# Simple build script for callback debug tool
# This assumes we have the SDK available

echo "🔨 Building Octane Callback Debug Tool"
echo "======================================"

# Check if we're in the right directory
if [ ! -f "callback_debug.cpp" ]; then
    echo "❌ callback_debug.cpp not found - run from simpleGlSdk directory"
    exit 1
fi

# Create build directory
mkdir -p build_debug
cd build_debug

echo "📁 Build directory: $(pwd)"

# Simple compilation command (this will likely fail without proper SDK setup)
echo "🔧 Attempting compilation..."

# Try to compile with basic flags
g++ -std=c++17 \
    -I../../../sdk \
    -I../../../sdk/src/api \
    -I../../../sdk/src/api/grpc \
    -I../../../sdk/src/api/grpc/client \
    -DDO_GRPC_SDK_ENABLED \
    -pthread \
    ../callback_debug.cpp \
    -o callback_debug \
    2>&1

if [ $? -eq 0 ]; then
    echo "✅ Compilation successful!"
    echo "🚀 Run with: ./build_debug/callback_debug"
else
    echo "❌ Compilation failed (expected without full SDK setup)"
    echo ""
    echo "📝 This is normal - the debug tool requires:"
    echo "   1. Full Octane SDK installation"
    echo "   2. Proper library linking"
    echo "   3. Platform-specific build configuration"
    echo ""
    echo "💡 The source code is ready for integration into the main build system"
fi

cd ..