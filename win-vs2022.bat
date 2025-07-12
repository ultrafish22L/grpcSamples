@echo off
setlocal

REM Check for clean argument
if /i "%~1"=="clean" goto :clean_only

REM Check for help argument  
if /i "%~1"=="help" goto :show_help
if /i "%~1"=="/?" goto :show_help
if /i "%~1"=="-h" goto :show_help

REM If we get here, run the normal build
goto :main_build

:clean_only
echo Cleaning GLEW build artifacts and forcing rebuild...
cd third_party\glew

REM Remove auto-generation artifacts
echo Removing auto-generation artifacts...
if exist auto\OpenGL-Registry rmdir /s /q auto\OpenGL-Registry
if exist auto\EGL-Registry rmdir /s /q auto\EGL-Registry
if exist auto\OpenGL-Registry-master rmdir /s /q auto\OpenGL-Registry-master
if exist auto\EGL-Registry-master rmdir /s /q auto\EGL-Registry-master
if exist auto\glfixes rmdir /s /q auto\glfixes
for %%f in (auto\*.tmp auto\*.zip auto\*.tar auto\*.gz) do if exist "%%f" del /q "%%f"

REM Remove generated source files
echo Removing generated source files...
if exist src\glew.c del /q src\glew.c
if exist include\GL\glew.h del /q include\GL\glew.h
if exist include\GL\wglew.h del /q include\GL\wglew.h

REM Remove built library files
echo Removing built library files...
if exist lib\Release rmdir /s /q lib\Release
if exist lib\Debug rmdir /s /q lib\Debug
if exist bin\Release rmdir /s /q bin\Release
if exist bin\Debug rmdir /s /q bin\Debug

echo ✓ GLEW cleanup completed - next build will regenerate all GLEW files
cd ..\..
goto :end

:show_help
echo.
echo GrpcSamples Windows Build Script
echo ================================
echo.
echo Usage: win-vs2022.bat [option]
echo.
echo Options:
echo   clean    - Force complete GLEW rebuild (removes all generated files)
echo   help     - Show this help message
echo   ^(none^)   - Build Visual Studio 2022 solution (skips GLEW if already built)
echo.
echo This script will:
echo 1. Check if GLEW is already built (skip if complete)
echo 2. Verify GLEW pre-built source files exist (no auto-generation needed)
echo 3. Build GLEW library using MSBuild/Visual Studio (if needed)
echo 4. Configure CMake for Visual Studio 2022
echo 5. Generate Visual Studio solution files
echo.
echo GLEW Build Optimization:
echo - Automatically skips GLEW build if files already exist
echo - Use 'clean' option to force GLEW rebuild when needed
echo.
echo Requirements:
echo - Visual Studio 2022 with C++ development tools
echo - CMake 3.15 or later
echo - Git (for GLEW auto-generation)
echo - Make utility (winget install GnuWin32.Make)
echo.
goto :end

:main_build

echo Building GrpcSamples Visual Studio 2022 Solution...
echo.

pushd .

echo Generating GLEW extensions and source files...
cd third_party\glew

REM Check if GLEW is already built successfully
if exist src\glew.c if exist include\GL\glew.h if exist include\GL\wglew.h if exist lib\Release\x64\glew32.lib goto :glew_already_built
goto :build_glew_from_scratch

:glew_already_built
echo ✓ GLEW already built successfully - skipping GLEW build process
echo   Found: src\glew.c, include\GL\glew.h, include\GL\wglew.h, lib\Release\x64\glew32.lib
echo   Use 'win-vs2022 clean' to force GLEW rebuild if needed
goto :cmake_setup

:build_glew_from_scratch
echo Building GLEW using pre-built source files...

REM GLEW repository includes pre-generated source files, no auto-generation needed
echo ✓ Using pre-built GLEW source files (skipping auto-generation)

REM Verify that essential GLEW files exist in the repository
if exist src\glew.c echo ✓ GLEW source file found: src\glew.c
if not exist src\glew.c echo ✗ Missing GLEW source file: src\glew.c && echo Error: GLEW repository incomplete && goto :error

if exist include\GL\glew.h echo ✓ GLEW header file found: include\GL\glew.h  
if not exist include\GL\glew.h echo ✗ Missing GLEW header file: include\GL\glew.h && echo Error: GLEW repository incomplete && goto :error
if exist include\GL\wglew.h echo ✓ GLEW Windows header found: include\GL\wglew.h
if not exist include\GL\wglew.h echo ✗ Missing GLEW Windows header: include\GL\wglew.h && echo Error: GLEW repository incomplete && goto :error

