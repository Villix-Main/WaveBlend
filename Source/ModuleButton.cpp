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
    Font lFont;
    lFont.setHeight(20);

    addAndMakeVisible(removeLabel);
    removeLabel.setFont(lFont);


    removeLabel.setText("x", dontSendNotification);
    removeLabel.addMouseListener(this, false);
}


void ModuleButton::resized()
{
    auto bounds = getLocalBounds();
    Rectangle<int> rect(bounds.getX() + 90, bounds.getY(), 30, 30);
    removeLabel.setBounds(rect);


    removeLabel.setJustificationType(Justification::centred);
    
}

void ModuleButton::mouseDown(const MouseEvent& e)
{
    // if mouse down event is triggered, check if the component that was clicked a label
    if (dynamic_cast<Label*>(e.eventComponent))
    {
        // If it was a label, set toBeRemovexd flag to true and send a change message to parent component
        // So this module button can be removed
        toBeRemoved = true;
        sendChangeMessage();
    }
}

//void ModuleButton::mouseEnter(const MouseEvent& e)
//{
//    if (dynamic_cast<Label*>(e.eventComponent))
//    {
//        removeLabel.setColour(0x1000281, Colours::red);
//
//    }
//}

bool ModuleButton::getToBeRemoved()
{
    return this->toBeRemoved;
}