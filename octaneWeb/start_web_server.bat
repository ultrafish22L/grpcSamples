@echo off
REM ========================================
REM OctaneWeb Complete Server Launcher
REM ========================================
REM Starts both the HTTP-to-gRPC proxy server
REM and the web server for octaneWeb
REM ========================================

echo.
echo ========================================
echo  OctaneWeb Complete Server Launcher
echo ========================================
echo.

REM Check if we're in the correct directory
if not exist "index.html" (
    echo ERROR: This script must be run from the octaneWeb folder
    echo Current directory: %CD%
    echo Expected files: index.html, js/, css/
    echo.
    pause
    exit /b 1
)

REM Start the web server
echo Starting web server...
echo Web server running at: http://localhost:8080/
echo.
echo ========================================
echo  Both Servers Running!
echo ========================================
echo.
echo Open in browser: http://localhost:8080/
echo Press any key to stop all servers...
echo.

python -m http.server 8080

REM If we get here, the web server stopped
echo.
echo ========================================
echo  Servers Stopped
echo ========================================
echo.
echo Note: The proxy server window may still be open.
echo Close it manually if needed.
echo.
pause