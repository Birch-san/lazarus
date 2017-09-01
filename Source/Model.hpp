//
//  Model.hpp
//  Lazarus
//
//  Created by Alex Birch on 01/09/2017.
//
//

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Model : private MidiKeyboardStateListener, private MidiInputCallback
{
public:
    Model();
    ~Model();
    
    void postMessageToList (const MidiMessage& message, const String& source);
    void addMessageToList (const MidiMessage& message, const String& source);
    void handleNoteOn (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
    void handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/) override;
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) override;
    void logMessage (const String& m);
    
    // This is used to dispach an incoming message to the message thread
    class IncomingMessageCallback   : public CallbackMessage
    {
    public:
        IncomingMessageCallback (Model* o, const MidiMessage& m, const String& s);
        void messageCallback() override;
        
        std::weak_ptr<Model> owner;
        MidiMessage message;
        String source;
    };
    
private:
    
    static String getMidiMessageDescription (const MidiMessage& m);
    
    MidiKeyboardState keyboardState;
    bool isAddingFromMidiInput;
    double startTime;
};
