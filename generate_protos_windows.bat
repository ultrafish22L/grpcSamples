@echo off
REM Manual protobuf generation script for Windows
REM Run this if CMake protobuf generation fails

echo Generating protobuf files for shared library...

REM Create generated directory
if not exist "shared\generated" mkdir "shared\generated"

REM Set paths (adjust these to match your protoc installation)
set PROTOC_PATH=third_party\protobuf\windows\release_64\protoc.exe
set GRPC_PLUGIN_PATH=third_party\grpc\windows\release_64\grpc_cpp_plugin.exe

REM Check if protoc exists
if not exist "%PROTOC_PATH%" (
    echo ERROR: protoc.exe not found at %PROTOC_PATH%
    echo Please install protobuf compiler or update the path in this script
    pause
    exit /b 1
)

REM Check if gRPC plugin exists
if not exist "%GRPC_PLUGIN_PATH%" (
    echo ERROR: grpc_cpp_plugin.exe not found at %GRPC_PLUGIN_PATH%
    echo Please install gRPC compiler or update the path in this script
    pause
    exit /b 1
)

REM Generate livelink.proto
echo Generating livelink.proto...
%PROTOC_PATH% --grpc_out=shared/generated --cpp_out=shared/generated --plugin=protoc-gen-grpc=%GRPC_PLUGIN_PATH% --proto_path=shared shared/livelink.proto

REM Generate camera_control.proto
echo Generating camera_control.proto...
%PROTOC_PATH% --grpc_out=shared/generated --cpp_out=shared/generated --plugin=protoc-gen-grpc=%GRPC_PLUGIN_PATH% --proto_path=shared shared/camera_control.proto

echo Done! Generated files are in shared/generated/
pause