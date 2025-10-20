# 🚀 Let's Build Your In-Game GUI! (Step-by-Step)

I'll walk you through EVERYTHING! Just follow along! 😊

---

## 📍 Step 1: Check What You Have

Let's see what's already installed:

### Open Command Prompt and type:
```bash
cmake --version
```

**Did you see a version number?**
- ✅ **YES** → Great! Skip to Step 2
- ❌ **NO** or **"not recognized"** → Continue below

---

## 🔧 Step 1A: Install CMake (If Needed)

1. **Go to:** https://cmake.org/download/
2. **Download:** Windows x64 Installer (the .msi file)
3. **Run the installer**
4. **IMPORTANT:** Check ☑ "Add CMake to system PATH for all users"
5. Click Next → Next → Install
6. **Restart your Command Prompt**
7. Test: `cmake --version` (should work now!)

---

## 💻 Step 2: Check for Visual Studio C++

### Open Command Prompt and type:
```bash
cl
```

**What happened?**
- ✅ **Saw version info** → You have it! Skip to Step 3
- ❌ **"not recognized"** → Need to install (continue below)

---

## 🔧 Step 2A: Install Visual Studio C++ (If Needed)

### Quick Option - Build Tools Only:
1. **Go to:** https://visualstudio.microsoft.com/downloads/
2. Scroll down to **"Tools for Visual Studio"**
3. Download **"Build Tools for Visual Studio 2022"**
4. **Run the installer**
5. **Select:** ☑ Desktop development with C++
6. Click **Install** (downloads ~3-4 GB)
7. Wait 10-20 minutes

### Full Option - Visual Studio Community:
1. **Go to:** https://visualstudio.microsoft.com/downloads/
2. Download **Visual Studio Community 2022** (FREE)
3. **Run the installer**
4. **Select:** ☑ Desktop development with C++
5. Click **Install** (downloads ~6-8 GB)
6. Wait 20-30 minutes

**After installation:** Restart your computer!

---

## 📁 Step 3: Get ImGui

### Manual Download:
1. **Go to:** https://github.com/ocornut/imgui
2. Click the green **"Code"** button
3. Click **"Download ZIP"**
4. **Extract the ZIP** somewhere
5. **Copy ALL files** from the extracted folder
6. **Paste into:** `C:\Users\omars\source\repos\RLModInjector\external\imgui\`

**Create the folder if it doesn't exist!**

### What you should have:
```
external\imgui\
├── imgui.h
├── imgui.cpp
├── imgui_draw.cpp
├── imgui_tables.cpp
├── imgui_widgets.cpp
├── backends\
│   ├── imgui_impl_win32.h
│   ├── imgui_impl_win32.cpp
│   ├── imgui_impl_dx11.h
│   └── imgui_impl_dx11.cpp
└── (other files...)
```

---

## 📁 Step 4: Get MinHook

### Manual Download:
1. **Go to:** https://github.com/TsudaKageyu/minhook/releases
2. Click the **latest release** (e.g., minhook_1_3_3.zip)
3. **Download the ZIP**
4. **Extract the ZIP**
5. **Copy the extracted folder** to:
   `C:\Users\omars\source\repos\RLModInjector\external\minhook\`

### What you should have:
```
external\minhook\
├── include\
│   └── MinHook.h
└── lib\
    ├── libMinHook.x64.lib
    └── libMinHook.x86.lib
```

---

## ✅ Step 5: Verify Everything

Run this to check:
```bash
cd C:\Users\omars\source\repos\RLModInjector
check_build_env.bat
```

**Should say "All checks passed!"**

If not, it will tell you what's missing!

---

## 🏗️ Step 6: Build It!

Now for the fun part!

### Option A: Using Build Script (Easiest)

1. **Open "Developer Command Prompt for VS 2022"**
   - Press Windows key
   - Type "developer command"
   - Click it

2. **Navigate to your project:**
   ```bash
   cd C:\Users\omars\source\repos\RLModInjector
   ```

3. **Run the build script:**
   ```bash
   build_all.bat
   ```

4. **Wait 2-5 minutes**

5. **Look for:**
   ```
   Build completed successfully!
   ```

### Option B: Using Visual Studio (Alternative)

1. **Open Visual Studio**
2. **File → Open → CMake...**
3. **Select:** `C:\Users\omars\source\repos\RLModInjector\CMakeLists.txt`
4. **Wait for CMake to configure**
5. **Build → Build All** (Ctrl+Shift+B)
6. **Wait for it to finish**

---

## 📂 Step 7: Find Your Files!

After building, look here:
```
build\bin\Release\
├── RLTASMod.dll          ← The mod with in-game GUI!
└── RLTASInjector.exe     ← The injector
```

**Copy BOTH files to a new folder!**

---

## 🎮 Step 8: Test It!

1. **Create a folder:** `C:\RocketLeagueTAS\`

2. **Copy both files there:**
   - `RLTASMod.dll`
   - `RLTASInjector.exe`

3. **Start Rocket League**

4. **Go to freeplay**

5. **Run RLTASInjector.exe as Administrator**
   - Right-click → Run as administrator

6. **Look for "SUCCESS!"**

7. **In Rocket League, press F9**

8. **See the beautiful in-game GUI!** 🎉

---

## 🎨 What You'll See

When you press F9:
```
┌──────────────────────────────────┐
│  Rocket League TAS Mod           │
├──────────────────────────────────┤
│  [Controls] [Settings] [...]     │
│                                   │
│  Dark theme, smooth rendering!   │
│                                   │
└──────────────────────────────────┘
```

---

## ❓ Where Are You Now?

**Tell me which step you're on:**
- [ ] Need to install CMake
- [ ] Need to install Visual Studio
- [ ] Need to download ImGui
- [ ] Need to download MinHook
- [ ] Ready to build!
- [ ] Already building!
- [ ] Got an error!

**Let me know and I'll help!** 😊
