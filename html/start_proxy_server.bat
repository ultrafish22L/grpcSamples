@echo off
REM HTML Demo Proxy Server Startup Script
REM This script builds dependencies and starts the gRPC proxy server for HTML demos

echo ========================================
echo HTML Demo Proxy Server Startup
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

REM Navigate to project root
cd ..
if not exist "CMakeLists.txt" (
    echo ERROR: Cannot find project root CMakeLists.txt
    echo Make sure you're running this from the html/ subdirectory
    echo.
    pause
    exit /b 1
)

echo Step 1: Installing Python dependencies...
echo ----------------------------------------
python -m pip install grpcio grpcio-tools aiohttp
if %ERRORLEVEL% neq 0 (
    echo ERROR: Failed to install Python dependencies
    echo Make sure Python is installed and accessible
    echo.
    pause
    exit /b 1
)

echo.
echo Step 2: Generating Python protobuf files...
echo -------------------------------------------

REM Check if build directory exists
if not exist "build" (
    echo Creating build directory...
    mkdir build
)

cd build

REM Generate protobuf files using CMake
echo Running CMake protobuf generation...
cmake --build . --target python_protobuf_generation
if %ERRORLEVEL% neq 0 (
    echo WARNING: CMake protobuf generation failed, trying manual generation...
    
    REM Fallback: Manual protobuf generation
    cd ..
    if not exist "shared\generated" mkdir shared\generated
    
    echo Generating protobuf files manually...
    python -m grpc_tools.protoc ^
        --proto_path=shared/protos/definitions ^
        --python_out=shared/generated ^
        --grpc_python_out=shared/generated ^
        shared/protos/definitions/livelink.proto ^
        shared/protos/definitions/camera_control.proto
    
    if %ERRORLEVEL% neq 0 (
        echo ERROR: Manual protobuf generation also failed
        echo Check that protobuf files exist in shared/protos/definitions/
        echo.
        pause
        exit /b 1
    )
    
    cd build
)

cd ..

echo.
echo Step 3: Checking generated files...
echo ----------------------------------
if exist "shared\generated\livelink_pb2.py" (
    echo ✓ livelink_pb2.py generated successfully
) else (
    echo ✗ livelink_pb2.py not found
)

if exist "shared\generated\livelink_pb2_grpc.py" (
    echo ✓ livelink_pb2_grpc.py generated successfully
) else (
    echo ✗ livelink_pb2_grpc.py not found
)

if exist "shared\generated\camera_control_pb2.py" (
    echo ✓ camera_control_pb2.py generated successfully
) else (
    echo ✗ camera_control_pb2.py not found
)

echo.
echo Step 4: Starting gRPC proxy server...
echo ------------------------------------
echo Server will run on: http://127.0.0.1:51023
echo Octane connection: 127.0.0.1:51022
echo.
echo ⚠️  IMPORTANT: You also need the HTTP server for HTML demos!
echo    Open another terminal and run: start_http_server.bat
echo    Then visit: http://localhost:8000/grpc_test.html
echo.
echo Press Ctrl+C to stop the server
echo.

REM Start the proxy server
cd proxy
python grpc_proxy.py

REM If we get here, the server stopped
echo.
echo Proxy server stopped.
pause