echo ✓ All GLEW source files verified successfully
    
REM Build GLEW library using Visual Studio
echo Building GLEW library with Visual Studio...
if exist build\vc12\glew.sln goto :build_glew_library
echo Warning: GLEW Visual Studio solution not found at build\vc12\glew.sln
echo GLEW library may not be available for linking
goto :continue_cmake

:build_glew_library
echo Found GLEW Visual Studio solution: build\vc12\glew.sln

REM Try to find MSBuild in common locations
if exist "%ProgramFiles%\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe" goto :use_vs2022_pro
if exist "%ProgramFiles%\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" goto :use_vs2022_com
if exist "%ProgramFiles%\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe" goto :use_vs2022_ent
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Professional\MSBuild\Current\Bin\MSBuild.exe" goto :use_vs2019_pro
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe" goto :use_vs2019_com
goto :try_path_msbuild

:use_vs2022_pro
echo Using MSBuild: VS2022 Professional
"%ProgramFiles%\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe" build\vc12\glew.sln /p:Configuration=Release /p:Platform=x64 /m
goto :check_build_result

:use_vs2022_com
echo Using MSBuild: VS2022 Community
"%ProgramFiles%\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" build\vc12\glew.sln /p:Configuration=Release /p:Platform=x64 /m
goto :check_build_result

:use_vs2022_ent
echo Using MSBuild: VS2022 Enterprise
"%ProgramFiles%\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe" build\vc12\glew.sln /p:Configuration=Release /p:Platform=x64 /m
goto :check_build_result

:use_vs2019_pro
echo Using MSBuild: VS2019 Professional
"%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Professional\MSBuild\Current\Bin\MSBuild.exe" build\vc12\glew.sln /p:Configuration=Release /p:Platform=x64 /m
goto :check_build_result

:use_vs2019_com
echo Using MSBuild: VS2019 Community
"%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe" build\vc12\glew.sln /p:Configuration=Release /p:Platform=x64 /m
goto :check_build_result

:try_path_msbuild
echo Warning: MSBuild not found in standard locations, trying PATH...
where msbuild >nul 2>&1
if %ERRORLEVEL% NEQ 0 goto :msbuild_not_found
echo Using MSBuild from PATH
msbuild build\vc12\glew.sln /p:Configuration=Release /p:Platform=x64 /m
goto :check_build_result

:msbuild_not_found
echo Warning: MSBuild not found, GLEW library may not be built
echo You may need to build build\vc12\glew.sln manually
goto :continue_cmake

:check_build_result
if %ERRORLEVEL% EQU 0 echo ✓ GLEW library built successfully
if %ERRORLEVEL% NEQ 0 echo Warning: GLEW library build failed, but continuing... && echo You may need to build build\vc12\glew.sln manually in Visual Studio

:continue_cmake
goto :check_existing_glew

:check_existing_glew
echo GLEW auto directory not found, checking for existing files...
if exist src\glew.c echo Using existing GLEW files && goto :cmake_setup
echo Error: No GLEW source files found and no auto-generation available
echo Please ensure the GLEW submodule is properly initialized
goto :error

:cmake_setup
cd ..\..

if not exist build mkdir build
if not exist build\win-vs2022 mkdir build\win-vs2022

cd build\win-vs2022

echo Generating Visual Studio 2022 solution...
cmake -G "Visual Studio 17 2022" -A x64 ../../

if %ERRORLEVEL% EQU 0 goto :cmake_success
echo.
echo Error: Failed to generate Visual Studio solution.
echo Please check that Visual Studio 2022 and CMake are properly installed.
goto :cmake_done

:cmake_success
echo.
echo Success! Visual Studio solution generated at:
echo %CD%\GrpcSamples.sln
echo.
echo You can now open the solution in Visual Studio 2022 and build.

:cmake_done

popd
pause
goto :end

:error
echo.
echo Build failed due to missing GLEW files.
echo.
echo To fix this issue:
echo 1. Check that the GLEW submodule is properly initialized:
echo    git submodule update --init --recursive
echo 2. Verify GLEW source files exist in third_party/glew/src/
echo 3. If using a custom GLEW version, ensure src/glew.c and include/GL/*.h exist
echo 4. Try running 'win-vs2022 clean' to reset and rebuild
echo.
popd
pause
exit /b 1

:end
