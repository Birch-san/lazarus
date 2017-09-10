/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SoundfontSynthVoice.h"
#include "SoundfontSynthSound.h"
// #include "Model.hpp"

AudioProcessor* JUCE_CALLTYPE createPluginFilter();


//==============================================================================
LazarusAudioProcessor::LazarusAudioProcessor()
     : AudioProcessor (getBusesProperties()),
       fluidSynthModel(new FluidSynthModel())
        /*,
       model(new Model())*/
{
    initialiseSynth();
}

LazarusAudioProcessor::~LazarusAudioProcessor()
{
    delete fluidSynthModel;
}

void LazarusAudioProcessor::initialiseSynth() {
    fluidSynthModel->initialise();

    const int numVoices = 8;

    // Add some voices...
    for (int i = numVoices; --i >= 0;)
        synth.addVoice (new SoundfontSynthVoice(fluidSynthModel->getSynth()));

    // ..and give the synth a sound to play
    synth.addSound (new SoundfontSynthSound());
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
    synth.setCurrentPlaybackSampleRate (sampleRate);
    keyboardState.reset();

    reset();
}

void LazarusAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    keyboardState.reset();
}

bool LazarusAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    // Only mono/stereo and input/output must have same layout
    const AudioChannelSet& mainOutput = layouts.getMainOutputChannelSet();
    const AudioChannelSet& mainInput  = layouts.getMainInputChannelSet();

    // input and output layout must either be the same or the input must be disabled altogether
    if (! mainInput.isDisabled() && mainInput != mainOutput)
        return false;

    // do not allow disabling the main buses
    if (mainOutput.isDisabled())
        return false;

    // only allow stereo and mono
    return mainOutput.size() <= 2;
}

AudioProcessor::BusesProperties LazarusAudioProcessor::getBusesProperties() {
    return BusesProperties().withInput  ("Input",  AudioChannelSet::stereo(), true)
            .withOutput ("Output", AudioChannelSet::stereo(), true);
}

//void LazarusAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
//{
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

//    process (buffer, midiMessages);
//}

void LazarusAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages) {
    jassert (!isUsingDoublePrecision());
    process (buffer, midiMessages);
}

void LazarusAudioProcessor::processBlock (AudioBuffer<double>& buffer, MidiBuffer& midiMessages) {
    jassert (isUsingDoublePrecision());
    process (buffer, midiMessages);
}

template <typename FloatType>
void LazarusAudioProcessor::process (AudioBuffer<FloatType>& buffer, MidiBuffer& midiMessages) {
    const int numSamples = buffer.getNumSamples();

    // Now pass any incoming midi messages to our keyboard state object, and let it
    // add messages to the buffer if the user is clicking on the on-screen keys
    keyboardState.processNextMidiBuffer (midiMessages, 0, numSamples, true);

    // and now get our synth to process these midi events and generate its output.
    synth.renderNextBlock (buffer, midiMessages, 0, numSamples);

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, numSamples);
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
