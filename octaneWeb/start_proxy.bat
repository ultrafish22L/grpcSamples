@echo off
REM ========================================
REM OctaneWeb Custom Proxy Server Launcher
REM ========================================
REM Starts the custom HTTP-to-gRPC proxy server
REM optimized specifically for octaneWeb
REM ========================================

echo.
echo ========================================
echo  OctaneWeb Custom Proxy Server
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

REM Check if custom proxy exists
if not exist "octane_proxy.py" (
    echo ERROR: Custom proxy server not found
    echo Expected location: octane_proxy.py
    echo Please ensure the custom proxy is in the octaneWeb directory
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
echo  Starting Custom Proxy Server...
echo ========================================
echo.
echo Custom Proxy: http://localhost:51024
echo Octane Target: 127.0.0.1:51022
echo Health Check:  http://localhost:51024/health
echo Test Suite:    http://localhost:51024/test
echo.
echo IMPORTANT:
echo 1. Make sure Octane Render is running with LiveLink enabled
echo 2. Open octaneWeb in browser: file:///%CD%\index.html
echo 3. Press Ctrl+C to stop the proxy server
echo.

REM Start the custom proxy server
python octane_proxy.py

REM If we get here, the server stopped
echo.
echo ========================================
echo  Custom Proxy Server Stopped
echo ========================================
echo.
pause