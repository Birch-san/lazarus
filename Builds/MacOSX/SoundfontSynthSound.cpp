//
// Created by Alex Birch on 07/09/2017.
//

#include "SoundfontSynthSound.h"

SoundfontSynthSound::SoundfontSynthSound() {}
SoundfontSynthSound::~SoundfontSynthSound() {}

bool SoundfontSynthSound::appliesToChannel(int) {
    return true;
}

bool SoundfontSynthSound::appliesToNote(int) {
    return true;
}