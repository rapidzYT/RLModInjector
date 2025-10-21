#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <d3d11.h>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

// Virtual Key Codes (in case Windows.h doesn't include them)
#ifndef VK_W
#define VK_W 0x57
#endif
#ifndef VK_S
#define VK_S 0x53
#endif
#ifndef VK_A
#define VK_A 0x41
#endif
#ifndef VK_D
#define VK_D 0x44
#endif
#ifndef VK_Q
#define VK_Q 0x51
#endif
#ifndef VK_E
#define VK_E 0x45
#endif

namespace RLTASMod {

// Forward declarations
class InputRecorder;
class InputReplayer;
class MemoryManager;
class VirtualController;
class ItemManager;
struct TASData;

// Input state structure
struct InputFrame {
    float timestamp;
    bool throttle;
    bool brake;
    bool steerLeft;
    bool steerRight;
    bool jump;
    bool boost;
    bool powerslide;
    bool airRollLeft;
    bool airRollRight;
    float pitch;
    float yaw;
    float roll;
};

// Game state structure
struct GameState {
    float carPosX, carPosY, carPosZ;
    float carRotPitch, carRotYaw, carRotRoll;
    float carVelX, carVelY, carVelZ;
    float carAngVelX, carAngVelY, carAngVelZ;
    float ballPosX, ballPosY, ballPosZ;
    float ballVelX, ballVelY, ballVelZ;
    float ballAngVelX, ballAngVelY, ballAngVelZ;
};

// TAS settings
struct TASSettings {
    float recordSpeed = 1.0f;
    float replaySpeed = 1.0f;
    bool breakOnThrottle = false;
    bool breakOnJump = false;
    bool breakOnBoost = false;
    bool breakOnAirRoll = false;
    bool breakOnSteering = false;
};

// Main TAS mod class
class TASMod {
public:
    TASMod();
    ~TASMod();

    bool Initialize();
    void Shutdown();
    void OnFrame();
    void RenderGUI();

private:
    // GUI state
    bool showGUI = false;
    bool initialized = false;
    
    // Tab indices
    int currentTab = 0;
    enum TabIndex {
        TAB_CONTROLS = 0,
        TAB_SETTINGS = 1,
        TAB_LOADED_TAS = 2,
        TAB_FILES = 3
    };

    // TAS state
    enum TASState {
        STATE_IDLE,
        STATE_RECORDING,
        STATE_REPLAYING
    };
    TASState currentState = STATE_IDLE;
    
    std::shared_ptr<TASData> currentTAS;
    std::shared_ptr<TASData> loadedTAS;
    std::string currentTASName;
    
    TASSettings settings;
    
    // Recording/replay
    std::unique_ptr<InputRecorder> recorder;
    std::unique_ptr<InputReplayer> replayer;
    std::unique_ptr<MemoryManager> memory;
    std::unique_ptr<VirtualController> virtualController;
    std::unique_ptr<ItemManager> itemManager;
    
    GameState initialState;
    float recordingStartTime = 0.0f;
    float replayStartTime = 0.0f;
    
    // File management
    std::vector<std::string> savedTASFiles;
    int selectedFileIndex = -1;
    
    // GUI rendering functions
    void RenderControlsTab();
    void RenderSettingsTab();
    void RenderLoadedTASTab();
    void RenderFilesTab();
    void RenderItemsTab();
    
    // TAS operations
    void NewTAS(const std::string& name);
    void StartRecording();
    void StopRecording();
    void StartReplaying();
    void StopReplaying();
    void UpdateTAS();
    void SaveTAS();
    void LoadTAS(const std::string& filename);
    void DeleteTAS(const std::string& filename);
    
    // Helper functions
    void CaptureInitialState();
    void RestoreInitialState();
    void RefreshTASFileList();
    bool CheckBreakInputs(const InputFrame& frame);
    float GetCurrentTime();
    
    // Input handling
    void ProcessInput();
    bool IsKeyPressed(int vkCode);
    bool IsKeyJustPressed(int vkCode);
    
    // Key state tracking
    std::map<int, bool> keyStates;
};

} // namespace RLTASMod
