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

    // Sub Hz Slider
	ModuleSlider hzSubSlider;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> hzSubAttachment;

    // 40 Hz Slider
	ModuleSlider hz40Slider;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> hz40Attachment;

	// 160 Hz Slider
	ModuleSlider hz160Slider;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> hz160Attachment;

	// 650 Hz Slider
	ModuleSlider hz650Slider;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> hz650Attachment;

	// 2.5 kHz Slider
	ModuleSlider hz2500Slider;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> hz2500Attachment;

	// Air Gain Slider
	ModuleSlider airGainSlider;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> airGainAttachment;

	// Air Band Slider
	ModuleSlider airBandSlider;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> airBandAttachment;

};