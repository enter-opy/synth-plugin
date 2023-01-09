/*
  ==============================================================================

    SynthSound.h
    Created: 27 Dec 2022 4:02:39pm
    Author:  vivek

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
using namespace juce;

class SynthSound : public SynthesiserSound {
public:
    bool appliesToNote(int midiNOteNumber) {
        return true;
    }

    bool appliesToChannel(int midiChannel) {
        return true;
    }
};