@echo off
echo Building Transportation Route Recommendation System...
echo.

REM Clean previous builds
if exist demo_complete_system.exe del demo_complete_system.exe
if exist test_node_simple.exe del test_node_simple.exe

REM Compile the complete system demo
echo Compiling complete system demo...
g++ -I. -std=c++17 ^
    demo_complete_system.cpp ^
    src/core/Node.cpp ^
    src/core/Edge.cpp ^
    src/core/Graph.cpp ^
    src/algorithms/DijkstraStrategy.cpp ^
    src/algorithms/RouteStrategy.cpp ^
    src/preferences/DecisionTree.cpp ^
    src/preferences/UserPreferences.cpp ^
    src/ui/Visualizer.cpp ^
    -o demo_complete_system.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ✅ Build successful! 
    echo.
    echo Available executables:
    echo   - demo_complete_system.exe : Complete system demonstration
    echo.
    echo To run the demo: .\demo_complete_system.exe
    echo.
) else (
    echo.
    echo ❌ Build failed! Check compilation errors above.
    echo.
)

pause
