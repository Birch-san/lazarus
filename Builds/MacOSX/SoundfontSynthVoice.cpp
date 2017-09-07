//
// Created by Alex Birch on 07/09/2017.
//

#include "SoundfontSynthVoice.h"
#include "SoundfontSynthSound.h"

SoundfontSynthVoice::SoundfontSynthVoice()
: tailOff (0.0) {

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
    tailOff = 0.0;
}

void SoundfontSynthVoice::stopNote (float /*velocity*/, bool allowTailOff) {
    if (allowTailOff) {
        // start a tail-off by setting this flag. The render callback will pick up on
        // this and do a fade out, calling clearCurrentNote() when it's finished.

        // we only need to begin a tail-off if it's not already doing so - the
        if (tailOff == 0.0) {
            // stopNote method could be called more than once.
            tailOff = 1.0;
        }
    } else {
        // we're being told to stop playing immediately, so reset everything..

        clearCurrentNote();
    }
}
void SoundfontSynthVoice::pitchWheelMoved (int /*newValue*/) {
    // who cares?
}

void SoundfontSynthVoice::controllerMoved (int /*controllerNumber*/, int /*newValue*/) {
    // what's a controller?
}

void SoundfontSynthVoice::renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) {

}