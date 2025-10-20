# Rocket League TAS Mod

> **A BakkesMod-style Tool-Assisted Speedrun mod for Rocket League with in-game overlay (F9 toggle)**

[![Platform](https://img.shields.io/badge/platform-Windows-blue.svg)](https://www.microsoft.com/windows)
[![Language](https://img.shields.io/badge/language-C%2B%2B17-orange.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/license-Educational-green.svg)](LICENSE)

---

## 🎯 Quick Start

**For New Users:**
1. Read [QUICKSTART.md](QUICKSTART.md) - Get up and running in 5 minutes
2. Read [INSTALLATION_GUIDE.md](INSTALLATION_GUIDE.md) - Detailed setup instructions
3. Read [RL_TAS_MOD_README.md](RL_TAS_MOD_README.md) - Full feature documentation

**Already Set Up?**
1. Start Rocket League
2. Run `RLTASInjector.exe` as Administrator
3. Press **F9** in-game to toggle the TAS GUI
4. Start creating TAS sequences!

---

## 🚀 Features

### ✨ Core Functionality
- 🎮 **In-Game Overlay** - Toggle with F9, doesn't interfere with gameplay
- 🎬 **Perfect Recording** - Capture all inputs with 1ms precision
- ▶️ **Exact Replay** - Pixel-perfect input reproduction
- 🔄 **Iterative Building** - Record, replay, and append to build complex sequences
- ⚡ **Speed Control** - Slow-motion recording and fast-forward replay (0.1x - 10x)
- 💾 **State Management** - Automatic car/ball position capture and restoration

### 📋 GUI Tabs

| Tab | Description |
|-----|-------------|
| **Controls** | Create TAS, start/stop, update, speed controls |
| **Settings** | Configure break inputs for replay interruption |
| **Loaded TAS** | View TAS info, save to file |
| **Files** | Browse, load, and delete saved TAS files |

---

## 📖 Documentation

| Document | Purpose |
|----------|---------|
| [QUICKSTART.md](QUICKSTART.md) | 5-minute quick start guide |
| [INSTALLATION_GUIDE.md](INSTALLATION_GUIDE.md) | Complete setup instructions |
| [RL_TAS_MOD_README.md](RL_TAS_MOD_README.md) | Full feature documentation |
| [PROJECT_SUMMARY.md](PROJECT_SUMMARY.md) | Technical overview |

---

## 🛠️ Building from Source

### 1️⃣ Prerequisites
- Windows 10/11 (64-bit)
- Visual Studio 2019+ with C++ workload
- CMake 3.15+

### 2️⃣ Setup Dependencies
```bash
# Run the dependency setup script
setup_dependencies.bat

# This will guide you through downloading:
# - ImGui (https://github.com/ocornut/imgui)
# - MinHook (https://github.com/TsudaKageyu/minhook)
```

### 3️⃣ Build
```bash
# Run the automated build script
build_all.bat

# Output will be in build/bin/Release/:
# - RLTASMod.dll
# - RLTASInjector.exe
```

---

## 🎯 How It Works

### The TAS Workflow

```
1. Load freeplay → Position car/ball
         ↓
2. New TAS → Captures starting positions
         ↓
3. Set speeds → Record: 0.5x, Replay: 1.0x
         ↓
4. Configure breaks → Jump, Boost enabled
         ↓
5. Start → Replays TAS (or records if empty)
         ↓
6. Press Jump → Stops replay, starts recording
         ↓
7. Do your inputs → Make improvements
         ↓
8. Stop → Ends recording
         ↓
9. Update → Appends to current TAS
         ↓
10. Repeat 5-9 → Build complex sequences
         ↓
11. Save TAS → Writes to file
```

### Supported Inputs

| Input | Keys | Notes |
|-------|------|-------|
| Throttle | W | Forward |
| Brake | S | Backward |
| Steer Left | A | |
| Steer Right | D | |
| Jump | Space | |
| Boost | Shift | |
| Powerslide | Ctrl | |
| Air Roll Left | Q | |
| Air Roll Right | E | |
| Pitch | Up/Down | |
| Yaw | Left/Right | |

---

## 📁 Project Structure

```
RocketLeagueTASMod/
├── src/                    # C++ source code
│   ├── TASMod.*           # Main TAS system & GUI
│   ├── InputRecorder.*    # Input recording
│   ├── InputReplayer.*    # Input playback
│   ├── TASData.*          # File I/O
│   ├── MemoryManager.*    # Game memory access
│   ├── D3D11Hook.*        # DirectX hooking
│   └── DllMain.cpp        # Entry point
├── injector/              # DLL injection tool
├── external/              # Dependencies (user downloads)
├── TAS/                   # Saved TAS files
└── docs/                  # Documentation
```

---

## ⚠️ Safety & Legal

### ⛔ Important Warnings

- ❌ **DO NOT use in online/competitive play**
- ❌ May be detected by anti-cheat systems
- ❌ May violate Rocket League Terms of Service
- ✅ **Use ONLY in offline modes** (freeplay, training)
- ✅ Educational and speedrunning purposes only
- ⚠️ **Use at your own risk**

### 🔒 What the Mod Does

- ✅ Reads game memory (positions, velocities)
- ✅ Writes game memory (state restoration)
- ✅ Hooks DirectX (GUI overlay)
- ✅ Records/simulates keyboard input
- ❌ No network activity
- ❌ No permanent file modifications
- ❌ No registry changes

---

## 🐛 Troubleshooting

| Issue | Solution |
|-------|----------|
| GUI won't open | Press F9 multiple times, check injection succeeded |
| Injection fails | Run as Administrator, disable antivirus |
| "RL not found" | Make sure Rocket League is running |
| Build errors | Run `setup_dependencies.bat` first |
| Memory offsets wrong | Update for your RL version (see docs) |

See [INSTALLATION_GUIDE.md](INSTALLATION_GUIDE.md) for detailed troubleshooting.

---

## 🤝 Contributing

Contributions are welcome! Please:
1. Fork the repository
2. Create a feature branch
3. Test thoroughly
4. Submit a pull request

---

## 📜 License

This project is for **educational purposes only**. Use responsibly and in accordance with Rocket League's Terms of Service.

---

## 🙏 Credits

- **ImGui** - Omar Cornut ([ocornut](https://github.com/ocornut))
- **MinHook** - Tsuda Kageyu ([TsudaKageyu](https://github.com/TsudaKageyu))
- **Inspired by** - BakkesMod

---

## 📞 Support

- 📖 Read the documentation in this repository
- 🐛 Open an issue for bugs
- 💡 Open a discussion for questions
- ⭐ Star the repo if you find it useful!

---

**Disclaimer**: Not affiliated with Psyonix or Epic Games. All trademarks belong to their respective owners.

---

Made with ❤️ for the Rocket League community