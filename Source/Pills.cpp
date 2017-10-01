//
// Created by Alex Birch on 01/10/2017.
//

#include "Pills.h"
#include "Pill.h"

using namespace std;

Pills::Pills(
        string label,
        const vector<string> &items,
        const function<void (int)> &onItemSelected,
        const function<int (const string&)> &itemToIndexMapper,
        int initiallySelectedItem
) : label(label),
    items(items),
    onItemSelected(onItemSelected),
    itemToIndexMapper(itemToIndexMapper)
{
    populate(initiallySelectedItem);
}

void Pills::populate(int initiallySelectedItem) {
    int index = 0;
    for (string item : items) {
        Pill* pill = addToList(new Pill(
                item,
                index,
                static_cast<const int>(items.size())
        ));
        pill->setRadioGroupId(34567);
        if (index == initiallySelectedItem) {
            pill->setToggleState(true, dontSendNotification);
        }
        index++;
    }
}

void Pills::buttonClicked (Button* button) {

}

template <typename ComponentType>
ComponentType* Pills::addToList (ComponentType* newComp) {
    components.add (newComp);
    addAndMakeVisible (newComp);
    return newComp;
}