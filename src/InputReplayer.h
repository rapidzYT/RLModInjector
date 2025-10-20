#pragma once

#include "TASMod.h"
#include "TASData.h"
#include <memory>

namespace RLTASMod {

class InputReplayer {
public:
    InputReplayer();
    ~InputReplayer();
    
    void StartReplay(std::shared_ptr<TASData> tas, float speed = 1.0f);
    void StopReplay();
    void Update();
    
    InputFrame* GetCurrentFrame();
    bool IsReplaying() const { return replaying; }
    float GetProgress() const;
    
private:
    std::shared_ptr<TASData> currentTAS;
    bool replaying = false;
    float replaySpeed = 1.0f;
    int currentFrameIndex = 0;
    float replayStartTime = 0.0f;
    float currentTime = 0.0f;
};

} // namespace RLTASMod
