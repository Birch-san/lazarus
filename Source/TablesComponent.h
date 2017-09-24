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
    ~TablesComponent();

    void resized() override;

private:
    shared_ptr<FluidSynthModel> fluidSynthModel;

    TableComponent* bankTable;
    TableComponent* presetTable;

    static vector<vector<string>> mapPresets(const BanksToPresets &banksToPresets, int bank);
    static vector<vector<string>> mapBanks(const BanksToPresets &banksToPresets);

    int rowToIndexMapper(vector<string> row);
    void onBankSelected(int bank);
    void onPresetSelected(int preset);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TablesComponent)
};
