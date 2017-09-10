/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Model.hpp"


//==============================================================================
LazarusAudioProcessor::LazarusAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
        model(new Model())
#endif
{
}

LazarusAudioProcessor::~LazarusAudioProcessor()
{

}

//==============================================================================
const String LazarusAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LazarusAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LazarusAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double LazarusAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LazarusAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LazarusAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LazarusAudioProcessor::setCurrentProgram (int index)
{
}

const String LazarusAudioProcessor::getProgramName (int index)
{
    return {};
}

void LazarusAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void LazarusAudioProcessor::prepareToPlay (double sampleRate, int /*samplesPerBlock*/)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    keyboardState.reset();



    reset();
}

void LazarusAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    keyboardState.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LazarusAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void LazarusAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // const int totalNumInputChannels  = getTotalNumInputChannels();
    // const int totalNumOutputChannels = getTotalNumOutputChannels();
    //
    // // In case we have more outputs than inputs, this code clears any output
    // // channels that didn't contain input data, (because these aren't
    // // guaranteed to be empty - they may contain garbage).
    // // This is here to avoid people getting screaming feedback
    // // when they first compile a plugin, but obviously you don't need to keep
    // // this code if your algorithm always overwrites all the output channels.
    // for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    //     buffer.clear (i, 0, buffer.getNumSamples());
    //
    // // This is the place where you'd normally do the guts of your plugin's
    // // audio processing...
    // for (int channel = 0; channel < totalNumInputChannels; ++channel)
    // {
    //     float* channelData = buffer.getWritePointer (channel);
    //
    //     // ..do something to the data...
    // }
    //
    // //    int midiEvents = midiMessages.getNumEvents();
    //
    // MidiBuffer::Iterator iterator (midiMessages);
    //
    // int samplePosition;
    // MidiMessage midiMessage;
    //
    // while(iterator.getNextEvent(midiMessage, samplePosition)) {
    //     model->handleIncomingMidiMessage(NULL, midiMessage);
    // }

    process (buffer, midiMessages);
}

void LazarusAudioProcessor::process (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int numSamples = buffer.getNumSamples();
    keyboardState.processNextMidiBuffer (midiMessages, 0, numSamples, true);
}

//==============================================================================
bool LazarusAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* LazarusAudioProcessor::createEditor()
{
    return new LazarusAudioProcessorEditor (*this);
}

//==============================================================================
void LazarusAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void LazarusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LazarusAudioProcessor();
}
