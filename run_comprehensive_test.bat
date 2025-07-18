@echo off
REM Comprehensive Octane gRPC API Test Suite - Windows Launcher
REM 
REM This batch file launches the comprehensive Octane API test suite on Windows.
REM It automatically detects the correct host (127.0.0.1 for Windows) and runs
REM all available tests against a live Octane instance.
REM
REM Prerequisites:
REM - Python 3.7+ installed and in PATH
REM - Octane Render running with LiveLink enabled on port 51022
REM - Required Python packages: grpcio, protobuf
REM
REM Usage:
REM   run_comprehensive_test.bat                    (uses 127.0.0.1:51022)
REM   run_comprehensive_test.bat <host>             (custom host)
REM   run_comprehensive_test.bat <host> <port>      (custom host and port)

echo.
echo 🔥 COMPREHENSIVE OCTANE gRPC API TEST SUITE - WINDOWS LAUNCHER
echo ================================================================
echo.

REM Check if Python is available
python --version >nul 2>&1
if errorlevel 1 (
    echo ❌ ERROR: Python is not installed or not in PATH
    echo Please install Python 3.7+ and add it to your PATH
    echo Download from: https://www.python.org/downloads/
    pause
    exit /b 1
)

REM Check if we're in the correct directory
if not exist "comprehensive_octane_test.py" (
    echo ❌ ERROR: comprehensive_octane_test.py not found
    echo Please run this batch file from the grpcSamples directory
    pause
    exit /b 1
)

REM Check if proxy directory exists (needed for protobuf imports)
if not exist "proxy" (
    echo ❌ ERROR: proxy directory not found
    echo Please ensure the proxy directory with protobuf files exists
    pause
    exit /b 1
)

echo ✅ Python found: 
python --version

echo ✅ Test script found: comprehensive_octane_test.py
echo ✅ Proxy directory found: proxy/
echo.

REM Check if Octane is running (optional check)
echo 🔍 Checking if Octane is running on port 51022...
netstat -an | findstr ":51022" >nul 2>&1
if errorlevel 1 (
    echo ⚠️  WARNING: No service detected on port 51022
    echo    Make sure Octane Render is running with LiveLink enabled
    echo    You can still run the test - it will show connection errors if Octane is not available
    echo.
) else (
    echo ✅ Service detected on port 51022 - likely Octane LiveLink
    echo.
)

REM Install required packages if needed
echo 📦 Checking Python dependencies...
python -c "import grpc, google.protobuf" >nul 2>&1
if errorlevel 1 (
    echo ⚠️  Installing required Python packages...
    pip install grpcio protobuf
    if errorlevel 1 (
        echo ❌ ERROR: Failed to install required packages
        echo Please install manually: pip install grpcio protobuf
        pause
        exit /b 1
    )
    echo ✅ Dependencies installed successfully
    echo.
)

echo 🚀 LAUNCHING COMPREHENSIVE OCTANE API TEST SUITE
echo ================================================
echo.

REM Run the test with any provided arguments
if "%~1"=="" (
    REM No arguments - use auto-detection
    python comprehensive_octane_test.py
) else if "%~2"=="" (
    REM Host provided
    python comprehensive_octane_test.py %1
) else (
    REM Host and port provided
    python comprehensive_octane_test.py %1 %2
)

REM Capture exit code
set TEST_EXIT_CODE=%errorlevel%

echo.
echo ================================================================
if %TEST_EXIT_CODE%==0 (
    echo 🎉 TEST SUITE COMPLETED SUCCESSFULLY!
    echo All tests passed or completed with acceptable results.
) else (
    echo 💥 TEST SUITE COMPLETED WITH ISSUES
    echo Some tests failed or encountered errors.
    echo Check the output above for details.
)

echo.
echo 📊 Test Results Summary:
echo - Exit Code: %TEST_EXIT_CODE%
echo - Log: Check console output above for detailed results
echo - Created Objects: Any nodes created during testing
echo.

REM Keep window open so user can see results
echo Press any key to close this window...
pause >nul

exit /b %TEST_EXIT_CODE%