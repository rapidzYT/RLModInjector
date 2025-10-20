# Rocket League TAS Mod

A comprehensive Tool-Assisted Speedrun (TAS) mod for Rocket League, similar to BakkesMod, featuring an in-game overlay with recording and replay capabilities.

## Features

### Core Functionality
- **In-Game Overlay**: Press F9 to toggle the GUI overlay
- **Input Recording**: Record all inputs (throttle, brake, steering, air roll, boost, etc.)
- **Perfect Replay**: Replay recorded inputs with pixel-perfect accuracy
- **State Management**: Automatically captures and restores car/ball positions
- **Speed Control**: Adjust recording and replay speed (0.1x to 10x)
- **Iterative TAS Building**: Record, replay, and append to build complex TAS sequences

### GUI Features
Four tabs for complete TAS management:

#### 1. Controls Tab
- **New TAS**: Create a new TAS and capture initial positions
- **Start/Stop**: Begin replaying or stop current operation
- **Update**: Save the last recording to the current TAS
- **Speed Controls**: Adjust record and replay speed independently

#### 2. Settings Tab
- Configure which inputs break out of replay mode
- Options for: Throttle, Steering, Jump, Boost, Air Roll
- When enabled, pressing these inputs during replay will stop and start recording

#### 3. Loaded TAS Tab
- View current TAS information (name, frames, duration)
- See initial car and ball positions
- Save TAS to file

#### 4. Files Tab
- Browse all saved TAS files
- Load previously saved TAS
- Delete unwanted TAS files

## How to Use

### Workflow

1. **Load up freeplay or a custom map** that you would like to make a TAS for
2. **Click "New TAS"** (Controls tab) and give your TAS a name
   - This captures your current car position and ball position as the starting position
3. **Set replay & record speed** (Controls tab) to whatever you like
   - You can always change these later
4. **Select break inputs** (Settings tab) 
   - Choose which inputs will take you out of replay and begin recording
5. **Click "Start"** (Controls tab) to start replaying your TAS
   - If you have no frames yet, it will jump straight to recording
   - During replay, press any configured break input to start recording new inputs
6. **Click "Stop"** (Controls tab) when finished
7. **Click "Update"** (Controls tab) to save the recording to your TAS
   - This appends your new inputs to the existing TAS
8. **Repeat steps 5-7** until you're happy with what you've made
9. **Click "Save TAS"** (Loaded TAS tab) to save your TAS to a file
10. **Find all your saved TAS files** under the Files tab

### Controls

#### Default Rocket League Controls
- **W**: Throttle
- **S**: Brake/Reverse
- **A**: Steer Left
- **D**: Steer Right
- **Space**: Jump
- **Shift**: Boost
- **Ctrl**: Powerslide
- **Q**: Air Roll Left
- **E**: Air Roll Right
- **Arrow Keys**: Pitch/Yaw

#### TAS Mod Controls
- **F9**: Toggle TAS GUI

## Installation

### Prerequisites
- Windows 10/11 (64-bit)
- Visual Studio 2019 or later (or Build Tools)
- CMake 3.15 or later
- Rocket League installed
- Administrator privileges

### Building from Source

1. **Clone this repository**
   ```bash
   git clone <repository-url>
   cd RocketLeagueTASMod
   ```

2. **Initialize submodules** (for ImGui and MinHook)
   ```bash
   git submodule update --init --recursive
   ```

3. **Download dependencies**
   - Download ImGui from https://github.com/ocornut/imgui
   - Extract to `external/imgui/`
   - Download MinHook from https://github.com/TsudaKageyu/minhook
   - Extract to `external/minhook/`

