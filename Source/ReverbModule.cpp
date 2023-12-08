/*
  ==============================================================================

    ReverbModule.cpp
    Created: 6 Dec 2023 11:47:43am
    Author:  martinezd

  ==============================================================================
*/

#include "ReverbModule.h"
 


ReverbModule::ReverbModule() :
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
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));

    // Predelay Slider
    addAndMakeVisible(predelaySlider);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));

    // Distance Slider
    addAndMakeVisible(distanceSlider);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));

    // Width Slider
    addAndMakeVisible(widthSlider);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));

    // Low Cut Slider
    addAndMakeVisible(lowCutSlider);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));
   
    // High Cut Slider
    addAndMakeVisible(highCutSlider);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));

    // Mix Slider
    addAndMakeVisible(mixSlider);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));
}

void ReverbModule::resized()
{
    const auto bounds = this->getLocalBounds();

    
    decaySlider.setBounds(61, 40, 85, 115);
    predelaySlider.setBounds(61, 197, 85, 115);
    distanceSlider.setBounds(240, 40, 85, 115);
    widthSlider.setBounds(240, 197, 85, 115);
    lowCutSlider.setBounds(390, 78, 55, 85);
    highCutSlider.setBounds(478, 78, 55, 85);

    mixSlider.setBounds(620, 40, 85, 115);
}
