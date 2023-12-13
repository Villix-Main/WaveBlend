/*
  ==============================================================================

    CompressorModule.cpp
    Created: 8 Dec 2023 9:56:35am
    Author:  martinezd

  ==============================================================================
*/

#include "CompressorModule.h"


CompressorModule::CompressorModule() :
    thresholdSlider("Threshold", -25, 0),
    ratioSlider("Ratio", 1, 20),
    attackSlider("attack", 5, 100),
    releaseSlider("release", 5, 500),
    sidechainLowCutSlider("Low Cut", 20, 2000),
    sidechainHighCutSlider("High Cut", 200, 20000),
    mixSlider("Mix", 0, 100),
    outputSlider("Output", -15, 10)
{
    f.setHeight(15);

    // Threshold Slider
    addAndMakeVisible(thresholdSlider);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));

    // Ratio Slider
    addAndMakeVisible(ratioSlider);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));

    // Attack Slider
    addAndMakeVisible(attackSlider);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));

    // Release Slider
    addAndMakeVisible(releaseSlider);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));

    // Sidechain Label
    addAndMakeVisible(sidechainLabel);
    sidechainLabel.setFont(f);
    sidechainLabel.setJustificationType(Justification::centred);
    sidechainLabel.setText("Sidechain", NotificationType::dontSendNotification);

    // Sidechain Low Cut Slider
    addAndMakeVisible(sidechainLowCutSlider);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));

    // Sidechain High Cut Slider
    addAndMakeVisible(sidechainHighCutSlider);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));

    // Mix Slider
    addAndMakeVisible(mixSlider);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));
    
    // Output Slider
    addAndMakeVisible(outputSlider);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));
}

void CompressorModule::resized()
{
    const auto bounds = this->getLocalBounds();


    thresholdSlider.setBounds(61, 40, 85, 115);
    ratioSlider.setBounds(61, 197, 85, 115);
    attackSlider.setBounds(240, 40, 85, 115);
    releaseSlider.setBounds(240, 197, 85, 115);

    sidechainLabel.setBounds(390, 20, 143, 20);
    sidechainLowCutSlider.setBounds(390, 78, 55, 85);
    sidechainHighCutSlider.setBounds(478, 78, 55, 85);

    mixSlider.setBounds(620, 40, 85, 115);
    outputSlider.setBounds(620, 197, 85, 115);
}