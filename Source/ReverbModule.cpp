/*
  ==============================================================================

    ReverbModule.cpp
    Created: 6 Dec 2023 11:47:43am
    Author:  martinezd

  ==============================================================================
*/

#include "ReverbModule.h"
 
class ModuleSlider :
    public Slider
{
public:
    ModuleSlider(String labelText, float minVal, float maxVal, int fontSize = 15) :
        labelText(labelText), minVal(minVal), maxVal(maxVal)
    {
        Font f;
        f.setHeight(fontSize);

        this->setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        this->setTextBoxStyle(Slider::TextBoxBelow, false, 40, 14);
        this->setRange(minVal, maxVal);

        // Slider Label
        addAndMakeVisible(sliderLabel);
        sliderLabel.setFont(f);
        sliderLabel.setText("Output", dontSendNotification);
        sliderLabel.setJustificationType(Justification::centred);
        sliderLabel.attachToComponent(this, false);
    }

private:
    String labelText;
    Label sliderLabel;
    float minVal;
    float maxVal;
};


ReverbModule::ReverbModule()
{
    const auto bounds = this->getLocalBounds();

    f.setHeight(15);

    // Decay Slider
    addAndMakeVisible(decaySlider);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));
    
    


    // Predelay Slider
    addAndMakeVisible(predelaySlider);
    predelaySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    predelaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 14);
    predelaySlider.setRange(-15.0f, 0.f);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));
    // Decay Label
    addAndMakeVisible(predelayLabel);
    predelayLabel.setFont(f);
    predelayLabel.setText("Output", dontSendNotification);
    predelayLabel.setJustificationType(Justification::centred);
    predelayLabel.attachToComponent(&predelaySlider, false);

    // Distance Slider
    addAndMakeVisible(distanceSlider);
    distanceSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    distanceSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 14);
    distanceSlider.setRange(-15.0f, 0.f);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));
    // Decay Label
    addAndMakeVisible(distanceLabel);
    distanceLabel.setFont(f);
    distanceLabel.setText("Output", dontSendNotification);
    distanceLabel.setJustificationType(Justification::centred);
    distanceLabel.attachToComponent(&distanceSlider, false);

    // Distance Slider
    addAndMakeVisible(distanceSlider);
    distanceSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    distanceSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 14);
    distanceSlider.setRange(-15.0f, 0.f);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));
    // Decay Label
    addAndMakeVisible(distanceLabel);
    distanceLabel.setFont(f);
    distanceLabel.setText("Output", dontSendNotification);
    distanceLabel.setJustificationType(Justification::centred);
    distanceLabel.attachToComponent(&distanceSlider, false);

    // Distance Slider
    addAndMakeVisible(distanceSlider);
    distanceSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    distanceSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 14);
    distanceSlider.setRange(-15.0f, 0.f);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));
    // Decay Label
    addAndMakeVisible(distanceLabel);
    distanceLabel.setFont(f);
    distanceLabel.setText("Output", dontSendNotification);
    distanceLabel.setJustificationType(Justification::centred);
    distanceLabel.attachToComponent(&distanceSlider, false);

}

void ReverbModule::resized()
{
   


}
