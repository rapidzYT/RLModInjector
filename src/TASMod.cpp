#include "TASMod.h"
#include "InputRecorder.h"
#include "InputReplayer.h"
#include "MemoryManager.h"
#include "TASData.h"
#include <Windows.h>
#include <filesystem>
#include <chrono>
#include <fstream>

namespace fs = std::filesystem;

namespace RLTASMod {

TASMod::TASMod() {
    recorder = std::make_unique<InputRecorder>();
    replayer = std::make_unique<InputReplayer>();
    memory = std::make_unique<MemoryManager>();
}

TASMod::~TASMod() {
    Shutdown();
}

bool TASMod::Initialize() {
    if (initialized) return true;
    
    // Initialize memory manager
    if (!memory->Initialize()) {
        return false;
    }
    
    // Create TAS directory if it doesn't exist
    fs::create_directories("TAS");
    
    // Refresh file list
    RefreshTASFileList();
    
    initialized = true;
    return true;
}

void TASMod::Shutdown() {
    if (currentState == STATE_RECORDING) {
        StopRecording();
    } else if (currentState == STATE_REPLAYING) {
        StopReplaying();
    }
    
    initialized = false;
}

void TASMod::OnFrame() {
    if (!initialized) return;
    
    // Check for F9 key to toggle GUI
    if (IsKeyJustPressed(VK_F9)) {
        showGUI = !showGUI;
    }
    
    // Process TAS operations
    if (currentState == STATE_RECORDING) {
        // Record inputs every frame
        ProcessInput();
    } else if (currentState == STATE_REPLAYING) {
        if (!replayer || !memory) return;
        
        auto frame = replayer->GetCurrentFrame();
        if (frame) {
            // Apply inputs to the game
            memory->ApplyInputs(*frame);
            
            // Check for break inputs (user taking over)
            if (CheckBreakInputs(*frame)) {
                StopReplaying();
                StartRecording();
            }
        } else {
            // Replay finished
            StopReplaying();
        }
    }
}

void TASMod::RenderGUI() {
    if (!showGUI) return;
    
    ImGui::SetNextWindowSize(ImVec2(600, 500), ImGuiCond_FirstUseEver);
    ImGui::Begin("Rocket League TAS Mod", &showGUI, ImGuiWindowFlags_MenuBar);
    
    // Tab bar
    if (ImGui::BeginTabBar("TASTabBar")) {
        if (ImGui::BeginTabItem("Controls")) {
            RenderControlsTab();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Settings")) {
            RenderSettingsTab();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Loaded TAS")) {
            RenderLoadedTASTab();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Files")) {
            RenderFilesTab();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    
    ImGui::End();
}

void TASMod::RenderControlsTab() {
    ImGui::Spacing();
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "TAS Controls");
    ImGui::Separator();
    ImGui::Spacing();
    
    // New TAS section
    ImGui::Text("Create New TAS:");
    static char tasName[256] = "";
    ImGui::InputText("TAS Name", tasName, sizeof(tasName));
    ImGui::SameLine();
    if (ImGui::Button("New TAS")) {
        if (strlen(tasName) > 0) {
            NewTAS(tasName);
            memset(tasName, 0, sizeof(tasName));
            ImGui::Text("TAS Created! Click Start to begin recording.");
        } else {
            ImGui::Text("Please enter a TAS name first!");
        }
    }
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    // Current TAS info
    if (!currentTASName.empty()) {
        ImGui::Text("Current TAS: %s", currentTASName.c_str());
        
        if (currentTAS) {
            ImGui::Text("Frames: %d", currentTAS->GetFrameCount());
            ImGui::Text("Duration: %.2f seconds", currentTAS->GetDuration());
        }
    } else {
        ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "No TAS loaded - Create a new TAS to begin");
    }
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    // Speed controls
    ImGui::Text("Record Speed:");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(200);
    if (ImGui::SliderFloat("##RecordSpeed", &settings.recordSpeed, 0.1f, 10.0f, "%.2fx")) {
        // Speed changed - update recorder if recording
        if (currentState == STATE_RECORDING && recorder) {
            // Speed will be used on next frame
        }
    }
    
    ImGui::Text("Replay Speed:");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(200);
    if (ImGui::SliderFloat("##ReplaySpeed", &settings.replaySpeed, 0.1f, 10.0f, "%.2fx")) {
        // Speed changed - update replayer if replaying
        if (currentState == STATE_REPLAYING && replayer) {
            // Speed will be used on next frame
        }
    }
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    // Control buttons
    ImGui::BeginDisabled(currentTASName.empty());
    
    if (currentState == STATE_IDLE) {
        if (ImGui::Button("Start", ImVec2(120, 40))) {
            StartReplaying();
        }
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "Click Start to begin replaying");
    } else if (currentState == STATE_RECORDING) {
        if (ImGui::Button("Stop Recording", ImVec2(120, 40))) {
            StopRecording();
        }
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "RECORDING...");
        // Show frame count while recording
        if (recorder) {
            ImGui::Text("Frames recorded: %d", recorder->GetFrameCount());
        }
    } else if (currentState == STATE_REPLAYING) {
        if (ImGui::Button("Stop Replaying", ImVec2(120, 40))) {
            StopReplaying();
        }
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "REPLAYING...");
    }
    
    ImGui::EndDisabled();
    
    ImGui::Spacing();
    
    // Update button (only available after recording)
    bool canUpdate = (currentState == STATE_IDLE && recorder && recorder->GetFrameCount() > 0);
    ImGui::BeginDisabled(!canUpdate);
    if (ImGui::Button("Update", ImVec2(120, 40))) {
        UpdateTAS();
    }
    ImGui::SameLine();
    if (canUpdate) {
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Click to save %d frames to TAS", recorder ? recorder->GetFrameCount() : 0);
    } else {
        ImGui::Text("Record something first, then Update to save it");
    }
    ImGui::EndDisabled();
}

