@echo off
echo =====================================================
echo      TRANSPORTATION ROUTE SYSTEM - Jakarta Edition
echo =====================================================
echo.
echo 🚀 Compiling the integrated Jakarta transportation system...
g++ -std=c++17 transport_system_fixed.cpp -o TransportAppWithJakarta.exe

if %errorlevel% equ 0 (
    echo.
    echo ✅ Compilation successful!
    echo.
    echo 📊 JAKARTA NETWORK FEATURES:
    echo    • 34 Real Jakarta Stations (TransJakarta, MRT, LRT)
    echo    • 66 Transportation Connections
    echo    • Interactive Web Map Visualization
    echo    • Real-time Route Calculation with Dijkstra Algorithm
    echo    • Auto-updating CSV data export
    echo.
    echo 🗺️ Opening interactive map in browser...
    start jakarta_current_map.html
    echo.
    echo 🎯 Starting the Transportation Route Recommendation System...
    echo.
    TransportAppWithJakarta.exe
) else (
    echo.
    echo ❌ Compilation failed. Please check the source code.
    pause
)
