@echo off
echo ===================================================
echo Transportation Route Recommendation System Builder
echo ===================================================
echo.

IF NOT EXIST "bin" mkdir bin

echo [1/4] Compiling Node.cpp...
g++ -c -std=c++17 -I . src/core/Node.cpp -o bin/Node.o
if %errorlevel% neq 0 (
    echo ERROR: Failed to compile Node.cpp
    exit /b %errorlevel%
)

echo [2/4] Compiling Edge.cpp...
g++ -c -std=c++17 -I . src/core/Edge.cpp -o bin/Edge.o
if %errorlevel% neq 0 (
    echo ERROR: Failed to compile Edge.cpp
    exit /b %errorlevel%
)

echo [3/4] Compiling Graph.cpp...
g++ -c -std=c++17 -I . src/core/Graph.cpp -o bin/Graph.o
if %errorlevel% neq 0 (
    echo ERROR: Failed to compile Graph.cpp
    exit /b %errorlevel%
)

echo [4/4] Linking final executable...
g++ -std=c++17 -o bin/TransportApp.exe main_simple.cpp bin/Node.o bin/Edge.o bin/Graph.o -I .
if %errorlevel% neq 0 (
    echo ERROR: Failed to link executable
    exit /b %errorlevel%
)

echo.
echo BUILD SUCCESSFUL!
echo ================
echo.
echo Your Transportation Route Recommendation System has been built successfully!
echo.
echo Executable location: bin\TransportApp.exe
echo.
echo To run the application:
echo   bin\TransportApp.exe
echo.
echo To run basic tests:
echo   .\test_basic.exe
echo.
echo Features implemented:
echo - Node management (GPS coordinates, distance calculations)
echo - Edge management (multiple criteria: time, distance, cost, transfers)
echo - Graph operations (add/remove nodes and edges)
echo - Dijkstra shortest path algorithm
echo - Multi-criteria optimization
echo.
echo Your final project core is ready!
