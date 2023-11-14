/*
  ==============================================================================

    ModuleButton.cpp
    Created: 14 Nov 2023 9:38:04am
    Author:  martinezd

  ==============================================================================
*/

#include "ModuleButton.h"


ModuleButton::ModuleButton()
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
    if (dynamic_cast<Label*>(e.eventComponent))
    {
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

bool ModuleButton::getShouldRemoveButton()
{
    return shouldRemoveButton;
}
