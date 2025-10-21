# 🔍 Research: Rocket League Input Methods

## Key Findings

### 1️⃣ **Rocket League uses Unreal Engine 3**

This means inputs go through:
- **Windows Raw Input** (for keyboard/mouse)
- **XInput** (for controllers)
- **Unreal Engine's PlayerInput class**

### 2️⃣ **BakkesMod Approach** (From Community Knowledge)

BakkesMod likely uses one of these methods:

**Method A: Hook ProcessEvent**
```cpp
// Unreal Engine 3's ProcessEvent function
// Called for every game event including inputs
typedef void(__thiscall* ProcessEventFn)(void*, void*, void*);

void HookProcessEvent(void* obj, void* function, void* params) {
    // Modify input params here
    if (isInputEvent(function)) {
        InjectTASInputs(params);
    }
    return OriginalProcessEvent(obj, function, params);
}
```

**Method B: Hook PlayerController->PlayerInput**
```cpp
// Find PlayerController in memory
// Access PlayerInput structure
struct PlayerInput {
    float aBaseX;        // Mouse X axis
    float aBaseY;        // Mouse Y axis  
    float aForward;      // W/S axis (throttle/brake)
    float aStrafe;       // A/D axis (steering)
    bool bJump;          // Jump button
    // etc...
};

// Write directly to it
playerInput->aForward = 1.0f;  // Full throttle!
playerInput->bJump = true;      // Jump!
```

**Method C: Hook Windows Input Functions**
```cpp
// Hook GetAsyncKeyState, GetKeyState, or GetRawInputData
// Modify return values to fake inputs
```

### 3️⃣ **Memory Addresses Needed**

To write directly to RL's input buffer, you need:

**PlayerController offset** (changes with RL updates!)
- Usually at: `RocketLeague.exe + OFFSET`
- Offset changes every game patch!
- Need to use **pattern scanning** to find it

**PlayerInput offset** (relative to PlayerController)
- Usually at: `PlayerController + 0x???`
- More stable than absolute addresses

---

## 🎯 **Practical Solutions**

### **Solution 1: Raw Input Hook (Easiest to Implement)**

Hook `GetRawInputData` to inject inputs:

```cpp
#include <MinHook.h>

typedef UINT(WINAPI* GetRawInputDataFn)(HRAWINPUT, UINT, LPVOID, PUINT, UINT);
GetRawInputDataFn OriginalGetRawInputData = nullptr;

UINT WINAPI HookGetRawInputData(HRAWINPUT hRawInput, UINT uiCommand, 
                                 LPVOID pData, PUINT pcbSize, UINT cbSizeHeader) {
    UINT result = OriginalGetRawInputData(hRawInput, uiCommand, pData, pcbSize, cbSizeHeader);
    
    if (pData && uiCommand == RID_INPUT) {
        RAWINPUT* raw = (RAWINPUT*)pData;
        
        if (raw->header.dwType == RIM_TYPEKEYBOARD) {
            // Modify keyboard input!
            if (g_TASMod && g_TASMod->IsReplaying()) {
                InputFrame frame = g_TASMod->GetCurrentInput();
                
                // Inject TAS keyboard inputs
                if (frame.throttle && raw->data.keyboard.VKey == 'W') {
                    raw->data.keyboard.Flags = RI_KEY_MAKE; // Press
                } else if (!frame.throttle && raw->data.keyboard.VKey == 'W') {
                    raw->data.keyboard.Flags = RI_KEY_BREAK; // Release
                }
                // Same for other keys...
            }
        }
    }
    
    return result;
}

// In initialization:
MH_CreateHookApi(L"user32.dll", "GetRawInputData", &HookGetRawInputData, 
                 (LPVOID*)&OriginalGetRawInputData);
MH_EnableHook(MH_ALL_HOOKS);
```

**Pros:**
- ✅ Works at OS level
- ✅ No game-specific offsets needed
- ✅ Survives game updates

**Cons:**
- ⚠️ Might not work if RL uses DirectInput
- ⚠️ Timing could be tricky

---

### **Solution 2: Pattern Scanning for PlayerController**

Find PlayerController dynamically:

```cpp
// Scan for known patterns in RocketLeague.exe
uintptr_t FindPlayerController() {
    // Pattern for PlayerController access
    // This changes per RL version!
    const char* pattern = "\x48\x8B\x0D\x00\x00\x00\x00\x48\x85\xC9\x74";
    const char* mask = "xxx????xxxx";
    
    uintptr_t result = PatternScan("RocketLeague.exe", pattern, mask);
    if (result) {
        // Calculate actual address from pattern
        int32_t offset = *(int32_t*)(result + 3);
        return result + offset + 7;
    }
    return 0;
}
```

Then write to input directly:

```cpp
struct UPlayerInput {
    char pad[0x64];
    float aForward;      // +0x64
    float aStrafe;       // +0x68
    float aUp;           // +0x6C
    // ...
};

uintptr_t playerController = FindPlayerController();
UPlayerInput* input = *(UPlayerInput**)(playerController + 0x???);
input->aForward = tasFrame.throttle ? 1.0f : 0.0f;
```

**Pros:**
- ✅ Direct input injection
- ✅ Most accurate for TAS
- ✅ How BakkesMod likely works

**Cons:**
- ⚠️ Need to find pattern for your RL version
- ⚠️ Breaks on every RL update
- ⚠️ Requires reverse engineering

---

### **Solution 3: SendInput API (Simpler than Raw Input)**

Use `SendInput` instead of `keybd_event`:

```cpp
void SimulateInput(bool pressed, WORD vkCode) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = vkCode;
    input.ki.dwFlags = pressed ? 0 : KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

// In ApplyInputs:
SimulateInput(frame.throttle, 'W');
SimulateInput(frame.brake, 'S');
SimulateInput(frame.jump, VK_SPACE);
// etc...
```

**Pros:**
- ✅ Easy to implement
- ✅ No hooking needed
- ✅ Works immediately

**Cons:**
- ⚠️ Might not work with RL (game might ignore it)
- ⚠️ Less precise timing

---

## 🚀 **What I Recommend**

### **Try These in Order:**

1. **First: Try `SendInput` instead of `keybd_event`**
   - Quick to test
   - Might just work!
   - 5 minute fix

2. **Second: Add Raw Input Hook**
   - More reliable
   - Intercepts before RL
   - 30 minute implementation

3. **Third: Use Cheat Engine**
   - Find PlayerInput address
   - Write inputs directly
   - Most accurate
   - 1-2 hour process

4. **Last Resort: Use RocketLib + Manual Control**
   - Use velocity injection instead of inputs
   - Not true TAS but works
   - Alternative approach

---

## 💡 **Next Steps**

**I can implement RIGHT NOW:**

**Option A:** Replace `keybd_event` with `SendInput` (quick test!) ⚡  
**Option B:** Add Raw Input API hook (more reliable) 🪝  
**Option C:** Guide you through Cheat Engine (most accurate) 🔍  
**Option D:** Integrate RocketLib (different approach) 🚀  

**Which one should I do first?** 🤔
