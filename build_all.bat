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
    echo.
    echo For detailed instructions, see: INSTALL_BUILD_TOOLS.md
    pause
    exit /b 1
)

REM Check if Visual Studio is installed
where cl >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Visual Studio compiler not found!
    echo.
    echo You need to install Visual Studio or Build Tools.
    echo.
    echo QUICK FIX:
    echo   1. Open "Developer Command Prompt for VS 2022"
    echo      - Press Windows key
    echo      - Type "developer command"
    echo      - Click the result
    echo   2. Navigate to this folder
    echo   3. Run build_all.bat again
    echo.
    echo OR INSTALL:
    echo   1. See INSTALL_BUILD_TOOLS.md for detailed instructions
    echo   2. Download Visual Studio Community 2022 (FREE^)
    echo   3. Select "Desktop development with C++" during install
    echo.
    pause
    exit /b 1
)

REM Create build directory
if not exist build mkdir build
cd build

echo.
echo Configuring CMake...
cmake .. -G "Visual Studio 17 2022" -A x64
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
