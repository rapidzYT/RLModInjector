#include "InputReplayer.h"
#include <chrono>

namespace RLTASMod {

InputReplayer::InputReplayer() {
}

InputReplayer::~InputReplayer() {
}

void InputReplayer::StartReplay(std::shared_ptr<TASData> tas, float speed) {
    currentTAS = tas;
    replaying = true;
    replaySpeed = speed;
    currentFrameIndex = 0;
    
    static auto startTime = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    replayStartTime = std::chrono::duration<float>(now - startTime).count();
}

void InputReplayer::StopReplay() {
    replaying = false;
    currentFrameIndex = 0;
}

void InputReplayer::Update() {
    if (!replaying || !currentTAS) return;
    
    static auto startTime = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    currentTime = std::chrono::duration<float>(now - startTime).count();
}

InputFrame* InputReplayer::GetCurrentFrame() {
    if (!replaying || !currentTAS) return nullptr;
    
    Update();
    
    float elapsedTime = (currentTime - replayStartTime) * replaySpeed;
    
    // Find the frame that should be playing at this time
    while (currentFrameIndex < currentTAS->GetFrameCount()) {
        auto frame = currentTAS->GetFrame(currentFrameIndex);
        if (frame && frame->timestamp <= elapsedTime) {
            currentFrameIndex++;
            if (currentFrameIndex >= currentTAS->GetFrameCount()) {
                StopReplay();
                return nullptr;
            }
            return currentTAS->GetFrame(currentFrameIndex);
        } else {
            break;
        }
    }
    
    return currentTAS->GetFrame(currentFrameIndex);
}

float InputReplayer::GetProgress() const {
    if (!currentTAS || currentTAS->GetFrameCount() == 0) return 0.0f;
    return (float)currentFrameIndex / currentTAS->GetFrameCount();
}

} // namespace RLTASMod
