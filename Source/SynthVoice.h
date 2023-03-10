/*
  ==============================================================================

    SynthVoice.h
    Created: 27 Dec 2022 4:02:56pm
    Author:  vivek

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public SynthesiserVoice {
public:
    bool canPlaySound(SynthesiserSound* sound) override {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }

    void getParameters(float attack, float decay, float sustain, float release, float cutoffFrequency, float resonanceLevel, float gainLevel) {
        envelope.setAttack(attack);
        envelope.setDecay(decay);
        envelope.setSustain(sustain);
        envelope.setRelease(release);

        cutoff = cutoffFrequency;
        resonance = resonanceLevel;
        gain = gainLevel;
    }

    void getOscillatorType(int selection) {
        wave = selection;
    }

    double getWavefromSelection() {
        if (wave == 1) {
            return oscillator.sinewave(frequency);
        } else if (wave == 2) {
            return oscillator.square(frequency);
        } else if (wave == 3) {
            return oscillator.triangle(frequency);
        } else if (wave == 4) {
            return oscillator.saw(frequency);
        } else {
            return oscillator.sinewave(frequency);
        }
    }

    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override {
        level = velocity;
        envelope.trigger = 1;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        std::cout << frequency << std::endl;
    }

    void stopNote(float velocity, bool allowTailoff) override {
        envelope.trigger = 0;
        allowTailoff = true;
        
        if (velocity == 0) {
            clearCurrentNote();
        }
    }

    void pitchWheelMoved(int pitchWheelValued) override {

    }

    void controllerMoved(int controllerNumber, int newControllerValue) override {

    }

    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSamples, int numSamples) override {
        for (int sample = 0; sample < numSamples; sample++) {
            sound = envelope.adsr(getWavefromSelection(), envelope.trigger) * level * gain;
            filteredSound = filter.lores(sound, cutoff, resonance);

            for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++) {
                outputBuffer.addSample(channel, startSamples, filteredSound);
            }

            ++startSamples;
        }
    }

private:
    double level;
    double gain;

    double frequency;
    
    int wave;
    double sound;
    double filteredSound;

    double cutoff;
    double resonance;

    maxiOsc oscillator;
    maxiEnv envelope;
    maxiFilter filter;
};