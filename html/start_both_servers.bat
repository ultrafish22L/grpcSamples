@echo off
REM Combined HTML Demo Server Startup Script
REM This script starts both the gRPC proxy server and HTTP server simultaneously

echo ========================================
echo HTML Demo - Start Both Servers
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

echo This script will start both servers required for HTML demos:
echo   1. gRPC Proxy Server (port 51023) - translates HTTP to gRPC
echo   2. HTTP Server (port 8000) - serves HTML demo files
echo.
echo WARNING:  Make sure Octane Render is running with LiveLink enabled!
echo.

REM Start the proxy server in a new window
echo Starting gRPC proxy server in new window...
start "gRPC Proxy Server" cmd /k "start_proxy_server.bat"

REM Wait a moment for the proxy to start
echo Waiting 3 seconds for proxy server to initialize...
timeout /t 3 /nobreak >nul

REM Start the HTTP server in another new window
echo Starting HTTP server in new window...
start "HTTP Server" cmd /k "start_http_server.bat"

echo.
echo SUCCESS: Both servers are starting in separate windows:
echo   • gRPC Proxy Server: http://127.0.0.1:51023
echo   • HTTP Server: http://localhost:8000
echo.
echo 🎮 Open these URLs in your browser:
echo   • Debug Tool: http://localhost:8000/grpc_test.html
echo   • 3D Demo: http://localhost:8000/web3d_octane_sync.html
echo.
echo 🛑 To stop servers: Close the server windows or press Ctrl+C in each
echo.
echo Press any key to exit this launcher...
pause >nul