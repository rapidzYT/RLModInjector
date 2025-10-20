@echo off
echo ========================================
echo Clean Build Script
echo ========================================
echo.

echo Deleting build folder...
if exist build rmdir /s /q build

echo Creating fresh build...
mkdir build
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
pause
