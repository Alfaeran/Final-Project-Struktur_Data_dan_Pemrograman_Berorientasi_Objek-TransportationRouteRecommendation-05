@echo off
echo =====================================
echo  Transportation System - Quick Start
echo =====================================
echo.
echo Compiling the integrated system...
g++ -std=c++17 transport_system_fixed.cpp -o TransportAppFixed.exe

if %errorlevel% equ 0 (
    echo.
    echo ✅ Compilation successful!
    echo.
    echo Starting the Transportation Route Recommendation System...
    echo.
    TransportAppFixed.exe
) else (
    echo.
    echo ❌ Compilation failed. Please check the source code.
    pause
)
