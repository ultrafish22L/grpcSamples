@echo off
REM Development Environment Launcher
REM Starts both Mock Octane server and Proxy server for HTML development

echo ========================================
echo Development Environment Launcher
echo ========================================
echo.

echo This script starts both servers needed for HTML development:
echo   1. Mock Octane gRPC Server (replaces Octane Render)
echo   2. Proxy Server (translates HTTP to gRPC)
echo.
echo After both servers start, you can open:
echo   - index.html (WebGL viewer with Octane sync)
echo.

REM Check if we're in the project root
if not exist "CMakeLists.txt" (
    echo ERROR: This script must be run from the project root directory
    echo Current directory: %CD%
    echo Expected file: CMakeLists.txt
    echo.
    pause
    exit /b 1
)

echo Step 1: Starting Mock Octane gRPC Server...
echo -------------------------------------------
start "Mock Octane Server" cmd /k "cd mock_octane && start_mock_octane.bat"

REM Wait a moment for the mock server to start
timeout /t 3 /nobreak >nul

echo Step 2: Starting Proxy Server...
echo --------------------------------
start "Proxy Server" cmd /k "cd html && start_proxy.bat"

echo.
echo ✅ Both servers are starting in separate windows:
echo   📭 Mock Octane Server: 127.0.0.1:51022
echo   🔄 Proxy Server: 127.0.0.1:51023
echo.
echo 🎮 Next steps:
echo   1. Wait for both servers to fully start
echo   2. Open html/index.html in your browser
echo.
echo Press any key to exit this launcher...
pause >nul