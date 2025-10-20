# Rocket League TAS Mod - Project Summary

## Overview

This is a complete Tool-Assisted Speedrun (TAS) mod for Rocket League, inspired by BakkesMod. It provides an in-game overlay with comprehensive recording and replay functionality.

## Project Structure

```
RocketLeagueTASMod/
├── src/                          # Main source code
│   ├── TASMod.h/cpp             # Core TAS system & GUI
│   ├── InputRecorder.h/cpp      # Records player inputs
│   ├── InputReplayer.h/cpp      # Replays recorded inputs
│   ├── TASData.h/cpp            # TAS file format & I/O
│   ├── MemoryManager.h/cpp      # Game memory manipulation
│   ├── D3D11Hook.h/cpp          # DirectX 11 hooking for overlay
│   └── DllMain.cpp              # DLL entry point
│
├── injector/                     # DLL injection tool
│   ├── Injector.cpp             # Injects DLL into RL process
│   └── CMakeLists.txt
│
├── external/                     # Third-party dependencies
│   ├── imgui/                   # GUI library (user downloads)
│   └── minhook/                 # Function hooking (user downloads)
│
├── TAS/                         # Saved TAS files (auto-created)
│
├── Documentation
│   ├── RL_TAS_MOD_README.md    # Main documentation
│   ├── INSTALLATION_GUIDE.md   # Detailed setup instructions
│   ├── QUICKSTART.md           # Quick start for new users
│   └── PROJECT_SUMMARY.md      # This file
│
├── Build Files
│   ├── CMakeLists.txt          # Main CMake configuration
│   ├── build_all.bat           # Automated build script
│   └── setup_dependencies.bat  # Dependency setup helper
│
└── Configuration
    └── .gitignore              # Git ignore rules
```

## Key Features Implemented

### 1. In-Game Overlay (ImGui)
- **F9 Toggle**: Show/hide GUI
- **DirectX 11 Hook**: Renders on top of game
- **Non-intrusive**: Doesn't interfere with gameplay when hidden

### 2. TAS Recording
- **High-precision capture**: 1ms resolution
- **All inputs captured**: Throttle, brake, steering, jump, boost, air roll, pitch, yaw
- **Variable speed**: Record in slow motion (0.1x to 10x)
- **State capture**: Saves car/ball position at start

### 3. TAS Replay
- **Perfect reproduction**: Exact input timing
- **Variable speed**: Slow-mo or fast-forward (0.1x to 10x)
- **Break inputs**: Configurable inputs that stop replay
- **Seamless transition**: Automatically switches to recording on break

### 4. GUI Tabs

#### Controls Tab
- Create new TAS with name
- Start/stop recording/replaying
- Update TAS with new recording
- Speed controls (record & replay)
- Real-time status display

#### Settings Tab
- Configure break inputs
- Select which inputs interrupt replay:
  - Throttle (W/S)
  - Steering (A/D)
  - Jump (Space)
  - Boost (Shift)
  - Air Roll (Q/E)

#### Loaded TAS Tab
- View TAS information
- Display initial state
- Save TAS to file
- Frame count and duration

#### Files Tab
- Browse saved TAS files
- Load previous TAS
- Delete unwanted TAS
- Refresh file list

### 5. File Management
- **Binary format**: Efficient storage
- **TAS directory**: Organized file structure
- **Load/Save**: Easy file operations
- **File browser**: In-game file selection

### 6. Memory Management
- **Position control**: Read/write car position
- **Velocity control**: Manipulate car/ball velocity
- **State restoration**: Reset to initial state
- **Direct memory access**: Low-level game manipulation

## Technical Implementation

### DLL Injection
- Uses Windows CreateRemoteThread API
- Injects into running RL process
- Administrator privileges required
- Clean injection/removal

### DirectX 11 Hooking
- MinHook library for function hooking
- Hooks Present() for rendering
- Hooks ResizeBuffers() for resolution changes
- ImGui backend for rendering

