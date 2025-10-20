#include "InputRecorder.h"

namespace RLTASMod {

InputRecorder::InputRecorder() {
}

InputRecorder::~InputRecorder() {
}

void InputRecorder::StartRecording(float speed) {
    frames.clear();
    recording = true;
    recordSpeed = speed;
}

void InputRecorder::StopRecording() {
    recording = false;
}

void InputRecorder::RecordFrame(const InputFrame& frame) {
    if (!recording) return;
    frames.push_back(frame);
}

void InputRecorder::Clear() {
    frames.clear();
}

} // namespace RLTASMod
