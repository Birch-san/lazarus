/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LazarusAudioProcessorEditor::LazarusAudioProcessorEditor (LazarusAudioProcessor& p)
    : AudioProcessorEditor (&p),
      processor (p),
      midiKeyboard (p.keyboardState, SurjectiveMidiKeyboardComponent::horizontalKeyboard),
      tablesComponent(p.getFluidSynthModel())
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    midiKeyboard.setName ("MIDI Keyboard");

    midiKeyboard.setWantsKeyboardFocus(false);
    tablesComponent.setWantsKeyboardFocus(false);

    setWantsKeyboardFocus(true);
    addAndMakeVisible (midiKeyboard);

    addAndMakeVisible(tablesComponent);
}

LazarusAudioProcessorEditor::~LazarusAudioProcessorEditor()
{
}

//==============================================================================
void LazarusAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

//    g.setColour (Colours::white);
//    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);

    if (!focusInitialized) {
        if (!hasKeyboardFocus(false) && isVisible()) {
            grabKeyboardFocus();
        }
        if (getCurrentlyFocusedComponent() == this) {
            focusInitialized = true;
        }
    }
}

void LazarusAudioProcessorEditor::resized()
{
    const int padding = 8;
    const int pianoHeight = 70;
    Rectangle<int> r (getLocalBounds().reduced (padding));

    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    midiKeyboard.setBounds (r.removeFromBottom (pianoHeight));

    Rectangle<int> r2 (getLocalBounds());
    r2.reduce(0, padding);
    r2.removeFromBottom(pianoHeight);
    tablesComponent.setBounds (r2);
}

bool LazarusAudioProcessorEditor::keyPressed(const KeyPress &key) {
//    if (!hasKeyboardFocus(false))
//        return false;
//    if (key.getKeyCode() == KeyPress::upKey){
//    }
//    cout << "hey\n";
    const int cursorKeys[] = {
            KeyPress::leftKey,
            KeyPress::rightKey,
            KeyPress::upKey,
            KeyPress::downKey
    };
    if (any_of(
            begin(cursorKeys),
            end(cursorKeys),
            [&](int i) { return i == key.getKeyCode(); }
    )) {
        return tablesComponent.keyPressed(key);
    } else {
        return midiKeyboard.keyPressed(key);
    }
//    for(auto childComponent : getChildren()) {
//        if (childComponent->keyPressed(key)) return true;
//    }
    return false;
}

bool LazarusAudioProcessorEditor::keyStateChanged (bool isKeyDown) {
    return midiKeyboard.keyStateChanged(isKeyDown);
//    for(auto childComponent : getChildren()) {
//        if (childComponent->keyStateChanged(isKeyDown)) return true;
//    }
//    return false;
}