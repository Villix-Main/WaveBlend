/*
  ==============================================================================

    ModuleSlider.h
    Created: 8 Dec 2023 7:45:21am
    Author:  martinezd

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


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
        sliderLabel.setText(labelText, dontSendNotification);
        sliderLabel.setJustificationType(Justification::centred);
        sliderLabel.attachToComponent(this, false);
    }

private:
    String labelText;
    Label sliderLabel;
    float minVal;
    float maxVal;

    
};