void TASMod::RenderSettingsTab() {
    ImGui::Spacing();
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Replay Break Settings");
    ImGui::Separator();
    ImGui::Spacing();
    
    ImGui::Text("Select which inputs will stop replay and start recording:");
    ImGui::Spacing();
    
    ImGui::Checkbox("Throttle (W/S)", &settings.breakOnThrottle);
    ImGui::Checkbox("Steering (A/D)", &settings.breakOnSteering);
    ImGui::Checkbox("Jump (Space)", &settings.breakOnJump);
    ImGui::Checkbox("Boost (Shift)", &settings.breakOnBoost);
    ImGui::Checkbox("Air Roll (Q/E)", &settings.breakOnAirRoll);
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    ImGui::TextWrapped("When any selected input is detected during replay, "
                      "the TAS will stop replaying and immediately start recording new inputs.");
}

void TASMod::RenderLoadedTASTab() {
    ImGui::Spacing();
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Loaded TAS Information");
    ImGui::Separator();
    ImGui::Spacing();
    
    if (!currentTASName.empty() && currentTAS) {
        ImGui::Text("TAS Name: %s", currentTASName.c_str());
        
        int frameCount = currentTAS->GetFrameCount();
        float duration = currentTAS->GetDuration();
        
        ImGui::Text("Total Frames: %d", frameCount);
        ImGui::Text("Duration: %.2f seconds", duration);
        
        // Show recorder info too
        if (recorder) {
            ImGui::Spacing();
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Recorder Buffer: %d frames (not saved yet)", recorder->GetFrameCount());
        }
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        // Initial state information
        ImGui::Text("Initial State:");
        ImGui::Text("Car Position: (%.2f, %.2f, %.2f)", 
                   initialState.carPosX, initialState.carPosY, initialState.carPosZ);
        ImGui::Text("Ball Position: (%.2f, %.2f, %.2f)", 
                   initialState.ballPosX, initialState.ballPosY, initialState.ballPosZ);
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        // Save button
        if (ImGui::Button("Save TAS", ImVec2(150, 40))) {
            SaveTAS();
        }
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.5f, 1.0f, 0.5f, 1.0f), "Save current TAS to file");
        
    } else {
        ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "No TAS loaded");
        ImGui::Spacing();
        ImGui::Text("Create a new TAS in the Controls tab to get started.");
    }
}

