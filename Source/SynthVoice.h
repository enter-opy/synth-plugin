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
    bool canPlaySound(SynthesiserSound* sound) {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }

    void getParam(float attack) {
        envelope.setAttack(attack);
    }

    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) {
        level = velocity;
        envelope.trigger = 1;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        std::cout << frequency << std::endl;
    }

    void stopNote(float velocity, bool allowTailoff) {
        envelope.trigger = 0;
        allowTailoff = true;
        
        if (velocity == 0) {
            clearCurrentNote();
        }
    }

    void pitchWheelMoved(int pitchWheelValued) {

    }

    void controllerMoved(int controllerNumber, int newControllerValue) {

    }

    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSamples, int numSamples) {
        //envelope.setAttack(20);
        envelope.setDecay(500);
        envelope.setSustain(0.0);
        envelope.setRelease(60);
        
        for (int sample = 0; sample < numSamples; sample++) {
            wave = oscillator.saw(frequency);
            sound = envelope.adsr(wave, envelope.trigger) * level;
            filteredSound = filter.lores(sound, 500, 0.1);

            for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++) {
                outputBuffer.addSample(channel, startSamples, filteredSound);
            }

            ++startSamples;
        }
    }

private:
    double level;
    double frequency;
    double wave;
    double sound;
    double filteredSound;
    maxiOsc oscillator;
    maxiEnv envelope;
    maxiFilter filter;
};