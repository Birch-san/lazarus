//
// Created by Alex Birch on 17/09/2017.
//

#include "Bank.h"

Bank::Bank(
        int preset,
        int bank,
        String name
) : preset(preset),
    bank(bank),
    name(name) {}

int Bank::getPreset() {
    return preset;
}

int Bank::getBank() {
    return bank;
}

String Bank::getName() {
    return name;
}