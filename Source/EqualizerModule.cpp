/*
  ==============================================================================

    EqualizerModule.cpp
    Created: 8 Dec 2023 10:29:42am
    Author:  martinezd

  ==============================================================================
*/

#include "EqualizerModule.h"
#include "WaveBlendColors.h"


EqualizerModule::EqualizerModule(AudioProcessorValueTreeState& vts) :
    mixSlider("Mix", 0, 100),
    outputSlider("Output", -15, 10),
    hzSubSlider("Sub", -5, 5),
    hz40Slider("40 Hz", -5, 5),
    hz160Slider("160 Hz", -5, 5),
    hz650Slider("650 Hz", -5, 5),
    hz2500Slider("2.5 kHz", -5, 5),
    airGainSlider("Air Gain", 0, 10),
    airBandSlider("Air Band", 2.5, 40)
{
    f.setHeight(15);

    // Mix Slider
    addAndMakeVisible(mixSlider);
    mixAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "equalizer_mix", mixSlider));

    // Output Slider
    addAndMakeVisible(outputSlider);
    outputAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "equalizer_output", outputSlider));

    // Sub Hz Slider
    addAndMakeVisible(hzSubSlider);
	hzSubAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "equalizer_sub_hz", hzSubSlider));

	// 40 Hz Slider
	addAndMakeVisible(hz40Slider);
	hz40Attachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "equalizer_40_hz", hz40Slider));

	// 160 Hz Slider
	addAndMakeVisible(hz160Slider);
	hz160Attachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "equalizer_160_hz", hz160Slider));

	// 650 Hz Slider
	addAndMakeVisible(hz650Slider);
	hz650Attachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "equalizer_650_hz", hz650Slider));

	// 2500 Hz Slider
	addAndMakeVisible(hz2500Slider);
	hz2500Attachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "equalizer_2500_hz", hz2500Slider));

	// Air Gain Slider
	addAndMakeVisible(airGainSlider);
	airGainAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "equalizer_air_gain", airGainSlider));

	// Air Band Slider
	addAndMakeVisible(airBandSlider);
	airBandAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "equalizer_air_band", airBandSlider));


}

void EqualizerModule::paint(Graphics& g)
{
    auto bounds = getLocalBounds();





}

void EqualizerModule::resized()
{
    const auto bounds = this->getLocalBounds();

    outputSlider.setBounds(690, 230, 50, 70);
	mixSlider.setBounds(750, 230, 50, 70);

    hzSubSlider.setBounds(69, 40, 85, 105);
    hz40Slider.setBounds(141, 180, 85, 105);
    hz160Slider.setBounds(238, 40, 85, 105);
    hz650Slider.setBounds(334, 180, 85, 105);
    hz2500Slider.setBounds(430, 40, 85, 105);
    airGainSlider.setBounds(527, 180, 85, 105);
    airBandSlider.setBounds(700, 40, 85, 105);
}