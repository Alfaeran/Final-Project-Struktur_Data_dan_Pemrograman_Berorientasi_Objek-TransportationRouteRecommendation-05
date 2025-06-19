@echo off
REM Build script for Transportation Route Recommendation System with Interactive Menu
REM Final Project - Data Structures & OOP

echo ===============================================================
echo Building Transportation Route Recommendation System
echo Interactive Menu + CRUD + Testing + Visualization
echo ===============================================================

REM Clean previous builds
echo Cleaning previous builds...
if exist *.exe del *.exe
if exist *.o del *.o
if exist obj\*.o del obj\*.o

REM Create directories if they don't exist
if not exist obj mkdir obj
if not exist obj\core mkdir obj\core
if not exist obj\algorithms mkdir obj\algorithms
if not exist obj\preferences mkdir obj\preferences
if not exist obj\io mkdir obj\io
if not exist obj\ui mkdir obj\ui
if not exist obj\utils mkdir obj\utils
if not exist obj\visualization mkdir obj\visualization
if not exist bin mkdir bin

echo.
echo Compiling source files...

REM Compile core components
echo Compiling core components...
g++ -c src/core/Node.cpp -o obj/core/Node.o -I. -std=c++17
if errorlevel 1 goto error

g++ -c src/core/Edge.cpp -o obj/core/Edge.o -I. -std=c++17
if errorlevel 1 goto error

g++ -c src/core/Graph.cpp -o obj/core/Graph.o -I. -std=c++17
if errorlevel 1 goto error

REM Compile algorithms
echo Compiling algorithms...
g++ -c src/algorithms/DijkstraStrategy.cpp -o obj/algorithms/DijkstraStrategy.o -I. -std=c++17
if errorlevel 1 goto error

g++ -c src/algorithms/RouteStrategy.cpp -o obj/algorithms/RouteStrategy.o -I. -std=c++17
if errorlevel 1 goto error

REM Compile preferences
echo Compiling preferences...
g++ -c src/preferences/DecisionTree.cpp -o obj/preferences/DecisionTree.o -I. -std=c++17
if errorlevel 1 goto error

g++ -c src/preferences/UserPreferences.cpp -o obj/preferences/UserPreferences.o -I. -std=c++17
if errorlevel 1 goto error

REM Skip MultiCriteriaScoring.cpp for now (include issue)
REM g++ -c src/preferences/MultiCriteriaScoring.cpp -o obj/preferences/MultiCriteriaScoring.o -I. -std=c++17
REM if errorlevel 1 goto error

REM Compile I/O components
echo Compiling I/O components...
g++ -c src/io/CSVHandler.cpp -o obj/io/CSVHandler.o -I. -std=c++17
if errorlevel 1 goto error

g++ -c src/io/FileManager.cpp -o obj/io/FileManager.o -I. -std=c++17
if errorlevel 1 goto error

g++ -c src/io/JSONHandler.cpp -o obj/io/JSONHandler.o -I. -std=c++17
if errorlevel 1 goto error

g++ -c src/io/ConfigManager.cpp -o obj/io/ConfigManager.o -I. -std=c++17
if errorlevel 1 goto error

REM Compile UI components
echo Compiling UI components...
g++ -c src/ui/Visualizer.cpp -o obj/ui/Visualizer.o -I. -std=c++17
if errorlevel 1 goto error

g++ -c src/ui/MenuSystem.cpp -o obj/ui/MenuSystem.o -I. -std=c++17
if errorlevel 1 goto error

REM Compile visualization components
echo Compiling visualization components...
g++ -c src/visualization/WebMapGenerator.cpp -o obj/visualization/WebMapGenerator.o -I. -std=c++17
if errorlevel 1 goto error

REM Compile utilities
echo Compiling utilities...
g++ -c src/utils/StringUtils.cpp -o obj/utils/StringUtils.o -I. -std=c++17
if errorlevel 1 goto error

