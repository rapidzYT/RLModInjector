# Rocket League TAS Mod - Installation Guide

## Quick Start (Pre-built Release)

1. Download the latest release from the releases page
2. Extract all files to a folder
3. Start Rocket League
4. Run `RLTASInjector.exe` as Administrator
5. Press F9 in Rocket League to open the TAS GUI

## Building from Source

### Step 1: Prerequisites

#### Required Software
- **Windows 10/11** (64-bit)
- **Visual Studio 2019 or 2022** 
  - Download: https://visualstudio.microsoft.com/
  - Install "Desktop development with C++" workload
- **CMake 3.15+**
  - Download: https://cmake.org/download/
  - Make sure to add CMake to PATH during installation
- **Git**
  - Download: https://git-scm.com/

### Step 2: Download Dependencies

#### ImGui
1. Go to https://github.com/ocornut/imgui
2. Click "Code" → "Download ZIP"
3. Extract the ZIP
4. Copy the contents to `external/imgui/` in the project folder

Required files:
```
external/imgui/
├── imgui.h
├── imgui.cpp
├── imgui_draw.cpp
├── imgui_tables.cpp
├── imgui_widgets.cpp
├── backends/
│   ├── imgui_impl_win32.h
│   ├── imgui_impl_win32.cpp
│   ├── imgui_impl_dx11.h
│   └── imgui_impl_dx11.cpp
```

#### MinHook
1. Go to https://github.com/TsudaKageyu/minhook/releases
2. Download the latest release (e.g., `minhook_1_3_3.zip`)
3. Extract the ZIP
4. Copy to `external/minhook/` in the project folder

Required structure:
```
external/minhook/
├── include/
│   └── MinHook.h
└── lib/
    ├── libMinHook.x64.lib
    └── libMinHook.x86.lib
```

### Step 3: Build the Project

#### Option A: Using the Build Script (Recommended)

1. Open Command Prompt or PowerShell
2. Navigate to the project directory
3. Run the build script:
   ```bash
   build_all.bat
   ```
4. Wait for the build to complete

#### Option B: Using Visual Studio

1. Open Visual Studio
2. File → Open → CMake
3. Select `CMakeLists.txt` from the project root
4. Wait for CMake to configure
5. Build → Build All (Ctrl+Shift+B)

#### Option C: Using CMake Command Line

1. Open "Developer Command Prompt for VS 2019/2022"
2. Navigate to project directory
3. Run these commands:
   ```bash
   mkdir build
   cd build
   cmake .. -G "Visual Studio 16 2019" -A x64
   cmake --build . --config Release
   ```

### Step 4: Locate Output Files

After building, you'll find:
- `build/bin/Release/RLTASMod.dll` - The mod DLL
- `build/bin/Release/RLTASInjector.exe` - The injector

### Step 5: Prepare for Use

