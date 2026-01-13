@echo off
REM Octane Icon Extraction Wrapper Script (Windows)
REM Extracts all Octane icons via gRPC and saves them for octaneWebR

setlocal
cd /d "%~dp0"

echo ==================================================
echo 🎨 Octane Icon Extraction Tool
echo ==================================================
echo.

REM Check if Python is available
python --version >nul 2>&1
if errorlevel 1 (
    echo ❌ Python not found in PATH
    echo    Please install Python 3.7+ and add to PATH
    pause
    exit /b 1
)

REM Check Python dependencies
echo 🔍 Checking Python dependencies...
python -c "import grpc, google.protobuf" >nul 2>&1
if errorlevel 1 (
    echo ⚠️  Missing Python dependencies
    echo    Installing grpcio and protobuf...
    pip install grpcio protobuf
)

REM Run extraction
echo.
echo 🚀 Starting icon extraction...
echo    Make sure Octane is running with LiveLink enabled
echo    (Help → LiveLink in Octane menu)
echo.
python extract_icons.py

if errorlevel 1 (
    echo.
    echo ❌ Icon extraction failed
    echo    Check that Octane is running with LiveLink enabled
    pause
    exit /b 1
)

echo.
echo ✅ Done! Check octaneWebR\client\public\icons\
pause
