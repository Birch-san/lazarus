//
// Created by Alex Birch on 17/09/2017.
//

#include "TablesComponent.h"

using namespace std;
using namespace placeholders;

TablesComponent::TablesComponent(
        shared_ptr<FluidSynthModel> fluidSynthModel
) : fluidSynthModel(fluidSynthModel),
    banksToPresets(fluidSynthModel->getBanks()),
    initialised(false)
{
    fluid_preset_t* currentPreset = getCurrentPreset();

    selectedBank = currentPreset->get_banknum(currentPreset);
    int selectedPreset = currentPreset->get_num(currentPreset);

    auto rowToIndexMapper = [](const vector<string> &row) {
        return stoi(row[0]);
    };
    auto itemToBankMapper = [](const string &item) {
        return stoi(item);
    };

    presetTable = new TableComponent(
            {"Preset", "Name"},
            mapPresets(
                    banksToPresets,
                    currentPreset->get_banknum(currentPreset)
            ),
            [this](int preset){
                this->onPresetSelected(preset);
            },
            rowToIndexMapper,
            selectedPreset
    );
    banks = new Pills(
            "Banks",
            mapBanks(banksToPresets),
            [this](int bank){
                this->onBankSelected(bank);
            },
            itemToBankMapper,
            selectedBank
    );

    presetTable->setWantsKeyboardFocus(false);

    addAndMakeVisible (presetTable);

    addAndMakeVisible (banks);

    initialised = true;
}

fluid_preset_t* TablesComponent::getCurrentPreset() {
    FluidSynthModel* fluidSynthModelP = fluidSynthModel.get();
    fluid_synth_t* synth = fluidSynthModelP->getSynth().get();

    return fluid_synth_get_channel_preset(synth, fluidSynthModelP->getChannel());
}

Preset TablesComponent::getFirstPresetInBank(int bank) {
    pair<BanksToPresets::const_iterator, BanksToPresets::const_iterator> iterators = banksToPresets.equal_range(bank);
    BanksToPresets::const_iterator it = iterators.first;
    return it->second;
}

void TablesComponent::onBankSelected(int bank) {
    if (!initialised) {
        return;
    }
    cout << "Bank " << bank << endl;
    selectedBank = bank;
    Preset firstPresetInBank = getFirstPresetInBank(bank);
    presetTable->setRows(
            mapPresets(
                    banksToPresets,
                    bank
            ),
            firstPresetInBank.getPreset()
    );
}

void TablesComponent::onPresetSelected(int preset) {
    if (!initialised) {
        return;
    }
    cout << "Preset " << preset << endl;
//    selectedPreset = preset;
    fluidSynthModel.get()->changePreset(selectedBank, preset);
}

TablesComponent::~TablesComponent() {
    delete presetTable;
    delete banks;
}

vector<string> TablesComponent::mapBanks(const BanksToPresets &banksToPresets) {
    vector<string> rows;

    const auto compareKey = [](const BanksToPresets::value_type& lhs, const BanksToPresets::value_type& rhs) {
        return lhs.first < rhs.first;
    };

    for(auto i = banksToPresets.begin(); i != banksToPresets.end(); i = std::upper_bound(i, banksToPresets.end(), *i, compareKey)) {
        rows.push_back(to_string(i->first));
    }

    return rows;
}


vector<vector<string>> TablesComponent::mapPresets(const BanksToPresets &banksToPresets, int bank) {
    vector<vector<string>> rows;

    pair<BanksToPresets::const_iterator, BanksToPresets::const_iterator> iterators = banksToPresets.equal_range(bank);
    for (auto it = iterators.first; it != iterators.second; ++it) {
        Preset b = it->second;
        vector<string> row;
        row.push_back(to_string(b.getPreset()));
        row.push_back(b.getName());

        rows.push_back(row);
    }

    return rows;
}

void TablesComponent::resized() {
    Rectangle<int> r (getLocalBounds());
    banks->setBounds (r.removeFromTop(30));

    presetTable->setBounds (r);
}

bool TablesComponent::keyPressed(const KeyPress &key) {
    if (key.getKeyCode() == KeyPress::leftKey
            || key.getKeyCode() == KeyPress::rightKey) {
        banks->cycle(key.getKeyCode() == KeyPress::rightKey);
        return true;
    }
    return presetTable->keyPressed(key);
}