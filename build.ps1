# Rocket League TAS Build Script
Write-Host "Building Rocket League TAS..." -ForegroundColor Green
Write-Host ""

# Check if MSBuild is available
$msbuild = Get-Command msbuild -ErrorAction SilentlyContinue
if (-not $msbuild) {
    Write-Host "MSBuild not found. Please install Visual Studio or Build Tools for Visual Studio." -ForegroundColor Red
    Write-Host ""
    Write-Host "You can download Build Tools from:" -ForegroundColor Yellow
    Write-Host "https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022" -ForegroundColor Yellow
    Write-Host ""
    Read-Host "Press Enter to exit"
    exit 1
}

Write-Host "Building solution..." -ForegroundColor Yellow
$buildResult = & msbuild RocketLeagueTAS.sln /p:Configuration=Release /p:Platform="Any CPU" /verbosity:minimal

if ($LASTEXITCODE -eq 0) {
    Write-Host ""
    Write-Host "Build successful!" -ForegroundColor Green
    Write-Host ""
    Write-Host "Output files:" -ForegroundColor Cyan
    Write-Host "- RocketLeagueTAS.DLL\bin\Release\RocketLeagueTAS.DLL.dll" -ForegroundColor White
    Write-Host "- RocketLeagueTAS.GUI\bin\Release\RocketLeagueTAS.GUI.exe" -ForegroundColor White
    Write-Host "- RocketLeagueTAS.Injector\bin\Release\RocketLeagueTAS.Injector.exe" -ForegroundColor White
    Write-Host ""
    Write-Host "Copying files to output directory..." -ForegroundColor Yellow
    
    # Create output directory
    if (-not (Test-Path "Output")) {
        New-Item -ItemType Directory -Path "Output" | Out-Null
    }
    
    # Copy files
    Copy-Item "RocketLeagueTAS.DLL\bin\Release\RocketLeagueTAS.DLL.dll" "Output\" -Force
    Copy-Item "RocketLeagueTAS.GUI\bin\Release\RocketLeagueTAS.GUI.exe" "Output\" -Force
    Copy-Item "RocketLeagueTAS.GUI\bin\Release\RocketLeagueTAS.GUI.exe.config" "Output\" -Force
    Copy-Item "RocketLeagueTAS.Injector\bin\Release\RocketLeagueTAS.Injector.exe" "Output\" -Force
    Copy-Item "RocketLeagueTAS.Injector\bin\Release\RocketLeagueTAS.Injector.exe.config" "Output\" -Force
    
    Write-Host ""
    Write-Host "All files copied to Output directory." -ForegroundColor Green
    Write-Host ""
    Write-Host "To use:" -ForegroundColor Cyan
    Write-Host "1. Start Rocket League" -ForegroundColor White
    Write-Host "2. Run Output\RocketLeagueTAS.Injector.exe as Administrator" -ForegroundColor White
    Write-Host "3. The TAS GUI will appear in Rocket League" -ForegroundColor White
    Write-Host ""
} else {
    Write-Host ""
    Write-Host "Build failed!" -ForegroundColor Red
    Write-Host ""
}

Read-Host "Press Enter to exit"