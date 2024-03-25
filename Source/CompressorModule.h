/*
  ==============================================================================

    CompressorModule.h
    Created: 8 Dec 2023 9:56:35am
    Author:  martinezd

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ModuleSlider.h"

class CompressorModule : public Component
{
public:
    CompressorModule(AudioProcessorValueTreeState& vts);

    void paint(Graphics&);
    void resized() override;
private:
    // Compressor Module Font
    Font f;

    // Threshold Slider
    ModuleSlider thresholdSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> thresholdAttachment;

    // Ratio Slider
    ModuleSlider ratioSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> ratioAttachment;

    // Attack Slider
    ModuleSlider attackSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackAttachment;

    // Release Slider
    ModuleSlider releaseSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;

    // Sidechain EQ Rect
    Rectangle<int> sidechainRect;

    // Sidechain EQ label
    Label sidechainLabel;

    // Low Cut Sidechain Slider
    ModuleSlider lowCutSidechainSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lowCutSidechainAttachment;

    // High Cut Sidechain Slider
    ModuleSlider highCutSidechainSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> highCutSidechainAttachment;

    // Mix Slider
    ModuleSlider mixSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mixAttachment;

    // Output Slider
    ModuleSlider outputSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> outputAttachment;
};