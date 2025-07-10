@echo off
REM HTML Demo HTTP Server Startup Script
REM This script starts a simple HTTP server to serve the HTML demo files

echo ========================================
echo HTML Demo HTTP Server Startup
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

echo Starting HTTP server for HTML demos...
echo Server URL: http://localhost:8000
echo.
echo ⚠️  IMPORTANT: You also need the gRPC proxy server running!
echo    Open another terminal and run: start_proxy_server.bat
echo    The proxy server must be running on port 51023
echo.
echo Available demos:
echo   • http://localhost:8000/grpc_test.html
echo   • http://localhost:8000/web3d_octane_sync.html
echo.
echo Press Ctrl+C to stop the server
echo.

REM Start Python HTTP server
python -m http.server 8000

REM If we get here, the server stopped
echo.
echo HTTP server stopped.
pause