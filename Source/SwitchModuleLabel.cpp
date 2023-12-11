/*
  ==============================================================================

    SwitchModuleLabel.cpp
    Created: 11 Dec 2023 11:56:49am
    Author:  martinezd

  ==============================================================================
*/

#include "SwitchModuleLabel.h"
#include "WaveBlendColors.h"

SwitchModuleLabel::SwitchModuleLabel()
{
    Font lFont;
    lFont.setHeight(20);

    this->setFont(lFont);


    this->setText("<>", dontSendNotification);
    this->addMouseListener(this, false);
}


void SwitchModuleLabel::mouseDown(const MouseEvent& e)
{
    sendChangeMessage();
}

void SwitchModuleLabel::mouseEnter(const MouseEvent&)
{
    this->setColour(0x1000281, WBColors::MoreLightGrey);
}

void SwitchModuleLabel::mouseExit(const MouseEvent&)
{
    this->setColour(0x1000281, Colours::white);
}