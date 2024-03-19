/*
  ==============================================================================

    SoloModuleLabel.h
    Created: 18 Mar 2024 1:21:48pm
    Author:  martinezd

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SoloModuleLabel : public Label,
	public MouseListener,
	public ChangeBroadcaster
{
public:
	SoloModuleLabel();

	bool isToggled = false;
	int firstTrigger = 0;

	void mouseDown(const MouseEvent&) override;
	void mouseEnter(const MouseEvent&) override;
	void mouseExit(const MouseEvent&) override;

	void setToggle();
}; 