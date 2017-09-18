//
// Created by Alex Birch on 17/09/2017.
//

#include "Bank.h"

using namespace std;

Bank::Bank(
        int bank,
        string name
) : bank(bank),
    name(name) {}

int Bank::getBank() {
    return bank;
}

string Bank::getName() {
    return name;
}