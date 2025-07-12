@echo off
REM Mock Octane gRPC Server Launcher for Windows
REM Simulates Octane Render's LiveLink service for development and testing

echo ========================================
echo Mock Octane gRPC Server
echo ========================================
echo.

REM Check if we're in the correct directory
if not exist "mock_octane_server.py" (
    echo ERROR: This script must be run from the mock_octane/ directory
    echo Current directory: %CD%
    echo Expected file: mock_octane_server.py
    echo.
    pause
    exit /b 1
)

echo This script starts a mock Octane gRPC server for development and testing.
echo Use this when you don't have Octane Render available but want to test
echo the HTML applications and gRPC connectivity.
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
python -m pip install grpcio grpcio-tools asyncio
if errorlevel 1 (
    echo WARNING: Failed to install some Python packages
    echo Continuing anyway - packages might already be installed
)

echo.
echo Step 2: Checking protobuf files...
echo ---------------------------------
if not exist "..\proxy\livelink_pb2.py" (
    echo ERROR: Protobuf files not found!
    echo Please run the build process first to generate protobuf files.
    echo Expected location: ..\proxy\livelink_pb2.py
    echo.
    pause
    exit /b 1
)
echo ✓ Protobuf files found

echo.
echo Step 3: Starting Mock Octane gRPC server...
echo ------------------------------------------
echo Server will run on: 127.0.0.1:51022 (same as real Octane)
echo.
echo 🎭 MOCK SERVER FEATURES:
echo   - Simulates GetCamera/SetCamera operations
echo   - Provides mock mesh data (Cube, Sphere, Teapot)
echo   - Realistic camera state management
echo   - Statistics and logging
echo.
echo 🔧 USAGE:
echo   1. Start this mock server (replaces Octane Render)
echo   2. Start the proxy server: ..\html\start_proxy.bat
echo   3. Open HTML applications: index.html
echo.
echo Press Ctrl+C to stop the server
echo.

REM Start the mock server
python mock_octane_server.py

REM If we get here, the server stopped
echo.
echo Mock Octane server stopped.
pause