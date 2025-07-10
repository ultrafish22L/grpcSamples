@echo off
REM Simplified Proxy Server Startup for file:// protocol usage
REM This script only starts the gRPC proxy server - no HTTP server needed

echo ========================================
echo gRPC Proxy Server (file:// protocol)
echo ========================================
echo.

REM Check if we're in the correct directory
if not exist "grpc_test.html" (
    echo ERROR: This script must be run from the html/ directory
    echo Current directory: %CD%
    echo Expected files: grpc_test.html, web3d_octane_sync.html
    echo.
    pause
    exit /b 1
)

echo This script starts ONLY the gRPC proxy server for file:// protocol usage.
echo No HTTP server needed - you can double-click the HTML files directly!
echo.
echo ⚠️  Make sure Octane Render is running with LiveLink enabled!
echo.

REM Check if Python is available
python --version >nul 2>&1
if errorlevel 1 (
    echo ERROR: Python not found in PATH
    echo Please install Python 3.7+ and add it to your PATH
    echo.
    pause
    exit /b 1
)

echo Step 1: Installing Python dependencies...
echo -----------------------------------------
python -m pip install grpcio grpcio-tools aiohttp
if errorlevel 1 (
    echo WARNING: Failed to install some Python packages
    echo Continuing anyway - packages might already be installed
)

echo.
echo Step 2: Checking protobuf files...
echo ---------------------------------

REM Check if protobuf files already exist
if exist "..\shared\generated\livelink_pb2.py" (
    if exist "..\shared\generated\livelink_pb2_grpc.py" (
        echo ✅ Protobuf files already exist, skipping generation
        goto :start_proxy
    )
)

echo Protobuf files not found, generating them...

REM Manual protobuf generation
cd ..
if not exist "shared\generated" mkdir shared\generated

echo Generating protobuf files manually...
python -m grpc_tools.protoc ^
    --proto_path=shared/protos/definitions ^
    --python_out=shared/generated ^
    --grpc_python_out=shared/generated ^
    shared/protos/definitions/livelink.proto ^
    shared/protos/definitions/camera_control.proto

if errorlevel 1 (
    echo ❌ Manual protobuf generation failed
    echo Make sure grpcio-tools is installed: pip install grpcio-tools
    echo Please check that protobuf files exist in shared/protos/definitions/
    cd html
    pause
    exit /b 1
)
echo ✅ Protobuf generation successful
cd html

:start_proxy
echo.
echo Step 3: Starting gRPC proxy server...
echo ------------------------------------
echo Server will run on: http://127.0.0.1:51023
echo Octane connection: 127.0.0.1:51022
echo.
echo 🎮 Usage:
echo   1. Double-click grpc_test.html (opens in browser via file://)
echo   2. Double-click web3d_octane_sync.html (opens in browser via file://)
echo   3. No HTTP server needed!
echo.
echo Press Ctrl+C to stop the server
echo.

REM Start the proxy server
cd ..\proxy
python grpc_proxy.py