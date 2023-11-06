/*
  ==============================================================================

    WaveBlendLookAndFeel.cpp
    Created: 6 Nov 2023 1:51:31pm
    Author:  martinezd

  ==============================================================================
*/

#include "WaveBlendLookAndFeel.h"


void WaveBlendLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPosProportional, float rotaryStartAngle,
    float rotaryEndAngle, juce::Slider&) 
{
    auto radius = (float)juce::jmin(width / 2, height / 2) - 4.0f;
    auto centreX = (float)x + (float)width * 0.5f;
    auto centreY = (float)y + (float)height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    // Fill of slider
    g.setColour(juce::Colour(0xff5B7586));
    g.fillEllipse(rx, ry, rw, rw);

    // Outline of slider
    g.setColour(juce::Colour(0xff707070));
    g.drawEllipse(rx, ry, rw, rw, 1.0f);


    // Pointer
    juce::Path p;
    auto pointerLength = radius * 0.8;
    auto pointerThickness = 2.0f;
    p.addRectangle(-pointerThickness * 0.5f, -radius * 0.8, pointerThickness, pointerLength);
    p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

    // Pointer Color
    g.setColour(juce::Colour(0xffC2C0C0));
    g.fillPath(p);
}