@echo off
setlocal enabledelayedexpansion

REM Check for clean argument
if /i "%~1"=="clean" goto :clean_only

REM Check for help argument  
if /i "%~1"=="help" goto :show_help
if /i "%~1"=="/?" goto :show_help
if /i "%~1"=="-h" goto :show_help

REM If we get here, run the normal build
goto :main_build

:clean_only
echo Cleaning GLEW auto-generation artifacts...
cd third_party\glew
if exist auto\OpenGL-Registry rmdir /s /q auto\OpenGL-Registry
if exist auto\EGL-Registry rmdir /s /q auto\EGL-Registry
if exist auto\OpenGL-Registry-master rmdir /s /q auto\OpenGL-Registry-master
if exist auto\EGL-Registry-master rmdir /s /q auto\EGL-Registry-master
for %%f in (auto\*.tmp auto\*.zip auto\*.tar auto\*.gz) do if exist "%%f" del /q "%%f"
echo GLEW cleanup completed.
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
echo   clean    - Clean GLEW auto-generation artifacts only
echo   help     - Show this help message
echo   ^(none^)   - Build Visual Studio 2022 solution
echo.
echo This script will:
echo 1. Clean any corrupted GLEW artifacts
echo 2. Generate GLEW extensions and source files
echo 3. Build GLEW library using MSBuild/Visual Studio
echo 4. Configure CMake for Visual Studio 2022
echo 5. Generate Visual Studio solution files
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

REM Clean up any existing auto-generation artifacts that might be corrupted
echo Cleaning up existing GLEW auto-generation artifacts...
if exist auto\OpenGL-Registry (
    echo Removing OpenGL-Registry...
    rmdir /s /q auto\OpenGL-Registry 2>nul
    if exist auto\OpenGL-Registry (
        echo Warning: Could not remove OpenGL-Registry, trying alternative method...
        rd /s /q auto\OpenGL-Registry 2>nul
    )
)
if exist auto\EGL-Registry (
    echo Removing EGL-Registry...
    rmdir /s /q auto\EGL-Registry 2>nul
    if exist auto\EGL-Registry (
        echo Warning: Could not remove EGL-Registry, trying alternative method...
        rd /s /q auto\EGL-Registry 2>nul
    )
)
if exist auto\OpenGL-Registry-master (
    echo Removing OpenGL-Registry-master...
    rmdir /s /q auto\OpenGL-Registry-master 2>nul
)
if exist auto\EGL-Registry-master (
    echo Removing EGL-Registry-master...
    rmdir /s /q auto\EGL-Registry-master 2>nul
)
REM Clean up any partial downloads or temporary files
for %%f in (auto\*.tmp auto\*.zip auto\*.tar auto\*.gz) do (
    if exist "%%f" (
        echo Removing %%f...
        del /q "%%f" 2>nul
    )
)

REM Verify cleanup was successful and try PowerShell as last resort
if exist auto\OpenGL-Registry (
    echo WARNING: Standard cleanup failed, trying PowerShell force removal...
    powershell -Command "if (Test-Path 'auto\OpenGL-Registry') { Remove-Item 'auto\OpenGL-Registry' -Recurse -Force -ErrorAction SilentlyContinue }" 2>nul
    if exist auto\OpenGL-Registry (
        echo ERROR: Failed to clean OpenGL-Registry directory
        echo This will cause GLEW auto-generation to fail
        echo Please manually delete: %CD%\auto\OpenGL-Registry
        echo Or run as Administrator to allow forced cleanup
    ) else (
        echo ✓ PowerShell cleanup successful for OpenGL-Registry
    )
)
if exist auto\EGL-Registry (
    echo WARNING: Standard cleanup failed, trying PowerShell force removal...
    powershell -Command "if (Test-Path 'auto\EGL-Registry') { Remove-Item 'auto\EGL-Registry' -Recurse -Force -ErrorAction SilentlyContinue }" 2>nul
    if exist auto\EGL-Registry (
        echo ERROR: Failed to clean EGL-Registry directory  
        echo This will cause GLEW auto-generation to fail
        echo Please manually delete: %CD%\auto\EGL-Registry
        echo Or run as Administrator to allow forced cleanup
    ) else (
        echo ✓ PowerShell cleanup successful for EGL-Registry
    )
)

