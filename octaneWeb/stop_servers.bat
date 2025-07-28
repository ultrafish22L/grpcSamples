@echo off
REM ========================================
REM OctaneWeb Server Stopper
REM ========================================
REM Stops all OctaneWeb servers cleanly
REM ========================================

echo.
echo ========================================
echo  Stopping OctaneWeb Servers
echo ========================================
echo.

echo Stopping Python HTTP servers...
taskkill /f /im python.exe >nul 2>&1

echo Stopping any remaining server processes...
for /f "tokens=5" %%a in ('netstat -aon ^| find ":8080" ^| find "LISTENING"') do taskkill /f /pid %%a >nul 2>&1
for /f "tokens=5" %%a in ('netstat -aon ^| find ":51023" ^| find "LISTENING"') do taskkill /f /pid %%a >nul 2>&1

echo.
echo ========================================
echo  All Servers Stopped
echo ========================================
echo.
echo You can now restart with start_proxy.bat
echo.
pause