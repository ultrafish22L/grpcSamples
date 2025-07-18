@echo off
REM Simple Test Proxy Server Launcher for Windows
REM Tests ObjectPtr passing between Octane gRPC APIs

echo.
echo ========================================
echo   Simple Test Proxy Server Launcher
echo ========================================
echo.
echo This proxy tests ObjectPtr passing with real Octane:
echo - Connects to Octane at host.docker.internal:51022
echo - Runs on http://localhost:51024
echo - Tests rootNodeGraph -^> name API chain
echo.

REM Check if Python is available
python --version >nul 2>&1
if errorlevel 1 (
    echo ❌ ERROR: Python not found in PATH
    echo Please install Python 3.7+ and add it to your PATH
    pause
    exit /b 1
)

REM Check if we're in the correct directory
if not exist "simple_test_proxy.py" (
    echo ❌ ERROR: simple_test_proxy.py not found
    echo Please run this script from the grpcSamples directory
    pause
    exit /b 1
)

REM Check if protobuf files exist
if not exist "proxy\apiprojectmanager_pb2.py" (
    echo ❌ ERROR: Protobuf files not found in proxy\ directory
    echo Please ensure the protobuf files are generated
    pause
    exit /b 1
)

echo ✅ Python found
echo ✅ simple_test_proxy.py found
echo ✅ Protobuf files found
echo.

echo 🚀 Starting Simple Test Proxy Server...
echo.
echo Server will run on: http://localhost:51024
echo Octane connection: host.docker.internal:51022
echo.
echo Available endpoints:
echo   POST /octaneapi.ApiProjectManagerService/rootNodeGraph
echo   POST /octaneapi.ApiItemService/name
echo.
echo Press Ctrl+C to stop the server
echo.

REM Start the proxy server
python simple_test_proxy.py

echo.
echo Server stopped.
pause