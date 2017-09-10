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
      midiKeyboard (p.keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    midiKeyboard.setName ("MIDI Keyboard");
    addAndMakeVisible (midiKeyboard);
}

LazarusAudioProcessorEditor::~LazarusAudioProcessorEditor()
{
}

//==============================================================================
void LazarusAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void LazarusAudioProcessorEditor::resized()
{
    Rectangle<int> r (getLocalBounds().reduced (8));

    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    midiKeyboard.setBounds (r.removeFromBottom (70));
}