### Input System
- Windows API (GetAsyncKeyState)
- High-resolution timestamps
- Frame-based recording
- Timing-accurate replay

### Memory System
- ReadProcessMemory/WriteProcessMemory
- Offset-based addressing
- Game state capture/restore
- Version-specific offsets

### File Format
```
[Header: "RLTAS"]
[Version: 1]
[GameState: initial positions]
[FrameCount: int]
[Frames: array of InputFrame]
```

## Workflow Supported

1. **Load freeplay** → Position car/ball
2. **New TAS** → Capture starting state
3. **Set speeds** → Adjust record/replay speed
4. **Configure breaks** → Select break inputs
5. **Start** → Begin replay (or record if empty)
6. **Break input** → Stop replay, start recording
7. **Stop** → End recording
8. **Update** → Save to current TAS
9. **Repeat 5-8** → Iteratively build TAS
10. **Save TAS** → Write to file
11. **Files tab** → Manage saved TAS

## Dependencies

### Required (User Downloads)
- **ImGui**: MIT License
  - Source: https://github.com/ocornut/imgui
  - Used for: GUI rendering
  - Files needed: Core + Win32 + DX11 backends

- **MinHook**: BSD 2-Clause License
  - Source: https://github.com/TsudaKageyu/minhook
  - Used for: Function hooking
  - Files needed: Include + x64 library

### System Dependencies
- Windows 10/11
- DirectX 11
- Visual C++ Runtime

### Build Tools
- CMake 3.15+
- Visual Studio 2019+ (C++17)
- Windows SDK

## Build Process

1. **Setup dependencies**
   ```bash
   setup_dependencies.bat
   ```

2. **Run build**
   ```bash
   build_all.bat
   ```

3. **Output**
   - `build/bin/Release/RLTASMod.dll`
   - `build/bin/Release/RLTASInjector.exe`

## Usage Flow

```
User → Starts RL → Runs Injector (as Admin)
                         ↓
                    DLL injected
                         ↓
                    Hooks Present()
                         ↓
                 Initializes ImGui
                         ↓
            User presses F9 → GUI shows
                         ↓
              User creates TAS → Records
                         ↓
              User replays → Inputs played
                         ↓
             User saves → File written
```

## Safety Considerations

### What it does:
- ✅ Reads game memory (car/ball positions)
- ✅ Writes game memory (positions/velocities)
- ✅ Hooks DirectX (for rendering GUI)
- ✅ Simulates keyboard input

### What it doesn't do:
- ❌ No network activity
- ❌ No file system access (except TAS folder)
- ❌ No registry modifications
- ❌ No permanent game file changes

### Risks:
- May be detected by anti-cheat
- Use only in offline modes
- Violates ToS if used online
- Memory offsets break on updates

## Future Enhancements (Potential)

- [ ] Controller input support
- [ ] Frame-by-frame stepping
- [ ] Savestates system
- [ ] TAS comparison tool
- [ ] Macro recording
- [ ] Video export
- [ ] Auto-offset finding
- [ ] Practice mode integration
- [ ] Replay file import
- [ ] Cloud TAS sharing

## Known Limitations

1. **Memory offsets**: Version-specific, need updates
2. **Keyboard only**: Controller inputs not fully supported
3. **Offline only**: Not safe for online play
4. **Windows only**: Platform-specific APIs
5. **DirectX 11**: Won't work with DX9/12

## License & Legal

- **Educational purposes only**
- Use at your own risk
- Not affiliated with Psyonix/Epic Games
- May violate ToS
- No warranty provided

## Credits

- **ImGui**: Omar Cornut (ocornut)
- **MinHook**: Tsuda Kageyu
- **Concept**: Inspired by BakkesMod
- **Implementation**: Original work

## Contact & Support

- GitHub Issues for bugs
- Documentation for usage
- Community for sharing

---

**Project Status**: Feature Complete
**Last Updated**: 2025-10-20
**Version**: 1.0
