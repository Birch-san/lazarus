//
// Created by Alex Birch on 17/09/2017.
//

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Bank {
public:
    Bank(
            int bank,
            String name
    );

    int getBank();
    String getName();

private:
    int bank;
    String name;
};