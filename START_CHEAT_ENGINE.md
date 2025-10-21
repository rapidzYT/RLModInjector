# 🚀 START HERE - Cheat Engine TAS Setup

## 📖 What You Need to Do

You're going to use **Cheat Engine** to find where Rocket League stores keyboard inputs in memory. Once you find these addresses, the TAS replay will work PERFECTLY!

---

## ⚡ Quick Start (3 Steps)

### **Step 1: Download Cheat Engine**
- Go to: https://www.cheatengine.org/downloads.php
- Download and install it
- **Run as Administrator**

### **Step 2: Follow the Guide**
- Open: **`CHEAT_ENGINE_GUIDE.md`** (in this folder)
- Follow it step-by-step to find input addresses
- Start with finding the **THROTTLE (W key)** address

### **Step 3: Update the Code**
- Once you find addresses, tell me!
- I'll help you update `MemoryManager.h`
- OR follow **`AFTER_CHEAT_ENGINE.md`** to do it yourself

---

## 📚 Files You'll Need

| File | What It Does |
|------|--------------|
| **`CHEAT_ENGINE_GUIDE.md`** | Step-by-step tutorial to find addresses |
| **`AFTER_CHEAT_ENGINE.md`** | How to update the code after finding addresses |
| **`src/MemoryManager.h`** | Where you'll paste the addresses |
| **`src/MemoryManager.cpp`** | Already updated to use the addresses! |

---

## 🎯 What You're Looking For

You need to find **memory addresses** for these inputs:

✅ **THROTTLE** (W key) - Most important, find this first!  
✅ **BRAKE** (S key)  
✅ **STEER LEFT** (A key)  
✅ **STEER RIGHT** (D key)  
✅ **JUMP** (Space)  
✅ **BOOST** (Shift)  
✅ **POWERSLIDE** (Ctrl)  

**Optional (for advanced TAS):**
- Air Roll Left (Q)
- Air Roll Right (E)
- Pitch/Yaw/Roll (mouse/right stick)

---

## ⏱️ How Long Will This Take?

- **First time:** 1-2 hours (learning Cheat Engine)
- **Once you know how:** 15-30 minutes
- **Finding just THROTTLE:** 10 minutes (enough to test!)

**💡 TIP:** Find just THROTTLE first, test it, then find the rest!

---

## 🆘 Need Help?

**Stuck on Cheat Engine?**
- Watch YouTube: "Cheat Engine tutorial find keyboard input"
- Read: CHEAT_ENGINE_GUIDE.md carefully
- Tell me where you're stuck!

**Found addresses but don't know what to do?**
- Post them here like this:
  ```
  THROTTLE: RocketLeague.exe + 0x1A2B3C4D
  ```
- I'll update the code for you!

---

## ✅ Success Path

```
1. Download Cheat Engine
   ↓
2. Open Rocket League in Freeplay
   ↓
3. Follow CHEAT_ENGINE_GUIDE.md
   ↓
4. Find THROTTLE address (W key)
   ↓
5. Post it here OR update MemoryManager.h
   ↓
6. Rebuild the mod
   ↓
7. Test replay - CAR MOVES! 🎉
```

---

## 🎮 Ready to Start?

1. **Download Cheat Engine** now
2. **Launch Rocket League** in Freeplay
3. **Open `CHEAT_ENGINE_GUIDE.md`**
4. **Start with Step 4** (Finding THROTTLE)

**You got this!** 💪🚀

---

## 🔥 Why This Works

**Current Problem:**
- `keybd_event` doesn't work because RL ignores Windows keyboard events

**Cheat Engine Solution:**
- Finds where RL stores input values in memory
- We write directly to that memory
- RL thinks you pressed the keys!
- **Perfect for TAS!** ✅

---

**Let's do this!** Start with `CHEAT_ENGINE_GUIDE.md` 📖
