/*
  ==============================================================================

    ReverbModule.h
    Created: 6 Dec 2023 11:47:43am
    Author:  martinezd

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ModuleSlider.h"


class ReverbModule : public Component
{
public:
    ReverbModule(AudioProcessorValueTreeState& vts);

    void resized() override;
private:
    // Reverb Module Font
    Font f;

    // Decay Slider
    ModuleSlider decaySlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> decayAttachment;

    // Predelay Slider
    ModuleSlider predelaySlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> predelayAttachment;

    // Distance Slider
    ModuleSlider dampingSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> dampingAttachment;

    // Stereo Width Slider
    ModuleSlider widthSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> widthAttachment;

    // EQ Label
    Label eqLabel;

    // Low Cut Slider
    ModuleSlider lowCutSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lowCutAttachment;

    // High Cut Slider
    ModuleSlider highCutSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> highCutAttachment;

    // Mix Slider
    ModuleSlider mixSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mixAttachment;                          
};