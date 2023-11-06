/*
  ==============================================================================

    WaveBlendLookAndFeel.h
    Created: 6 Nov 2023 1:51:31pm
    Author:  martinezd

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class WaveBlendLookAndFeel : public juce::LookAndFeel_V4
{
public:

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPosProportional, float rotaryStartAngle,
        float rotaryEndAngle, juce::Slider&) override;

private:
};