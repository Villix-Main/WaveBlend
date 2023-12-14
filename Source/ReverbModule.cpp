/*
  ==============================================================================

    ReverbModule.cpp
    Created: 6 Dec 2023 11:47:43am
    Author:  martinezd

  ==============================================================================
*/

#include "ReverbModule.h"
 


ReverbModule::ReverbModule(AudioProcessorValueTreeState& vts) :
    decaySlider("Decay", 0.2, 10),
    predelaySlider("Predelay", 0, 500),
    distanceSlider("Distance", 0, 100),
    widthSlider("Width", 0, 100),
    lowCutSlider("Low Cut", 20, 2000),
    highCutSlider("High Cut", 200, 20000),
    mixSlider("Mix", 0, 100)
{
    f.setHeight(15);

    // Decay Slider
    addAndMakeVisible(decaySlider);
    decayAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "decay", decaySlider));

    // Predelay Slider
    addAndMakeVisible(predelaySlider);
    predelayAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "predelay", predelaySlider));

    // Distance Slider
    addAndMakeVisible(distanceSlider);
    distanceAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "distance", distanceSlider));

    // Width Slider
    addAndMakeVisible(widthSlider);
    widthAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "width", widthSlider));

    // EQ Label
    addAndMakeVisible(eqLabel);
    eqLabel.setFont(f);
    eqLabel.setJustificationType(Justification::centred);
    eqLabel.setText("EQ", NotificationType::dontSendNotification);

    // Low Cut Slider
    addAndMakeVisible(lowCutSlider);
    lowCutAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "low_cut", lowCutSlider));
   
    // High Cut Slider
    addAndMakeVisible(highCutSlider);
    highCutAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "high_cut", highCutSlider));

    // Mix Slider
    addAndMakeVisible(mixSlider);
    mixAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "slider", mixSlider));
}

void ReverbModule::resized()
{
    const auto bounds = this->getLocalBounds();

    
    decaySlider.setBounds(61, 40, 85, 115);
    predelaySlider.setBounds(61, 197, 85, 115);
    distanceSlider.setBounds(240, 40, 85, 115);
    widthSlider.setBounds(240, 197, 85, 115);

    eqLabel.setBounds(390, 20, 143, 20);
    lowCutSlider.setBounds(390, 78, 55, 85);
    highCutSlider.setBounds(478, 78, 55, 85);

    mixSlider.setBounds(620, 40, 85, 115);
}
