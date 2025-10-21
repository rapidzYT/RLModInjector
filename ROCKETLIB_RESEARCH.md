# 🚀 RocketLib Research & Integration Plan

## What is RocketLib?

RocketLib is a library that hooks into Rocket League and provides:
- ✅ **Car position** (X, Y, Z)
- ✅ **Ball position** (X, Y, Z)  
- ✅ **Translation factors** (velocity X, Y, Z)
- ✅ **Rotation factors** (rotation X, Y, Z)
- ✅ **Real-time entity manipulation**

**Found at:** https://github.com/h311d1n3r/RocketLib

---

## 🔍 How It Works

### Memory Hooking:
```cpp
// Hooks into RocketLeague.exe at offset 0xebd720
// Intercepts entity updates every frame
SIZE_T off = 0xebd720;
SIZE_T addr = (SIZE_T)GetModuleHandleA("RocketLeague.exe") + off;
```

### Entity Access:
```cpp
Entity ball;
Entity battleCar;
Game game = Game(&battleCar, &ball);

// Read position
float x = ball.getX();
float y = ball.getY();

// Write velocity
ball.setTranslationFactorY(20); // Make ball bounce up!
```

---

## ⚠️ The Problem

**RocketLib does NOT provide input injection!**

It gives you:
- ✅ Position control
- ✅ Velocity control  
- ✅ Rotation control
- ❌ NO input control (W, A, S, D, Space, etc.)

**For TAS, we need INPUTS not just position!**

---

## 🎯 Solutions for Input Control

### Option 1: Memory Scan for Input Buffer (Recommended)

Use **Cheat Engine** to find where RL stores inputs:

**Steps:**
1. Open RL in Cheat Engine
2. Hold W, search for changed values
3. Release W, search for unchanged values
4. Repeat until you find input addresses
5. Use those offsets in MemoryManager

**Example:**
```cpp
// After finding offsets with Cheat Engine
struct RLInputBuffer {
    bool throttle;      // Offset: 0x????
    bool brake;         // Offset: 0x????
    bool steerLeft;     // Offset: 0x????
    bool steerRight;    // Offset: 0x????
    bool jump;          // Offset: 0x????
    bool boost;         // Offset: 0x????
    // etc...
};

uintptr_t inputBase = FindPlayerController();
auto* inputs = (RLInputBuffer*)(inputBase + INPUT_OFFSET);
inputs->throttle = true; // Direct input injection!
```

### Option 2: Hook Windows Raw Input API

Hook `GetRawInputData` or `RegisterRawInputDevices`:

```cpp
typedef UINT(WINAPI* GetRawInputDataFn)(HRAWINPUT, UINT, LPVOID, PUINT, UINT);
GetRawInputDataFn OriginalGetRawInputData;

UINT WINAPI HookGetRawInputData(...) {
    // Inject TAS inputs here before RL processes them
    if (isReplaying) {
        ModifyInputData(...);
    }
    return OriginalGetRawInputData(...);
}
```

### Option 3: Hook DirectInput/XInput

RL might use DirectInput or XInput for controller support:

```cpp
// Hook IDirectInput8::GetDeviceState
typedef HRESULT(STDMETHODCALLTYPE* GetDeviceStateFn)(IDirectInputDevice8*, DWORD, LPVOID);

HRESULT STDMETHODCALLTYPE HookGetDeviceState(..., LPVOID data) {
    HRESULT result = OriginalGetDeviceState(..., data);
    
    if (isReplaying) {
        // Modify the input state with TAS inputs
        auto* state = (DIJOYSTATE2*)data;
        ApplyTASInputs(state);
    }
    
    return result;
}
```

### Option 4: Search for Similar Projects

Look for:
- **Rocket League input mods**
- **Unreal Engine 3 input hooking** (RL uses UE3)
- **BakkesMod source code** (if available)

---

## 🔥 Hybrid Approach (Best for TAS!)

**Combine RocketLib + Input Hooking:**

1. **Use RocketLib for:**
   - State management (position, velocity)
   - Detecting when car/ball change
   - Verifying TAS accuracy

2. **Use Input Hooking for:**
   - Recording actual button presses
   - Replaying inputs precisely
   - True input-level TAS

**Architecture:**
```
TAS Mod
├── RocketLib Integration
│   ├── Read car/ball state
│   ├── Verify replay accuracy
│   └── Save initial conditions
└── Input Hook Layer
    ├── Record inputs (W, A, S, D, etc.)
    ├── Replay inputs frame-perfect
    └── Hook at OS/API level
```

---

## 📝 Recommended Next Steps

### Step 1: Use Cheat Engine (Easiest)

**I'll help you find input offsets:**

1. Download Cheat Engine
2. Attach to RocketLeague.exe
3. Search for input values
4. Document the offsets
5. Update MemoryManager.cpp

**Then inputs will work!** ✅

### Step 2: Research More

Search for:
- "Rocket League input hooking"
- "Unreal Engine 3 input injection"
- "BakkesMod input source code"
- GitHub: rocket league + input

### Step 3: Try Raw Input Hook

I can add a `GetRawInputData` hook to intercept inputs before RL sees them.

---

## ❓ Which Approach Do You Want?

**A:** Use Cheat Engine to find input offsets (I'll guide you!) 🔍  
**B:** Add Raw Input API hooking (I'll code it!) 🪝  
**C:** Search for more RL modding resources first 📚  
**D:** Try DirectInput/XInput hooking 🎮  

**Your choice?** 🤔
