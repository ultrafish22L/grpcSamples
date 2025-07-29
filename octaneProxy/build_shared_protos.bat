@echo off
setlocal enabledelayedexpansion

REM 🚀 Shared Protobuf Build Script for octaneProxy (Windows)
REM Generates Python protobuf files from shared/protos/definitions/

echo 🚀 Shared Protobuf Build Script
echo ================================

REM Get script directory
set "SCRIPT_DIR=%~dp0"
set "PROJECT_ROOT=%SCRIPT_DIR%.."

REM Define paths
set "SHARED_PROTO_DIR=%PROJECT_ROOT%\shared\protos\definitions"
set "OUTPUT_DIR=%SCRIPT_DIR%generated"

echo 📁 Source directory: %SHARED_PROTO_DIR%
echo 📁 Output directory: %OUTPUT_DIR%

REM Verify source directory exists
if not exist "%SHARED_PROTO_DIR%" (
    echo ❌ Source directory not found: %SHARED_PROTO_DIR%
    exit /b 1
)

REM Create output directory
echo 📂 Creating output directory...
if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

REM Clean existing files
echo 🧹 Cleaning existing shared protobuf files...
del /q "%OUTPUT_DIR%\livelink_pb2*.py" 2>nul
del /q "%OUTPUT_DIR%\camera_control_pb2*.py" 2>nul

REM Verify tools
echo 🔧 Verifying protobuf tools...
python -c "import grpc_tools.protoc" >nul 2>&1
if errorlevel 1 (
    echo ❌ grpcio-tools not found. Install with: pip install grpcio-tools
    exit /b 1
)
echo ✅ Tools verified

REM Generate Python files from shared proto files
echo ⚙️  Generating shared protobuf files...

set GENERATED_COUNT=0
set FAILED_COUNT=0

REM Process livelink.proto
if exist "%SHARED_PROTO_DIR%\livelink.proto" (
    echo    Processing: livelink.proto
    python -m grpc_tools.protoc --proto_path="%SHARED_PROTO_DIR%" --python_out="%OUTPUT_DIR%" --grpc_python_out="%OUTPUT_DIR%" "%SHARED_PROTO_DIR%\livelink.proto" >nul 2>&1
    if errorlevel 1 (
        echo    ❌ Failed: livelink.proto
        set /a FAILED_COUNT+=1
    ) else (
        echo    ✅ Success: livelink.proto
        set /a GENERATED_COUNT+=1
    )
) else (
    echo    ❌ Not found: livelink.proto
    set /a FAILED_COUNT+=1
)

REM Process camera_control.proto
if exist "%SHARED_PROTO_DIR%\camera_control.proto" (
    echo    Processing: camera_control.proto
    python -m grpc_tools.protoc --proto_path="%SHARED_PROTO_DIR%" --python_out="%OUTPUT_DIR%" --grpc_python_out="%OUTPUT_DIR%" "%SHARED_PROTO_DIR%\camera_control.proto" >nul 2>&1
    if errorlevel 1 (
        echo    ❌ Failed: camera_control.proto
        set /a FAILED_COUNT+=1
    ) else (
        echo    ✅ Success: camera_control.proto
        set /a GENERATED_COUNT+=1
    )
) else (
    echo    ❌ Not found: camera_control.proto
    set /a FAILED_COUNT+=1
)

REM Update __init__.py
echo # Generated protobuf package - includes both shared and SDK protobuf files > "%OUTPUT_DIR%\__init__.py"

REM Summary
echo 📊 Build Summary
echo ================
echo ✅ Successfully generated: %GENERATED_COUNT% shared protobuf files
if %FAILED_COUNT% gtr 0 (
    echo ❌ Failed to generate: %FAILED_COUNT% files
)

REM Count generated files
set SHARED_FILES=0
for %%f in ("%OUTPUT_DIR%\*livelink*" "%OUTPUT_DIR%\*camera_control*") do (
    if exist "%%f" set /a SHARED_FILES+=1
)
echo 📁 Total shared protobuf files: %SHARED_FILES%

if %FAILED_COUNT% equ 0 (
    echo 🎉 Shared protobuf files generated successfully!
    echo 💡 These files provide the LiveLinkService for camera control and mesh access
    exit /b 0
) else (
    echo ⚠️  Some files failed, but others may be available
    exit /b 1
)