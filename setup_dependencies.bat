@echo off
echo ================================================
echo Rocket League TAS Mod - Dependency Setup
echo ================================================
echo.
echo This script will help you download and set up the required dependencies.
echo.

REM Create external directory
if not exist external mkdir external
cd external

echo.
echo [1/2] Setting up ImGui...
echo.

if exist imgui (
    echo ImGui directory already exists. Skipping...
) else (
    echo Please download ImGui manually:
    echo 1. Go to: https://github.com/ocornut/imgui
    echo 2. Click 'Code' -^> 'Download ZIP'
    echo 3. Extract the ZIP
    echo 4. Copy all contents to: external/imgui/
    echo.
    echo Press any key when done...
    pause >nul
    
    if not exist imgui (
        echo ERROR: imgui folder not found! Please extract ImGui to external/imgui/
        cd ..
        pause
        exit /b 1
    )
)

echo.
echo [2/2] Setting up MinHook...
echo.

if exist minhook (
    echo MinHook directory already exists. Skipping...
) else (
    echo Please download MinHook manually:
    echo 1. Go to: https://github.com/TsudaKageyu/minhook/releases
    echo 2. Download the latest release ZIP (e.g., minhook_1_3_3.zip)
    echo 3. Extract the ZIP
    echo 4. Copy the extracted folder to: external/minhook/
    echo.
    echo The structure should be:
    echo external/minhook/include/MinHook.h
    echo external/minhook/lib/libMinHook.x64.lib
    echo.
    echo Press any key when done...
    pause >nul
    
    if not exist minhook (
        echo ERROR: minhook folder not found! Please extract MinHook to external/minhook/
        cd ..
        pause
        exit /b 1
    )
)

cd ..

echo.
echo ================================================
echo Dependency setup complete!
echo ================================================
echo.
echo Verifying installation...
echo.

set ERROR_FOUND=0

if not exist external\imgui\imgui.h (
    echo ERROR: external\imgui\imgui.h not found!
    set ERROR_FOUND=1
)

if not exist external\imgui\backends\imgui_impl_win32.h (
    echo ERROR: external\imgui\backends\imgui_impl_win32.h not found!
    set ERROR_FOUND=1
)

if not exist external\imgui\backends\imgui_impl_dx11.h (
    echo ERROR: external\imgui\backends\imgui_impl_dx11.h not found!
    set ERROR_FOUND=1
)

if not exist external\minhook\include\MinHook.h (
    echo ERROR: external\minhook\include\MinHook.h not found!
    set ERROR_FOUND=1
)

if not exist external\minhook\lib\libMinHook.x64.lib (
    echo ERROR: external\minhook\lib\libMinHook.x64.lib not found!
    set ERROR_FOUND=1
)

if %ERROR_FOUND%==1 (
    echo.
    echo Some files are missing! Please check the structure and try again.
    pause
    exit /b 1
)

echo.
echo All dependencies verified successfully!
echo.
echo You can now run build_all.bat to build the project.
echo.
pause
