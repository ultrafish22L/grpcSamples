@echo off
REM ========================================
REM OctaneWeb Proxy Server Launcher
REM ========================================
REM This script starts the HTTP-to-gRPC proxy server
REM required for octaneWeb to communicate with Octane LiveLink
REM ========================================

echo.
echo ========================================
echo  OctaneWeb Proxy Server Launcher
echo ========================================
echo.

REM Check if we're in the correct directory
if not exist "index.html" (
    echo ERROR: This script must be run from the octaneWeb folder
    echo Current directory: %CD%
    echo Expected files: index.html, js/, css/
    echo.
    pause
    exit /b 1
)

REM Check if proxy directory exists
if not exist "..\proxy\grpc_proxy.py" (
    echo ERROR: Proxy server not found
    echo Expected location: ..\proxy\grpc_proxy.py
    echo Please ensure you're in the correct grpcSamples directory structure
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
python -c "import grpcio, aiohttp" >nul 2>&1
if errorlevel 1 (
    echo WARNING: Required packages not found
    echo Installing grpcio and aiohttp...
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
echo Proxy will run on: http://localhost:51023
echo Octane LiveLink:   127.0.0.1:51022
echo.
echo IMPORTANT:
echo 1. Make sure Octane Render is running with LiveLink enabled
echo 2. Open octaneWeb in browser: file:///%CD%\index.html
echo 3. Press Ctrl+C to stop the proxy server
echo.

REM Change to proxy directory and start server
cd ..\proxy
python grpc_proxy.py

REM If we get here, the server stopped
echo.
echo ========================================
echo  Proxy Server Stopped
echo ========================================
echo.
pause