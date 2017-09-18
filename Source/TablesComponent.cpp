//
// Created by Alex Birch on 17/09/2017.
//

#include "TablesComponent.h"

using namespace std;

TablesComponent::TablesComponent(
        shared_ptr<FluidSynthModel> fluidSynthModel
) : fluidSynthModel(fluidSynthModel)
{
    unique_ptr<PresetsToBanks> presetsToBanks = fluidSynthModel->getBanks();

    vector<string> presetColumns = {"Preset"};
    vector<string> bankColumns = {"Bank", "Name"};
    presetTable = new TableComponent(
            presetColumns,
            *mapPresets(
                    *presetsToBanks
            )
    );
    bankTable = new TableComponent(
            bankColumns,
            *mapBanks(
                    *presetsToBanks,
                    0
            )
    );

    addAndMakeVisible (presetTable);
    addAndMakeVisible (bankTable);
}

unique_ptr<vector<vector<string>>> TablesComponent::mapPresets(const PresetsToBanks& presetsToBanks) {
    vector<vector<string>> rows;

    const auto compareKey = [](const PresetsToBanks::value_type& lhs, const PresetsToBanks::value_type& rhs) {
        return lhs.first < rhs.first;
    };

    for(auto i = presetsToBanks.begin(); i != presetsToBanks.end(); i = std::upper_bound(i, presetsToBanks.end(), *i, compareKey)) {
        vector<string> row;

        row.push_back(to_string(i->first));

        rows.push_back(row);
    }

    return unique_ptr<vector<vector<string>>>(&rows);
}


unique_ptr<vector<vector<string>>> TablesComponent::mapBanks(const PresetsToBanks& presetsToBanks, int bank) {
    vector<vector<string>> rows;

    pair<PresetsToBanks::const_iterator, PresetsToBanks::const_iterator> iterators = presetsToBanks.equal_range(bank);
    for (auto it = iterators.first; it != iterators.second; ++it) {
        Bank b = it->second;
        vector<string> row;
        row.push_back(to_string(b.getBank()));
        row.push_back(b.getName());

        rows.push_back(row);
    }

    return unique_ptr<vector<vector<string>>>(&rows);
}