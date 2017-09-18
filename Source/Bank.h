//
// Created by Alex Birch on 17/09/2017.
//

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

using namespace std;

class Bank {
public:
    Bank(
            int bank,
            string name
    );

    int getBank();
    string getName();

private:
    int bank;
    string name;
};