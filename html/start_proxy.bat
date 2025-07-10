@echo off
REM gRPC Proxy Server Launcher
REM Starts the gRPC-Web proxy server for HTML applications

echo ========================================
echo gRPC Proxy Server for HTML Applications
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

echo This script starts the gRPC proxy server for HTML applications.
echo The proxy translates HTTP requests from browsers to gRPC calls to Octane.
echo.
echo WARNING: Make sure Octane Render is running with LiveLink enabled!
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
python -m pip install grpcio grpcio-tools aiohttp aiohttp-cors
if errorlevel 1 (
    echo WARNING: Failed to install some Python packages
    echo Continuing anyway - packages might already be installed
)

echo.
echo Step 2: Starting gRPC proxy server...
echo ------------------------------------
echo Server will run on: http://127.0.0.1:51023
echo Octane connection: 127.0.0.1:51022
echo.
echo 🎮 Usage:
echo   1. Open grpc_test.html in your browser (any HTTP server or file://)
echo   2. Open web3d_octane_sync.html in your browser
echo   3. Both applications will connect through this proxy to Octane
echo.
echo Press Ctrl+C to stop the server
echo.

REM Start the proxy server
cd ..\proxy
python grpc_proxy.py

REM If we get here, the server stopped
echo.
echo Proxy server stopped.
pause