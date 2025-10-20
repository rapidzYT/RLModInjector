@echo off
echo Testing Rocket League TAS Build...
echo.

REM Check if build output exists
if not exist "RocketLeagueTAS.DLL\bin\Release\RocketLeagueTAS.DLL.dll" (
    echo ERROR: RocketLeagueTAS.DLL.dll not found!
    echo Please run build.bat first.
    echo.
    pause
    exit /b 1
)

if not exist "RocketLeagueTAS.GUI\bin\Release\RocketLeagueTAS.GUI.exe" (
    echo ERROR: RocketLeagueTAS.GUI.exe not found!
    echo Please run build.bat first.
    echo.
    pause
    exit /b 1
)

if not exist "RocketLeagueTAS.Injector\bin\Release\RocketLeagueTAS.Injector.exe" (
    echo ERROR: RocketLeagueTAS.Injector.exe not found!
    echo Please run build.bat first.
    echo.
    pause
    exit /b 1
)

echo All build outputs found!
echo.

REM Check file sizes
echo File sizes:
for %%f in ("RocketLeagueTAS.DLL\bin\Release\RocketLeagueTAS.DLL.dll" "RocketLeagueTAS.GUI\bin\Release\RocketLeagueTAS.GUI.exe" "RocketLeagueTAS.Injector\bin\Release\RocketLeagueTAS.Injector.exe") do (
    echo %%~nxf: %%~zf bytes
)

echo.
echo Build test completed successfully!
echo.
pause