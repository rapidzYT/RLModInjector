# Rocket League TAS Setup Guide

## Quick Start

1. **Build the project**:
   ```bash
   # Windows Command Prompt
   build.bat
   
   # Or PowerShell
   .\build.ps1
   ```

2. **Start Rocket League**

3. **Run the injector as Administrator**:
   ```bash
   # Double-click launch.bat and select "Run as administrator"
   # Or run manually:
   RocketLeagueTAS.Injector.exe
   ```

4. **Use the TAS GUI** that appears in Rocket League

## Detailed Setup

### Prerequisites

- **Windows 10/11** (64-bit)
- **.NET Framework 4.8** or later
- **Visual Studio 2019+** or **Build Tools for Visual Studio**
- **Rocket League** (any version, but memory offsets may need updating)
- **Administrator privileges** (required for DLL injection)

### Installation Steps

#### Option 1: Using Pre-built Files
1. Download the latest release
2. Extract to a folder
3. Run `launch.bat` as Administrator

#### Option 2: Building from Source
1. Clone or download the source code
2. Open Command Prompt or PowerShell in the project directory
3. Run `build.bat` or `build.ps1`
4. Files will be compiled to the `Output` directory
5. Run `launch.bat` as Administrator

### Building with Visual Studio

1. Open `RocketLeagueTAS.sln` in Visual Studio
2. Right-click the solution and select "Build Solution"
3. Output files will be in `bin/Release` folders

### Building with Command Line

```bash
# Using MSBuild directly
msbuild RocketLeagueTAS.sln /p:Configuration=Release /p:Platform="Any CPU"

# Using the provided script
build.bat
```

## Usage Instructions

### Recording a TAS

1. Start Rocket League and load into a match
2. Run the injector as Administrator
3. In the TAS GUI, click "Start" in the Recording section
4. Play normally - all inputs are recorded
5. Click "Stop" when finished
6. Save the recording to a file

### Replaying a TAS

1. Load a previously saved recording
2. Click "Start" in the Replay section
3. The car and ball will teleport to the first position
4. Inputs will be replayed exactly as recorded

### Controls

- **W/A/S/D**: Movement
- **Space**: Jump
- **Shift**: Boost
- **Ctrl**: Powerslide
- **Arrow Keys**: Car rotation
- **Mouse**: Camera control

## Troubleshooting

### Common Issues

#### "Process not found"
- Make sure Rocket League is running
- Check that the process name is correct (usually "RocketLeague")

#### "DLL injection failed"
- Run as Administrator
- Disable antivirus temporarily
- Check Windows Defender exclusions

#### "DLL not found"
- Ensure all files are in the same directory
- Run `build.bat` to compile the project

#### "Memory access denied"
- Run as Administrator
- Disable antivirus
- Check Windows Defender settings

#### "Build failed"
- Install Visual Studio or Build Tools
- Ensure .NET Framework 4.8 is installed
- Check that all source files are present

### Memory Offsets

The memory offsets in `MemoryManager.cs` are specific to certain Rocket League versions. If the mod doesn't work:

1. Use a memory scanner like Cheat Engine
2. Find the correct offsets for your game version
3. Update the offsets in `MemoryManager.cs`
4. Rebuild the project

### Antivirus Issues

Some antivirus software may flag the DLL injection as malicious:

1. Add the project folder to exclusions
2. Temporarily disable real-time protection
3. Use Windows Defender exclusions

## File Structure

```
RocketLeagueTAS/
├── RocketLeagueTAS.sln          # Visual Studio solution
├── build.bat                    # Windows build script
├── build.ps1                    # PowerShell build script
├── launch.bat                   # Quick launcher
├── README.md                    # This file
├── SETUP.md                     # Setup guide
├── RocketLeagueTAS.DLL/         # Main TAS DLL
├── RocketLeagueTAS.GUI/         # GUI application
├── RocketLeagueTAS.Injector/    # DLL injector
└── Output/                      # Compiled files (after build)
```

## Advanced Configuration

### Custom Memory Offsets

Edit `RocketLeagueTAS.DLL/MemoryManager.cs`:

```csharp
// Update these offsets for your game version
private const long CAR_POSITION_OFFSET = 0x01C8F2E8;
private const long CAR_ROTATION_OFFSET = 0x01C8F2F4;
// ... etc
```

### Recording Settings

Edit `RocketLeagueTAS.DLL/TASCore.cs`:

```csharp
// Change recording frequency (default: 1000 FPS)
Thread.Sleep(1); // 1ms = 1000 FPS
```

### GUI Customization

Edit `RocketLeagueTAS.GUI/TASGUI.Designer.cs` to modify the interface.

## Safety and Legal

- **Use only in offline modes** or private matches
- **Not for competitive play** - may be detected by anti-cheat
- **Educational purposes only** - for learning and speedrunning
- **Use at your own risk** - may violate game terms of service

## Support

If you encounter issues:

1. Check this setup guide
2. Verify all prerequisites are met
3. Check the troubleshooting section
4. Ensure you're running as Administrator
5. Try disabling antivirus temporarily

## Contributing

To contribute to this project:

1. Fork the repository
2. Make your changes
3. Test thoroughly
4. Submit a pull request

## License

This project is for educational purposes only. Use responsibly and in accordance with Rocket League's terms of service.