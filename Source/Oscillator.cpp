/*
  ==============================================================================

    Oscillator.cpp
    Created: 19 Jan 2023 7:30:22pm
    Author:  vivek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(SynthFrameworkAudioProcessor& p) :
    audioProcessor(p)
{
    setSize(200, 200);

    oscillatorMenu.addItem("Sine", 1);
    oscillatorMenu.addItem("Square", 2);
    oscillatorMenu.addItem("Triangle", 3);
    oscillatorMenu.addItem("SawTooth", 4);
    oscillatorMenu.addListener(this);
    oscillatorMenu.setSelectedId(1);
    addAndMakeVisible(oscillatorMenu);

    oscillatorMenu.setJustificationType(Justification::centred);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (juce::Graphics& g)
{
    
}

void Oscillator::resized()
{
    juce::Rectangle<int> area = getLocalBounds();
    oscillatorMenu.setBounds(area.removeFromTop(20));

}

void Oscillator::comboBoxChanged(ComboBox* comboBox) {
    if (comboBox == &oscillatorMenu) {
        audioProcessor.waveType = oscillatorMenu.getSelectedId();
    }
}