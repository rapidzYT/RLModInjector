@echo off
echo Building Rocket League TAS...
echo.

REM Check if MSBuild is available
where msbuild >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo MSBuild not found. Please install Visual Studio or Build Tools for Visual Studio.
    echo.
    echo You can download Build Tools from:
    echo https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022
    echo.
    pause
    exit /b 1
)

echo Building solution...
msbuild RocketLeagueTAS.sln /p:Configuration=Release /p:Platform="Any CPU" /verbosity:minimal

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful!
    echo.
    echo Output files:
    echo - RocketLeagueTAS.DLL\bin\Release\RocketLeagueTAS.DLL.dll
    echo - RocketLeagueTAS.GUI\bin\Release\RocketLeagueTAS.GUI.exe
    echo - RocketLeagueTAS.Injector\bin\Release\RocketLeagueTAS.Injector.exe
    echo.
    echo Copying files to output directory...
    
    REM Create output directory
    if not exist "Output" mkdir Output
    
    REM Copy DLL
    copy "RocketLeagueTAS.DLL\bin\Release\RocketLeagueTAS.DLL.dll" "Output\"
    
    REM Copy GUI
    copy "RocketLeagueTAS.GUI\bin\Release\RocketLeagueTAS.GUI.exe" "Output\"
    copy "RocketLeagueTAS.GUI\bin\Release\RocketLeagueTAS.GUI.exe.config" "Output\"
    
    REM Copy Injector
    copy "RocketLeagueTAS.Injector\bin\Release\RocketLeagueTAS.Injector.exe" "Output\"
    copy "RocketLeagueTAS.Injector\bin\Release\RocketLeagueTAS.Injector.exe.config" "Output\"
    
    echo.
    echo All files copied to Output directory.
    echo.
    echo To use:
    echo 1. Start Rocket League
    echo 2. Run Output\RocketLeagueTAS.Injector.exe as Administrator
    echo 3. The TAS GUI will appear in Rocket League
    echo.
) else (
    echo.
    echo Build failed!
    echo.
)

pause