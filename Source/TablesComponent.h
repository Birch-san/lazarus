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

    TableComponent* presetTable;
    TableComponent* bankTable;

    shared_ptr<FluidSynthModel> fluidSynthModel;

    static unique_ptr<vector<vector<string>>> mapBanks(const PresetsToBanks& presetsToBanks, int bank);
    static unique_ptr<vector<vector<string>>> mapPresets(const PresetsToBanks& presetsToBanks);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TablesComponent)
};
