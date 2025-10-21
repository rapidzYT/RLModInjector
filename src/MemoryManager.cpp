#include "MemoryManager.h"
#include "TASMod.h"
#include <TlHelp32.h>

namespace RLTASMod {

MemoryManager::MemoryManager() {
}

MemoryManager::~MemoryManager() {
    Shutdown();
}

bool MemoryManager::Initialize() {
    // Get current process handle (we're already injected into RL)
    processHandle = GetCurrentProcess();
    baseAddress = GetBaseAddress();
    
    return processHandle != nullptr && baseAddress != 0;
}

void MemoryManager::Shutdown() {
    // Don't close the handle as it's the current process
    processHandle = nullptr;
}

bool MemoryManager::GetGameState(GameState& state) {
    if (!processHandle || !baseAddress) return false;
    
    // Read car position
    ReadMemory(baseAddress + CAR_POSITION_OFFSET, &state.carPosX, sizeof(float) * 3);
    
    // Read car rotation
    ReadMemory(baseAddress + CAR_ROTATION_OFFSET, &state.carRotPitch, sizeof(float) * 3);
    
    // Read car velocity
    ReadMemory(baseAddress + CAR_VELOCITY_OFFSET, &state.carVelX, sizeof(float) * 3);
    
    // Read car angular velocity
    ReadMemory(baseAddress + CAR_ANGULAR_VELOCITY_OFFSET, &state.carAngVelX, sizeof(float) * 3);
    
    // Read ball position
    ReadMemory(baseAddress + BALL_POSITION_OFFSET, &state.ballPosX, sizeof(float) * 3);
    
    // Read ball velocity
    ReadMemory(baseAddress + BALL_VELOCITY_OFFSET, &state.ballVelX, sizeof(float) * 3);
    
    // Read ball angular velocity
    ReadMemory(baseAddress + BALL_ANGULAR_VELOCITY_OFFSET, &state.ballAngVelX, sizeof(float) * 3);
    
    return true;
}

bool MemoryManager::SetGameState(const GameState& state) {
    if (!processHandle || !baseAddress) return false;
    
    // Write car position
    WriteMemory(baseAddress + CAR_POSITION_OFFSET, &state.carPosX, sizeof(float) * 3);
    
    // Write car rotation
    WriteMemory(baseAddress + CAR_ROTATION_OFFSET, &state.carRotPitch, sizeof(float) * 3);
    
    // Write car velocity
    WriteMemory(baseAddress + CAR_VELOCITY_OFFSET, &state.carVelX, sizeof(float) * 3);
    
    // Write car angular velocity
    WriteMemory(baseAddress + CAR_ANGULAR_VELOCITY_OFFSET, &state.carAngVelX, sizeof(float) * 3);
    
    // Write ball position
    WriteMemory(baseAddress + BALL_POSITION_OFFSET, &state.ballPosX, sizeof(float) * 3);
    
    // Write ball velocity
    WriteMemory(baseAddress + BALL_VELOCITY_OFFSET, &state.ballVelX, sizeof(float) * 3);
    
    // Write ball angular velocity
    WriteMemory(baseAddress + BALL_ANGULAR_VELOCITY_OFFSET, &state.ballAngVelX, sizeof(float) * 3);
    
    return true;
}

bool MemoryManager::ApplyInputs(const InputFrame& frame) {
    // ========================================
    // METHOD 1: Direct Memory Write (MOST ACCURATE!)
    // Uses addresses found with Cheat Engine
    // ========================================
    
    if (INPUT_BASE_OFFSET != 0) {
        // Use direct memory writes (fill in offsets from Cheat Engine!)
        uintptr_t inputBase = baseAddress + INPUT_BASE_OFFSET;
        
        // Write throttle (W key) - float 0.0 or 1.0
        if (INPUT_THROTTLE_OFFSET != 0) {
            float throttle = frame.throttle ? 1.0f : 0.0f;
            WriteMemory(inputBase + INPUT_THROTTLE_OFFSET, &throttle, sizeof(float));
        }
        
        // Write brake (S key) - float 0.0 or 1.0
        if (INPUT_BRAKE_OFFSET != 0) {
            float brake = frame.brake ? 1.0f : 0.0f;
            WriteMemory(inputBase + INPUT_BRAKE_OFFSET, &brake, sizeof(float));
        }
        
        // Write steering (A/D keys) - float -1.0 to 1.0
        if (INPUT_STEER_OFFSET != 0) {
            float steer = 0.0f;
            if (frame.steerLeft) steer = -1.0f;
            if (frame.steerRight) steer = 1.0f;
            WriteMemory(inputBase + INPUT_STEER_OFFSET, &steer, sizeof(float));
        }
        
        // Write jump (Space) - byte 0 or 1
        if (INPUT_JUMP_OFFSET != 0) {
            byte jump = frame.jump ? 1 : 0;
            WriteMemory(inputBase + INPUT_JUMP_OFFSET, &jump, sizeof(byte));
        }
        
        // Write boost (Shift) - byte 0 or 1
        if (INPUT_BOOST_OFFSET != 0) {
            byte boost = frame.boost ? 1 : 0;
            WriteMemory(inputBase + INPUT_BOOST_OFFSET, &boost, sizeof(byte));
        }
        
        // Write powerslide (Ctrl) - byte 0 or 1
        if (INPUT_POWERSLIDE_OFFSET != 0) {
            byte powerslide = frame.powerslide ? 1 : 0;
            WriteMemory(inputBase + INPUT_POWERSLIDE_OFFSET, &powerslide, sizeof(byte));
        }
        
        // Write air roll left (Q) - byte 0 or 1
        if (INPUT_AIR_ROLL_LEFT_OFFSET != 0) {
            byte airRollLeft = frame.airRollLeft ? 1 : 0;
            WriteMemory(inputBase + INPUT_AIR_ROLL_LEFT_OFFSET, &airRollLeft, sizeof(byte));
        }
        
        // Write air roll right (E) - byte 0 or 1
        if (INPUT_AIR_ROLL_RIGHT_OFFSET != 0) {
            byte airRollRight = frame.airRollRight ? 1 : 0;
            WriteMemory(inputBase + INPUT_AIR_ROLL_RIGHT_OFFSET, &airRollRight, sizeof(byte));
        }
        
        // Write pitch (Up/Down arrows) - float -1.0 to 1.0
        if (INPUT_PITCH_OFFSET != 0) {
            WriteMemory(inputBase + INPUT_PITCH_OFFSET, &frame.pitch, sizeof(float));
        }
        
        // Write yaw (Left/Right arrows) - float -1.0 to 1.0
        if (INPUT_YAW_OFFSET != 0) {
            WriteMemory(inputBase + INPUT_YAW_OFFSET, &frame.yaw, sizeof(float));
        }
        
        // Write roll - float -1.0 to 1.0
        if (INPUT_ROLL_OFFSET != 0) {
            WriteMemory(inputBase + INPUT_ROLL_OFFSET, &frame.roll, sizeof(float));
        }
        
        return true;
    }
    
    // ========================================
    // METHOD 2: Fallback - Windows Input Simulation
    // (Doesn't work well but kept for testing)
    // ========================================
    
    // Helper to press or release a key
    auto SetKeyState = [](int vk, bool pressed) {
        if (pressed) {
            keybd_event(vk, 0, 0, 0);  // Key down
        } else {
            keybd_event(vk, 0, 0x0002, 0);  // Key up (KEYEVENTF_KEYUP = 0x0002)
        }
    };
    
    // Apply all inputs (fallback method - won't work well in RL!)
    SetKeyState('W', frame.throttle);
    SetKeyState('S', frame.brake);
    SetKeyState('A', frame.steerLeft);
    SetKeyState('D', frame.steerRight);
    SetKeyState(VK_SPACE, frame.jump);
    SetKeyState(VK_SHIFT, frame.boost);
    SetKeyState(VK_CONTROL, frame.powerslide);
    SetKeyState('Q', frame.airRollLeft);
    SetKeyState('E', frame.airRollRight);
    SetKeyState(VK_UP, frame.pitch > 0.5f);
    SetKeyState(VK_DOWN, frame.pitch < -0.5f);
    SetKeyState(VK_LEFT, frame.yaw < -0.5f);
    SetKeyState(VK_RIGHT, frame.yaw > 0.5f);
    
    return true;
}

bool MemoryManager::ReadMemory(uintptr_t address, void* buffer, size_t size) {
    SIZE_T bytesRead;
    return ReadProcessMemory(processHandle, (LPCVOID)address, buffer, size, &bytesRead) && bytesRead == size;
}

bool MemoryManager::WriteMemory(uintptr_t address, const void* buffer, size_t size) {
    SIZE_T bytesWritten;
    DWORD oldProtect;
    
    // Change memory protection
    VirtualProtectEx(processHandle, (LPVOID)address, size, PAGE_EXECUTE_READWRITE, &oldProtect);
    
    bool result = WriteProcessMemory(processHandle, (LPVOID)address, buffer, size, &bytesWritten) && bytesWritten == size;
    
    // Restore memory protection
    VirtualProtectEx(processHandle, (LPVOID)address, size, oldProtect, &oldProtect);
    
    return result;
}

uintptr_t MemoryManager::GetBaseAddress() {
    return (uintptr_t)GetModuleHandleA(NULL);
}

} // namespace RLTASMod
