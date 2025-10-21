#pragma once

#include <Windows.h>
#include "TASMod.h"

namespace RLTASMod {

// Virtual Xbox 360 Controller using ViGEm
class VirtualController {
public:
    VirtualController();
    ~VirtualController();
    
    bool Initialize();
    void Shutdown();
    
    // Apply TAS inputs to virtual controller
    bool ApplyInputs(const InputFrame& frame);
    
    bool IsInitialized() const { return isInitialized; }
    
private:
    bool isInitialized = false;
    
    // ViGEm handles (will be void* until we have the SDK)
    void* vigemClient = nullptr;
    void* vigemController = nullptr;
    
    // Helper to load ViGEm DLL dynamically
    HMODULE vigemDll = nullptr;
    
    // Function pointers for ViGEm API
    typedef void* (*vigem_alloc_fn)();
    typedef void (*vigem_free_fn)(void*);
    typedef int (*vigem_connect_fn)(void*);
    typedef void (*vigem_disconnect_fn)(void*);
    typedef void* (*vigem_target_x360_alloc_fn)();
    typedef void (*vigem_target_free_fn)(void*);
    typedef int (*vigem_target_add_fn)(void*, void*);
    typedef int (*vigem_target_remove_fn)(void*, void*);
    typedef int (*vigem_target_x360_update_fn)(void*, void*, void*);
    
    vigem_alloc_fn vigem_alloc = nullptr;
    vigem_free_fn vigem_free = nullptr;
    vigem_connect_fn vigem_connect = nullptr;
    vigem_disconnect_fn vigem_disconnect = nullptr;
    vigem_target_x360_alloc_fn vigem_target_x360_alloc = nullptr;
    vigem_target_free_fn vigem_target_free = nullptr;
    vigem_target_add_fn vigem_target_add = nullptr;
    vigem_target_remove_fn vigem_target_remove = nullptr;
    vigem_target_x360_update_fn vigem_target_x360_update = nullptr;
    
    bool LoadViGEmDLL();
};

// Xbox 360 Controller report structure (for when ViGEm isn't available)
#pragma pack(push, 1)
struct XUSB_REPORT {
    WORD wButtons;
    BYTE bLeftTrigger;
    BYTE bRightTrigger;
    SHORT sThumbLX;
    SHORT sThumbLY;
    SHORT sThumbRX;
    SHORT sThumbRY;
};
#pragma pack(pop)

// Button definitions
#define XUSB_GAMEPAD_DPAD_UP          0x0001
#define XUSB_GAMEPAD_DPAD_DOWN        0x0002
#define XUSB_GAMEPAD_DPAD_LEFT        0x0004
#define XUSB_GAMEPAD_DPAD_RIGHT       0x0008
#define XUSB_GAMEPAD_START            0x0010
#define XUSB_GAMEPAD_BACK             0x0020
#define XUSB_GAMEPAD_LEFT_THUMB       0x0040
#define XUSB_GAMEPAD_RIGHT_THUMB      0x0080
#define XUSB_GAMEPAD_LEFT_SHOULDER    0x0100
#define XUSB_GAMEPAD_RIGHT_SHOULDER   0x0200
#define XUSB_GAMEPAD_A                0x1000
#define XUSB_GAMEPAD_B                0x2000
#define XUSB_GAMEPAD_X                0x4000
#define XUSB_GAMEPAD_Y                0x8000

} // namespace RLTASMod