4. **Build with CMake**
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build . --config Release
   ```

5. **Output files** will be in `build/bin/`
   - `RLTASMod.dll` - Main mod DLL
   - `RLTASInjector.exe` - Injector executable

### Quick Build (Windows)

Run the provided batch file:
```bash
build_all.bat
```

## Usage

1. **Start Rocket League**
2. **Run RLTASInjector.exe as Administrator**
3. **Press F9 in Rocket League** to open the TAS GUI
4. **Start creating your TAS!**

## File Structure

```
RocketLeagueTASMod/
├── src/
│   ├── TASMod.h/cpp          # Main TAS mod class
│   ├── InputRecorder.h/cpp   # Input recording system
│   ├── InputReplayer.h/cpp   # Input replay system
│   ├── TASData.h/cpp         # TAS data management
│   ├── MemoryManager.h/cpp   # Game memory manipulation
│   ├── D3D11Hook.h/cpp       # DirectX 11 hooking
│   └── DllMain.cpp           # DLL entry point
├── injector/
│   ├── Injector.cpp          # DLL injector
│   └── CMakeLists.txt
├── external/
│   ├── imgui/                # ImGui library
│   └── minhook/              # MinHook library
├── TAS/                      # Saved TAS files (created automatically)
├── CMakeLists.txt
└── README.md
```

## Technical Details

### Input Recording
- Records at high precision (1ms intervals)
- Captures all button states and analog inputs
- Timestamps are relative to recording start
- Supports variable recording speed

### Input Replay
- Replays inputs with exact timing
- Supports variable replay speed
- Can break out of replay on specific inputs
- Automatically loops back to recording mode

### Memory Management
- Direct memory access to Rocket League process
- Reads/writes car position, rotation, velocity, angular velocity
- Reads/writes ball position, velocity, angular velocity
- **Note**: Memory offsets may need updating for different RL versions

### File Format
TAS files are saved in binary format:
- Header: "RLTAS"
- Version: int (currently 1)
- Initial game state: GameState struct
- Frame count: int
- Frames: Array of InputFrame structs

## Troubleshooting

### "Failed to initialize D3D11 Hook"
- Make sure you're running Rocket League in DirectX 11 mode
- Try restarting Rocket League

### "Failed to initialize TAS Mod"
- Ensure Rocket League is fully loaded before injecting
- Check that you have the latest version of the mod

### "Rocket League not found"
- Make sure Rocket League is running
- The process name must be "RocketLeague.exe"

### Injection fails
- Run RLTASInjector.exe as Administrator
- Disable antivirus temporarily
- Add exception for the mod in Windows Defender

### Memory offsets are wrong
- Memory offsets in `MemoryManager.cpp` are version-specific
- Use Cheat Engine or similar to find correct offsets for your RL version
- Update the offset constants and rebuild

### GUI doesn't appear
- Make sure you're pressing F9
- Check that the DLL was injected successfully
- Try restarting Rocket League

## Safety & Legal

⚠️ **IMPORTANT WARNINGS**:
- This mod modifies game memory and may be detected by anti-cheat
- **Use ONLY in offline modes or private matches**
- **DO NOT use in competitive/online play**
- This is for educational and speedrunning purposes only
- Use at your own risk
- May violate Rocket League's Terms of Service

## Advanced Configuration

### Changing Memory Offsets

Edit `src/MemoryManager.h`:

```cpp
static constexpr uintptr_t CAR_POSITION_OFFSET = 0x01C8F2E8;
static constexpr uintptr_t CAR_ROTATION_OFFSET = 0x01C8F2F4;
// Update for your RL version
```

### Customizing Recording Rate

Edit `src/DllMain.cpp`:

```cpp
Sleep(100); // Change this value (in ms)
```

### GUI Styling

The GUI uses ImGui's dark theme by default. To customize:

Edit `src/D3D11Hook.cpp`:
```cpp
ImGui::StyleColorsDark();  // Change to StyleColorsLight() or StyleColorsClassic()
```

## Known Issues

- Memory offsets must be updated for each Rocket League update
- Some input methods (controller) may not be captured perfectly
- Anti-cheat may detect the mod in online play

## Future Improvements

- [ ] Add controller input support
- [ ] Implement frame-by-frame step through
- [ ] Add TAS comparison/diff tool
- [ ] Export TAS to video format
- [ ] Auto-update memory offsets
- [ ] Add savestates system
- [ ] Implement macro recording

## Contributing

Contributions are welcome! Please:
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## License

This project is for educational purposes only. Use responsibly and in accordance with Rocket League's terms of service.

## Disclaimer

This mod is not affiliated with Psyonix or Epic Games. All trademarks belong to their respective owners.

## Credits

- ImGui by Omar Cornut
- MinHook by Tsuda Kageyu
- Inspired by BakkesMod

## Support

For issues, questions, or contributions:
- Open an issue on GitHub
- Check existing documentation
- Review troubleshooting section

---

**Remember**: Always use this mod responsibly and ethically. Never use it to gain unfair advantages in competitive play.
