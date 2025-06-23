@echo off
echo ===============================================
echo   TRANSPORTATION ROUTE SYSTEM - RUN SCRIPT
echo ===============================================
echo.

REM Check if executable exists
if exist "build\TransportApp.exe" (
    echo Starting Transportation Route System...
    echo.
    cd build
    TransportApp.exe
    cd ..
) else (
    echo Executable not found! Please build the project first.
    echo Run: build.bat
    echo.
)

pause
