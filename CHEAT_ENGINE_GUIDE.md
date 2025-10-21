# 🔍 Cheat Engine Guide - Find Rocket League Input Addresses

## 📥 Step 1: Download Cheat Engine

1. Go to: https://www.cheatengine.org/downloads.php
2. Download **Cheat Engine 7.5** (latest version)
3. Install it (skip any toolbar offers during installation)
4. Run Cheat Engine

---

## 🎮 Step 2: Launch Rocket League

1. Start Rocket League
2. Go to **Freeplay** mode
3. Make sure you can drive around

**⚠️ Important:** 
- Use **Windowed mode** or **Borderless** (easier to switch between RL and Cheat Engine)
- Settings → Video → Display Mode → Windowed/Borderless

---

## 🔗 Step 3: Attach Cheat Engine to Rocket League

1. In Cheat Engine, click the **Computer icon** (top-left)
2. Find **RocketLeague.exe** in the process list
3. Click it and press **Open**
4. You should see "RocketLeague.exe" in the window title

---

## 🔎 Step 4: Find THROTTLE Input (W key)

### Scan for W Key Pressed:

1. **In Rocket League:** Drive around freely (don't press W yet)
2. **In Cheat Engine:**
   - **Scan Type:** First Scan
   - **Value Type:** Float or 4 Bytes
   - **Value:** 0
   - Click **First Scan**

3. **In Rocket League:** **HOLD W KEY** (throttle)
4. **In Cheat Engine:**
   - **Scan Type:** Next Scan
   - **Value:** 1 (or changed value)
   - Click **Next Scan**

5. **In Rocket League:** **RELEASE W KEY**
6. **In Cheat Engine:**
   - **Value:** 0
   - Click **Next Scan**

7. **Repeat steps 3-6** until you have **less than 100 addresses** (ideally 1-10)

### Verify the Address:

1. Double-click addresses to add them to the bottom list
2. **In Rocket League:** Press and release W
3. **In Cheat Engine:** Watch the addresses - the correct one will change between 0 and 1 (or 0.0 and 1.0)
4. **Right-click** the correct address → **Find out what accesses this address**
5. Click **Yes** to attach debugger
6. **In Rocket League:** Press W a few times
7. You'll see code accessing this address - this confirms it's the input!

### Get the Address:

- **Right-click** the address → **Pointer scan for this address**
- OR just note the address (like `1A2B3C4D`) - we'll use it later

**Example:** `RocketLeague.exe+1A2B3C4D` or static address `0x7FF61A2B3C4D`

---

## 🔎 Step 5: Find Other Inputs

Repeat Step 4 for each input:

### BRAKE (S key):
- Search for 0 when not pressed
- Search for 1 when pressing S
- Find the address

### STEER LEFT (A key):
- Search for 0 when not pressed
- Search for -1 or negative value when pressing A
- (Steering might be -1.0 to 1.0 range)

### STEER RIGHT (D key):
- Search for 0 when not pressed
- Search for 1 when pressing D

### JUMP (Space):
- **Value Type:** Byte (or 1 byte)
- Search for 0 when not pressed
- Search for 1 when pressing Space

### BOOST (Shift):
- **Value Type:** Byte
- Search for 0 when not pressed
- Search for 1 when pressing Shift

### POWERSLIDE (Ctrl):
- **Value Type:** Byte
- Search for 0 when not pressed
- Search for 1 when pressing Ctrl

---

## 📝 Step 6: Document All Addresses

Create a list like this:

```
THROTTLE:   RocketLeague.exe + 0x1A2B3C4D  (or static: 0x7FF61A2B3C4D)
BRAKE:      RocketLeague.exe + 0x1A2B3C51
STEER:      RocketLeague.exe + 0x1A2B3C55
JUMP:       RocketLeague.exe + 0x1A2B3C59
BOOST:      RocketLeague.exe + 0x1A2B3C5D
POWERSLIDE: RocketLeague.exe + 0x1A2B3C61
```

**⚠️ IMPORTANT:**
- If the address looks like `RocketLeague.exe+OFFSET`, use the OFFSET
- If it's a green address (static), note the full address
- We need **OFFSETS** not full addresses (addresses change each run!)

---

## 🔧 Step 7: Find the Base Pointer (Advanced)

If addresses are green (static), we need to find the pointer path:

1. **Right-click** an address → **Pointer scan for this address**
2. Save the scan results
3. **Restart Rocket League**
4. **Rescan for this address** (it will be different now)
5. **Pointer scan** → **Filter to new location**
6. You'll get pointer paths like: `[RocketLeague.exe+0x123456]+0x40+0x10`

This gives us:
- **Base:** `RocketLeague.exe+0x123456`
- **Offsets:** `0x40, 0x10`

---

## 💻 Step 8: Update Your Mod

Once you have the addresses, **tell me** and I'll update the code!

**What I need from you:**

```
Found these addresses:

THROTTLE:   RocketLeague.exe + 0x????????
BRAKE:      RocketLeague.exe + 0x????????
STEER:      RocketLeague.exe + 0x????????
JUMP:       RocketLeague.exe + 0x????????
BOOST:      RocketLeague.exe + 0x????????
POWERSLIDE: RocketLeague.exe + 0x????????

Or if using pointers:
Base:       RocketLeague.exe + 0x????????
Offsets:    0x??, 0x??, 0x??
```

---

## 🎯 Quick Tips

### If you find TOO MANY addresses:
- Use **Value Type: Float** instead of 4 Bytes
- Add more scan iterations (press/release more times)
- Try searching for **changed value** instead of specific numbers

### If you find ZERO addresses:
- The input might be stored differently (try Float instead of Byte)
- The value might not be 0/1 (try "Unknown initial value" → "Changed value")
- Some inputs might be combined (steering might be one float from -1 to 1)

### To find PITCH/YAW/ROLL (analog inputs):
- **Value Type:** Float
- Search for 0 when not touching
- Search for "changed value" when moving mouse/stick
- Range is usually -1.0 to 1.0

---

## 🚨 Troubleshooting

### "Access Denied" when attaching:
- **Run Cheat Engine as Administrator**
- Right-click → Run as administrator

### Addresses change every restart:
- **This is normal!** We need to find the base pointer
- Use pointer scans (Step 7)

### Can't find any addresses:
- Make sure RL is in **Freeplay** (not main menu)
- Try different **Value Types** (Float, 4 Bytes, Byte)
- Try "Unknown initial value" scan first

---

## ✅ What Happens Next

After you find the addresses:

1. **You tell me the addresses**
2. **I update `MemoryManager.cpp`** with the offsets
3. **Rebuild the mod**
4. **Test replay** - your car should move on its own! 🚀

---

## 📹 Video Tutorial (If Stuck)

Search YouTube for:
- "Cheat Engine tutorial find keyboard inputs"
- "Cheat Engine pointer scan tutorial"
- "Game hacking with Cheat Engine"

---

## 🎮 Ready to Start?

1. Download Cheat Engine
2. Launch RL in Freeplay
3. Follow Step 4 to find THROTTLE (W key)
4. **Post your results here!**

**Good luck!** 🍀 This will make your TAS work perfectly! 💪

---

## Alternative: Test Mode

If you want to **test if an address works** before doing all of them:

1. Find THROTTLE address
2. **In Cheat Engine:** Select it → Check **"Active"** box → Set **Value to 1.0**
3. **In Rocket League:** Your car should accelerate on its own!
4. If it works, you found it! Continue finding the rest!
