//
// Created by Alex Birch on 07/09/2017.
//

#include "SoundfontSynthVoice.h"
#include "SoundfontSynthSound.h"

SoundfontSynthVoice::SoundfontSynthVoice() {

}
SoundfontSynthVoice::~SoundfontSynthVoice() {

}

bool SoundfontSynthVoice::canPlaySound(SynthesiserSound* sound) {
    return dynamic_cast<SoundfontSynthSound*> (sound) != nullptr;
}
void SoundfontSynthVoice::startNote(
        int midiNoteNumber,
        float velocity,
        SynthesiserSound* /*sound*/,
        int /*currentPitchWheelPosition*/) {
}

void SoundfontSynthVoice::stopNote (float /*velocity*/, bool allowTailOff) {

}
void SoundfontSynthVoice::pitchWheelMoved (int /*newValue*/) {

}

void SoundfontSynthVoice::controllerMoved (int /*controllerNumber*/, int /*newValue*/) {

}

void SoundfontSynthVoice::renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) {

}