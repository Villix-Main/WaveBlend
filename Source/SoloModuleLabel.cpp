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
}


void SoloModuleLabel::setToggle()
{

}



void SoloModuleLabel::mouseEnter(const MouseEvent&)
{
	if (!isToggled)
		this->setColour(0x1000281, WBColors::MoreLightGrey);
	else
		this->setColour(0x1000281, Colours::white);
}

void SoloModuleLabel::mouseExit(const MouseEvent&)
{
	if (!isToggled)
		this->setColour(0x1000281, Colours::white);
	else
		this->setColour(0x1000281, WBColors::MoreLightGrey);

}

