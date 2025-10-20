#include "MemoryManager.h"
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
    // This would use DirectInput or similar to inject inputs
    // For now, this is a placeholder
    // In a real implementation, you'd hook into the game's input processing
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
