/*
  ==============================================================================

    Filter.cpp
    Created: 28 Jan 2023 4:47:56pm
    Author:  vivek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Filter.h"

//==============================================================================
Filter::Filter(SynthFrameworkAudioProcessor& p) : 
    audioProcessor(p)
{
    setSize(500, 320);

    cutoffSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    cutoffSlider.setRange(0.0f, 8000.0f, 1.0f);
    cutoffSlider.setSkewFactorFromMidPoint(2000.0f);
    cutoffSlider.setValue(8000.0f);
    cutoffSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    cutoffSlider.setTextValueSuffix(" Hz");
    cutoffSlider.addListener(this);
    addAndMakeVisible(cutoffSlider);

    resonanceSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    resonanceSlider.setRange(0.0f, 100.0f, 1.0f);
    resonanceSlider.setValue(0.0f);
    resonanceSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    resonanceSlider.setTextValueSuffix(" %");
    resonanceSlider.addListener(this);
    addAndMakeVisible(resonanceSlider);

    gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSlider.setRange(-48.0f, 6.0f, 0.1f);
    gainSlider.setSkewFactorFromMidPoint(-9.0f);
    gainSlider.setValue(0.0f);
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    gainSlider.setTextValueSuffix(" dB");
    gainSlider.addListener(this);
    addAndMakeVisible(gainSlider);

}

Filter::~Filter()
{
}

void Filter::paint (juce::Graphics& g)
{
    
}

void Filter::resized()
{
    cutoffSlider.setBounds(20, 20, 150, 150);
    resonanceSlider.setBounds(180, 45, 100, 100);

    gainSlider.setBounds(360, 20, 50, 150);
}

void Filter::sliderValueChanged(Slider* slider) {
    if (slider == &cutoffSlider) {
        audioProcessor.cutoffFrequency = cutoffSlider.getValue();
    }
    else if (slider == &resonanceSlider) {
        audioProcessor.resonanceLevel = resonanceSlider.getValue();
    }
    else if (slider == &gainSlider) {
        audioProcessor.gainLevel = pow(10, gainSlider.getValue() / 20.0);
    }
}