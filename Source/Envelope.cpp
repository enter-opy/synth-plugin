/*
  ==============================================================================

    Envelope.cpp
    Created: 19 Jan 2023 10:46:17pm
    Author:  vivek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(SynthFrameworkAudioProcessor& p) :
    audioProcessor(p)
{
    setSize(400, 320);

    attackSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    attackSlider.setRange(0.1f, 5000.0f, 0.1f);
    attackSlider.setSkewFactorFromMidPoint(1000.0f);
    attackSlider.setValue(0.1f);
    attackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    attackSlider.setTextValueSuffix(" ms");
    attackSlider.addListener(this);
    addAndMakeVisible(attackSlider);

    decaySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    decaySlider.setRange(0.1f, 5000.0f, 0.1f);
    decaySlider.setSkewFactorFromMidPoint(1000.0f);
    decaySlider.setValue(0.1f);
    decaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    decaySlider.setTextValueSuffix(" ms");
    decaySlider.addListener(this);
    addAndMakeVisible(decaySlider);

    sustainSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sustainSlider.setRange(0.1f, 100.0f, 0.1f);
    sustainSlider.setValue(100.0f);
    sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    sustainSlider.setTextValueSuffix(" %");
    sustainSlider.addListener(this);
    addAndMakeVisible(sustainSlider);

    releaseSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    releaseSlider.setRange(0.1f, 5000.0f, 0.1f);
    releaseSlider.setSkewFactorFromMidPoint(1000.0f);
    releaseSlider.setValue(0.1f);
    releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    releaseSlider.setTextValueSuffix(" ms");
    releaseSlider.addListener(this);
    addAndMakeVisible(releaseSlider);
}

Envelope::~Envelope()
{
}

void Envelope::paint (juce::Graphics& g)
{
    
}

void Envelope::resized()
{
    attackSlider.setBounds(20, 20, 100, 100);
    decaySlider.setBounds(140, 20, 100, 100);
    sustainSlider.setBounds(260, 20, 100, 100);
    releaseSlider.setBounds(380, 20, 100, 100);
}

void Envelope::sliderValueChanged(Slider* slider) {
    if (slider == &attackSlider) {
        audioProcessor.attackTime = attackSlider.getValue();
    }
    else if (slider == &decaySlider) {
        audioProcessor.decayTime = decaySlider.getValue();
    }
    else if (slider == &sustainSlider) {
        audioProcessor.sustainLevel = sustainSlider.getValue() / 100.0;
    }
    else if (slider == &releaseSlider) {
        audioProcessor.releaseTime = releaseSlider.getValue();
    }
}