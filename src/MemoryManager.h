#pragma once

#include <Windows.h>

namespace RLTASMod {
    struct InputFrame;
    struct GameState;
}

namespace RLTASMod {

class MemoryManager {
public:
    MemoryManager();
    ~MemoryManager();
    
    bool Initialize();
    void Shutdown();
    
    bool GetGameState(GameState& state);
    bool SetGameState(const GameState& state);
    bool ApplyInputs(const InputFrame& frame);
    
private:
    HANDLE processHandle = nullptr;
    uintptr_t baseAddress = 0;
    
    // Memory offsets (these would need to be updated for specific RL version)
    static constexpr uintptr_t CAR_POSITION_OFFSET = 0x01C8F2E8;
    static constexpr uintptr_t CAR_ROTATION_OFFSET = 0x01C8F2F4;
    static constexpr uintptr_t CAR_VELOCITY_OFFSET = 0x01C8F300;
    static constexpr uintptr_t CAR_ANGULAR_VELOCITY_OFFSET = 0x01C8F30C;
    static constexpr uintptr_t BALL_POSITION_OFFSET = 0x01D0A3B8;
    static constexpr uintptr_t BALL_VELOCITY_OFFSET = 0x01D0A3C4;
    static constexpr uintptr_t BALL_ANGULAR_VELOCITY_OFFSET = 0x01D0A3D0;
    
    // Helper functions
    bool ReadMemory(uintptr_t address, void* buffer, size_t size);
    bool WriteMemory(uintptr_t address, const void* buffer, size_t size);
    uintptr_t GetBaseAddress();
};

} // namespace RLTASMod
