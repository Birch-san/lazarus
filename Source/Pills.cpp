//
// Created by Alex Birch on 01/10/2017.
//

#include "Pills.h"

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

}

void Pills::buttonClicked (Button* button) {

}

template <typename ComponentType>
ComponentType* Pills::addToList (ComponentType* newComp) {
    components.add (newComp);
    addAndMakeVisible (newComp);
    return newComp;
}