void TASMod::RenderFilesTab() {
    ImGui::Spacing();
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Saved TAS Files");
    ImGui::Separator();
    ImGui::Spacing();
    
    if (ImGui::Button("Refresh File List")) {
        RefreshTASFileList();
    }
    
    ImGui::Spacing();
    
    // Display file list
    if (savedTASFiles.empty()) {
        ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "No saved TAS files found");
    } else {
        ImGui::BeginChild("FileList", ImVec2(0, 300), true);
        
        for (int i = 0; i < savedTASFiles.size(); i++) {
            bool isSelected = (selectedFileIndex == i);
            
            if (ImGui::Selectable(savedTASFiles[i].c_str(), isSelected)) {
                selectedFileIndex = i;
            }
        }
        
        ImGui::EndChild();
        
        ImGui::Spacing();
        
        // File operations
        ImGui::BeginDisabled(selectedFileIndex < 0);
        
        if (ImGui::Button("Load Selected", ImVec2(120, 30))) {
            LoadTAS(savedTASFiles[selectedFileIndex]);
        }
        ImGui::SameLine();
        
        if (ImGui::Button("Delete Selected", ImVec2(120, 30))) {
            DeleteTAS(savedTASFiles[selectedFileIndex]);
            RefreshTASFileList();
            selectedFileIndex = -1;
        }
        
        ImGui::EndDisabled();
    }
}

void TASMod::NewTAS(const std::string& name) {
    // Stop any current operation
    if (currentState != STATE_IDLE) {
        if (currentState == STATE_RECORDING) StopRecording();
        if (currentState == STATE_REPLAYING) StopReplaying();
    }
    
    // Capture current game state
    CaptureInitialState();
    
    // Create new TAS
    currentTAS = std::make_shared<TASData>();
    currentTAS->SetInitialState(initialState);
    currentTASName = name;
    
    // Clear recorder
    recorder->Clear();
}

void TASMod::StartRecording() {
    if (currentState != STATE_IDLE) {
        // Already recording or replaying
        return;
    }
    
    // If no TAS exists, create a default one
    if (!currentTAS) {
        NewTAS("default_tas");
    }
    
    currentState = STATE_RECORDING;
    recordingStartTime = GetCurrentTime();
    recorder->StartRecording(settings.recordSpeed);
}

void TASMod::StopRecording() {
    if (currentState != STATE_RECORDING) return;
    
    recorder->StopRecording();
    currentState = STATE_IDLE;
}

void TASMod::StartReplaying() {
    if (currentState != STATE_IDLE) return;
    
    // If no TAS or no frames, start recording instead
    if (!currentTAS || currentTAS->GetFrameCount() == 0) {
        StartRecording();
        return;
    }
    
    // Make sure replayer exists
    if (!replayer) return;
    
    // Restore initial state
    RestoreInitialState();
    
    // Start replaying
    currentState = STATE_REPLAYING;
    replayStartTime = GetCurrentTime();
    replayer->StartReplay(currentTAS, settings.replaySpeed);
}

void TASMod::StopReplaying() {
    if (currentState != STATE_REPLAYING) return;
    
    replayer->StopReplay();
    currentState = STATE_IDLE;
}

void TASMod::UpdateTAS() {
    if (!currentTAS || !recorder) return;
    
    // Get recorded frames and add them to the current TAS
    auto frames = recorder->GetRecordedFrames();
    
    if (frames.size() > 0) {
        currentTAS->AppendFrames(frames);
        // Clear the recorder so we can record again
        recorder->Clear();
    }
}

