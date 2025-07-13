# macOS Build Instructions

## Prerequisites

### Install Homebrew (if not already installed)
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### Install Required Dependencies
```bash
# Install gRPC, Protocol Buffers, and Abseil
brew install grpc protobuf abseil

# Install CMake and build tools
brew install cmake

# Install OpenGL development libraries (usually included with Xcode)
xcode-select --install
```

## Build Process

### 1. Clone and Setup
```bash
git clone https://github.com/ultrafish22L/grpcSamples.git
cd grpcSamples
mkdir build
cd build
```

### 2. Configure and Build
```bash
# Configure with CMake
cmake ..

# Build all applications
make -j$(sysctl -n hw.ncpu)

# Or build specific targets
make simpleGL
make simpleGlGrpc
```

### 3. Run Applications
```bash
# Run the basic OpenGL viewer
./bin/simpleGL

# Run the gRPC-enabled viewer
./bin/simpleGlGrpc
```

## Supported Homebrew Locations

The build system automatically detects gRPC and protobuf installations in:
- `/opt/homebrew` (Apple Silicon Macs)
- `/usr/local` (Intel Macs)

## Troubleshooting

### gRPC Libraries Not Found
If you see "macOS gRPC libraries not found", install them with:
```bash
brew install grpc protobuf abseil
```

### Protoc Not Found
If protoc is not detected, ensure it's in your PATH:
```bash
which protoc
# Should show: /opt/homebrew/bin/protoc or /usr/local/bin/protoc
```

### Build Errors
1. Ensure Xcode command line tools are installed:
   ```bash
   xcode-select --install
   ```

2. Update Homebrew and dependencies:
   ```bash
   brew update
   brew upgrade grpc protobuf abseil
   ```

3. Clean and rebuild:
   ```bash
   rm -rf build
   mkdir build
   cd build
   cmake ..
   make
   ```

## Architecture Support

- **Apple Silicon (M1/M2)**: Fully supported with native ARM64 builds
- **Intel x86_64**: Fully supported with x86_64 builds

The build system automatically detects your architecture and uses the appropriate Homebrew prefix.