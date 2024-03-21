/*
  ==============================================================================

    SoloModuleLabel.cpp
    Created: 18 Mar 2024 1:21:48pm
    Author:  martinezd

  ==============================================================================
*/

#include "SoloModuleLabel.h"
#include "WaveBlendColors.h"


SoloModuleLabel::SoloModuleLabel()
{
	Font lFont;
	lFont.setHeight(20);

	this->setFont(lFont);


	this->setText("s", dontSendNotification);
	this->addMouseListener(this, false);
}


void SoloModuleLabel::mouseDown(const MouseEvent& e)
{
	sendChangeMessage();
		
	
	if (firstTrigger++ == 1)
	{
		isToggled = !isToggled;
		firstTrigger = 0;
	}

	setColor();
}

void SoloModuleLabel::setToggle(bool toggle)
{
	isToggled = toggle;
	setColor();
}


void SoloModuleLabel::mouseEnter(const MouseEvent&)
{
	this->setColour(0x1000281, WBColors::MoreLightGrey);
}

void SoloModuleLabel::mouseExit(const MouseEvent&)
{
	setColor();
}

void SoloModuleLabel::setColor()
{
	if (!isToggled)
		this->setColour(0x1000281, Colours::white);
	else
		this->setColour(0x1000281, WBColors::SecondaryGrey);
}
