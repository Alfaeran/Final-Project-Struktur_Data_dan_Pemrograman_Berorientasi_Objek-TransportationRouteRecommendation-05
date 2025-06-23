@echo off
echo ========================================
echo    PROJECT CLEANUP UTILITY
echo ========================================
echo.

echo This script will clean up unnecessary files and keep only the essentials.
echo.
echo Files that will be KEPT:
echo   ✅ standalone_transport_system.cpp (Main file)
echo   ✅ build_standalone.bat (Build script)
echo   ✅ STANDALONE_GUIDE.md (Documentation)
echo   ✅ PANDUAN.md (Installation guide)
echo   ✅ README.md (Project overview)
echo   ✅ QUICK_START.md (Quick reference)
echo.
echo Files that will be REMOVED:
echo   ❌ All scattered test files in root
echo   ❌ Old main_*.cpp files
echo   ❌ Temporary build files
echo   ❌ Object files and executables (except standalone)
echo   ❌ Complex folder structure (will keep simplified)
echo.

choice /c YN /m "Proceed with cleanup"
if errorlevel 2 goto cancel

echo.
echo Starting cleanup...
echo.

REM Remove scattered test files in root
echo Removing scattered test files...
del /q test_*.cpp 2>nul
del /q demo_*.cpp 2>nul
del /q main_clean.cpp 2>nul
del /q main_new.cpp 2>nul
del /q main_broken.cpp 2>nul
del /q temp_*.cpp 2>nul
del /q sample_*.cpp 2>nul

REM Remove old build files
echo Removing build artifacts...
del /q *.o 2>nul
del /q *.exe 2>nul
if exist obj rmdir /s /q obj 2>nul

REM Keep only essential files in root
echo Keeping essential files only...

REM Create a new simplified structure
if not exist bin mkdir bin
if not exist docs mkdir docs

REM Move documentation files to docs folder
move PANDUAN.md docs\ 2>nul
move QUICK_START.md docs\ 2>nul
move STANDALONE_GUIDE.md docs\ 2>nul

echo.
echo ✅ CLEANUP COMPLETED!
echo ==================
echo.
echo 📁 Project structure is now simplified:
echo.
echo Final-Project.../
echo ├── standalone_transport_system.cpp  # ⭐ MAIN FILE
echo ├── build_standalone.bat            # 🔧 BUILD SCRIPT  
echo ├── README.md                       # 📖 PROJECT OVERVIEW
echo ├── docs/                           # 📚 DOCUMENTATION
echo │   ├── PANDUAN.md                  # 📋 Detailed guide
echo │   ├── QUICK_START.md              # ⚡ Quick reference
echo │   └── STANDALONE_GUIDE.md         # 🚀 Standalone guide
echo └── bin/                            # 📦 OUTPUT FOLDER
echo.
echo 🎯 To use the project:
echo   1. Run: build_standalone.bat
echo   2. Or manual: g++ -std=c++17 standalone_transport_system.cpp -o app.exe
echo.
echo 📚 For documentation:
echo   - README.md (project overview)
echo   - docs/STANDALONE_GUIDE.md (standalone version guide)
echo   - docs/PANDUAN.md (complete installation guide)
echo   - docs/QUICK_START.md (quick reference)
echo.
goto end

:cancel
echo.
echo Cleanup cancelled by user.
echo.

:end
echo Press any key to exit...
pause >nul
