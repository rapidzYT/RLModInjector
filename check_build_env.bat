@echo off
echo ================================================
echo Build Environment Checker
echo ================================================
echo.

REM Check for Visual Studio / Build Tools
echo [1/3] Checking for Visual Studio compiler...
where cl >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    echo [OK] Visual Studio compiler found!
    cl 2>&1 | findstr /C:"Version" 
    echo.
) else (
    echo [FAIL] Visual Studio compiler NOT found!
    echo.
    echo This means you need to either:
    echo   1. Install Visual Studio or Build Tools
    echo   2. Open "Developer Command Prompt for VS 2022"
    echo.
    echo See INSTALL_BUILD_TOOLS.md for detailed instructions.
    echo.
    goto :end_fail
)

REM Check for CMake
echo [2/3] Checking for CMake...
where cmake >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    echo [OK] CMake found!
    cmake --version | findstr /C:"version"
    echo.
) else (
    echo [FAIL] CMake NOT found!
    echo.
    echo Download from: https://cmake.org/download/
    echo Make sure to check "Add CMake to PATH" during installation
    echo.
    goto :end_fail
)

REM Check for dependencies
echo [3/3] Checking for dependencies...

set DEPS_OK=1

if not exist external\imgui\imgui.h (
    echo [FAIL] ImGui not found in external\imgui\
    echo        Run setup_dependencies.bat to install
    set DEPS_OK=0
) else (
    echo [OK] ImGui found
)

if not exist external\minhook\include\MinHook.h (
    echo [FAIL] MinHook not found in external\minhook\
    echo        Run setup_dependencies.bat to install
    set DEPS_OK=0
) else (
    echo [OK] MinHook found
)

echo.

if %DEPS_OK%==0 (
    echo Some dependencies are missing!
    echo Run: setup_dependencies.bat
    echo.
    goto :end_fail
)

echo ================================================
echo All checks passed! You're ready to build!
echo ================================================
echo.
echo Next steps:
echo   1. Run: build_all.bat
echo   2. Wait for build to complete
echo   3. Check build\bin\Release\ for output files
echo.
pause
exit /b 0

:end_fail
echo.
echo ================================================
echo Setup Required
echo ================================================
echo.
echo Please fix the issues above, then run this script again.
echo.
echo For help, see:
echo   - INSTALL_BUILD_TOOLS.md (for Visual Studio/CMake)
echo   - setup_dependencies.bat (for ImGui/MinHook)
echo.
pause
exit /b 1
