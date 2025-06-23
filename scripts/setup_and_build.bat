@echo off
echo ===============================================================
echo Transportation Route Recommendation System - Setup and Build
echo ===============================================================
echo.

:check_admin
net session >nul 2>&1
if %errorLevel% neq 0 (
    echo This script doesn't require administrator privileges.
    echo.
)

echo This script will:
echo 1. Fix all include paths in source files
echo 2. Fix specific include paths in key files
echo 3. Update Edge.h class declaration to match implementation
echo 4. Add missing Edge::getWeight implementation
echo 5. Update Node.h class declaration to match implementation
echo 6. Build the project
echo.
echo Press any key to continue or Ctrl+C to cancel...
pause >nul

echo.
echo Step 1: Fixing all source file include paths...
call fix_all_includes.bat
if %errorlevel% neq 0 goto :error

echo.
echo Step 2: Fixing specific include paths...
call fix_includes.bat
if %errorlevel% neq 0 goto :error

echo.
echo Step 3: Fixing Edge class declaration...
call fix_edge.bat
if %errorlevel% neq 0 goto :error

echo.
echo Step 4: Adding missing Edge::getWeight implementation...
call fix_edge_weight.bat
if %errorlevel% neq 0 goto :error

echo.
echo Step 5: Fixing Node class declaration...
call fix_node.bat
if %errorlevel% neq 0 goto :error

echo.
echo Step 6: Fixing core includes...
call fix_core_includes.bat
if %errorlevel% neq 0 goto :error

echo.
echo Step 7: Building the project...
call build.bat
if %errorlevel% neq 0 goto :error

echo.
echo ===============================================================
echo All steps completed successfully!
echo.
echo If you encounter any issues while running the application:
echo 1. Check that all the fix scripts ran without errors
echo 2. Make sure CMake is installed and in your PATH
echo 3. Check that you have a C++ compiler (g++ or Visual Studio)
echo.
echo To run the application:
echo build\bin\transport_route_recommender
echo.
echo To run the tests:
echo build\bin\run_tests
echo ===============================================================

goto :end

:error
echo.
echo An error occurred during the setup process.
echo Error code: %errorlevel%
exit /b %errorlevel%

:end
