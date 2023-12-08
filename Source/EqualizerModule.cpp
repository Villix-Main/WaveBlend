/*
  ==============================================================================

    EqualizerModule.cpp
    Created: 8 Dec 2023 10:29:42am
    Author:  martinezd

  ==============================================================================
*/

#include "EqualizerModule.h"


EqualizerModule::EqualizerModule() :
    mixSlider("Mix", 0, 100),
    outputSlider("Output", -15, 10)
{
    f.setHeight(15);

    // Mix Slider
    addAndMakeVisible(mixSlider);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));

    // Output Slider
    addAndMakeVisible(outputSlider);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));
}

void EqualizerModule::resized()
{
    const auto bounds = this->getLocalBounds();

    mixSlider.setBounds(620, 40, 85, 115);
    outputSlider.setBounds(620, 197, 85, 115);
}