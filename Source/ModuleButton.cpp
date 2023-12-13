/*
  ==============================================================================

    ModuleButton.cpp
    Created: 14 Nov 2023 9:38:04am
    Author:  martinezd

  ==============================================================================
*/

#include "ModuleButton.h"


ModuleButton::ModuleButton(bool isAddModuleButton) :
    isAddModuleButton(isAddModuleButton)
{
    // if button is the add module button, dont draw remove label
    // But draw it otherwise
    if (isAddModuleButton)
        return;


    drawLabels();
}


void ModuleButton::drawLabels()
{
    //Font lFont;
    //lFont.setHeight(20);

    //addAndMakeVisible(removeLabel);
    //removeLabel.setFont(lFont);


    //removeLabel.setText("x", dontSendNotification);
    //removeLabel.addMouseListener(this, false);

    removeLabel.addChangeListener(this);
    addAndMakeVisible(removeLabel);

    switchLabel.addChangeListener(this);
    addAndMakeVisible(switchLabel);
}


void ModuleButton::resized()
{
    auto bounds = getLocalBounds();
    Rectangle<int> removeLabelRect(bounds.getX() + 90, bounds.getY(), 30, 30);
    Rectangle<int> switchLabelRect(bounds.getX() + 5, bounds.getY(), 30, 30);

    removeLabel.setBounds(removeLabelRect);
    switchLabel.setBounds(switchLabelRect);

    removeLabel.setJustificationType(Justification::centred);
    
}

void ModuleButton::changeListenerCallback(ChangeBroadcaster* source)
{
    if (dynamic_cast<RemoveModuleLabel*>(source))
        buttonAction = ModuleButtonAction::Remove;
    else if (dynamic_cast<SwitchModuleLabel*>(source))
        buttonAction = ModuleButtonAction::Switch;

    sendChangeMessage();
}

ModuleButtonAction ModuleButton::getButtonAction()
{
    return this->buttonAction;
}

void ModuleButton::setButtonAction(ModuleButtonAction action)
{
    this->buttonAction = action;
}

