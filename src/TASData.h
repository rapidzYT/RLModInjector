#pragma once

#include "TASMod.h"
#include <vector>
#include <string>

namespace RLTASMod {

class TASData {
public:
    TASData();
    ~TASData();
    
    void SetInitialState(const GameState& state);
    const GameState& GetInitialState() const { return initialState; }
    
    void AppendFrame(const InputFrame& frame);
    void AppendFrames(const std::vector<InputFrame>& frames);
    void Clear();
    
    InputFrame* GetFrame(int index);
    int GetFrameCount() const { return frames.size(); }
    float GetDuration() const;
    
    bool SaveToFile(const std::string& filename) const;
    bool LoadFromFile(const std::string& filename);
    
private:
    GameState initialState;
    std::vector<InputFrame> frames;
};

} // namespace RLTASMod