g++ -c src/utils/Validator.cpp -o obj/utils/Validator.o -I. -std=c++17
if errorlevel 1 goto error

REM Compile test implementations
echo Compiling test implementations...
g++ -c tests/test_implementations.cpp -o obj/test_implementations.o -I. -std=c++17
if errorlevel 1 goto error

REM Compile main application
echo Compiling main application...
g++ -c src/main.cpp -o obj/main.o -I. -std=c++17
if errorlevel 1 goto error

echo.
echo Linking executables...

REM Link main interactive application
echo Building main interactive application...
g++ -o bin/TransportApp.exe obj/main.o ^
    obj/core/Node.o obj/core/Edge.o obj/core/Graph.o ^
    obj/algorithms/DijkstraStrategy.o obj/algorithms/RouteStrategy.o ^
    obj/preferences/DecisionTree.o obj/preferences/UserPreferences.o ^
    obj/io/CSVHandler.o obj/io/FileManager.o obj/io/JSONHandler.o obj/io/ConfigManager.o ^
    obj/ui/Visualizer.o obj/ui/MenuSystem.o ^
    obj/visualization/WebMapGenerator.o ^
    obj/utils/StringUtils.o obj/utils/Validator.o ^
    -I. -std=c++17
if errorlevel 1 goto error

REM Link test suite
echo Building test suite...
g++ -o bin/test_suite.exe tests/test_main.cpp ^
    obj/test_implementations.o ^
    obj/core/Node.o obj/core/Edge.o obj/core/Graph.o ^
    obj/algorithms/DijkstraStrategy.o obj/algorithms/RouteStrategy.o ^
    obj/preferences/DecisionTree.o obj/preferences/UserPreferences.o ^
    obj/io/CSVHandler.o obj/io/FileManager.o obj/io/JSONHandler.o obj/io/ConfigManager.o ^
    obj/ui/Visualizer.o obj/ui/MenuSystem.o ^
    obj/visualization/WebMapGenerator.o ^
    obj/utils/StringUtils.o obj/utils/Validator.o ^
    -I. -std=c++17
if errorlevel 1 goto error

REM Build demo application (keep existing)
echo Building demo application...
g++ -o bin/demo_complete.exe demo_complete_system.cpp ^
    obj/core/Node.o obj/core/Edge.o obj/core/Graph.o ^
    obj/algorithms/DijkstraStrategy.o obj/algorithms/RouteStrategy.o ^
    obj/preferences/DecisionTree.o obj/preferences/UserPreferences.o ^
    obj/io/CSVHandler.o obj/io/FileManager.o obj/io/JSONHandler.o obj/io/ConfigManager.o ^
    obj/ui/Visualizer.o ^
    obj/utils/StringUtils.o obj/utils/Validator.o ^
    -I. -std=c++17
if errorlevel 1 goto error

echo.
echo ===============================================================
echo BUILD SUCCESSFUL!
echo ===============================================================
echo.
echo Executables created:
echo   bin/TransportApp.exe     - Main interactive application
echo   bin/test_suite.exe       - Comprehensive test suite  
echo   bin/demo_complete.exe    - System demonstration
echo.
echo Usage examples:
echo   bin/TransportApp.exe                    - Start interactive menu
echo   bin/TransportApp.exe -d                 - Run demo mode
echo   bin/TransportApp.exe -t                 - Run test suite
echo   bin/TransportApp.exe -f network.csv     - Load network from file
echo   bin/TransportApp.exe -h                 - Show help
echo.
echo   bin/test_suite.exe                      - Run all tests
echo   bin/demo_complete.exe                   - Run complete demo
echo.
goto end

:error
echo.
echo ===============================================================
echo BUILD FAILED!
echo ===============================================================
echo Check the error messages above for details.
echo Make sure all source files exist and there are no syntax errors.
exit /b 1

:end
echo Build completed successfully!
