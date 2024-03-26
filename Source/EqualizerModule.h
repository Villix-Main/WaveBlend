/*
  ==============================================================================

    EqualizerModule.h
    Created: 8 Dec 2023 10:29:42am
    Author:  martinezd

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ModuleSlider.h"

class EqualizerModule : public Component
{
public:
    EqualizerModule(AudioProcessorValueTreeState& vts);

    void paint(Graphics&) override;
    void resized() override;
private:
    // Compressor Module Font
    Font f;

    // Mix Slider
    ModuleSlider mixSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mixAttachment;

    // Output Slider
    ModuleSlider outputSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> outputAttachment;
};