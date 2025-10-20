# 🎯 Which File Should You Use?

## 📁 What Gets Built (4 Projects)

When you build the solution, **4 projects** build:

| # | Project | Output File | Do You Need It? |
|---|---------|-------------|-----------------|
| 1 | **RocketLeagueTAS.DLL** | `RocketLeagueTAS.DLL.dll` | ❌ (Auto-included) |
| 2 | **RocketLeagueTAS.GUI** | `RocketLeagueTAS.GUI.exe` | ❌ (Old version) |
| 3 | **RocketLeagueTAS.Injector** | `RocketLeagueTAS.Injector.exe` | ❌ (Old version) |
| 4 | **RocketLeagueTAS.App** | `RocketLeagueTAS.exe` | ✅ **USE THIS!** |

---

## ✅ You Only Need ONE File!

### **Use This:**
```
RocketLeagueTAS.App/bin/Debug/RocketLeagueTAS.exe
```

**This is the all-in-one GUI app I just created for you!**

---

## ❌ You DON'T Need These:

### Old Files (Ignore These):
- `RocketLeagueTAS.GUI.exe` - Old separate GUI
- `RocketLeagueTAS.Injector.exe` - Old command line injector
- `RocketLeagueTAS.DLL.dll` - Gets auto-copied to the App folder

---

## 🤔 Why Do All 4 Build?

Because the solution file includes all 4 projects for backwards compatibility and development purposes.

### Here's what they do:

**1. RocketLeagueTAS.DLL** (Library)
- Core TAS functionality
- Recording/replay engine
- Memory management
- **Used by** the other 3 projects

**2. RocketLeagueTAS.GUI** (OLD)
- Separate GUI window
- Old approach
- **Don't use** - replaced by App

**3. RocketLeagueTAS.Injector** (OLD)
- Command line injector
- Old approach
- **Don't use** - replaced by App

**4. RocketLeagueTAS.App** (NEW ✨)
- **All-in-one solution**
- **Beautiful GUI**
- **Includes injection + controls**
- **This is what you want!**

---

## 💡 How to Build Only What You Need

If you want to build ONLY the new app:

### Option 1: Set Startup Project

1. Right-click **RocketLeagueTAS.App** in Solution Explorer
2. Click **"Set as Startup Project"**
3. Press **F5** to build and run

### Option 2: Build Single Project

1. Right-click **RocketLeagueTAS.App** in Solution Explorer
2. Click **"Build"**
3. Only this project (and DLL dependency) will build

### Option 3: Disable Other Projects

1. Right-click Solution → **Configuration Manager**
2. Uncheck **Build** for:
   - RocketLeagueTAS.GUI
   - RocketLeagueTAS.Injector
3. Keep checked:
   - RocketLeagueTAS.DLL (needed)
   - RocketLeagueTAS.App (your main app)

---

## 🎯 Quick Answer

**Just use:**
```
RocketLeagueTAS.App/bin/Debug/RocketLeagueTAS.exe
```

**Forget the other 3!**

---

## 📋 What Each File Does

### RocketLeagueTAS.exe (THE ONE YOU WANT)
```
✅ Beautiful GUI
✅ One-click injection
✅ Record controls
✅ Replay controls
✅ File management
✅ Everything in one place
```

### RocketLeagueTAS.Injector.exe (OLD - Don't Use)
```
❌ Command line only
❌ No GUI
❌ Requires manual steps
❌ Replaced by the App
```

### RocketLeagueTAS.GUI.exe (OLD - Don't Use)
```
❌ Separate window
❌ Doesn't include injector
❌ Less user-friendly
❌ Replaced by the App
```

### RocketLeagueTAS.DLL.dll (Backend - Auto-managed)
```
🔧 Core engine
🔧 Used by all apps
🔧 Auto-copied where needed
🔧 You don't run this directly
```

---

## 🚀 Simple Workflow

1. **Build the solution** (builds all 4)
2. **Go to:** `RocketLeagueTAS.App/bin/Debug/`
3. **Run:** `RocketLeagueTAS.exe`
4. **Ignore the other files!**

---

## ❓ FAQ

### "Why not delete the old projects?"

I kept them for:
- Backwards compatibility
- Alternative options
- Development/testing
- Learning purposes

But **you only need the new App!**

### "Does the App need the DLL?"

Yes, but it's **automatically copied** to the App's folder during build. You don't need to do anything!

### "Can I delete the old EXEs?"

You can ignore them. They're harmless. Or you can disable them from building (see Option 3 above).

---

## ✨ Bottom Line

**4 files build, but you only need 1:**

```
RocketLeagueTAS.exe ← USE THIS! 🎯
```

**It's the all-in-one solution with everything you need!** 🎉

---

## 🎮 Ready to Use!

Just run `RocketLeagueTAS.exe` and enjoy the beautiful GUI! ✨
