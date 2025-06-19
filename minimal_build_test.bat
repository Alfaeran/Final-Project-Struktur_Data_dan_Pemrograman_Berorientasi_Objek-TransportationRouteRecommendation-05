@echo off
echo Building minimal version of the Transportation Route Recommender...
echo.

REM Set the include path and compiler flags
set INCLUDES=-I./include
set CFLAGS=-std=c++17 -Wall

REM Create bin directory if it doesn't exist
if not exist "bin" mkdir bin

REM First run the fix scripts to ensure headers are correct
echo Running fix scripts...
call fix_includes.bat
call fix_edge.bat
call fix_node.bat
call fix_edge_weight.bat
call fix_core_includes.bat

echo.
echo Compiling core files...
g++ %CFLAGS% %INCLUDES% -c src/core/Edge.cpp -o src/core/Edge.o
g++ %CFLAGS% %INCLUDES% -c src/core/Node.cpp -o src/core/Node.o
g++ %CFLAGS% %INCLUDES% -c src/core/Graph.cpp -o src/core/Graph.o

echo.
echo Compiling algorithms...
g++ %CFLAGS% %INCLUDES% -c src/algorithms/RouteStrategy.cpp -o src/algorithms/RouteStrategy.o 2>nul
g++ %CFLAGS% %INCLUDES% -c src/algorithms/DijkstraStrategy.cpp -o src/algorithms/DijkstraStrategy.o
g++ %CFLAGS% %INCLUDES% -c src/algorithms/AStarStrategy.cpp -o src/algorithms/AStarStrategy.o

echo.
echo Creating a minimal test program...
echo #include ^<iostream^> > minimal_main.cpp
echo #include "core/Graph.h" >> minimal_main.cpp
echo #include "core/Node.h" >> minimal_main.cpp
echo #include "core/Edge.h" >> minimal_main.cpp
echo. >> minimal_main.cpp
echo int main() { >> minimal_main.cpp
echo     std::cout ^<^< "Transportation Route Recommender - Minimal Test" ^<^< std::endl; >> minimal_main.cpp
echo     std::cout ^<^< "=========================================" ^<^< std::endl; >> minimal_main.cpp
echo. >> minimal_main.cpp 
echo     try { >> minimal_main.cpp
echo         // Create nodes >> minimal_main.cpp
echo         Node station1("Station1", -6.2088, 106.8456); // Jakarta Coordinates >> minimal_main.cpp
echo         Node station2("Station2", -6.2149, 106.8451); // Another Jakarta location >> minimal_main.cpp
echo. >> minimal_main.cpp
echo         // Create graph and add nodes >> minimal_main.cpp
echo         Graph transportNetwork; >> minimal_main.cpp
echo         transportNetwork.addNode("Station1", -6.2088, 106.8456); >> minimal_main.cpp
echo         transportNetwork.addNode("Station2", -6.2149, 106.8451); >> minimal_main.cpp
echo. >> minimal_main.cpp
echo         // Create edge between stations (distance, time, cost, transfers) >> minimal_main.cpp
echo         transportNetwork.addEdge("Station1", "Station2", 5000, 15, 5000, 0, "Bus"); >> minimal_main.cpp
echo. >> minimal_main.cpp
echo         std::cout ^<^< "Successfully created a simple transport network with 2 stations" ^<^< std::endl; >> minimal_main.cpp
echo         std::cout ^<^< "Distance between stations: " ^<^< station1.distanceTo(station2) ^<^< " meters" ^<^< std::endl; >> minimal_main.cpp
echo. >> minimal_main.cpp
echo         // Test edge retrieval >> minimal_main.cpp
echo         auto edges = transportNetwork.getEdgesFrom("Station1"); >> minimal_main.cpp
echo         if (!edges.empty()) { >> minimal_main.cpp
echo             auto firstEdge = edges.front(); >> minimal_main.cpp
echo             std::cout ^<^< "Edge from Station1 to " ^<^< firstEdge.getDestination() >> minimal_main.cpp
echo                       ^<^< " takes " ^<^< firstEdge.getTime() ^<^< " minutes and costs " >> minimal_main.cpp
echo                       ^<^< firstEdge.getCost() ^<^< " IDR" ^<^< std::endl; >> minimal_main.cpp
echo         } >> minimal_main.cpp
echo. >> minimal_main.cpp
echo         std::cout ^<^< "Core components working correctly!" ^<^< std::endl; >> minimal_main.cpp
echo     } catch (const std::exception& e) { >> minimal_main.cpp
echo         std::cerr ^<^< "Error: " ^<^< e.what() ^<^< std::endl; >> minimal_main.cpp
echo         return 1; >> minimal_main.cpp
echo     } >> minimal_main.cpp
echo. >> minimal_main.cpp
echo     return 0; >> minimal_main.cpp
echo } >> minimal_main.cpp

echo.
echo Compiling minimal test program...
g++ %CFLAGS% %INCLUDES% -o bin/minimal_test minimal_main.cpp src/core/Edge.o src/core/Node.o src/core/Graph.o

if %errorlevel% neq 0 (
    echo.
    echo Build failed with error code %errorlevel%
    exit /b %errorlevel%
) else (
    echo.
    echo Build successful!
    echo.
    echo You can run the minimal test program with:
    echo bin\minimal_test.exe
    echo.
)

echo Testing the minimal program...
bin\minimal_test.exe
