@echo off
REM 🚀 Octane Protobuf Build Script (Windows)
REM Generates Python protobuf files from Octane SDK proto definitions
REM 
REM Usage: build_protos.bat
REM Output: octaneProxy\generated\*.py files

setlocal enabledelayedexpansion

echo 🚀 Octane Protobuf Build Script
echo =================================

REM Get script directory
set "SCRIPT_DIR=%~dp0"
set "PROJECT_ROOT=%SCRIPT_DIR%.."

REM Define paths (normalize backslashes)
set "PROTO_SOURCE_DIR=%PROJECT_ROOT%\sdk\src\api\grpc\protodef"
set "OUTPUT_DIR=%SCRIPT_DIR%generated"

echo 📁 Source directory: %PROTO_SOURCE_DIR%
echo 📁 Output directory: %OUTPUT_DIR%

REM Verify source directory exists
if not exist "%PROTO_SOURCE_DIR%" (
    echo ❌ Error: Proto source directory not found: %PROTO_SOURCE_DIR%
    exit /b 1
)

REM Create output directory
echo 📂 Creating output directory...
if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

REM Clean existing generated files
echo 🧹 Cleaning existing generated files...
if exist "%OUTPUT_DIR%\*.py" del /q "%OUTPUT_DIR%\*.py"

REM Check if Python is available
python --version >nul 2>&1
if errorlevel 1 (
    echo ❌ Error: Python not found
    exit /b 1
)

REM Test grpc_tools availability
python -c "import grpc_tools.protoc" >nul 2>&1
if errorlevel 1 (
    echo ❌ Error: grpc_tools not installed. Run: pip install grpcio-tools
    exit /b 1
)

echo ✅ Tools verified

REM Count proto files
set PROTO_COUNT=0
for %%f in ("%PROTO_SOURCE_DIR%\*.proto") do (
    set /a PROTO_COUNT+=1
)
echo 📊 Found %PROTO_COUNT% proto files to process

REM Generate Python files from proto files
echo ⚙️  Generating Python protobuf files...

REM Define core files that should be processed first (dependencies)
set "CORE_FILES=common.proto octaneenums.proto octaneids.proto octanevectypes.proto octanetime.proto octaneinfos.proto octanenet.proto octaneimageexport.proto octanereferenceexport.proto octanerenderpasses.proto octanevolume.proto"

REM Files with known conflicts to skip
set "SKIP_FILES=apinodesystem_1.proto apinodesystem_2.proto apinodesystem_3.proto apinodesystem_4.proto apinodesystem_5.proto apinodesystem_6.proto apinodesystem_7.proto apinodesystem_8.proto"

set GENERATED_COUNT=0
set FAILED_COUNT=0

REM Process core files first
echo    Step 1: Processing core dependency files...
for %%f in (%CORE_FILES%) do (
    if exist "%PROTO_SOURCE_DIR%\%%f" (
        echo       Processing: %%f
        python -m grpc_tools.protoc --proto_path="%PROTO_SOURCE_DIR%" --python_out="%OUTPUT_DIR%" --grpc_python_out="%OUTPUT_DIR%" "%PROTO_SOURCE_DIR%\%%f" >nul 2>&1
        if errorlevel 1 (
            set /a FAILED_COUNT+=1
        ) else (
            set /a GENERATED_COUNT+=1
        )
    )
)

REM Process remaining files (excluding problematic ones)
echo    Step 2: Processing remaining API files...
for %%f in ("%PROTO_SOURCE_DIR%\*.proto") do (
    set "FILENAME=%%~nxf"
    set "SKIP_FILE=false"
    
    REM Check if it's a core file (already processed)
    for %%c in (%CORE_FILES%) do (
        if "!FILENAME!"=="%%c" set "SKIP_FILE=true"
    )
    
    REM Check if it's in the skip list
    for %%s in (%SKIP_FILES%) do (
        if "!FILENAME!"=="%%s" (
            set "SKIP_FILE=true"
            echo       Skipping problematic: !FILENAME!
        )
    )
    
    if "!SKIP_FILE!"=="false" (
        echo       Processing: !FILENAME!
        python -m grpc_tools.protoc --proto_path="%PROTO_SOURCE_DIR%" --python_out="%OUTPUT_DIR%" --grpc_python_out="%OUTPUT_DIR%" "%%f" >nul 2>&1
        if errorlevel 1 (
            set /a FAILED_COUNT+=1
        ) else (
            set /a GENERATED_COUNT+=1
        )
    )
)

REM Create __init__.py to make it a Python package
echo # Generated protobuf package > "%OUTPUT_DIR%\__init__.py"

REM Summary
echo 📊 Build Summary
echo ================
echo ✅ Successfully generated: %GENERATED_COUNT% files
if %FAILED_COUNT% gtr 0 (
    echo ❌ Failed to generate: %FAILED_COUNT% files
)

REM Count generated files
set GENERATED_FILES=0
for %%f in ("%OUTPUT_DIR%\*.py") do (
    set /a GENERATED_FILES+=1
)
echo 📁 Total Python files in output: %GENERATED_FILES%

REM Show some example files
echo 📋 Sample generated files:
set SHOWN_COUNT=0
for %%f in ("%OUTPUT_DIR%\*.py") do (
    if !SHOWN_COUNT! lss 5 (
        echo    %%~nxf
        set /a SHOWN_COUNT+=1
    )
)

if %GENERATED_FILES% gtr 5 (
    set /a REMAINING=%GENERATED_FILES%-5
    echo    ... and !REMAINING! more files
)

if %FAILED_COUNT% equ 0 (
    echo 🎉 Build completed successfully!
    echo    Generated files are ready in: %OUTPUT_DIR%
    exit /b 0
) else (
    echo ⚠️  Build completed with errors
    exit /b 1
)