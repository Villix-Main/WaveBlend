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


    drawRemoveLabel();
}


void ModuleButton::drawRemoveLabel()
{
    //Font lFont;
    //lFont.setHeight(20);

    //addAndMakeVisible(removeLabel);
    //removeLabel.setFont(lFont);


    //removeLabel.setText("x", dontSendNotification);
    //removeLabel.addMouseListener(this, false);

    removeLabel.addChangeListener(this);
    addAndMakeVisible(removeLabel);
}


void ModuleButton::resized()
{
    auto bounds = getLocalBounds();
    Rectangle<int> rect(bounds.getX() + 90, bounds.getY(), 30, 30);
    removeLabel.setBounds(rect);


    removeLabel.setJustificationType(Justification::centred);
    
}

void ModuleButton::changeListenerCallback(ChangeBroadcaster* source)
{
    toBeRemoved = true;
    sendChangeMessage();
}



bool ModuleButton::getToBeRemoved()
{
    return this->toBeRemoved;
}