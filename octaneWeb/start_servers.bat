@echo off
REM ========================================
REM OctaneWeb Complete Server Launcher
REM ========================================
REM Starts both the HTTP-to-gRPC proxy server
REM and the web server for octaneWeb
REM ========================================

echo.
echo ========================================
echo  OctaneWeb Complete Server Launcher
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
if not exist "..\octaneProxy\octane_proxy.py" (
    echo ERROR: Octane proxy server not found
    echo Expected location: octane_proxy.py
    echo Please ensure the proxy directory exists with octane_proxy.py
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
python -c "import grpcio, aiohttp, numpy" >nul 2>&1
if errorlevel 1 (
    echo WARNING: Required packages not found
    echo Installing core packages: grpcio, aiohttp, protobuf, numpy...
    pip install grpcio aiohttp protobuf numpy
    if errorlevel 1 (
        echo ERROR: Failed to install core packages
        echo Please run manually: pip install grpcio aiohttp protobuf numpy
        echo.
        pause
        exit /b 1
    )
)

echo Core packages found ✓

echo.
echo Checking optional packages for enhanced functionality...
python -c "import PIL" >nul 2>&1
if errorlevel 1 (
    echo Installing Pillow for PNG export functionality...
    pip install Pillow
    if errorlevel 1 (
        echo WARNING: Failed to install Pillow (PNG export will be disabled)
        echo This is not critical - the system will work without it
    ) else (
        echo Pillow installed ✓ (PNG export enabled)
    )
) else (
    echo Pillow found ✓ (PNG export enabled)
)

echo.
echo ========================================
echo  Starting Servers...
echo ========================================
echo.
echo Proxy Server: http://localhost:51023
echo Web Server:   http://localhost:8080
echo Octane Target: Auto-detected (127.0.0.1:51022 on Windows)
echo.
echo NETWORKING: The proxy automatically detects your environment:
echo - Windows/Native: Uses 127.0.0.1:51022 for Octane
echo - Docker/Sandbox: Uses host.docker.internal:51022 for Octane
echo - Override: Set SANDBOX_USE_HOST_NETWORK=true for Docker mode
echo.
echo Test Endpoints:
echo - Proxy Health: http://localhost:51023/health
echo - Web App:      http://localhost:8080/
echo.
echo IMPORTANT:
echo 1. Make sure Octane Render is running with LiveLink enabled
echo 2. Both servers will start automatically
echo 3. Open http://localhost:8080/ in your browser
echo 4. Press Ctrl+C in either window to stop servers
echo.

REM Start the proxy server in background
echo Starting proxy server...
start "OctaneWeb Proxy" cmd /k "cd ..\octaneProxy && python octane_proxy.py"

REM Wait a moment for proxy to start
timeout /t 3 /nobreak >nul

REM Start the web server
echo Starting web server...
echo Web server running at: http://localhost:8080/
echo.
echo ========================================
echo  Both Servers Running!
echo ========================================
echo.
echo Open in browser: http://localhost:8080/
echo Press any key to stop all servers...
echo.

python -m http.server 8080

REM If we get here, the web server stopped
echo.
echo ========================================
echo  Servers Stopped
echo ========================================
echo.
echo Note: The proxy server window may still be open.
echo Close it manually if needed.
echo.
pause