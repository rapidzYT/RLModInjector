#include "VirtualController.h"
#include <cstring>

namespace RLTASMod {

VirtualController::VirtualController() {
}

VirtualController::~VirtualController() {
    Shutdown();
}

bool VirtualController::LoadViGEmDLL() {
    // Try to load ViGEmClient.dll
    vigemDll = LoadLibraryA("ViGEmClient.dll");
    if (!vigemDll) {
        // Try from system directory
        char systemPath[MAX_PATH];
        GetSystemDirectoryA(systemPath, MAX_PATH);
        strcat_s(systemPath, "\\ViGEmClient.dll");
        vigemDll = LoadLibraryA(systemPath);
    }
    
    if (!vigemDll) {
        return false;
    }
    
    // Load function pointers
    vigem_alloc = (vigem_alloc_fn)GetProcAddress(vigemDll, "vigem_alloc");
    vigem_free = (vigem_free_fn)GetProcAddress(vigemDll, "vigem_free");
    vigem_connect = (vigem_connect_fn)GetProcAddress(vigemDll, "vigem_connect");
    vigem_disconnect = (vigem_disconnect_fn)GetProcAddress(vigemDll, "vigem_disconnect");
    vigem_target_x360_alloc = (vigem_target_x360_alloc_fn)GetProcAddress(vigemDll, "vigem_target_x360_alloc");
    vigem_target_free = (vigem_target_free_fn)GetProcAddress(vigemDll, "vigem_target_free");
    vigem_target_add = (vigem_target_add_fn)GetProcAddress(vigemDll, "vigem_target_add");
    vigem_target_remove = (vigem_target_remove_fn)GetProcAddress(vigemDll, "vigem_target_remove");
    vigem_target_x360_update = (vigem_target_x360_update_fn)GetProcAddress(vigemDll, "vigem_target_x360_update");
    
    return vigem_alloc && vigem_connect && vigem_target_x360_alloc && vigem_target_add && vigem_target_x360_update;
}

bool VirtualController::Initialize() {
    if (isInitialized) return true;
    
    // Try to load ViGEm DLL
    if (!LoadViGEmDLL()) {
        MessageBoxA(NULL, 
            "ViGEmClient.dll not found!\n\n"
            "To use TAS replay, please install ViGEmBus driver:\n"
            "https://github.com/nefarius/ViGEmBus/releases\n\n"
            "The mod will continue without virtual controller support.",
            "ViGEm Not Available", 
            MB_OK | MB_ICONWARNING);
        return false;
    }
    
    // Allocate ViGEm client
    vigemClient = vigem_alloc();
    if (!vigemClient) {
        MessageBoxA(NULL, "Failed to allocate ViGEm client!", "Error", MB_OK | MB_ICONERROR);
        return false;
    }
    
    // Connect to ViGEm bus driver
    int result = vigem_connect(vigemClient);
    if (result != 0) {
        MessageBoxA(NULL, 
            "Failed to connect to ViGEm bus driver!\n\n"
            "Please make sure ViGEmBus driver is installed:\n"
            "https://github.com/nefarius/ViGEmBus/releases\n\n"
            "Error code: " + result,
            "ViGEm Connection Failed", 
            MB_OK | MB_ICONERROR);
        vigem_free(vigemClient);
        vigemClient = nullptr;
        return false;
    }
    
    // Allocate virtual Xbox 360 controller
    vigemController = vigem_target_x360_alloc();
    if (!vigemController) {
        MessageBoxA(NULL, "Failed to allocate virtual controller!", "Error", MB_OK | MB_ICONERROR);
        vigem_disconnect(vigemClient);
        vigem_free(vigemClient);
        vigemClient = nullptr;
        return false;
    }
    
    // Add controller to ViGEm bus
    result = vigem_target_add(vigemClient, vigemController);
    if (result != 0) {
        MessageBoxA(NULL, "Failed to add virtual controller to bus!", "Error", MB_OK | MB_ICONERROR);
        vigem_target_free(vigemController);
        vigem_disconnect(vigemClient);
        vigem_free(vigemClient);
        vigemController = nullptr;
        vigemClient = nullptr;
        return false;
    }
    
    isInitialized = true;
    MessageBoxA(NULL, 
        "Virtual Controller Initialized! ✅\n\n"
        "Your TAS inputs will now be sent through a virtual Xbox 360 controller.\n"
        "Rocket League will accept them perfectly!",
        "Success!", 
        MB_OK | MB_ICONINFORMATION);
    
    return true;
}

void VirtualController::Shutdown() {
    if (!isInitialized) return;
    
    if (vigemController && vigemClient) {
        vigem_target_remove(vigemClient, vigemController);
        vigem_target_free(vigemController);
        vigemController = nullptr;
    }
    
    if (vigemClient) {
        vigem_disconnect(vigemClient);
        vigem_free(vigemClient);
        vigemClient = nullptr;
    }
    
    if (vigemDll) {
        FreeLibrary(vigemDll);
        vigemDll = nullptr;
    }
    
    isInitialized = false;
}

bool VirtualController::ApplyInputs(const InputFrame& frame) {
    if (!isInitialized || !vigemController || !vigemClient) {
        return false;
    }
    
    // Create Xbox 360 controller report
    XUSB_REPORT report;
    ZeroMemory(&report, sizeof(XUSB_REPORT));
    
    // Map TAS inputs to Xbox 360 controller
    
    // Throttle (W) -> Left Trigger
    report.bLeftTrigger = frame.throttle ? 255 : 0;
    
    // Brake (S) -> Right Trigger  
    report.bRightTrigger = frame.brake ? 255 : 0;
    
    // Steering (A/D) -> Left Stick X-axis
    if (frame.steerLeft) {
        report.sThumbLX = -32767; // Full left
    } else if (frame.steerRight) {
        report.sThumbLX = 32767;  // Full right
    } else {
        report.sThumbLX = 0;      // Center
    }
    
    // Jump (Space) -> A Button
    if (frame.jump) {
        report.wButtons |= XUSB_GAMEPAD_A;
    }
    
    // Boost (Shift) -> B Button
    if (frame.boost) {
        report.wButtons |= XUSB_GAMEPAD_B;
    }
    
    // Powerslide (Ctrl) -> X Button
    if (frame.powerslide) {
        report.wButtons |= XUSB_GAMEPAD_X;
    }
    
    // Air Roll Left (Q) -> Left Bumper
    if (frame.airRollLeft) {
        report.wButtons |= XUSB_GAMEPAD_LEFT_SHOULDER;
    }
    
    // Air Roll Right (E) -> Right Bumper
    if (frame.airRollRight) {
        report.wButtons |= XUSB_GAMEPAD_RIGHT_SHOULDER;
    }
    
    // Pitch -> Right Stick Y-axis (Up/Down arrows)
    report.sThumbRY = (SHORT)(frame.pitch * 32767.0f);
    
    // Yaw -> Right Stick X-axis (Left/Right arrows)
    report.sThumbRX = (SHORT)(frame.yaw * 32767.0f);
    
    // Roll (combined with air roll buttons above)
    // If neither air roll button, use roll value for left stick Y
    if (!frame.airRollLeft && !frame.airRollRight) {
        report.sThumbLY = (SHORT)(frame.roll * 32767.0f);
    }
    
    // Send report to virtual controller
    int result = vigem_target_x360_update(vigemClient, vigemController, &report);
    
    return (result == 0);
}

} // namespace RLTASMod
