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
#include "Modules.h"


struct ModuleButtonData
{
    int index = -1;
    String moduleName;
};


class ModuleButtonsComponent : public juce::Component,
    public juce::Button::Listener,
    public ChangeListener,
    public ChangeBroadcaster
{
public:
    ModuleButtonsComponent();

    ~ModuleButtonsComponent() { }

    void drawAddModuleButton();

    void resized() override;

    // Event is called when a module button is clicked
    void buttonClicked(Button* button) override;

    // Listener method that will be called when module button remove label is called
    void changeListenerCallback(ChangeBroadcaster* source);


    String getModuleToRender();
    ModuleButtonAction getButtonAction();

private:
    WaveBlendLookAndFeel lookAndFeel;

    ModuleButton test;

    std::vector<std::unique_ptr<ModuleButton>> moduleButtons;
    bool addModuleButtonIsDrawn = false;
    
    // List of module names in plugin
    std::vector<String> moduleNames;
    std::vector<String> currentModules;
    int moduleCount = 0;
    String moduleToRender;

    ModuleButtonData currentModule;
    ModuleButtonData previousModule;
    //String previousModule;

    int addModuleButtonIndex = 0;

    ModuleButtonAction buttonAction;

    void focusOnButton(int index, String modName);

    bool existsInCurrentModules(String mod);
    void removeFromCurrentModules(String mod);
};