@echo off
echo =====================================================
echo      TRANSPORTATION ROUTE SYSTEM - Complete Demo
echo =====================================================
echo.
echo 🚀 Compiling the Jakarta transportation system...
g++ -std=c++17 transport_system_fixed.cpp -o TransportAppComplete.exe

if %errorlevel% equ 0 (
    echo.
    echo ✅ Compilation successful!
    echo.
    echo 📊 JAKARTA NETWORK FEATURES:
    echo    • 34 Real Jakarta Stations (TransJakarta, MRT, LRT, KRL)
    echo    • 66 Transportation Connections
    echo    • Interactive Web Map Visualization
    echo    • Real-time Route Calculation with Dijkstra Algorithm
    echo    • Auto-updating CSV data export
    echo.
    echo 🗺️ Opening interactive map in browser...
    start jakarta_map_fixed.html
    echo.
    echo ⏱️ Waiting 3 seconds for map to load...
    timeout 3 > nul
    echo.
    echo 🎯 Starting the Transportation Route Recommendation System...
    echo.
    TransportAppComplete.exe
) else (
    echo.
    echo ❌ Compilation failed. Please check the source code.
    pause
)
