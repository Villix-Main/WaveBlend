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

    std::unique_ptr<TextButton> addModuleButton;
    std::vector<std::unique_ptr<TextButton>> moduleButtons;
    
    std::vector<std::string> moduleNames{ "Compressor", "Reverb", "Equalizer" };
    std::vector<std::string> currentModules;

    int addModuleButtonIndex = 0;
};