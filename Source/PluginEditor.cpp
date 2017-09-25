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
      midiKeyboard (p.keyboardState, MidiKeyboardComponent::horizontalKeyboard),
      tablesComponent(p.getFluidSynthModel())
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    midiKeyboard.setName ("MIDI Keyboard");
    bindKeysToMidiKeyboard();
    addAndMakeVisible (midiKeyboard);

    addAndMakeVisible(tablesComponent);
}

LazarusAudioProcessorEditor::~LazarusAudioProcessorEditor()
{
}

// FL studio key chart:
// http://s3.amazonaws.com/fl_resource/flkeychart.png
void LazarusAudioProcessorEditor::bindKeysToMidiKeyboard() {
    midiKeyboard.clearKeyMappings();
    midiKeyboard.setKeyPressBaseOctave(5); // C3
    int ix, degree;
    int whiteJumps[] = {2,2,1,2,2,2,1};
    int blackJumps[] = {2,3,2,2,3,2};
    int whiteJumpsC = sizeof(whiteJumps)/sizeof(whiteJumps[0]);
    int blackJumpsC = sizeof(blackJumps)/sizeof(blackJumps[0]);

    ix = degree = 0;
    for (const char keyCode : "ZXCVBNM,./") {
        KeyPress keypress(keyCode);
        midiKeyboard.setKeyPressForNote(keypress, degree);
        degree += whiteJumps[ix++ % whiteJumpsC];
    }

    ix = 0;
    degree = 1;
    for (const char keyCode : "SDGHJL;") {
        KeyPress keypress(keyCode);
        midiKeyboard.setKeyPressForNote(keypress, degree);
        degree += blackJumps[ix++ % blackJumpsC];
    }
}

//==============================================================================
void LazarusAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

//    g.setColour (Colours::white);
//    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
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
