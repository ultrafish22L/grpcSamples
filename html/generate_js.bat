@echo off
REM Generate JavaScript files for HTML demos from proto definitions
REM This script uses the protoc-gen-grpc-web plugin built by CMake

echo Generating JavaScript files for HTML demos...

REM Check if protoc-gen-grpc-web plugin exists
if not exist "protoc-gen-grpc-web.exe" (
    echo ERROR: protoc-gen-grpc-web.exe not found in html directory
    echo Please build the project first using CMake on Windows
    echo The plugin is automatically built when configuring the project on Windows
    pause
    exit /b 1
)

REM Check if protoc exists in third_party (go up one directory)
set PROTOC_PATH=..\third_party\protobuf\windows\release_64\protoc.exe
if not exist "%PROTOC_PATH%" (
    set PROTOC_PATH=..\third_party\protobuf\windows\debug_64\protoc.exe
)
if not exist "%PROTOC_PATH%" (
    echo ERROR: protoc.exe not found in ..\third_party\protobuf\windows
    echo Please ensure protobuf libraries are properly installed
    pause
    exit /b 1
)

REM Create generated directory if it doesn't exist
if not exist "generated" mkdir generated

REM Generate JavaScript files from proto definitions
echo Using protoc: %PROTOC_PATH%
echo Using plugin: protoc-gen-grpc-web.exe

REM Create generated directory if it doesn't exist
if not exist "generated" mkdir generated

REM Generate JavaScript files from livelink.proto
echo Generating from livelink.proto...
%PROTOC_PATH% --proto_path=..\shared\protos --proto_path=..\third_party --js_out=import_style=commonjs:generated\ --grpc-web_out=import_style=commonjs,mode=grpcwebtext:generated\ --plugin=protoc-gen-grpc-web=protoc-gen-grpc-web.exe ..\shared\protos\livelink.proto

if %ERRORLEVEL% EQU 0 (
    echo Successfully generated JavaScript files in generated\
    echo Files generated:
    dir generated\
) else (
    echo ERROR: Failed to generate JavaScript files
    pause
    exit /b 1
)

echo.
echo JavaScript generation complete!
echo.
echo You can now use these files in your HTML demos:
echo - Import the generated *_pb.js files for message types
echo - Import the generated *_grpc_web_pb.js files for service clients
echo - Use with livelink.js for easy integration
echo.
echo The generated files will be placed in the 'generated' directory
echo and can be used by the HTML demos (grpc_test.html, web3d_octane_sync.html)

pause