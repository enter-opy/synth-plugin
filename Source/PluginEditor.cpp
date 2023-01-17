/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthFrameworkAudioProcessorEditor::SynthFrameworkAudioProcessorEditor (SynthFrameworkAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 320);

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
    attackSlider.setBounds(20, 20, 100, 100);
    decaySlider.setBounds(140, 20, 100, 100);
    sustainSlider.setBounds(260, 20, 100, 100);
    releaseSlider.setBounds(380, 20, 100, 100);

    cutoffSlider.setBounds(20, 140, 150, 150);
    resonanceSlider.setBounds(180, 165, 100, 100);

    gainSlider.setBounds(360, 140, 50, 150);
}

void SynthFrameworkAudioProcessorEditor::sliderValueChanged(Slider* slider) {
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
    else if (slider == &cutoffSlider) {
        audioProcessor.cutoffFrequency = cutoffSlider.getValue();
    }
    else if (slider == &resonanceSlider) {
        audioProcessor.resonanceLevel = resonanceSlider.getValue();
    }
    else if (slider == &gainSlider) {
        audioProcessor.gainLevel = pow(10, gainSlider.getValue() / 20.0);
    }
}