@echo off
setlocal enabledelayedexpansion

REM Windows Visual Studio 2022 Build Script for gRPC Samples
REM Builds GLEW using Visual Studio project files (Windows standard approach)
REM Automatically handles protobuf submodule and header generation

echo ========================================
echo gRPC Samples - Windows Build Script
echo ========================================
echo.

if "%1"=="help" goto :help
if "%1"=="clean" goto :clean_build
if "%1"=="/?" goto :help
if "%1"=="-h" goto :help

goto :main_build

:help
echo Usage: win-vs2022.bat [clean^|help]
echo.
echo This script builds the gRPC Samples project for Windows using Visual Studio 2022.
echo.
echo Commands:
echo   (no args)  - Build the project (default)
echo   clean      - Clean all build artifacts and rebuild from scratch
echo   help       - Show this help message
echo.
echo Features:
echo - Uses Visual Studio project files for GLEW (Windows standard approach)
echo - Automatically initializes protobuf submodule
echo - Generates required protobuf headers
echo - Automatically skips GLEW build if files already exist
echo - Use 'clean' option to force GLEW rebuild when needed
echo.
echo Requirements:
echo - Visual Studio 2022 with C++ development tools
echo - CMake 3.15 or later
echo.
echo Note: GLEW is built using official Visual Studio project files (build/vc15/).
echo This is the recommended Windows approach and does not require Unix tools.
echo.
goto :end

:main_build

echo Checking Visual Studio installation...
where msbuild >nul 2>&1
if %ERRORLEVEL% NEQ 0 echo Error: MSBuild not found. Please install Visual Studio 2022 with C++ development tools. && goto :error

echo Checking CMake installation...
where cmake >nul 2>&1
if %ERRORLEVEL% NEQ 0 echo Error: CMake not found. Please install CMake 3.15 or later. && goto :error

echo Initializing protobuf submodule...
git submodule update --init --recursive third_party/protobuf
if %ERRORLEVEL% NEQ 0 echo Warning: Failed to initialize protobuf submodule, but continuing...

echo.
echo ========================================
echo Building GLEW
echo ========================================

pushd third_party\glew

REM Check if GLEW is already built successfully
if exist src\glew.c if exist include\GL\glew.h if exist include\GL\wglew.h if exist lib\Release\x64\glew32.lib goto :glew_already_built
goto :build_glew_from_scratch

:glew_already_built
echo GLEW already built successfully - skipping GLEW build process
echo Found: src\glew.c, include\GL\glew.h, include\GL\wglew.h, lib\Release\x64\glew32.lib
echo Use 'win-vs2022 clean' to force GLEW rebuild if needed
goto :cmake_setup

:build_glew_from_scratch
echo Building GLEW using Visual Studio project files (Windows standard approach)...

REM Use Visual Studio project files for Windows (official GLEW recommendation)
echo Checking for Visual Studio project files...
if exist build\vc15\glew.sln goto :use_vs_projects
echo No Visual Studio project files found, checking source files for CMake build...
goto :verify_glew_sources

:use_vs_projects
echo Building GLEW with Visual Studio project files...
cd build\vc15

echo Building GLEW static library for x64 Release...

REM Try Visual Studio 2022 toolset first
echo Trying Visual Studio 2022 toolset (v143)...
msbuild glew_static.vcxproj /p:Configuration=Release /p:Platform=x64 /p:PlatformToolset=v143 /nologo /verbosity:minimal
if %ERRORLEVEL% EQU 0 goto :glew_vs_success

echo Visual Studio 2022 toolset not found, trying v142...
msbuild glew_static.vcxproj /p:Configuration=Release /p:Platform=x64 /p:PlatformToolset=v142 /nologo /verbosity:minimal
if %ERRORLEVEL% EQU 0 goto :glew_vs_success

echo Visual Studio 2019 toolset not found, trying v141...
msbuild glew_static.vcxproj /p:Configuration=Release /p:Platform=x64 /p:PlatformToolset=v141 /nologo /verbosity:minimal
if %ERRORLEVEL% EQU 0 goto :glew_vs_success

echo All Visual Studio toolsets failed
cd ..\..
goto :verify_glew_sources

:glew_vs_success
echo GLEW library built successfully with Visual Studio!
cd ..\..
goto :check_glew_completeness

:verify_glew_sources
echo Verifying GLEW source files for CMake build...
if exist src\glew.c echo GLEW source file found: src\glew.c
if not exist src\glew.c echo ERROR: Missing GLEW source file: src\glew.c && echo GLEW repository may be incomplete && goto :error

if exist include\GL\glew.h echo GLEW header file found: include\GL\glew.h  
if not exist include\GL\glew.h echo ERROR: Missing GLEW header file: include\GL\glew.h && echo GLEW repository may be incomplete && goto :error
if exist include\GL\wglew.h echo GLEW Windows header found: include\GL\wglew.h
if not exist include\GL\wglew.h echo ERROR: Missing GLEW Windows header: include\GL\wglew.h && echo GLEW repository may be incomplete && goto :error

:check_glew_completeness
echo All GLEW files verified successfully

:cmake_setup
popd

echo.
echo ========================================
echo Generating Protobuf Headers
echo ========================================

REM Generate protobuf well-known headers if needed
if exist third_party\protobuf\src\google\protobuf\any.proto goto :generate_protobuf_headers
echo Protobuf submodule not found, skipping header generation...
goto :cmake_configure

:generate_protobuf_headers
echo Generating protobuf well-known headers...
python generate_wellknown_protos.py
if %ERRORLEVEL% EQU 0 echo Protobuf headers generated successfully
if %ERRORLEVEL% NEQ 0 echo Warning: Failed to generate protobuf headers, but continuing...

:cmake_configure
if not exist build mkdir build
if not exist build\win-vs2022 mkdir build\win-vs2022

cd build\win-vs2022

echo.
echo ========================================
echo Generating Visual Studio Solution
echo ========================================

echo Generating Visual Studio 2022 solution...
cmake -G "Visual Studio 17 2022" -A x64 ../../

if %ERRORLEVEL% EQU 0 goto :cmake_success
echo.
echo Error: Failed to generate Visual Studio solution.
echo Please check that Visual Studio 2022 and CMake are properly installed.
goto :cmake_done

:cmake_success
echo.
echo ========================================
echo Build Complete!
echo ========================================
echo.
echo Success! Visual Studio solution generated at:
echo %CD%\GrpcSamples.sln
echo.
echo You can now open the solution in Visual Studio 2022 and build.

:cmake_done

popd
pause
goto :end

:clean_build
echo Cleaning all build artifacts...
if exist build rmdir /s /q build
if exist third_party\glew\lib rmdir /s /q third_party\glew\lib
if exist third_party\glew\bin rmdir /s /q third_party\glew\bin
echo Clean complete. Run without arguments to rebuild.
pause
goto :end

:error
echo.
echo ========================================
echo Build Failed
echo ========================================
echo.
echo Build failed. Please check the error messages above.
echo.
echo Common solutions:
echo 1. Install Visual Studio 2022 with C++ development tools
echo 2. Install CMake 3.15 or later
echo 3. Check that the GLEW submodule is properly initialized:
echo    git submodule update --init --recursive
echo 4. Try running 'win-vs2022 clean' to reset and rebuild
echo.
popd
pause
exit /b 1

:end