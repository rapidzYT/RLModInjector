# 📝 After Finding Addresses with Cheat Engine

## You Found the Addresses! Now What?

Once you've used Cheat Engine to find the input addresses, follow these steps to update the mod:

---

## 📋 Step 1: Format Your Addresses

You should have something like this from Cheat Engine:

```
THROTTLE:   RocketLeague.exe + 0x1A2B3C4D
BRAKE:      RocketLeague.exe + 0x1A2B3C51
STEER:      RocketLeague.exe + 0x1A2B3C55
JUMP:       RocketLeague.exe + 0x1A2B3C59
BOOST:      RocketLeague.exe + 0x1A2B3C5D
POWERSLIDE: RocketLeague.exe + 0x1A2B3C61
```

**Extract just the OFFSET part** (the hex number after the `+`)

---

## 🔧 Step 2: Update MemoryManager.h

1. Open `src/MemoryManager.h` in a text editor
2. Find this section:

```cpp
// TODO: Replace these with addresses found using Cheat Engine
static const uintptr_t INPUT_BASE_OFFSET = 0x0;        // Base pointer to input structure
static const uintptr_t INPUT_THROTTLE_OFFSET = 0x0;    // W key (float: 0.0 or 1.0)
static const uintptr_t INPUT_BRAKE_OFFSET = 0x0;       // S key (float: 0.0 or 1.0)
static const uintptr_t INPUT_STEER_OFFSET = 0x0;       // A/D keys (float: -1.0 to 1.0)
static const uintptr_t INPUT_JUMP_OFFSET = 0x0;        // Space (byte: 0 or 1)
static const uintptr_t INPUT_BOOST_OFFSET = 0x0;       // Shift (byte: 0 or 1)
static const uintptr_t INPUT_POWERSLIDE_OFFSET = 0x0;  // Ctrl (byte: 0 or 1)
```

3. **Replace the `0x0` values** with your Cheat Engine addresses:

**Example:**
```cpp
// Addresses found with Cheat Engine on 2025-10-20
static const uintptr_t INPUT_BASE_OFFSET = 0x0;           // Not needed if using direct offsets
static const uintptr_t INPUT_THROTTLE_OFFSET = 0x1A2B3C4D;    // W key
static const uintptr_t INPUT_BRAKE_OFFSET = 0x1A2B3C51;       // S key
static const uintptr_t INPUT_STEER_OFFSET = 0x1A2B3C55;       // A/D steering
static const uintptr_t INPUT_JUMP_OFFSET = 0x1A2B3C59;        // Space
static const uintptr_t INPUT_BOOST_OFFSET = 0x1A2B3C5D;       // Shift
static const uintptr_t INPUT_POWERSLIDE_OFFSET = 0x1A2B3C61;  // Ctrl
```

---

## 🏗️ Step 3: Rebuild the Mod

1. Open **Visual Studio Developer Command Prompt**
2. Navigate to your project:
   ```
   cd C:\Users\omars\source\repos\RLModInjector
   ```
3. Run the build script:
   ```
   build_all.bat
   ```
4. Wait for it to compile

---

## 🧪 Step 4: Test It!

1. **Inject the mod** into Rocket League
2. **Press F9** to open GUI
3. **Record a few seconds** of driving
4. **Click Update** to save
5. **Click Start** to replay

**🎉 YOUR CAR SHOULD MOVE ON ITS OWN!**

---

## 🐛 Troubleshooting

### Car doesn't move during replay:
1. **Double-check the addresses** in MemoryManager.h
2. Make sure you used the **OFFSET** not the full address
3. Verify you found the correct addresses (test in Cheat Engine by changing values)

### Build errors after editing:
1. Make sure all addresses start with `0x`
2. Check for typos in the hex values
3. Don't add commas or semicolons inside the `0x` value

### Addresses don't work after RL update:
- **Rocket League updates break addresses!**
- You'll need to find them again with Cheat Engine
- This is why BakkesMod uses pattern scanning (advanced)

---

## 📊 Advanced: Using Pointer Paths

If Cheat Engine gave you a pointer path like:

```
[[RocketLeague.exe+0x123456]+0x40]+0x10
```

This means:
- Base: `RocketLeague.exe + 0x123456`
- First offset: `0x40`
- Second offset: `0x10`

**To use this in code:**

```cpp
// In MemoryManager.cpp, modify ApplyInputs:
uintptr_t basePtr = baseAddress + 0x123456;          // Base pointer
uintptr_t firstPtr = *(uintptr_t*)basePtr;           // Dereference first
uintptr_t inputBase = *(uintptr_t*)(firstPtr + 0x40); // Dereference second
uintptr_t throttleAddr = inputBase + 0x10;           // Final address

float throttle = frame.throttle ? 1.0f : 0.0f;
WriteMemory(throttleAddr, &throttle, sizeof(float));
```

**Or tell me the pointer path and I'll implement it for you!**

---

## ✅ Success Checklist

- [ ] Found at least THROTTLE address with Cheat Engine
- [ ] Updated MemoryManager.h with the addresses
- [ ] Rebuilt the mod successfully
- [ ] Injected into Rocket League
- [ ] Opened GUI with F9
- [ ] Recorded some driving
- [ ] Clicked Update
- [ ] Clicked Start
- [ ] **CAR MOVES ON ITS OWN!** 🎉

---

## 🆘 Need Help?

**Post your Cheat Engine results here:**

```
THROTTLE:   RocketLeague.exe + 0x????????
BRAKE:      RocketLeague.exe + 0x????????
STEER:      RocketLeague.exe + 0x????????
...
```

**And I'll:**
1. Help you format them correctly
2. Update the code for you
3. Explain any issues
4. Help debug if it doesn't work

---

**Ready to find those addresses?** 🔍  
**Check CHEAT_ENGINE_GUIDE.md and let's do this!** 🚀
