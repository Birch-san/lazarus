//
// Created by Alex Birch on 17/09/2017.
//

#include "TablesComponent.h"

using namespace std;

TablesComponent::TablesComponent(
        shared_ptr<FluidSynthModel> fluidSynthModel
) : fluidSynthModel(fluidSynthModel)
{
    BanksToPresets banksToPresets(fluidSynthModel->getBanks());

    auto rowToIndexMapper = [](vector<string> row) {
        return stoi(row[0]);
    };

    bankTable = new TableComponent(
            {"Bank"},
            mapBanks(
                    banksToPresets
            ),
            [](int row) {
                cout << "Bank " << row << endl;
            },
            rowToIndexMapper
    );
    presetTable = new TableComponent(
            {"Preset", "Name"},
            mapPresets(
                    banksToPresets,
                    0
            ),
            [](int row) {
                cout << "Preset " << row << endl;
            },
            rowToIndexMapper
    );

    addAndMakeVisible (bankTable);
    addAndMakeVisible (presetTable);
}

TablesComponent::~TablesComponent() {
    delete bankTable;
    delete presetTable;
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
    const int halfHeight = getLocalBounds().proportionOfHeight(0.5f);

    Rectangle<int> r (getLocalBounds());
    bankTable->setBounds (r.removeFromTop (halfHeight));

    Rectangle<int> r2 (getLocalBounds());
    presetTable->setBounds (r2.removeFromBottom(halfHeight));
}