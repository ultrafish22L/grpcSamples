@echo off
echo Building GrpcSamples Visual Studio 2022 Solution...
echo.

pushd .

echo Generating GLEW extensions and source files...
cd third_party\glew

REM Clean up any existing auto-generation artifacts that might be corrupted
if exist auto\OpenGL-Registry (
    echo Cleaning existing OpenGL-Registry...
    rmdir /s /q auto\OpenGL-Registry
)
if exist auto\EGL-Registry (
    echo Cleaning existing EGL-Registry...
    rmdir /s /q auto\EGL-Registry
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