void TASMod::SaveTAS() {
    if (!currentTAS || currentTASName.empty()) return;
    
    std::string filename = "TAS/" + currentTASName + ".tas";
    currentTAS->SaveToFile(filename);
    
    RefreshTASFileList();
}

void TASMod::LoadTAS(const std::string& filename) {
    auto tas = std::make_shared<TASData>();
    if (tas->LoadFromFile("TAS/" + filename)) {
        currentTAS = tas;
        currentTASName = filename.substr(0, filename.find_last_of('.'));
        initialState = currentTAS->GetInitialState();
    }
}

void TASMod::DeleteTAS(const std::string& filename) {
    fs::remove("TAS/" + filename);
}

void TASMod::CaptureInitialState() {
    memory->GetGameState(initialState);
}

void TASMod::RestoreInitialState() {
    memory->SetGameState(initialState);
}

void TASMod::RefreshTASFileList() {
    savedTASFiles.clear();
    
    if (fs::exists("TAS") && fs::is_directory("TAS")) {
        for (const auto& entry : fs::directory_iterator("TAS")) {
            if (entry.path().extension() == ".tas") {
                savedTASFiles.push_back(entry.path().filename().string());
            }
        }
    }
}

bool TASMod::CheckBreakInputs(const InputFrame& frame) {
    // Check if any break inputs are active
    if (settings.breakOnThrottle && (IsKeyPressed(VK_W) || IsKeyPressed(VK_S))) return true;
    if (settings.breakOnSteering && (IsKeyPressed(VK_A) || IsKeyPressed(VK_D))) return true;
    if (settings.breakOnJump && IsKeyPressed(VK_SPACE)) return true;
    if (settings.breakOnBoost && IsKeyPressed(VK_SHIFT)) return true;
    if (settings.breakOnAirRoll && (IsKeyPressed(VK_Q) || IsKeyPressed(VK_E))) return true;
    
    return false;
}

void TASMod::ProcessInput() {
    if (!recorder) return;
    
    InputFrame frame;
    frame.timestamp = (GetCurrentTime() - recordingStartTime) / settings.recordSpeed;
    
    // Capture input state
    frame.throttle = IsKeyPressed(VK_W);
    frame.brake = IsKeyPressed(VK_S);
    frame.steerLeft = IsKeyPressed(VK_A);
    frame.steerRight = IsKeyPressed(VK_D);
    frame.jump = IsKeyPressed(VK_SPACE);
    frame.boost = IsKeyPressed(VK_SHIFT);
    frame.powerslide = IsKeyPressed(VK_CONTROL);
    frame.airRollLeft = IsKeyPressed(VK_Q);
    frame.airRollRight = IsKeyPressed(VK_E);
    
    // Get analog inputs (simplified - would need actual game state)
    frame.pitch = IsKeyPressed(VK_UP) ? 1.0f : (IsKeyPressed(VK_DOWN) ? -1.0f : 0.0f);
    frame.yaw = IsKeyPressed(VK_LEFT) ? -1.0f : (IsKeyPressed(VK_RIGHT) ? 1.0f : 0.0f);
    frame.roll = 0.0f;
    
    // Actually record the frame
    recorder->RecordFrame(frame);
}

float TASMod::GetCurrentTime() {
    static auto startTime = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<float>(now - startTime).count();
}

bool TASMod::IsKeyPressed(int vkCode) {
    return (GetAsyncKeyState(vkCode) & 0x8000) != 0;
}

bool TASMod::IsKeyJustPressed(int vkCode) {
    bool currentState = IsKeyPressed(vkCode);
    bool wasPressed = keyStates[vkCode];
    keyStates[vkCode] = currentState;
    return currentState && !wasPressed;
}

} // namespace RLTASMod
