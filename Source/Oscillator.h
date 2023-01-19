/*
  ==============================================================================

    Oscillator.h
    Created: 19 Jan 2023 7:30:22pm
    Author:  vivek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
using namespace juce;

//==============================================================================
/*
*/
class Oscillator  : public juce::Component, private ComboBox::Listener
{
public:
    Oscillator(SynthFrameworkAudioProcessor&);
    ~Oscillator() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void comboBoxChanged(ComboBox*) override;

private:
    SynthFrameworkAudioProcessor& audioProcessor;

    ComboBox oscillatorMenu;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
