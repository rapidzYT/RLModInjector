#include "TASData.h"
#include <fstream>
#include <cstring>

namespace RLTASMod {

TASData::TASData() {
    memset(&initialState, 0, sizeof(GameState));
}

TASData::~TASData() {
}

void TASData::SetInitialState(const GameState& state) {
    initialState = state;
}

void TASData::AppendFrame(const InputFrame& frame) {
    frames.push_back(frame);
}

void TASData::AppendFrames(const std::vector<InputFrame>& newFrames) {
    frames.insert(frames.end(), newFrames.begin(), newFrames.end());
}

void TASData::Clear() {
    frames.clear();
}

InputFrame* TASData::GetFrame(int index) {
    if (index < 0 || index >= frames.size()) return nullptr;
    return &frames[index];
}

float TASData::GetDuration() const {
    if (frames.empty()) return 0.0f;
    return frames.back().timestamp;
}

bool TASData::SaveToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;
    
    // Write header
    const char* header = "RLTAS";
    file.write(header, 5);
    
    // Write version
    int version = 1;
    file.write(reinterpret_cast<const char*>(&version), sizeof(int));
    
    // Write initial state
    file.write(reinterpret_cast<const char*>(&initialState), sizeof(GameState));
    
    // Write frame count
    int frameCount = frames.size();
    file.write(reinterpret_cast<const char*>(&frameCount), sizeof(int));
    
    // Write frames
    for (const auto& frame : frames) {
        file.write(reinterpret_cast<const char*>(&frame), sizeof(InputFrame));
    }
    
    file.close();
    return true;
}

bool TASData::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;
    
    // Read and verify header
    char header[6] = {0};
    file.read(header, 5);
    if (strcmp(header, "RLTAS") != 0) {
        file.close();
        return false;
    }
    
    // Read version
    int version;
    file.read(reinterpret_cast<char*>(&version), sizeof(int));
    
    // Read initial state
    file.read(reinterpret_cast<char*>(&initialState), sizeof(GameState));
    
    // Read frame count
    int frameCount;
    file.read(reinterpret_cast<char*>(&frameCount), sizeof(int));
    
    // Read frames
    frames.clear();
    frames.reserve(frameCount);
    for (int i = 0; i < frameCount; i++) {
        InputFrame frame;
        file.read(reinterpret_cast<char*>(&frame), sizeof(InputFrame));
        frames.push_back(frame);
    }
    
    file.close();
    return true;
}

} // namespace RLTASMod
