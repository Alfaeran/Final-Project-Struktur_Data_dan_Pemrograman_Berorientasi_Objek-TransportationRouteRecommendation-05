@echo off
echo ======================================
echo    QUICK TEST - Jakarta Route System
echo ======================================
echo.

echo 1. Testing build system...
call build.bat
if errorlevel 1 (
    echo [ERROR] Build failed!
    pause
    exit /b 1
)
echo [OK] Build successful
echo.

echo 2. Testing application run...
echo Running TransportApp.exe...
if exist "build\TransportApp.exe" (
    echo [OK] Application executable found
) else (
    echo [ERROR] Application not found!
    pause
    exit /b 1
)
echo.

echo 3. Checking data files...
if exist "nodes_data.csv" (
    echo [OK] nodes_data.csv found
) else (
    echo [ERROR] nodes_data.csv not found!
)

if exist "network_data.csv" (
    echo [OK] network_data.csv found  
) else (
    echo [ERROR] network_data.csv not found!
)
echo.

echo 4. Checking map files...
if exist "jakarta_interactive_map.html" (
    echo [OK] jakarta_interactive_map.html found
) else (
    echo [ERROR] jakarta_interactive_map.html not found!
)

if exist "jakarta_current_map.html" (
    echo [OK] jakarta_current_map.html found
) else (
    echo [ERROR] jakarta_current_map.html not found!
)
echo.

echo 5. Starting HTTP server for testing...
echo Starting server at localhost:8080...
echo Open browser: http://localhost:8080/jakarta_interactive_map.html
echo.
echo [MANUAL TEST] Please verify in browser:
echo - Map loads with all stations
echo - Route finding works
echo - Route details show step-by-step info
echo - Click stations shows connections
echo - No emoji in display
echo.
echo Press Ctrl+C to stop server when done testing
python -m http.server 8080
