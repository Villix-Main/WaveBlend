/*
  ==============================================================================

    SimpleFilter.h
    Created: 27 Feb 2024 9:13:44am
    Author:  martinezd

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>


// A simple lowpass/highpass filter
class SimpleFilter
{
public:

    void setCutoffFrequency(float frequency);
    void setSampleRate(float sampleRate);

    void processBlock(AudioBuffer<float>&, MidiBuffer&, bool isHighpass);

private:
    float cutoffFrequency;
    float sampleRate;
    std::vector<float> dnBuffer;
};