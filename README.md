# Rocket League TAS (Tool-Assisted Speedrun) Mod

A comprehensive Rocket League mod similar to BakkesMod that provides TAS functionality with recording and replay capabilities.

## Features

- **Input Recording**: Records all button presses, mouse movements, and timing with high precision
- **Input Replay**: Replays recorded inputs exactly as they were recorded
- **State Teleportation**: Teleports car and ball to the first position when starting replay
- **Memory Manipulation**: Direct manipulation of car and ball positions, velocities, and rotations
- **GUI Interface**: Easy-to-use graphical interface for controlling TAS functions
- **DLL Injection**: Seamless injection into Rocket League process

## Components

### 1. RocketLeagueTAS.DLL
The main DLL that gets injected into Rocket League. Contains:
- Input recording and replay system
- Memory manipulation for game state
- TAS core functionality

### 2. RocketLeagueTAS.GUI
Standalone GUI application for controlling TAS functions:
- Start/Stop recording
- Start/Stop replay
- Load/Save recordings
- Pause/Resume functionality
- Teleport to start position

### 3. RocketLeagueTAS.Injector
DLL injector that injects the TAS DLL into Rocket League process.

## How to Use

### Prerequisites
- .NET Framework 4.8
- Rocket League installed
- Administrator privileges (for DLL injection)

### Installation
1. Build the solution using Visual Studio or MSBuild
2. Copy all files to a single directory
3. Run as Administrator

### Usage
1. Start Rocket League
2. Run `RocketLeagueTAS.Injector.exe` as Administrator
3. The TAS GUI will appear in Rocket League
4. Use the GUI to control recording and replay

### Recording
1. Click "Start" in the Recording section
2. Play Rocket League normally - all inputs are recorded
3. Click "Stop" when finished
4. Save the recording to a file

### Replaying
1. Load a previously saved recording
2. Click "Start" in the Replay section
3. The car and ball will teleport to the first position
4. Inputs will be replayed exactly as recorded

## Technical Details

### Input Recording
- Records at 1000 FPS for maximum precision
- Captures all keyboard inputs (WASD, Space, Shift, Ctrl, Arrow keys)
- Records mouse position
- Stores timestamps with microsecond precision

### Memory Manipulation
- Direct memory access to Rocket League process
- Manipulates car position, rotation, velocity, and angular velocity
- Manipulates ball position, velocity, and angular velocity
- Uses Windows API for process memory access

### File Format
Recordings are saved in binary format with:
- Input states with timestamps
- Game state snapshots
- Metadata (creation time, version)

## Safety Notes

- This mod modifies game memory and may be detected by anti-cheat systems
- Use only in offline modes or private matches
- Always backup your recordings
- The mod is for educational and speedrunning purposes only

## Building

### Requirements
- Visual Studio 2019 or later
- .NET Framework 4.8 SDK

### Build Steps
1. Open `RocketLeagueTAS.sln` in Visual Studio
2. Build the solution (Ctrl+Shift+B)
3. Output files will be in `bin/Debug` or `bin/Release` folders

### Project Structure
```
RocketLeagueTAS/
├── RocketLeagueTAS.sln
├── RocketLeagueTAS.DLL/
│   ├── TASCore.cs
│   ├── InputRecorder.cs
│   ├── InputReplayer.cs
│   ├── MemoryManager.cs
│   ├── GameState.cs
│   └── DllMain.cs
├── RocketLeagueTAS.GUI/
│   ├── TASGUI.cs
│   ├── TASGUI.Designer.cs
│   └── Program.cs
└── RocketLeagueTAS.Injector/
    ├── DLLInjector.cs
    └── Program.cs
```

## Troubleshooting

### Common Issues
1. **"Process not found"**: Make sure Rocket League is running
2. **"DLL injection failed"**: Run as Administrator
3. **"DLL not found"**: Ensure all files are in the same directory
4. **"Memory access denied"**: Run as Administrator and disable antivirus

### Memory Offsets
The memory offsets in `MemoryManager.cs` are specific to certain Rocket League versions. You may need to update them for different game versions.

## License

This project is for educational purposes only. Use at your own risk.

## Disclaimer

This mod is not affiliated with Psyonix or Epic Games. Use responsibly and in accordance with Rocket League's terms of service.