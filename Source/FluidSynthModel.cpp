//
// Created by Alex Birch on 10/09/2017.
//

#include <iostream>
#include "FluidSynthModel.h"

FluidSynthModel::~FluidSynthModel() {
    if (initialised) {
//        delete_fluid_audio_driver(driver);
        delete_fluid_settings(settings);
    }
}

void FluidSynthModel::initialise() {
    settings = new_fluid_settings();
    // https://sourceforge.net/p/fluidsynth/wiki/FluidSettings/
//    fluid_settings_setstr(settings, "synth.verbose", "yes");

    fluid_synth_t* synth = new_fluid_synth(settings);
//    fluid_synth_sfload(synth, "/Users/birch/Documents/soundfont/EarthBound.sf2", 1);
    fluid_synth_sfload(synth, "/Users/birch/Documents/soundfont/free/Perfect Sine.sf2", 1);
    fluid_synth_set_gain(synth, 2.0);

//    driver = new_fluid_audio_driver(settings, synth);

    this->synth = shared_ptr<fluid_synth_t>(synth, [](fluid_synth_t* f) {
        std::cout << "[fluid_synth_t deleter invoked]\n";
        delete_fluid_synth(f);
    });

    initialised = true;
}

shared_ptr<fluid_synth_t> FluidSynthModel::getSynth() {
    // https://msdn.microsoft.com/en-us/library/hh279669.aspx
    // You can pass a shared_ptr to another function in the following ways:
    // Pass the shared_ptr by value. This invokes the copy constructor, increments the reference count, and makes the callee an owner.
    return synth;
}