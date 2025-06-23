@echo off
echo ===============================================
echo   TRANSPORTATION ROUTE SYSTEM - BUILD SCRIPT
echo ===============================================
echo.

REM Create build directory if it doesn't exist
if not exist "build" mkdir build

REM Compile the main application
echo Compiling Transportation Route System...
g++ -std=c++17 src/standalone_transport_system.cpp -o build/TransportApp.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ✓ Build successful! Executable created: build/TransportApp.exe
    echo.
    echo To run the application:
    echo   cd build
    echo   TransportApp.exe
    echo.
) else (
    echo.
    echo ✗ Build failed! Please check for compilation errors.
    echo.
)

pause
