/*
  ==============================================================================

    Filter.h
    Created: 28 Jan 2023 4:47:56pm
    Author:  vivek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter  : public juce::Component,
    public Slider::Listener
{
public:
    Filter(SynthFrameworkAudioProcessor&);
    ~Filter() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider* slider) override;

private:
    SynthFrameworkAudioProcessor& audioProcessor;

    Slider cutoffSlider;
    Slider resonanceSlider;

    Slider gainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
