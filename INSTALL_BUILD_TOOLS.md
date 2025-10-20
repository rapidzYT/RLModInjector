# Installing Build Tools - Step by Step Guide

## The Problem

You're seeing: **"Visual Studio compiler not found!"**

This means you need to install the C++ compiler to build the project.

---

## ✅ Solution: Install Visual Studio Build Tools

You have **2 options** (choose one):

### Option 1: Visual Studio Community (Recommended - Full IDE)

**Best for**: If you want to edit code, debug, or develop

1. **Download Visual Studio Community 2022** (FREE)
   - Go to: https://visualstudio.microsoft.com/downloads/
   - Click "Free download" under "Community 2022"

2. **Run the installer**
   - Double-click the downloaded file
   - Wait for the installer to load

3. **Select Workloads**
   - ✅ Check **"Desktop development with C++"**
   - This is the ONLY thing you need to check
   
4. **Install**
   - Click "Install" button (bottom right)
   - Wait 10-30 minutes (downloads ~6-8 GB)

5. **Done!**
   - After installation, you can run `build_all.bat` directly

---

### Option 2: Build Tools Only (Smaller - Just Compiler)

**Best for**: If you only want to build, not develop

1. **Download Build Tools for Visual Studio 2022** (FREE)
   - Go to: https://visualstudio.microsoft.com/downloads/
   - Scroll down to "All Downloads"
   - Expand "Tools for Visual Studio"
   - Click "Build Tools for Visual Studio 2022"

2. **Run the installer**
   - Double-click the downloaded file
   - Wait for the installer to load

3. **Select Workloads**
   - ✅ Check **"Desktop development with C++"**
   - Under "Installation details" (right side), make sure these are checked:
     - ✅ MSVC v143 - VS 2022 C++ x64/x86 build tools
     - ✅ Windows 10/11 SDK
     - ✅ CMake tools for Windows

4. **Install**
   - Click "Install" button
   - Wait 5-15 minutes (downloads ~3-4 GB)

5. **After installation**
   - Use the special command prompt (see below)

---

## 🚀 How to Build After Installing

### If you installed Visual Studio Community:

**Option A: Use the GUI**
1. Open Visual Studio
2. File → Open → CMake
3. Select `CMakeLists.txt` from the project folder
4. Build → Build All

**Option B: Use Command Line**
1. Open **"Developer Command Prompt for VS 2022"**
   - Press Windows key
   - Type "Developer Command Prompt"
   - Click the result
2. Navigate to your project folder:
   ```bash
   cd C:\path\to\RocketLeagueTASMod
   ```
3. Run the build script:
   ```bash
   build_all.bat
   ```

### If you installed Build Tools only:

1. Open **"Developer Command Prompt for VS 2022"**
   - Press Windows key
   - Type "Developer Command Prompt"
   - Click the result
   
2. Navigate to your project folder:
   ```bash
   cd C:\path\to\RocketLeagueTASMod
   ```

3. Run the build script:
   ```bash
   build_all.bat
   ```

---

## 🔍 Finding the Developer Command Prompt

After installing Visual Studio or Build Tools:

1. **Press Windows key**
2. **Type**: `developer command`
3. **Look for**:
   - "Developer Command Prompt for VS 2022"
   - OR "x64 Native Tools Command Prompt for VS 2022"
4. **Click it**
5. **Navigate to project** and run `build_all.bat`

---

## ⚡ Quick Test

To verify your installation:

1. Open Developer Command Prompt
2. Type: `cl`
3. You should see:
   ```
   Microsoft (R) C/C++ Optimizing Compiler Version 19.xx.xxxxx
   ...
   ```

If you see "cl is not recognized", the installation didn't work correctly.

---

## 🆘 Still Having Issues?

### "I don't see Developer Command Prompt"

**Solution:**
1. Restart your computer
2. Search again for "Developer Command Prompt"
3. If still not there, reinstall and make sure you checked "Desktop development with C++"

### "cl is not recognized"

**Solution:**
1. Make sure you selected "Desktop development with C++" during installation
2. Restart your computer
3. Try opening "x64 Native Tools Command Prompt" instead

### "CMake not found"

**Solution:**
1. Download CMake: https://cmake.org/download/
2. During installation, select "Add CMake to PATH"
3. Restart your computer
4. Try again

### "Installation is too big!"

**Minimum requirements:**
- Visual Studio Build Tools: ~3-4 GB
- Visual Studio Community: ~6-8 GB

**To reduce size:**
- Only install "Desktop development with C++"
- Uncheck optional components in the installer

---

## 📋 Complete Installation Checklist

- [ ] Downloaded Visual Studio or Build Tools installer
- [ ] Ran the installer
- [ ] Selected "Desktop development with C++"
- [ ] Waited for installation to complete
- [ ] Can find "Developer Command Prompt for VS 2022" in Start menu
- [ ] Opened Developer Command Prompt and typed `cl` - saw compiler info
- [ ] Navigated to project folder in Developer Command Prompt
- [ ] Ran `build_all.bat` successfully

---

## 🎯 Alternative: Use Pre-built Release

If you don't want to install build tools:

1. Check if there's a pre-built release available
2. Download the release ZIP
3. Extract and use directly
4. No compilation needed!

(Note: You'll still need to download ImGui/MinHook separately)

---

## 💡 Pro Tips

1. **Use the correct command prompt**
   - Regular Command Prompt → ❌ Won't work
   - Developer Command Prompt → ✅ Has compiler

2. **Keep it installed**
   - You'll need it for rebuilding after code changes
   - Needed for other C++ projects too

3. **Add to favorites**
   - Pin "Developer Command Prompt" to taskbar
   - Makes it easier to access

---

## ✅ Success!

Once installed, you should be able to:
```bash
cd C:\path\to\RocketLeagueTASMod
build_all.bat
```

And see:
```
========================================
Rocket League TAS Mod - Build Script
========================================

Configuring CMake...
Building project...
...
Build completed successfully!
```

---

**Next step after successful build:**
→ Read [QUICKSTART.md](QUICKSTART.md) to use the mod!
