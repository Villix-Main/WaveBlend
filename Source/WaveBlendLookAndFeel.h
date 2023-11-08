/*
  ==============================================================================

    WaveBlendLookAndFeel.h
    Created: 6 Nov 2023 1:51:31pm
    Author:  martinezd

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WaveBlendColors.h"

class WaveBlendLookAndFeel : public juce::LookAndFeel_V4
{
public:

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPosProportional, float rotaryStartAngle,
        float rotaryEndAngle, juce::Slider&) override;

    
    Font getLabelFont(Label&) override;


    static const Font getCustomFont()
    {
        static auto typeface = 
            Typeface::createSystemTypefaceFor(BinaryData::segoeui_ttf, BinaryData::segoeui_ttfSize);

        return Font(typeface);

    }

    Typeface::Ptr getTypefaceForFont(const Font& f) override
    {
        // This can be used to fully change/inject fonts.
        // For example: return different TTF/OTF based on weight of juce::Font (bold/italic/etc)
        return getCustomFont().getTypeface();
    }


private:
};