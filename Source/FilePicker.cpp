//
// Created by Alex Birch on 03/10/2017.
//

#include "FilePicker.h"

FilePicker::FilePicker()
: fileChooser(
        "File",
        File(),
        true,
        false,
        false,
        "*.sf2;*.sf3",
        String(),
        "Choose a Soundfont file to load into the synthesizer"
) {
//    setOpaque (true);
    addAndMakeVisible (fileChooser);
    fileChooser.addListener (this);
}
FilePicker::~FilePicker() {
    fileChooser.removeListener (this);
}

void FilePicker::resized() {
    Rectangle<int> r (getLocalBounds());
    fileChooser.setBounds (r);
}

void FilePicker::filenameComponentChanged (FilenameComponent*) {
//    fileChooser.getCurrentFile().loadFileAsString()
}