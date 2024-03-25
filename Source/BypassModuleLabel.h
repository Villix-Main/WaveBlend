/*
  ==============================================================================

    BypassModuleLabel.h
    Created: 25 Mar 2024 8:00:30am
    Author:  martinezd

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class BypassModuleLabel : public Label,
	public MouseListener,
	public ChangeBroadcaster
{
public:
	BypassModuleLabel();

	bool isToggled = false;
	int firstTrigger = 0;

	void setToggle(bool toggle);

	void mouseDown(const MouseEvent&) override;
	void mouseEnter(const MouseEvent&) override;
	void mouseExit(const MouseEvent&) override;

private:
	void setColor();
};