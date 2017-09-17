//
// Created by Alex Birch on 17/09/2017.
//

#include "Bank.h"

Bank::Bank(
        int bank,
        String name
) : bank(bank),
    name(name) {}

int Bank::getBank() {
    return bank;
}

String Bank::getName() {
    return name;
}