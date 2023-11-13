/*
  ==============================================================================

    ModuleButtonsComponent.h
    Created: 12 Nov 2023 8:45:51pm
    Author:  Villi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WaveBlendLookAndFeel.h"


class ModuleButtonsComponent : public juce::Component,
    public juce::Button::Listener
{
public:
    ModuleButtonsComponent();

    ~ModuleButtonsComponent() { }

    void resized() override;

    void buttonClicked(Button* button) override;

private:
    WaveBlendLookAndFeel lookAndFeel;

    TextButton addModuleButton;
};