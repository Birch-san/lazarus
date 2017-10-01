//
// Created by Alex Birch on 17/09/2017.
//

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Pills.h"
#include "TableComponent.h"
#include "Preset.h"
#include "PresetsToBanks.h"
#include "FluidSynthModel.h"
#include <memory>
#include <fluidsynth.h>

using namespace std;

class TablesComponent : public Component {
public:
    TablesComponent(
            shared_ptr<FluidSynthModel> fluidSynthModel
    );
    ~TablesComponent();

    void resized() override;

    bool keyPressed(const KeyPress &key) override;

private:
    shared_ptr<FluidSynthModel> fluidSynthModel;
    int selectedBank;
//    int selectedPreset;

    Pills* banks;
    TableComponent* bankTable;
    TableComponent* presetTable;

    TableComponent* focused;

    BanksToPresets banksToPresets;

    static vector<vector<string>> mapPresets(const BanksToPresets &banksToPresets, int bank);
    static vector<vector<string>> mapBanks(const BanksToPresets &banksToPresets);
    static vector<string> mapBanks2(const BanksToPresets &banksToPresets);

    void onBankSelected(int bank);
    void onPresetSelected(int preset);

    fluid_preset_t* getCurrentPreset();
    Preset getFirstPresetInBank(int bank);

    bool initialised;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TablesComponent)
};
