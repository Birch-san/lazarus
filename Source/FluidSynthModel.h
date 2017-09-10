//
// Created by Alex Birch on 10/09/2017.
//

#pragma once

#include <fluidsynth.h>
#include <memory>

// https://stackoverflow.com/a/13446565/5257399
using std::shared_ptr;

class FluidSynthModel {
public:
    ~FluidSynthModel();

    shared_ptr<fluid_synth_t> getSynth();
    void initialise();

private:
    shared_ptr<fluid_synth_t> synth;
    fluid_settings_t* settings;
    fluid_audio_driver_t* driver;

    bool initialised;
};