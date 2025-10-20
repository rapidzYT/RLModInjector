# 🎮 You Built It! Now Let's Use It!

## ✅ Step-by-Step Usage Guide

### Step 1: Find Your Built Files

Navigate to your build output folders and find these files:

```
RocketLeagueTAS.Injector/bin/Debug/
└── RocketLeagueTAS.Injector.exe    ← You need this

RocketLeagueTAS.DLL/bin/Debug/
└── RocketLeagueTAS.DLL.dll         ← You need this
```

**Full paths are probably:**
- `C:\Users\omars\Source\Repos\RLModInjector\RocketLeagueTAS.Injector\bin\Debug\RocketLeagueTAS.Injector.exe`
- `C:\Users\omars\Source\Repos\RLModInjector\RocketLeagueTAS.DLL\bin\Debug\RocketLeagueTAS.DLL.dll`

---

### Step 2: Create a Folder and Copy Files

1. **Create a new folder** somewhere easy to find:
   - Example: `C:\RocketLeagueTAS\`

2. **Copy these 2 files** to that folder:
   - `RocketLeagueTAS.Injector.exe`
   - `RocketLeagueTAS.DLL.dll`

**IMPORTANT:** Both files MUST be in the same folder!

---

### Step 3: Start Rocket League

1. **Launch Rocket League** normally
2. **Load into freeplay** or training
3. **Leave it running**

---

### Step 4: Run the Injector

1. Go to your folder (e.g., `C:\RocketLeagueTAS\`)
2. **Right-click** `RocketLeagueTAS.Injector.exe`
3. Select **"Run as administrator"**

**You should see:**
```
Searching for Rocket League process...
Found Rocket League! Process ID: [number]
DLL Path: [path]
Injecting DLL...
SUCCESS! TAS DLL injected successfully!
```

---

### Step 5: Use the TAS

Now the TAS is running inside Rocket League!

The C# version uses the TASCore class to:
- Record your inputs
- Replay them
- Manage game state

**Note:** The C# version doesn't have the F9 GUI overlay (that's in the C++ version). The C# version works through code/API.

---

## 🔧 What You Can Do Now

### Option A: Test Basic Functionality

The injected DLL is now running in Rocket League. You can:
1. Play normally - inputs are being captured
2. The memory manager is active
3. TAS core is initialized

### Option B: Add GUI Control (Optional)

You also built `RocketLeagueTAS.GUI.exe`. You can:
1. Run it separately (doesn't need to be in same folder)
2. Use it to control recording/replay
3. It will communicate with the injected DLL

**To use the GUI:**
```
RocketLeagueTAS.GUI/bin/Debug/RocketLeagueTAS.GUI.exe
```
Just double-click it after injecting the DLL.

---

## 🎯 What Each Part Does

| Component | What It Does |
|-----------|--------------|
| **RocketLeagueTAS.Injector.exe** | Injects the DLL into Rocket League |
| **RocketLeagueTAS.DLL.dll** | The TAS engine (recording, replay, memory) |
| **RocketLeagueTAS.GUI.exe** | Optional control panel |

---

## 🎮 Quick Test

**To verify it's working:**

1. ✅ Injector shows "SUCCESS!"
2. ✅ Rocket League didn't crash
3. ✅ You can still play normally

If all 3 are true, **it's working!** 🎉

---

## ⚠️ Important Notes

### If You Get Errors:

**"Rocket League not found"**
- Make sure RL is actually running
- Wait a few seconds after launching RL

**"DLL injection failed"**
- Run as Administrator
- Disable antivirus temporarily
- Make sure both files are in same folder

**"DLL not found"**
- Both .exe and .dll MUST be in same folder
- Check the path shown in the injector

**Rocket League crashes**
- Memory offsets may be wrong for your RL version
- Use only in offline/freeplay mode
- Restart RL and try again

---

## 🚀 Want the F9 In-Game Overlay?

The C# version you just built works, but doesn't have the F9 overlay.

**For the F9 overlay (like BakkesMod):**
- You need to build the C++ version
- See [EASY_BUILD_GUIDE.md](EASY_BUILD_GUIDE.md) for setup
- The C++ version has the full ImGui interface

---

## 📊 Comparison

| Feature | C# Version (What You Built) | C++ Version |
|---------|---------------------------|-------------|
| Build Difficulty | ⭐ Easy | ⭐⭐⭐⭐ Hard |
| GUI | Separate window | F9 in-game overlay |
| Recording | ✅ Yes | ✅ Yes |
| Replay | ✅ Yes | ✅ Yes |
| Speed Control | ✅ Yes | ✅ Yes |
| State Management | ✅ Yes | ✅ Yes |

---

## 🎉 Next Steps

Now that you have it working:

1. **Test basic injection** - Make sure it doesn't crash
2. **Try the GUI** - Run RocketLeagueTAS.GUI.exe
3. **Experiment** - See what the TAS can do
4. **Optional:** Build the C++ version for F9 overlay

---

## 📋 Quick Checklist

- [x] Built the solution successfully
- [ ] Created folder with both .exe and .dll
- [ ] Started Rocket League
- [ ] Ran injector as Administrator
- [ ] Saw "SUCCESS!" message
- [ ] Game didn't crash
- [ ] (Optional) Ran the GUI application

---

## 🆘 Still Stuck?

If you need help:
1. Check what error message you're getting
2. Make sure you're in offline/freeplay mode
3. Verify both files are in the same folder
4. Try disabling antivirus
5. Make sure you ran as Administrator

---

**You're ready to go! Start the injector and test it out!** 🚀⚽

---

## 💡 Pro Tip

Create a shortcut to the injector:
1. Right-click `RocketLeagueTAS.Injector.exe`
2. Create shortcut
3. Right-click shortcut → Properties
4. Click "Advanced" → Check "Run as administrator"
5. Now you can just double-click the shortcut!
