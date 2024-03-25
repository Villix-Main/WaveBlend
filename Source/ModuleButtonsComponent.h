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
#include "UIState.h"
#include "ModuleButtonData.h"
#include "UIStateStore.h"




class ModuleButtonsComponent : public juce::Component,
    public juce::Button::Listener,
    public ChangeListener,
    public ChangeBroadcaster
{
public:
    //ModuleButtonsComponent();
    ModuleButtonsComponent(AudioProcessorValueTreeState& vts);

    ~ModuleButtonsComponent() { }

    void drawAddModuleButton();

    void resized() override;

    // Event is called when a module button is clicked
    void buttonClicked(Button* button) override;

    // Listener method that will be called when module button remove label is called
    void changeListenerCallback(ChangeBroadcaster* source);

	void renderFromState(UIState& currentState);


    StringArray& getCurrentModules();
    ModuleButtonData getCurrentModule();

    String getModuleToRender();
    String getModuleToRemove();

    ModuleButtonAction getButtonAction();

private:
    WaveBlendLookAndFeel lookAndFeel;

    //ModuleButton test;

    std::vector<std::unique_ptr<ModuleButton>> moduleButtons;
    bool addModuleButtonIsDrawn = false;
    
    // List of module names in plugin
    StringArray moduleNames;
    StringArray currentModules;
    int moduleCount = 0;

    String moduleToRender;
    String moduleToRemove;

    ModuleButtonData currentModule;
    ModuleButtonData previousModule;
    //String previousModule;

    int addModuleButtonIndex = 0;

    ModuleButtonAction buttonAction;
    UIState currentState;
    //UIStateStore uiStateStore;

    std::atomic<float>* currentSoloModulePtr;
    std::atomic<float>* reverbBypassPtr;
    std::atomic<float>* compressorBypassPtr;
    std::atomic<float>* equalizerBypassPtr;


    void focusOnButton(int index, String modName);

    bool existsInCurrentModules(String mod);
    void removeFromCurrentModules(String mod);

};