/*
  ==============================================================================

    BypassModuleLabel.cpp
    Created: 25 Mar 2024 8:00:30am
    Author:  martinezd

  ==============================================================================
*/

#include "BypassModuleLabel.h"
#include "WaveBlendColors.h"


BypassModuleLabel::BypassModuleLabel()
{
	Font lFont;
	lFont.setHeight(20);

	this->setFont(lFont);


	this->setText("o", dontSendNotification);
	this->addMouseListener(this, false);
}


void BypassModuleLabel::mouseDown(const MouseEvent& e)
{
	sendChangeMessage();


	if (firstTrigger++ == 1)
	{
		isToggled = !isToggled;
		firstTrigger = 0;
	}

	setColor();
}

void BypassModuleLabel::setToggle(bool toggle)
{
	isToggled = toggle;
	setColor();
}


void BypassModuleLabel::mouseEnter(const MouseEvent&)
{
	this->setColour(0x1000281, WBColors::MoreLightGrey);
}

void BypassModuleLabel::mouseExit(const MouseEvent&)
{
	setColor();
}

void BypassModuleLabel::setColor()
{
	if (!isToggled)
		this->setColour(0x1000281, Colours::white);
	else
		this->setColour(0x1000281, WBColors::SecondaryGrey);
}
