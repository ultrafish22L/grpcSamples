@echo off
echo ========================================
echo OCTANE gRPC API TEST SUITE - ADVANCED
echo ========================================
echo.
echo USAGE OPTIONS:
echo   runOctaneGrpcTest.bat         - Default stable tests (133 tests)
echo   python octaneGrpcTest.py -1    - Stage 1 only (70 tests)
echo   python octaneGrpcTest.py -3    - Stages 1-3 (85 tests)
echo   python octaneGrpcTest.py -7    - Stages 1-7 (113 tests)
echo   python octaneGrpcTest.py --all - All tests including errors
echo   python octaneGrpcTest.py -crash - Include crash tests (DANGEROUS!)
echo.
echo WARNING: -crash flag will crash Octane Render!
echo.
set /p choice="Enter stage number (1-9) or press Enter for default: "

if "%choice%"=="" (
    echo Running default stable tests...
    python octaneGrpcTest.py
) else (
    echo Running Stage %choice% tests...
    python octaneGrpcTest.py -%choice%
)

echo.
pause