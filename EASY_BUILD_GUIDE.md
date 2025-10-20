# 🚀 Easy Build Guide - No Experience Needed!

## You Got an Error? Don't Worry! 👍

If you saw: **"Visual Studio compiler not found!"**

This just means you need to install some free tools first. It's easy!

---

## 🎯 Your Goal

Get these installed:
1. ✅ Visual Studio (the compiler)
2. ✅ CMake (the build tool)
3. ✅ ImGui & MinHook (the libraries)

Then you can build the mod!

---

## 📝 Step-by-Step Instructions

### Step 1: Install Visual Studio (10-30 minutes)

This is the compiler that turns source code into a working program.

**Download Visual Studio Community 2022** (FREE):
1. Go to: https://visualstudio.microsoft.com/downloads/
2. Click the big blue "Free download" button under "Community 2022"
3. Run the downloaded file (might be called `vs_community__xxx.exe`)

**Install the C++ Tools:**
1. The installer will open with a list of options
2. Find and **CHECK** the box that says:
   ```
   ☑ Desktop development with C++
   ```
3. Click "Install" (bottom right)
4. Wait 10-30 minutes (downloads about 6-8 GB)
5. You can close the installer when done

**Verify:**
- Press Windows key
- Type: "developer command"
- You should see: "Developer Command Prompt for VS 2022"
- If you see it, you're good! ✅

---

### Step 2: Install CMake (5 minutes)

CMake is the tool that sets up the build process.

**Download CMake:**
1. Go to: https://cmake.org/download/
2. Scroll down to "Latest Release"
3. Download: `cmake-X.XX.X-windows-x86_64.msi` (the Windows installer)

**Install:**
1. Run the downloaded MSI file
2. **IMPORTANT**: When asked about PATH, select:
   ```
   ☑ Add CMake to the system PATH for all users
   ```
3. Click "Next" → "Next" → "Install"
4. Click "Finish"

**Verify:**
1. Open a NEW Command Prompt (Windows key → type "cmd")
2. Type: `cmake --version`
3. You should see version info
4. If you see it, you're good! ✅

---

### Step 3: Get Dependencies (5 minutes)

Now get the libraries (ImGui and MinHook).

**Run the helper script:**
1. In the project folder, double-click: `setup_dependencies.bat`
2. Follow the prompts:

**For ImGui:**
1. Go to: https://github.com/ocornut/imgui
2. Click the green "Code" button
3. Click "Download ZIP"
4. Extract the ZIP
5. Copy ALL contents to: `external/imgui/`

**For MinHook:**
1. Go to: https://github.com/TsudaKageyu/minhook/releases
2. Download the latest ZIP (e.g., `minhook_1_3_3.zip`)
3. Extract the ZIP
4. Copy the extracted folder to: `external/minhook/`

The structure should look like:
```
external/
├── imgui/
│   ├── imgui.h
│   ├── imgui.cpp
│   └── backends/
│       ├── imgui_impl_win32.h
│       └── imgui_impl_dx11.h
└── minhook/
    ├── include/
    │   └── MinHook.h
    └── lib/
        └── libMinHook.x64.lib
```

---

### Step 4: Build! (5 minutes)

Now you're ready to build!

**Option A: Quick Check (Recommended)**
1. Double-click: `check_build_env.bat`
2. This verifies everything is set up
3. If all checks pass, continue to Option B
4. If anything fails, fix it first

**Option B: Build the Project**

**Method 1: Using Visual Studio (Easier)**
1. Open Visual Studio
2. File → Open → CMake...
3. Select `CMakeLists.txt` from the project folder
4. Wait for CMake to configure (watch the Output window)
5. Build → Build All (or press Ctrl+Shift+B)
6. Wait for build to complete
7. Find output in: `out/build/x64-Release/bin/`

**Method 2: Using Command Line**
1. Press Windows key
2. Type: "developer command"
3. Click "Developer Command Prompt for VS 2022"
4. Navigate to the project folder:
   ```bash
   cd C:\path\to\RocketLeagueTASMod
   ```
   Replace `C:\path\to\RocketLeagueTASMod` with your actual path
5. Run:
   ```bash
   build_all.bat
   ```
6. Wait for build to complete
7. Find output in: `build/bin/Release/`

**Success looks like:**
```
========================================
Build completed successfully!
========================================

Output files:
- build\bin\Release\RLTASMod.dll
- build\bin\Release\RLTASInjector.exe
```

---

## 🎉 You're Done!

You should now have:
- ✅ `RLTASMod.dll` - The mod
- ✅ `RLTASInjector.exe` - The injector

**Next step:**
→ Read [QUICKSTART.md](QUICKSTART.md) to use the mod!

---

## ❌ Common Problems

### "Developer Command Prompt not found"

**Cause:** Visual Studio not installed correctly

**Fix:**
1. Reinstall Visual Studio Community
2. Make sure you check "Desktop development with C++"
3. Restart your computer
4. Try again

---

### "cmake is not recognized"

**Cause:** CMake not in PATH

**Fix:**
1. Reinstall CMake
2. During installation, select "Add CMake to PATH"
3. Restart your computer
4. Open a NEW command prompt
5. Try again

---

### "ImGui not found" or "MinHook not found"

**Cause:** Dependencies not in the right place

**Fix:**
1. Run `setup_dependencies.bat`
2. Follow the prompts carefully
3. Make sure files are in the exact folders specified
4. Run `check_build_env.bat` to verify

---

### Build fails with errors

**Cause:** Missing dependencies or wrong paths

**Fix:**
1. Run `check_build_env.bat` to see what's wrong
2. Fix any failed checks
3. Make sure you're in Developer Command Prompt
4. Try building again

---

### "Access denied" or "Permission denied"

**Cause:** Antivirus blocking or no admin rights

**Fix:**
1. Run as Administrator
2. Add exception for the project folder in antivirus
3. Try again

---

## 🆘 Still Stuck?

If you're still having trouble:

1. **Check the detailed guide**: [INSTALL_BUILD_TOOLS.md](INSTALL_BUILD_TOOLS.md)
2. **Verify each step**: Did you do ALL the steps above?
3. **Restart your computer**: Sometimes this helps
4. **Try the checklist**: Run `check_build_env.bat`

---

## 📋 Quick Checklist

Before asking for help, verify:
- [ ] Visual Studio Community 2022 installed
- [ ] "Desktop development with C++" checked during install
- [ ] Can find "Developer Command Prompt for VS 2022" in Start menu
- [ ] CMake installed and added to PATH
- [ ] ImGui downloaded and in `external/imgui/`
- [ ] MinHook downloaded and in `external/minhook/`
- [ ] Running from Developer Command Prompt (not regular cmd)
- [ ] In the correct project directory

---

## 💡 Tips

1. **Be patient**: First-time setup takes 30-60 minutes total
2. **Follow exactly**: Miss one step and it won't work
3. **Use Developer Command Prompt**: Regular Command Prompt won't work
4. **Check paths**: Make sure dependencies are in the right folders
5. **Restart when needed**: After installing tools, restart your PC

---

## ✅ Success Path

```
Install Visual Studio (30 min)
         ↓
Install CMake (5 min)
         ↓
Download ImGui & MinHook (5 min)
         ↓
Run check_build_env.bat (verify)
         ↓
Run build_all.bat (or use VS)
         ↓
Success! Use the mod!
```

**Total time: About 1 hour for first-time setup**

---

You can do this! Just follow the steps carefully and you'll have the mod built in no time! 🚀
