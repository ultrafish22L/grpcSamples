@echo off
REM ========================================
REM Octane gRPC Proxy Server for Windows
REM ========================================
REM Simple launcher for the gRPC proxy server
REM Uses correct port 51023 and Windows networking
REM ========================================

echo.
echo ========================================
echo  Octane gRPC Proxy Server
echo ========================================
echo.

REM Check if we're in the correct directory
if not exist "grpc_proxy.py" (
    echo ERROR: This script must be run from the proxy folder
    echo Current directory: %CD%
    echo Expected file: grpc_proxy.py
    echo.
    pause
    exit /b 1
)

echo Checking Python installation...
python --version >nul 2>&1
if errorlevel 1 (
    echo ERROR: Python not found in PATH
    echo Please install Python 3.7+ and add it to your PATH
    echo Download from: https://python.org/downloads/
    echo.
    pause
    exit /b 1
)

echo Python found: 
python --version

echo.
echo Checking required Python packages...
python -c "import grpcio, aiohttp, protobuf" >nul 2>&1
if errorlevel 1 (
    echo WARNING: Required packages not found
    echo Installing grpcio, aiohttp, and protobuf...
    pip install grpcio aiohttp protobuf
    if errorlevel 1 (
        echo ERROR: Failed to install required packages
        echo Please run manually: pip install grpcio aiohttp protobuf
        echo.
        pause
        exit /b 1
    )
)

echo Required packages found ✓

echo.
echo ========================================
echo  Starting Proxy Server...
echo ========================================
echo.
echo Proxy Server: http://localhost:51023
echo Octane Target: 127.0.0.1:51022 (Windows native)
echo Health Check: http://localhost:51023/health
echo.
echo IMPORTANT:
echo 1. Make sure Octane Render is running with LiveLink enabled
echo 2. Octane should be accessible at 127.0.0.1:51022
echo 3. Press Ctrl+C to stop the server
echo.

REM Start the proxy server with Windows-specific settings
python grpc_proxy.py --port 51023 --octane-host 127.0.0.1 --octane-port 51022

echo.
echo ========================================
echo  Proxy Server Stopped
echo ========================================
echo.
pause