1. Create a new folder (e.g., `C:\RocketLeagueTAS\`)
2. Copy both files to this folder:
   - `RLTASMod.dll`
   - `RLTASInjector.exe`
3. Keep them in the same directory!

## Usage

### First Time Setup

1. **Start Rocket League**
   - Launch the game normally
   - Load into freeplay or training

2. **Run the Injector**
   - Right-click `RLTASInjector.exe`
   - Select "Run as administrator"
   - You should see: "SUCCESS! TAS Mod injected successfully!"

3. **Open the GUI**
   - In Rocket League, press **F9**
   - The TAS GUI should appear

### Creating Your First TAS

1. **Load into freeplay**
2. **Position your car and ball** where you want to start
3. **Press F9** to open the TAS GUI
4. **Go to Controls tab**
5. **Type a name** for your TAS (e.g., "test_flip")
6. **Click "New TAS"**
   - This captures the current position
7. **Click "Start"** to begin recording
8. **Perform your inputs** (drive, jump, boost, etc.)
9. **Click "Stop"** when done
10. **Click "Update"** to save the recording
11. **Click "Start"** again to replay your inputs
12. **Go to Loaded TAS tab**
13. **Click "Save TAS"** to save to a file

### Advanced Usage

#### Iterative TAS Building
1. Create a new TAS and record initial inputs
2. Click Update to save
3. Click Start to replay
4. During replay, press any enabled break input (e.g., W, Space)
5. This will stop replay and start recording from that point
6. Click Stop when done
7. Click Update to append the new inputs
8. Repeat to build complex sequences

#### Speed Control
- **Record Speed**: Slow down recording to make precise inputs
  - 0.5x = Half speed (easier to control)
  - 1.0x = Normal speed
  - 2.0x = Double speed
- **Replay Speed**: Speed up or slow down playback
  - 0.1x = Very slow (analyze frame by frame)
  - 1.0x = Normal speed
  - 10.0x = Very fast (quick testing)

#### Break Input Settings
1. Go to Settings tab
2. Enable inputs that should break out of replay:
   - **Throttle**: Pressing W or S stops replay
   - **Jump**: Pressing Space stops replay
   - **Boost**: Pressing Shift stops replay
   - etc.
3. Use these to make corrections at specific points

## Troubleshooting

### "Rocket League not found"
**Solution:**
- Make sure Rocket League is actually running
- Check Task Manager for "RocketLeague.exe"
- Wait a few seconds after game launch

### "Failed to inject DLL"
**Solutions:**
1. Run as Administrator
2. Disable antivirus temporarily
3. Add exception in Windows Defender:
   - Settings → Update & Security → Windows Security
   - Virus & threat protection → Manage settings
   - Add or remove exclusions → Add folder
   - Select your TAS mod folder

### "DLL not found"
**Solutions:**
- Make sure `RLTASMod.dll` is in the same folder as `RLTASInjector.exe`
- Use full paths (no spaces in folder names)

### GUI doesn't appear (F9 doesn't work)
**Solutions:**
1. Check console output - did injection succeed?
2. Try F9 several times
3. Restart Rocket League and reinject
4. Make sure you're in-game (not in menus)

### Build errors

#### "CMake not found"
- Install CMake from https://cmake.org/download/
- Add to PATH during installation
- Restart Command Prompt

#### "Cannot open include file: 'imgui.h'"
- Make sure ImGui is extracted to `external/imgui/`
- Check folder structure matches Step 2

#### "Cannot open file 'libMinHook.x64.lib'"
- Make sure MinHook is extracted to `external/minhook/`
- Check that `lib` folder contains the .lib files

#### "MSBuild not found" or "cl not found"
- Install Visual Studio with C++ workload
- Use "Developer Command Prompt for VS"

### Game crashes after injection
**Solutions:**
- Memory offsets may be wrong for your RL version
- Update offsets in `src/MemoryManager.h`
- Use only in offline/freeplay mode

### Inputs not recording properly
**Check:**
- Are you using default keyboard controls?
- Controller inputs currently not fully supported
- Make sure you clicked "Start" first

### Can't save TAS files
**Solutions:**
- Make sure you have write permissions
- Check that `TAS/` folder was created
- Run as Administrator

## Uninstalling

1. Close Rocket League
2. Delete the TAS mod folder
3. Delete any saved TAS files you don't want
4. No registry changes or permanent modifications made

## Security & Privacy

### Why Administrator?
- DLL injection requires admin privileges
- Memory manipulation requires admin access
- This is standard for game mods

### Is it safe?
- Source code is available for review
- No network connectivity
- No data collection
- Only modifies Rocket League process memory
- Does not modify game files permanently

### Antivirus Warnings
- DLL injection is flagged by some antivirus
- This is a false positive
- Add exception if you trust the source
- Always scan downloaded files

## Getting Help

### Before asking for help:
1. Read this guide completely
2. Check the main README
3. Review troubleshooting section
4. Check if issue already reported

### When reporting issues, include:
- Windows version
- Rocket League version
- Visual Studio version
- Exact error message
- Steps to reproduce
- Build output or injector console output

## Next Steps

Once installed:
1. Read the main README for detailed usage
2. Practice making simple TAS sequences
3. Experiment with speed controls
4. Try the break input feature
5. Share your TAS files!

## Updates

### Updating the Mod
1. Download new version
2. Replace old DLL and EXE files
3. Reinject into Rocket League

### Updating After RL Patches
- Memory offsets may change
- Watch for mod updates
- Or update offsets yourself (see Advanced section in README)

---

**Need more help?** Check the GitHub issues page or main documentation.
