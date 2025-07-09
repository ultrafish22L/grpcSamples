# gRPC-Web Plugin Build for HTML Demos

This document explains how to build and use the gRPC-Web plugin for generating JavaScript files for HTML demos.

## Overview

The gRPC-Web plugin (`protoc-gen-grpc-web`) is a tool that generates JavaScript files from Protocol Buffer definitions. These JavaScript files enable web browsers to communicate with gRPC services.

**Important**: This plugin is **only for HTML demos** and is **completely separate** from:
- C++ applications (simpleGL, simpleGlGrpc, simpleGlSdk)
- Octane SDK integration
- Any C++ gRPC functionality

**Update (July 2025)**: The HTML demos now use a custom HTTP-based gRPC-Web implementation that doesn't require generated files. The plugin is still available for advanced use cases, but the demos work without it.

## Windows Build (Automatic)

On Windows, the plugin is automatically built when you configure the project with CMake:

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

This will:
1. Build the `protoc-gen-grpc-web.exe` plugin in the `bin/` directory
2. Use existing third-party libraries (protobuf, grpc, abseil) from `third_party/`
3. Place the plugin in the "ThirdParty" folder in Visual Studio (separate from main projects)

## Generated Files

The plugin outputs will be in:
- **Executable**: `html/protoc-gen-grpc-web.exe` (HTML demo tool)
- **Visual Studio**: ThirdParty folder (isolated from main projects)
- **C++ Executables**: `bin/` directory (separate from HTML tools)

## Usage

### Generating JavaScript Files

Use the provided batch script (from the html directory):
```bash
cd html
generate_js.bat
```

Or manually (from the html directory):
```bash
# Example command (adjust proto file path as needed)
..\third_party\protobuf\windows\release_64\protoc.exe ^
  --js_out=import_style=commonjs:generated/ ^
  --grpc-web_out=import_style=commonjs,mode=grpcwebtext:generated/ ^
  --plugin=protoc-gen-grpc-web=protoc-gen-grpc-web.exe ^
  your_proto_file.proto
```

### Using Generated Files in HTML

The generated JavaScript files go in the `html/generated/` directory and can be used by:
- `html/grpc_test.html` - Basic connectivity testing
- `html/web3d_octane_sync.html` - 3D visualization with LiveLink
- Custom implementations requiring protobuf classes

**Note**: The current HTML demos use a custom implementation in `html/livelink.js` that doesn't require generated files, providing better compatibility and reliability.

## Project Isolation

The gRPC-Web plugin build is completely isolated:

### What it DOES:
- ✅ Builds `protoc-gen-grpc-web.exe` for JavaScript generation in `html/` directory
- ✅ Uses existing Windows third-party libraries
- ✅ Enables HTML demos to communicate with Octane LiveLink
- ✅ Placed in separate Visual Studio folder
- ✅ Keeps HTML tools separate from C++ executables

### What it DOES NOT do:
- ❌ Affect C++ application builds
- ❌ Modify SDK integration
- ❌ Change any C++ gRPC functionality
- ❌ Build on non-Windows platforms
- ❌ Interfere with existing project structure

## Dependencies

The plugin uses these existing third-party libraries:
- **Protobuf**: `third_party/protobuf/windows/`
- **Abseil**: `third_party/absl/windows/`
- **Headers**: Include files from existing installations

No additional dependencies are required - everything uses the existing third-party structure.

## Troubleshooting

### Build Issues
1. **Missing libraries**: Ensure `third_party/protobuf/windows/` contains the required libraries
2. **Wrong platform**: Plugin only builds on Windows
3. **CMake errors**: Check that Visual Studio and Windows SDK are properly installed

### Runtime Issues
1. **Plugin not found**: Ensure `html/protoc-gen-grpc-web.exe` exists after build
2. **Protoc not found**: Check `third_party/protobuf/windows/release_64/protoc.exe`
3. **Generation fails**: Verify proto file paths and syntax

## File Structure

```
grpcSamples/
├── bin/                                # C++ executables
│   ├── simpleGL.exe
│   ├── simpleGlGrpc.exe
│   └── simpleGlSdk.exe
├── html/                               # HTML demos and tools
│   ├── protoc-gen-grpc-web.exe         # gRPC-Web plugin (HTML tool)
│   ├── generated/                      # Generated JavaScript files
│   ├── grpc_test.html                  # HTML demo
│   ├── web3d_octane_sync.html          # 3D HTML demo
│   ├── livelink.js                     # JavaScript library
│   └── generate_js.bat                 # Generation script
├── third_party/
│   ├── grpc-web/                       # Plugin source code
│   ├── protobuf/windows/               # Protobuf libraries
│   └── absl/windows/                   # Abseil libraries
└── [C++ source directories]
```

## Integration with Main Project

The gRPC-Web plugin is integrated into the main CMake build but remains completely separate:

```cmake
# In main CMakeLists.txt
if(WIN32)
    message(STATUS "Building grpc-web plugin for HTML demos (Windows)")
    add_subdirectory(third_party/grpc-web)
    set(BUILD_GRPC_WEB_PLUGIN ON)
else()
    message(STATUS "Skipping grpc-web plugin build (Windows only)")
    set(BUILD_GRPC_WEB_PLUGIN OFF)
endif()
```

This ensures the plugin builds automatically on Windows but doesn't interfere with other platforms or C++ applications.