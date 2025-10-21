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
    
    // ========================================
    // INPUT OFFSETS - FILL THESE IN AFTER USING CHEAT ENGINE!
    // See CHEAT_ENGINE_GUIDE.md for instructions
    // ========================================
    
    // TODO: Replace these with addresses found using Cheat Engine
    static constexpr uintptr_t INPUT_BASE_OFFSET = 0x0;        // Base pointer to input structure
    static constexpr uintptr_t INPUT_THROTTLE_OFFSET = 0x0;    // W key (float: 0.0 or 1.0)
    static constexpr uintptr_t INPUT_BRAKE_OFFSET = 0x0;       // S key (float: 0.0 or 1.0)
    static constexpr uintptr_t INPUT_STEER_OFFSET = 0x0;       // A/D keys (float: -1.0 to 1.0)
    static constexpr uintptr_t INPUT_JUMP_OFFSET = 0x0;        // Space (byte: 0 or 1)
    static constexpr uintptr_t INPUT_BOOST_OFFSET = 0x0;       // Shift (byte: 0 or 1)
    static constexpr uintptr_t INPUT_POWERSLIDE_OFFSET = 0x0;  // Ctrl (byte: 0 or 1)
    static constexpr uintptr_t INPUT_AIR_ROLL_LEFT_OFFSET = 0x0;   // Q key (byte: 0 or 1)
    static constexpr uintptr_t INPUT_AIR_ROLL_RIGHT_OFFSET = 0x0;  // E key (byte: 0 or 1)
    static constexpr uintptr_t INPUT_PITCH_OFFSET = 0x0;       // Up/Down (float: -1.0 to 1.0)
    static constexpr uintptr_t INPUT_YAW_OFFSET = 0x0;         // Left/Right (float: -1.0 to 1.0)
    static constexpr uintptr_t INPUT_ROLL_OFFSET = 0x0;        // Roll (float: -1.0 to 1.0)
    
    // Helper functions
    bool ReadMemory(uintptr_t address, void* buffer, size_t size);
    bool WriteMemory(uintptr_t address, const void* buffer, size_t size);
    uintptr_t GetBaseAddress();
};

} // namespace RLTASMod
