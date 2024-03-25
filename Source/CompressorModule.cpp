/*
  ==============================================================================

    CompressorModule.cpp
    Created: 8 Dec 2023 9:56:35am
    Author:  martinezd

  ==============================================================================
*/

#include "CompressorModule.h"
#include "WaveBlendColors.h"


CompressorModule::CompressorModule(AudioProcessorValueTreeState& vts) :
    thresholdSlider("Threshold", -25, 0),
    ratioSlider("Ratio", 1.f, 30.f),
    attackSlider("attack", 5, 80),
    releaseSlider("release", 5, 500),
    lowCutSidechainSlider("Low Cut", 20, 2000),
    highCutSidechainSlider("High Cut", 200, 20000),
    mixSlider("Mix", 0, 100),
    outputSlider("Output", -15, 10)
{
    f.setHeight(17);
    f.setBold(true);

    // Threshold Slider
    addAndMakeVisible(thresholdSlider);
    thresholdAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "threshold", thresholdSlider));

    // Ratio Slider
    addAndMakeVisible(ratioSlider);
    ratioAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "ratio", ratioSlider));

    // Attack Slider
    addAndMakeVisible(attackSlider);
    attackAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "attack", attackSlider));

    // Release Slider
    addAndMakeVisible(releaseSlider);
    releaseAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "release", releaseSlider));

    // Sidechain Label
    addAndMakeVisible(sidechainLabel);
    sidechainLabel.setFont(f);
    sidechainLabel.setJustificationType(Justification::centred);
    sidechainLabel.setText("Sidechain", NotificationType::dontSendNotification);

    // Low Cut Sidechain Slider
    addAndMakeVisible(lowCutSidechainSlider);
    lowCutSidechainAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "lowcut_sidechain", lowCutSidechainSlider));

    // High Cut Sidechain Slider
    addAndMakeVisible(highCutSidechainSlider);
    highCutSidechainAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "highcut_sidechain", highCutSidechainSlider));

    // Mix Slider
    addAndMakeVisible(mixSlider);
    mixAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "compressor_mix", mixSlider));
    
    // Output Slider
    addAndMakeVisible(outputSlider);
    outputAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "compressor_output", outputSlider));
}

void CompressorModule::paint(Graphics& g)
{
	g.setColour(WBColors::SecondaryLightGrey);

	g.drawRoundedRectangle(sidechainRect.toFloat(), 10, 1);
}


void CompressorModule::resized()
{
    const auto bounds = this->getLocalBounds();


    thresholdSlider.setBounds(61, 40, 85, 115);
    ratioSlider.setBounds(61, 197, 85, 115);
    attackSlider.setBounds(240, 40, 85, 115);
    releaseSlider.setBounds(240, 197, 85, 115);

    sidechainRect.setBounds(362, 20, 200, 190);
    sidechainLabel.setBounds(390, 27, 143, 20);
	sidechainLabel.setColour(Label::textColourId, WBColors::MoreLightGrey);
    lowCutSidechainSlider.setBounds(390, 78, 55, 85);
    highCutSidechainSlider.setBounds(478, 78, 55, 85);

    mixSlider.setBounds(620, 40, 85, 115);
    outputSlider.setBounds(620, 197, 85, 115);
}