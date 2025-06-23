@echo off
echo ========================================
echo   STANDALONE TRANSPORT SYSTEM BUILDER
echo ========================================
echo.

echo Building standalone application...
g++ -std=c++17 standalone_transport_system.cpp -o TransportApp_Standalone.exe

if %errorlevel% neq 0 (
    echo.
    echo ❌ BUILD FAILED!
    echo Check for compilation errors above.
    pause
    exit /b %errorlevel%
)

echo.
echo ✅ BUILD SUCCESSFUL!
echo ==================
echo.
echo 📁 Executable created: TransportApp_Standalone.exe
echo.
echo 🚀 To run the application:
echo    TransportApp_Standalone.exe
echo.
echo 🎯 This standalone version includes:
echo    ✅ Complete graph data structures
echo    ✅ Dijkstra pathfinding algorithm  
echo    ✅ Interactive menu system
echo    ✅ Network visualization
echo    ✅ Map generation (HTML + CSV)
echo    ✅ System testing suite
echo    ✅ CRUD operations for nodes/edges
echo.
echo Press any key to run the application...
pause >nul

echo.
echo Starting application...
TransportApp_Standalone.exe

echo.
echo Application completed. Press any key to exit.
pause >nul
