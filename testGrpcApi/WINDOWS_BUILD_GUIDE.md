# testGrpcApi Windows Build Guide

## Quick Fix for Windows Build Errors

If you're getting any of these errors:
```
error C1083: Cannot open include file: 'imgui_impl_glfw.h': No such file or directory
error C4430: missing type specifier - int assumed. Note: C++ does not support default-int
error C2146: syntax error: missing ')' before identifier 'LONGLONG'
error C2065: 'LONGLONG': undeclared identifier
see previous definition of 'APIENTRY'
```

These have been **FIXED** in the latest commit. Simply pull the latest changes:

```bash
git pull origin main
```

## Windows Build Instructions

### Method 1: Visual Studio 2022 (Recommended)

1. **Generate Visual Studio Solution**:
   ```cmd
   win-vs2022.bat
   ```

2. **Open Solution**:
   - Open `build\win-vs2022\GrpcSamples.sln` in Visual Studio 2022
   - Set `testGrpcApi` as startup project
   - Build Solution (Ctrl+Shift+B)

3. **Run Application**:
   - Press F5 to run with debugging
   - Or find executable at `bin\testGrpcApi.exe`

### Method 2: Command Line Build

1. **Create Build Directory**:
   ```cmd
   mkdir build\windows
   cd build\windows
   ```

2. **Generate Build Files**:
   ```cmd
   cmake -G "Visual Studio 17 2022" -A x64 ..\..\
   ```

3. **Build Project**:
   ```cmd
   cmake --build . --config Release --target testGrpcApi
   ```

## Prerequisites

### Required Software
- **Visual Studio 2022** with C++ development tools
- **CMake 3.16+** 
- **Git** for version control

### System Libraries (Automatically Handled)
The build system automatically links these Windows libraries:
- `opengl32.lib` - OpenGL graphics
- `gdi32.lib` - Graphics Device Interface
- `user32.lib` - User interface functions
- `kernel32.lib` - Core Windows functions
- `shell32.lib` - Shell functions

## Troubleshooting

### Common Issues and Solutions

#### 1. Header Include Errors (imgui_impl_glfw.h, LONGLONG, APIENTRY)
**Status**: ✅ **FIXED** in latest commit

**Solution**: Pull latest changes:
```cmd
git pull origin main
```

**Technical Details**: 
- Created `shared/windows_headers.h` compatibility layer
- Fixed Windows header inclusion order conflicts
- Resolved gRPC LONGLONG type definition issues
- Fixed APIENTRY redefinition between Windows and OpenGL headers
- Added proper Windows type definitions before gRPC headers

#### 2. Visual Studio Version Issues
**Error**: CMake generator not found

**Solution**: 
- Ensure Visual Studio 2022 is installed with C++ tools
- For VS 2019, modify `win-vs2022.bat` to use `"Visual Studio 16 2019"`

#### 3. Missing Dependencies
**Error**: Cannot find required libraries

**Solution**: 
- All dependencies are included in `third_party/` directory
- No additional installations required
- Build system automatically handles library linking

#### 4. Runtime Library Mismatch
**Error**: LNK2038 runtime library mismatch

**Solution**: 
- Build system automatically configures static runtime linking
- Uses `/MT` (Release) and `/MTd` (Debug) flags
- Matches third-party library configuration

#### 5. Large Object File Errors
**Error**: C1128 number of sections exceeded

**Solution**: 
- Build system automatically adds `/bigobj` flag
- Handles large ImGui compilation units
- No manual intervention required

## Build Configuration Details

### Compiler Settings (MSVC)
- **Parallel Compilation**: `/MP` flag enabled
- **Warning Level**: `/W3` with specific warning suppressions
- **Runtime Library**: Static linking (`/MT`, `/MTd`)
- **Exception Handling**: `/EHsc` enabled
- **Large Objects**: `/bigobj` flag for ImGui

### Library Linking
- **Static Libraries**: All dependencies statically linked
- **System Libraries**: Windows-specific libraries automatically included
- **Cross-Platform**: Conditional linking based on platform detection

### Include Directories
- `third_party/imgui/` - Dear ImGui headers
- `third_party/imgui/backends/` - Platform-specific backends
- `shared/` - Shared component headers
- `shared/protos/` - Protocol buffer generated files

## Verification

### Build Success Indicators
1. **No Compilation Errors**: Clean build output
2. **Executable Created**: `bin\testGrpcApi.exe` exists
3. **Proper Linking**: No unresolved symbol errors
4. **Size Check**: Executable ~3-4MB (includes ImGui)

### Runtime Testing
```cmd
# Test basic functionality (requires display)
bin\testGrpcApi.exe

# Expected: ImGui window opens with OTOY theme
# Features: Connection controls, 3D rendering, activity log
```

## Advanced Configuration

### Custom Build Options
```cmd
# Debug build with verbose output
cmake --build . --config Debug --target testGrpcApi --verbose

# Release build with optimizations
cmake --build . --config Release --target testGrpcApi
```

### Development Setup
1. **Set Startup Project**: Right-click `testGrpcApi` → "Set as Startup Project"
2. **Working Directory**: Automatically set to `bin/` directory
3. **Debugging**: F5 to run with debugger attached

## Integration Notes

### Shared Component Usage
- **CameraSyncLiveLink**: gRPC communication with Octane
- **ActivityLogger**: Thread-safe logging system
- **PerformanceTracker**: FPS and performance monitoring
- **ModernRenderer**: OpenGL-based 3D rendering

### Protocol Buffer Integration
- Uses shared protobuf generation system
- Generated files in `shared/protos/`
- Automatic dependency management

## Support

### Getting Help
1. **Check Latest Commit**: Ensure you have the latest fixes
2. **Review Build Output**: Look for specific error messages
3. **Verify Prerequisites**: Confirm Visual Studio 2022 installation
4. **Clean Build**: Delete `build/` directory and regenerate

### Known Working Configuration
- **OS**: Windows 10/11
- **IDE**: Visual Studio 2022 (17.x)
- **Architecture**: x64
- **Runtime**: Static linking (/MT)
- **CMake**: 3.16+

---

**Last Updated**: 2025-01-15  
**Status**: ✅ All known Windows build issues resolved  
**Commit**: Latest main branch includes all fixes