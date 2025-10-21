# 🔍 Research: Proper Input Injection for Rocket League

## The Problem

`keybd_event()` doesn't work well with games because:
- Games use DirectInput, XInput, or Raw Input
- They bypass Windows keyboard events
- Rocket League uses Unreal Engine's input system

---

## 🎮 How BakkesMod Actually Works

BakkesMod uses the **Unreal Engine SDK** approach:

### What BakkesMod Does:
1. **Finds the PlayerController object** in memory
2. **Writes directly to the input buffer**
3. **Hooks ProcessEvent** (Unreal Engine function)
4. **Injects inputs at the engine level**

### Why This Works:
- Bypasses Windows input completely
- Works directly with game engine
- Perfect for TAS replay
- Deterministic results

---

## ✅ Proper Solution for Rocket League TAS

You need to hook into Rocket League's Unreal Engine input system:

### Method 1: Hook PlayerController (Best)

```cpp
// Find PlayerController in memory
UPlayerController* PC = GetPlayerController();

// Set input values directly
PC->PlayerInput->aForward = 1.0f;  // Throttle
PC->PlayerInput->aStrafe = 0.5f;   // Steering
PC->PlayerInput->bJump = true;     // Jump
// etc...
```

### Method 2: Hook Input Processing Function

```cpp
// Hook the function that processes inputs
typedef void(__thiscall* ProcessInputFn)(void*, float);
ProcessInputFn OriginalProcessInput;

// In the hook, inject your TAS inputs
void __fastcall ProcessInputHook(void* thisPtr, float DeltaTime) {
    // Apply TAS inputs here
    if (isReplaying) {
        ApplyTASInputs(thisPtr);
    }
    return OriginalProcessInput(thisPtr, DeltaTime);
}
```

### Method 3: Memory Patching (Simpler but less elegant)

```cpp
// Find input struct in memory
struct RLInputs {
    float Throttle;
    float Steer;
    float Pitch;
    float Yaw;
    float Roll;
    bool Jump;
    bool Boost;
    // etc...
};

// Write directly to it
uintptr_t inputAddress = FindInputBuffer();
WriteMemory(inputAddress, &tasInputs, sizeof(RLInputs));
```

---

## 🛠️ What We Need to Fix Your Mod

### Option 1: Use BakkesMod SDK (Easiest)

BakkesMod has a plugin SDK you can use:
- https://github.com/bakkesmodorg/BakkesModSDK

**Steps:**
1. Download BakkesMod SDK
2. Create a BakkesMod plugin instead
3. Use their input injection API
4. Much easier and more reliable!

### Option 2: Find RL's Input Buffer (Advanced)

Use Cheat Engine to:
1. Find where inputs are stored in memory
2. Get the memory address
3. Write TAS inputs directly there
4. Update MemoryManager with correct offsets

### Option 3: Hook Unreal Engine Functions (Very Advanced)

1. Find Unreal Engine input functions
2. Hook them with MinHook
3. Inject inputs at engine level
4. Requires deep game knowledge

---

## 🎯 My Recommendation

### **For a Working TAS Right Now:**

**Use BakkesMod Plugin Approach!**

BakkesMod is specifically designed for Rocket League and has:
- ✅ Proper input injection
- ✅ Working hooks
- ✅ SDK with documentation
- ✅ Active community
- ✅ Already handles all the hard stuff

**I can convert your TAS mod to a BakkesMod plugin!**

This would give you:
- ✅ Working input replay (actually moves the car)
- ✅ Speed control that works
- ✅ State management that works
- ✅ Built-in GUI system
- ✅ No injection issues

---

## 🔄 Alternative: Simpler Standalone Mod

**If you don't want to use BakkesMod:**

I can create a simpler version that:
- Uses memory scanning to find input buffer
- Writes inputs directly to memory
- Works without complex hooking
- More reliable for basic TAS

---

## ❓ What Do You Prefer?

**Option A: Convert to BakkesMod Plugin** ⭐ Recommended
- Most reliable
- Proper input injection
- Everything will work
- Uses existing infrastructure

**Option B: Find Memory Offsets**
- Stay standalone
- Need to use Cheat Engine
- More work but custom solution

**Option C: Simplified Version**
- Remove complex features
- Focus on what works
- Basic but functional

---

**Which approach would you like?** I can help with any of these! 🚀
