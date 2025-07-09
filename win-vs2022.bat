@echo off
echo Building GrpcSamples Visual Studio 2022 Solution...
echo.

pushd .

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
