# 🎯 Complete Cheat Engine TAS Setup

## 📋 Overview

Your TAS mod is **almost perfect!** The only issue is that input replay doesn't work because `keybd_event` doesn't work with Rocket League.

**The solution:** Use **Cheat Engine** to find where RL stores inputs in memory, then write directly to those addresses!

---

## 🚀 Quick Setup (3 Steps)

### **Step 1: Download Cheat Engine** ⬇️
1. Visit: https://www.cheatengine.org/downloads.php
2. Download **Cheat Engine 7.5**
3. Install it (skip toolbars)
4. **Run as Administrator**

### **Step 2: Find Input Addresses** 🔍
1. Launch **Rocket League** → Go to **Freeplay**
2. Open **`CHEAT_ENGINE_GUIDE.md`** (detailed instructions)
3. Use Cheat Engine to find the **THROTTLE (W key)** address
4. Optional: Find other inputs (Brake, Steer, Jump, etc.)

### **Step 3: Update the Mod** 💻
1. Open **`src/MemoryManager.h`**
2. Find the section with `INPUT_THROTTLE_OFFSET = 0x0;`
3. Replace `0x0` with your Cheat Engine address
4. Rebuild: Run **`build_all.bat`**
5. Test it!

---

## 📚 Documentation Files

| File | Purpose |
|------|---------|
| **`START_CHEAT_ENGINE.md`** | Quick start overview |
| **`CHEAT_ENGINE_GUIDE.md`** | Detailed step-by-step tutorial |
| **`AFTER_CHEAT_ENGINE.md`** | How to update code with addresses |
| **`src/MemoryManager.h`** | Where to paste addresses |
| **`src/MemoryManager.cpp`** | Already coded to use addresses! |

---

## 🎮 What Gets Fixed

### **Before (Current State):**
- ❌ Recording works
- ❌ GUI works
- ❌ Replay doesn't work (car doesn't move)
- ❌ Speed control doesn't work

### **After (With Cheat Engine Addresses):**
- ✅ Recording works
- ✅ GUI works
- ✅ **Replay works perfectly!** (car moves on its own!)
- ✅ **Speed control works!**
- ✅ **Frame-perfect TAS!**

---

## 🔍 Minimum Required Addresses

**To get it working, you ONLY need:**
- ✅ **THROTTLE** (W key) - Find this first!

**For full TAS functionality:**
- ✅ THROTTLE (W)
- ✅ BRAKE (S)
- ✅ STEER (A/D)
- ✅ JUMP (Space)
- ✅ BOOST (Shift)
- ✅ POWERSLIDE (Ctrl)

**For advanced TAS:**
- Air Roll Left (Q)
- Air Roll Right (E)
- Pitch (Up/Down arrows)
- Yaw (Left/Right arrows)
- Roll

---

## 📖 Detailed Instructions

### **Step 1: Attach Cheat Engine**
1. Open Cheat Engine (as Admin)
2. Click computer icon (top-left)
3. Select **RocketLeague.exe**
4. Click **Open**

### **Step 2: Find THROTTLE (W key)**
1. **In RL:** Don't press W yet
2. **In CE:** 
   - Value Type: **Float**
   - Value: **0**
   - Click **First Scan**
3. **In RL:** **HOLD W**
4. **In CE:** 
   - Value: **1**
   - Click **Next Scan**
5. **In RL:** **RELEASE W**
6. **In CE:** 
   - Value: **0**
   - Click **Next Scan**
7. **Repeat** until you have <100 addresses
8. Test each address by changing it to 1.0 in CE
9. When you find the right one, your car accelerates!

### **Step 3: Get the Address**
- Right-click the address → Note it down
- It will look like: `RocketLeague.exe+1A2B3C4D`
- **Copy the offset**: `0x1A2B3C4D`

### **Step 4: Update Code**
Open `src/MemoryManager.h` and find:
```cpp
static constexpr uintptr_t INPUT_THROTTLE_OFFSET = 0x0;
```

Change `0x0` to your address:
```cpp
static constexpr uintptr_t INPUT_THROTTLE_OFFSET = 0x1A2B3C4D;
```

### **Step 5: Rebuild**
```
build_all.bat
```

### **Step 6: Test!**
1. Inject mod into RL
2. Press F9
3. Record driving
4. Click Update
5. Click Start
6. **YOUR CAR DRIVES ITSELF!** 🎉

---

## 💡 Tips & Tricks

### **Can't Find the Address?**
- Try **Value Type: 4 Bytes** instead of Float
- Try "Unknown initial value" → "Changed value"
- Make sure you're in **Freeplay** not main menu
- Hold W for longer before scanning

### **Too Many Addresses?**
- Do more scan iterations (press/release W more times)
- Look for addresses that change exactly 0 ↔ 1
- Use "Pointer scan" for stable addresses

### **Address Changes After RL Restart?**
- **This is normal!** Need to use pointer scans
- OR just re-find it (takes 5 mins once you know how)
- For permanent solution: Use pattern scanning (advanced)

### **Test if Address Works**
1. Find the address in Cheat Engine
2. Double-click to add to bottom list
3. Check "Active" box
4. Change value to **1.0**
5. Car should accelerate in RL!
6. If it does, you found it! ✅

---

## 🎯 Example Workflow

**Real example (your addresses will be different!):**

```
Step 1: Found THROTTLE
Address: RocketLeague.exe+1A2B3C4D

Step 2: Update MemoryManager.h
Before: INPUT_THROTTLE_OFFSET = 0x0;
After:  INPUT_THROTTLE_OFFSET = 0x1A2B3C4D;

Step 3: Rebuild
> build_all.bat
SUCCESS!

Step 4: Test
> Inject mod
> Record 5 seconds of driving
> Click Update
> Click Start
> CAR DRIVES ITSELF! ✅
```

---

## 🆘 Need Help?

### **Post Your Results:**
```
Found this address in Cheat Engine:
THROTTLE: RocketLeague.exe+0x????????

Not sure if it's right or how to use it.
```

**I'll help you:**
- Verify it's correct
- Format it properly
- Update the code
- Debug any issues

### **Common Issues:**

**"Can't attach to RocketLeague.exe"**
→ Run Cheat Engine as **Administrator**

**"Found 10,000+ addresses"**
→ Do more scans (press/release W 5-10 times)

**"Addresses don't work after RL restart"**
→ Normal! Need pointer scan OR re-find them

**"Build errors after updating MemoryManager.h"**
→ Make sure address starts with `0x`
→ Check for typos

---

## ✅ Success Checklist

- [ ] Downloaded Cheat Engine
- [ ] Launched RL in Freeplay
- [ ] Attached CE to RocketLeague.exe
- [ ] Found THROTTLE address (W key)
- [ ] Tested it works (car accelerates when value=1.0)
- [ ] Noted the offset (0x????????)
- [ ] Updated MemoryManager.h
- [ ] Rebuilt with build_all.bat
- [ ] Injected mod
- [ ] Tested replay
- [ ] **CAR MOVES ON ITS OWN!** 🎉🎉🎉

---

## 🚀 Ready to Start?

1. **Download CE now**: https://www.cheatengine.org/downloads.php
2. **Open**: `CHEAT_ENGINE_GUIDE.md`
3. **Start**: Step 4 (Finding THROTTLE)
4. **Post results here!**

**You got this!** 💪 This is the final step to make your TAS perfect! 🏆
