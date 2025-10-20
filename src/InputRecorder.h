#pragma once

#include "TASMod.h"
#include <vector>

namespace RLTASMod {

class InputRecorder {
public:
    InputRecorder();
    ~InputRecorder();
    
    void StartRecording(float speed = 1.0f);
    void StopRecording();
    void RecordFrame(const InputFrame& frame);
    void Clear();
    
    const std::vector<InputFrame>& GetRecordedFrames() const { return frames; }
    int GetFrameCount() const { return frames.size(); }
    bool IsRecording() const { return recording; }
    
private:
    std::vector<InputFrame> frames;
    bool recording = false;
    float recordSpeed = 1.0f;
};

} // namespace RLTASMod
