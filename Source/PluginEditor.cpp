/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthFrameworkAudioProcessorEditor::SynthFrameworkAudioProcessorEditor (SynthFrameworkAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), oscillatorGUI(p), envelopeGUI(p), filterGUI(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (760, 560);

    addAndMakeVisible(&oscillatorGUI);

    addAndMakeVisible(&envelopeGUI);

    addAndMakeVisible(&filterGUI);
}

SynthFrameworkAudioProcessorEditor::~SynthFrameworkAudioProcessorEditor()
{
}

//==============================================================================
void SynthFrameworkAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
}

void SynthFrameworkAudioProcessorEditor::resized()
{    
    oscillatorGUI.setBounds(20, 20, 200, 200);
    envelopeGUI.setBounds(240, 20, 500, 320);
    filterGUI.setBounds(130, 220, 500, 320);
}