//
//  Model.cpp
//  Lazarus
//
//  Created by Alex Birch on 01/09/2017.
//
//

#include "Model.hpp"

Model::Model()
: isAddingFromMidiInput(false),
  startTime(Time::getMillisecondCounterHiRes() * 0.001) {
  keyboardState.addListener(this);
}

Model::~Model(){
    keyboardState.removeListener(this);
}
    
void Model::handleNoteOn (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) {
    if (! isAddingFromMidiInput)
    {
        MidiMessage m (MidiMessage::noteOn (midiChannel, midiNoteNumber, velocity));
        m.setTimeStamp (Time::getMillisecondCounterHiRes() * 0.001);
        postMessageToList (m, "On-Screen Keyboard");
    }
}

void Model::handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/) {
    if (! isAddingFromMidiInput)
    {
        MidiMessage m (MidiMessage::noteOff (midiChannel, midiNoteNumber));
        m.setTimeStamp (Time::getMillisecondCounterHiRes() * 0.001);
        postMessageToList (m, "On-Screen Keyboard");
    }
}
    
void Model::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) {
    const ScopedValueSetter<bool> scopedInputFlag (isAddingFromMidiInput, true);
    keyboardState.processNextMidiEvent (message);
    postMessageToList (message, source->getName());
}
    
void Model::postMessageToList (const MidiMessage& message, const String& source)
{
    (new IncomingMessageCallback (this, message, source))->post();
}

Model::IncomingMessageCallback::IncomingMessageCallback (Model* o, const MidiMessage& m, const String& s)
        : owner (std::shared_ptr<Model>(o)), message (m), source (s) {}
        
void Model::IncomingMessageCallback::messageCallback ()
{
    auto tmp = owner.lock();
    if (tmp != nullptr)
        tmp->addMessageToList (message, source);
}

void Model::addMessageToList (const MidiMessage& message, const String& source) {
    const double time = message.getTimeStamp() - startTime;
    
    const int hours = ((int) (time / 3600.0)) % 24;
    const int minutes = ((int) (time / 60.0)) % 60;
    const int seconds = ((int) time) % 60;
    const int millis = ((int) (time * 1000.0)) % 1000;
    
    const String timecode (String::formatted ("%02d:%02d:%02d.%03d",
                                              hours,
                                              minutes,
                                              seconds,
                                              millis));
    
    const String description (getMidiMessageDescription (message));
    
    const String midiMessageString (timecode + "  -  " + description + " (" + source + ")"); // [7]
    logMessage (midiMessageString);
}
    
String Model::getMidiMessageDescription (const MidiMessage& m)
{
    if (m.isNoteOn())           return "Note on "  + MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3);
    if (m.isNoteOff())          return "Note off " + MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3);
    if (m.isProgramChange())    return "Program change " + String (m.getProgramChangeNumber());
    if (m.isPitchWheel())       return "Pitch wheel " + String (m.getPitchWheelValue());
    if (m.isAftertouch())       return "After touch " + MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3) +  ": " + String (m.getAfterTouchValue());
    if (m.isChannelPressure())  return "Channel pressure " + String (m.getChannelPressureValue());
    if (m.isAllNotesOff())      return "All notes off";
    if (m.isAllSoundOff())      return "All sound off";
    if (m.isMetaEvent())        return "Meta event";
    
    if (m.isController())
    {
        String name (MidiMessage::getControllerName (m.getControllerNumber()));
        
        if (name.isEmpty())
            name = "[" + String (m.getControllerNumber()) + "]";
        
        return "Controller " + name + ": " + String (m.getControllerValue());
    }
    
    return String::toHexString (m.getRawData(), m.getRawDataSize());
}
    
void Model::logMessage (const String& m)
{
    
}
