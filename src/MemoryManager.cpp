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
    // Simulate keyboard inputs using Windows API
    // Helper to press or release a key
    auto SetKeyState = [](int vk, bool pressed) {
        if (pressed) {
            keybd_event(vk, 0, 0, 0);  // Key down
        } else {
            keybd_event(vk, 0, 0x0002, 0);  // Key up (KEYEVENTF_KEYUP = 0x0002)
        }
    };
    
    // Apply all inputs
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
