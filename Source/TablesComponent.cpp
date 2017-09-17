//
// Created by Alex Birch on 17/09/2017.
//

#include "TablesComponent.h"

TablesComponent::TablesComponent(
        shared_ptr<PresetsToBanks> presetsToBanks
) : presetsToBanks(presetsToBanks)
{
    presetTable = new TableComponent();
    bankTable = new TableComponent();

    addAndMakeVisible (presetTable);
    addAndMakeVisible (bankTable);
}

void TablesComponent::resized() {
}