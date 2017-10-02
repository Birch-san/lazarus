//
// Created by Alex Birch on 01/10/2017.
//

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

using namespace std;

class Pills : public Component,
              public ButtonListener {
public:
    Pills(
            string label,
            const vector<string> &items,
            const function<void (int)> &onItemSelected,
            const function<int (const string&)> &itemToIDMapper,
            int initiallySelectedItem
    );

    void buttonClicked (Button* button) override;
    void cycle(bool right);

private:
    string label;
    vector<string> items;
    function<void (int)> onItemSelected;
    function<int (const string&)> itemToIDMapper;

    OwnedArray<TextButton> buttons;
    Button *selected;

    TextButton* addToList (TextButton* newButton);

    void populate(int initiallySelectedItem);
    void resized() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Pills)
};