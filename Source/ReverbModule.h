/*
  ==============================================================================

    ReverbModule.h
    Created: 6 Dec 2023 11:47:43am
    Author:  martinezd

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ReverbModule : public Component
{
public:
    ReverbModule();

    void resized() override;
private:
    // Reverb Module Font
    Font f;

    // Decay Slider
    Slider decaySlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    Label decayLabel;

    // Predelay Slider
    Slider predelaySlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> predelayAttachment;
    Label predelayLabel;

    // Distance Slider
    Slider distanceSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> distanceAttachment;
    Label distanceLabel;

    // Stereo Width Slider
    Slider widthSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> widthAttachment;
    Label widthLabel;

    // Low Cut Slider
    Slider lowCutSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lowCutAttachment;
    Label lowCutDbLabel;

    // High Cut Slider
    Slider highCutSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> highCutAttachment;
    Label highCutLabel;

    // Mix Slider
    Slider mixSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mixAttachment;
    Label mixLabel;
                                    
};