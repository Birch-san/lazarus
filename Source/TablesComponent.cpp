//
// Created by Alex Birch on 17/09/2017.
//

#include "TablesComponent.h"

using namespace std;

TablesComponent::TablesComponent(
        shared_ptr<FluidSynthModel> fluidSynthModel
) : fluidSynthModel(fluidSynthModel),
    banksToPresets(fluidSynthModel->getBanks()),
    bankTable({"Bank"},
            mapBanks(
                    banksToPresets
            )),
    presetTable({"Preset", "Name"},
            mapPresets(
                    banksToPresets,
                    0
            ))
{
    addAndMakeVisible (bankTable);
    addAndMakeVisible (presetTable);
}

vector<vector<string>> TablesComponent::mapBanks(const BanksToPresets &banksToPresets) {
    vector<vector<string>> rows;

    const auto compareKey = [](const BanksToPresets::value_type& lhs, const BanksToPresets::value_type& rhs) {
        return lhs.first < rhs.first;
    };

    for(auto i = banksToPresets.begin(); i != banksToPresets.end(); i = std::upper_bound(i, banksToPresets.end(), *i, compareKey)) {
        vector<string> row;

        row.push_back(to_string(i->first));

        rows.push_back(row);
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
    Rectangle<int> r (getLocalBounds().reduced (8));
    bankTable.setBounds (r.removeFromBottom (120));
    presetTable.setBounds (r.removeFromBottom (100));
}