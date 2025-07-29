@echo off
setlocal enabledelayedexpansion

REM 🚀 Complete Octane Protobuf Build Script (Windows)
REM Generates both shared and SDK Python protobuf files for octaneProxy

echo 🚀 Complete Octane Protobuf Build Script
echo =======================================

echo 📋 This script will generate:
echo    1. Shared protobuf files (livelink.proto, camera_control.proto)
echo    2. Essential SDK protobuf files (Octane API)
echo    3. Combined generated/ directory for octaneProxy

REM Step 1: Generate shared protobuf files
echo.
echo 🔄 Step 1: Generating shared protobuf files...
call build_shared_protos.bat
if errorlevel 1 (
    echo ❌ Failed to generate shared protobuf files
    exit /b 1
)
echo ✅ Shared protobuf files generated successfully

REM Step 2: Generate essential SDK protobuf files
echo.
echo 🔄 Step 2: Generating essential SDK protobuf files...
call build_essential_protos.bat
if errorlevel 1 (
    echo ❌ Failed to generate essential SDK protobuf files
    exit /b 1
)
echo ✅ Essential SDK protobuf files generated successfully

REM Summary
echo.
echo 📊 Complete Build Summary
echo =========================

REM Count files
set TOTAL_FILES=0
for %%f in ("generated\*.py") do set /a TOTAL_FILES+=1

set SHARED_FILES=0
for %%f in ("generated\*livelink*" "generated\*camera_control*") do (
    if exist "%%f" set /a SHARED_FILES+=1
)

set /a SDK_FILES=TOTAL_FILES-SHARED_FILES-1

echo 📁 Total Python files generated: %TOTAL_FILES%
echo 📁 Shared protobuf files: %SHARED_FILES%
echo 📁 SDK protobuf files: %SDK_FILES%

echo.
echo 📋 Key generated files:
echo    Shared LiveLink API:
echo      - livelink_pb2.py / livelink_pb2_grpc.py
echo      - camera_control_pb2.py / camera_control_pb2_grpc.py
echo    Essential Octane SDK:
echo      - apinodesystem_pb2.py / apinodesystem_pb2_grpc.py
echo      - apiprojectmanager_pb2.py / apiprojectmanager_pb2_grpc.py
echo      - apirender_pb2.py / apirender_pb2_grpc.py
echo      - common_pb2.py and core dependencies

echo.
echo 🎉 All protobuf files generated successfully!
echo 💡 octaneProxy now has access to both shared LiveLink API and full Octane SDK
echo 🚀 Ready to run: python octane_proxy.py