@echo off
echo ========================================
echo OCTANE gRPC API TEST SUITE
echo ========================================
echo.
echo This will test your Octane Render gRPC API connection
echo Make sure Octane Render is running with LiveLink enabled
echo.
pause

echo Installing Python dependencies...
pip install -r requirements.txt

echo.
echo Running Octane API tests...
echo Default: All stable tests (133 tests, no crashes)
echo.
python octaneGrpcTest.py

echo.
echo Test complete! Press any key to exit...
pause > nul