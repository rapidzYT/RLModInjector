@echo off
echo ========================================
echo Rocket League TAS Mod - Build Script
echo ========================================
echo.

REM Check if CMake is installed
where cmake >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: CMake not found! Please install CMake first.
    echo Download from: https://cmake.org/download/
    pause
    exit /b 1
)

REM Check if Visual Studio is installed
where cl >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Visual Studio compiler not found!
    echo Please run this from Visual Studio Developer Command Prompt
    echo Or install Visual Studio Build Tools
    pause
    exit /b 1
)

REM Create build directory
if not exist build mkdir build
cd build

echo.
echo Configuring CMake...
cmake .. -G "Visual Studio 16 2019" -A x64
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: CMake configuration failed!
    cd ..
    pause
    exit /b 1
)

echo.
echo Building project...
cmake --build . --config Release
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Build failed!
    cd ..
    pause
    exit /b 1
)

cd ..

echo.
echo ========================================
echo Build completed successfully!
echo ========================================
echo.
echo Output files:
echo - build\bin\Release\RLTASMod.dll
echo - build\bin\Release\RLTASInjector.exe
echo.
echo To use:
echo 1. Copy both files to the same directory
echo 2. Start Rocket League
echo 3. Run RLTASInjector.exe as Administrator
echo 4. Press F9 in game to toggle the TAS GUI
echo.
pause
