//
// Created by Alex Birch on 07/09/2017.
//

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class SoundfontSynthVoice : public SynthesiserVoice {
public:
    SoundfontSynthVoice();
    ~SoundfontSynthVoice();

    bool canPlaySound (SynthesiserSound* sound) override;
    void startNote (
            int midiNoteNumber,
            float velocity,
            SynthesiserSound* /*sound*/,
            int /*currentPitchWheelPosition*/) override;

    void stopNote (float /*velocity*/, bool allowTailOff) override;
    void pitchWheelMoved (int /*newValue*/) override;

    void controllerMoved (int /*controllerNumber*/, int /*newValue*/) override;

    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;

};
