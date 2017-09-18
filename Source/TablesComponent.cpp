//
// Created by Alex Birch on 17/09/2017.
//

#include "TablesComponent.h"
#include <string>

using namespace std;

TablesComponent::TablesComponent(
        shared_ptr<FluidSynthModel> fluidSynthModel
) : fluidSynthModel(fluidSynthModel)
{
    presetTable = new TableComponent();
    bankTable = new TableComponent();

    shared_ptr<PresetsToBanks> presetsToBanks = fluidSynthModel->getBanks();

    vector<string> columns = {"", ""};

    addAndMakeVisible (presetTable);
    addAndMakeVisible (bankTable);
}

void TablesComponent::resized() {
}