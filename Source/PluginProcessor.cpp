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

AudioProcessor* JUCE_CALLTYPE createPluginFilter();


//==============================================================================
LazarusAudioProcessor::LazarusAudioProcessor()
     : AudioProcessor (getBusesProperties()),
       fluidSynthModel(),
       lastUIWidth(400),
       lastUIHeight(300)
{
    initialiseSynth();
}

LazarusAudioProcessor::~LazarusAudioProcessor()
{
//    delete fluidSynthModel;
}

void LazarusAudioProcessor::initialiseSynth() {
    fluidSynthModel.initialise();

    fluidSynth = fluidSynthModel.getSynth();

    const int numVoices = 8;

    // Add some voices...
    for (int i = numVoices; --i >= 0;)
        synth.addVoice (new SoundfontSynthVoice(fluidSynthModel.getSynth()));

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

void LazarusAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages) {
    jassert (!isUsingDoublePrecision());
    const int numSamples = buffer.getNumSamples();

    // Now pass any incoming midi messages to our keyboard state object, and let it
    // add messages to the buffer if the user is clicking on the on-screen keys
    keyboardState.processNextMidiBuffer (midiMessages, 0, numSamples, true);

    // and now get our synth to process these midi events and generate its output.
    synth.renderNextBlock (buffer, midiMessages, 0, numSamples);
    fluid_synth_process(fluidSynth, numSamples, 1, nullptr, buffer.getNumChannels(), buffer.getArrayOfWritePointers());

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
//    for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
//        buffer.clear (i, 0, numSamples);
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

    // Create an outer XML element..
    XmlElement xml ("MYPLUGINSETTINGS");

    // add some attributes to it..
    xml.setAttribute ("uiWidth", lastUIWidth);
    xml.setAttribute ("uiHeight", lastUIHeight);

    // Store the values of all our parameters, using their param ID as the XML attribute
    for (auto* param : getParameters())
        if (auto* p = dynamic_cast<AudioProcessorParameterWithID*> (param))
            xml.setAttribute (p->paramID, p->getValue());

    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xml, destData);
}

void LazarusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    // This getXmlFromBinary() helper function retrieves our XML from the binary blob..
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState != nullptr)
    {
        // make sure that it's actually our type of XML object..
        if (xmlState->hasTagName ("MYPLUGINSETTINGS"))
        {
            // ok, now pull out our last window size..
            lastUIWidth  = jmax (xmlState->getIntAttribute ("uiWidth", lastUIWidth), 400);
            lastUIHeight = jmax (xmlState->getIntAttribute ("uiHeight", lastUIHeight), 300);

            // Now reload our parameters..
            for (auto* param : getParameters())
                if (auto* p = dynamic_cast<AudioProcessorParameterWithID*> (param))
                    p->setValue ((float) xmlState->getDoubleAttribute (p->paramID, p->getValue()));
        }
    }
}

// FluidSynth only supports float in its process function, so that's all we can support.
bool LazarusAudioProcessor::supportsDoublePrecisionProcessing() const {
    return false;
}

FluidSynthModel* LazarusAudioProcessor::getFluidSynthModel() {
    return &fluidSynthModel;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LazarusAudioProcessor();
}

void LazarusAudioProcessor::setLastUIWidth(int width) {
    this->lastUIWidth = width;
}
void LazarusAudioProcessor::setLastUIHeight(int height) {
    this->lastUIHeight = height;
}

int LazarusAudioProcessor::getLastUIWidth() {
    return lastUIWidth;
}
int LazarusAudioProcessor::getLastUIHeight() {
    return lastUIHeight;
}