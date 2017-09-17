//
// Created by Alex Birch on 17/09/2017.
//

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Bank {
public:
    Bank(
            int preset,
            int bank,
            String name
    );

    int getPreset();
    int getBank();
    String getName();

private:
    int preset;
    int bank;
    String name;
};