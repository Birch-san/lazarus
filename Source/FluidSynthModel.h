//
// Created by Alex Birch on 10/09/2017.
//

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <fluidsynth.h>
#include <memory>
#include "PresetsToBanks.h"


// https://stackoverflow.com/a/13446565/5257399
using std::shared_ptr;

class FluidSynthModel {
public:
    ~FluidSynthModel();

    fluid_synth_t* getSynth();
    void initialise();

    BanksToPresets getBanks();

    void changePreset(int bank, int preset);
    int getChannel();

    void onFileNameChanged(const string &absPath);

private:
    fluid_synth_t* synth;
    fluid_settings_t* settings;
//    fluid_audio_driver_t* driver;

    const fluid_preset_t getFirstPreset();
    void selectFirstPreset();

    void unloadAndLoadFont(const string &absPath);
    void loadFont(const string &absPath);

    bool initialised;
    unsigned int sfont_id;
    unsigned int channel;
};