@echo off
echo Rocket League TAS Launcher
echo ========================
echo.

REM Check if Rocket League is running
tasklist /FI "IMAGENAME eq RocketLeague.exe" 2>NUL | find /I /N "RocketLeague.exe">NUL
if "%ERRORLEVEL%"=="0" (
    echo Rocket League is running.
    echo.
) else (
    echo Rocket League is not running!
    echo Please start Rocket League first.
    echo.
    pause
    exit /b 1
)

REM Check if we're running as administrator
net session >nul 2>&1
if %errorLevel% == 0 (
    echo Running as Administrator - OK
    echo.
) else (
    echo This script needs to be run as Administrator for DLL injection.
    echo Right-click and select "Run as administrator"
    echo.
    pause
    exit /b 1
)

REM Check if files exist
if not exist "RocketLeagueTAS.Injector.exe" (
    echo RocketLeagueTAS.Injector.exe not found!
    echo Please run build.bat first to compile the project.
    echo.
    pause
    exit /b 1
)

if not exist "RocketLeagueTAS.DLL.dll" (
    echo RocketLeagueTAS.DLL.dll not found!
    echo Please run build.bat first to compile the project.
    echo.
    pause
    exit /b 1
)

echo Injecting TAS DLL into Rocket League...
echo.

REM Run the injector
RocketLeagueTAS.Injector.exe

echo.
echo TAS injection completed.
echo The TAS GUI should now be visible in Rocket League.
echo.
pause