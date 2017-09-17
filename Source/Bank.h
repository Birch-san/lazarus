//
// Created by Alex Birch on 17/09/2017.
//

#pragma once

class Bank {
public:
    Bank(
            int preset,
            int bank,
            char* name
    );

    int getPreset();
    int getBank();
    char* getName();

private:
    int preset;
    int bank;
    char* name;
};