if exist auto\Makefile (
    echo Running GLEW auto-generation...
    make -C auto
    if %ERRORLEVEL% NEQ 0 (
        echo Warning: GLEW auto-generation failed, checking if files exist...
    ) else (
        echo GLEW auto-generation completed
    )
    
    REM Verify that essential GLEW files were generated
    if exist src\glew.c (
        echo ✓ GLEW source file found: src\glew.c
    ) else (
        echo ✗ Missing GLEW source file: src\glew.c
        echo Error: GLEW auto-generation incomplete
        goto :error
    )
    
    if exist include\GL\glew.h (
        echo ✓ GLEW header file found: include\GL\glew.h
    ) else (
        echo ✗ Missing GLEW header file: include\GL\glew.h
        echo Error: GLEW auto-generation incomplete
        goto :error
    )
    
    if exist include\GL\wglew.h (
        echo ✓ GLEW Windows header found: include\GL\wglew.h
    ) else (
        echo ✗ Missing GLEW Windows header: include\GL\wglew.h
        echo Error: GLEW auto-generation incomplete
        goto :error
    )
    
    echo GLEW files verified successfully
    
    REM Build GLEW library using Visual Studio
    echo Building GLEW library with Visual Studio...
    if exist build\vc12\glew.sln (
        echo Found GLEW Visual Studio solution: build\vc12\glew.sln
        
        REM Try to find MSBuild in common locations
        set "MSBUILD_PATH="
        if exist "%ProgramFiles%\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe" (
            set "MSBUILD_PATH=%ProgramFiles%\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe"
        ) else if exist "%ProgramFiles%\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" (
            set "MSBUILD_PATH=%ProgramFiles%\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
        ) else if exist "%ProgramFiles%\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe" (
            set "MSBUILD_PATH=%ProgramFiles%\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe"
        ) else if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Professional\MSBuild\Current\Bin\MSBuild.exe" (
            set "MSBUILD_PATH=%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Professional\MSBuild\Current\Bin\MSBuild.exe"
        ) else if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe" (
            set "MSBUILD_PATH=%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe"
        ) else (
            echo Warning: MSBuild not found in standard locations, trying PATH...
            where msbuild >nul 2>&1
            if %ERRORLEVEL% EQU 0 (
                set "MSBUILD_PATH=msbuild"
            ) else (
                echo Warning: MSBuild not found, GLEW library may not be built
                echo You may need to build build\vc12\glew.sln manually
                goto :skip_glew_build
            )
        )
        
        echo Using MSBuild: !MSBUILD_PATH!
        "!MSBUILD_PATH!" build\vc12\glew.sln /p:Configuration=Release /p:Platform=x64 /m
        if %ERRORLEVEL% EQU 0 (
            echo ✓ GLEW library built successfully
        ) else (
            echo Warning: GLEW library build failed, but continuing...
            echo You may need to build build\vc12\glew.sln manually in Visual Studio
        )
        
        :skip_glew_build
    ) else (
        echo Warning: GLEW Visual Studio solution not found at build\vc12\glew.sln
        echo GLEW library may not be available for linking
    )
    
) else (
    echo GLEW auto directory not found, checking for existing files...
    if exist src\glew.c (
        echo Using existing GLEW files
    ) else (
        echo Error: No GLEW source files found and no auto-generation available
        echo Please ensure the GLEW submodule is properly initialized
        goto :error
    )
)
cd ..\..

if not exist build mkdir build
if not exist build\win-vs2022 mkdir build\win-vs2022

cd build\win-vs2022

echo Generating Visual Studio 2022 solution...
cmake -G "Visual Studio 17 2022" -A x64 ../../

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Success! Visual Studio solution generated at:
    echo %CD%\GrpcSamples.sln
    echo.
    echo You can now open the solution in Visual Studio 2022 and build.
) else (
    echo.
    echo Error: Failed to generate Visual Studio solution.
    echo Please check that Visual Studio 2022 and CMake are properly installed.
)

popd
pause
goto :end

:error
echo.
echo Build failed due to missing GLEW files.
echo.
echo To fix this issue:
echo 1. Ensure you have 'make' installed (try: winget install GnuWin32.Make)
echo 2. Or manually run GLEW auto-generation:
echo    cd third_party\glew
echo    make -C auto
echo 3. Or check that the GLEW submodule is properly initialized
echo.
popd
pause
exit /b 1

:end
