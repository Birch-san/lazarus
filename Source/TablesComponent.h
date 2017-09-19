//
// Created by Alex Birch on 17/09/2017.
//

#pragma once

#include "TableComponent.h"
#include "PresetsToBanks.h"
#include "FluidSynthModel.h"
#include <memory>

using namespace std;

class TablesComponent : public Component {
public:
    TablesComponent(
            shared_ptr<FluidSynthModel> fluidSynthModel
    );

//    void resized() override;

private:

    TableComponent* bankTable;
    TableComponent* presetTable;

    shared_ptr<FluidSynthModel> fluidSynthModel;

    static unique_ptr<vector<vector<string>>> mapPresets(const BanksToPresets &banksToPresets, int bank);
    static unique_ptr<vector<vector<string>>> mapBanks(const BanksToPresets &banksToPresets);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TablesComponent)
};
