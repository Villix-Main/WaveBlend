/*
  ==============================================================================

    RemoveModuleLabel.cpp
    Created: 14 Nov 2023 1:32:40pm
    Author:  martinezd

  ==============================================================================
*/

#include "RemoveModuleLabel.h"
#include "WaveBlendColors.h"

RemoveModuleLabel::RemoveModuleLabel()
{
    Font lFont;
    lFont.setHeight(20);

    this->setFont(lFont);


    this->setText("x", dontSendNotification);
    this->addMouseListener(this, false);
}


void RemoveModuleLabel::mouseDown(const MouseEvent& e)
{
    sendChangeMessage();
}

void RemoveModuleLabel::mouseEnter(const MouseEvent&)
{
    this->setColour(0x1000281, WBColors::MoreLightGrey);
}

void RemoveModuleLabel::mouseExit(const MouseEvent&)
{
    this->setColour(0x1000281, Colours::white);
}