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
    populate(initiallySelectedItem);
}

void Pills::populate(int initiallySelectedItem) {
    int index = 0;
    for (string item : items) {
        TextButton* pill = addToList(new TextButton(
                item
        ));
//        pill->setBounds(20 + index * 55, 260, 55, 24);
        pill->setConnectedEdges (
                (index == 0 ? 0 : Button::ConnectedOnLeft)
                        | (index == items.size() ? 0 : Button::ConnectedOnRight)
        );
        pill->setRadioGroupId(34567);
        if (index == initiallySelectedItem) {
            pill->setToggleState(true, dontSendNotification);
        }
        index++;
    }
}

void Pills::buttonClicked (Button* button) {

}

TextButton* Pills::addToList (TextButton* newButton) {
    buttons.add (newButton);
    addAndMakeVisible (newButton);
    return newButton;
}

void Pills::resized() {
    int index = 0;
    for(TextButton* t : buttons) {
        Rectangle<int> r (getLocalBounds());
        r.removeFromLeft(index*50);
        t->setBounds (r);
        index++;
    }
}