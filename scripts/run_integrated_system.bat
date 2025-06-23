@echo off
echo ================================================
echo    INTEGRATED TRANSPORTATION SYSTEM DEMO
echo ================================================
echo.
echo Compiling the integrated transport system...
g++ -std=c++17 transport_system_fixed.cpp -o TransportAppFixed.exe

if %ERRORLEVEL% EQU 0 (
    echo ✅ Compilation successful!
    echo.
    echo Starting the integrated transportation system...
    echo.
    echo FEATURES:
    echo - Real-time CSV data export
    echo - Interactive HTML map generation
    echo - Automatic map updates after route finding
    echo - CRUD operations with live visualization
    echo.
    echo Instructions:
    echo 1. Try option 2 to find a route (e.g., Central_Station to University)
    echo 2. Use option 6 to generate/update the interactive map
    echo 3. Open 'jakarta_current_map.html' in your browser to see results
    echo 4. Add new nodes/edges and see them reflected in the map
    echo.
    pause
    .\TransportAppFixed.exe
) else (
    echo ❌ Compilation failed!
    pause
)
