/*
  ==============================================================================

    ModuleButton.h
    Created: 14 Nov 2023 9:38:04am
    Author:  martinezd

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "RemoveModuleLabel.h"
#include "SwitchModuleLabel.h"
#include "Modules.h"
#include "SoloModuleLabel.h"
#include "BypassModuleLabel.h"

class ModuleButton : public TextButton,
    public MouseListener,
    public ChangeBroadcaster,
    public ChangeListener
{
public:
    ModuleButton(bool isAddModuleButton = false);
    
    // Draws labels on buttons that will be used to perform different actions
    void drawLabels();

    void resized() override;

    void changeListenerCallback(ChangeBroadcaster* source);

    // Event method is called when module button or label is clicked
    // But this method will only perform when the remove label is clicked
    //void mouseDown(const MouseEvent&) override;
    //void mouseEnter(const MouseEvent&) override;

    // Getter function for 'toBeRemoved' field
    //bool getToBeRemoved();

    ModuleButtonAction getButtonAction();
    void setButtonAction(ModuleButtonAction action);
    
    void setSoloLabelToggle(bool toggle);

private:
    // Label that will be used to remove a module button from UI
    //Label removeLabel;
    RemoveModuleLabel removeLabel;

    // Label that will be used to switch the module that a module button has
    SwitchModuleLabel switchLabel;

    // Label that will be used to solo a module in plugin
    SoloModuleLabel soloLabel;

    // Label that will be used to bypass a module in plugin
    BypassModuleLabel bypassLabel;

    // Enum to determine the action of the button labels
    ModuleButtonAction buttonAction;

    // Sets a module button flag to be removed.
    // Parent component will use this flag to determine if module needs to be removed
    bool toBeRemoved = false;

    // If true, the remove label will not be drawn on button
    // If false, it will be drawn
    bool isAddModuleButton = false;
};