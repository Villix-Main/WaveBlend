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
#include "ModuleButton.h"


class ModuleButtonsComponent : public juce::Component,
    public juce::Button::Listener,
    public ChangeListener
{
public:
    ModuleButtonsComponent();

    ~ModuleButtonsComponent() { }

    void resized() override;

    void buttonClicked(Button* button) override;

    void changeListenerCallback(ChangeBroadcaster* source);

private:
    WaveBlendLookAndFeel lookAndFeel;

    ModuleButton test;

    std::unique_ptr<ModuleButton> addModuleButton;
    std::vector<std::unique_ptr<ModuleButton>> moduleButtons;
    
    std::vector<std::string> moduleNames{ "Compressor", "Reverb", "Equalizer" };
    std::vector<std::string> currentModules;

    int addModuleButtonIndex = 0;
};