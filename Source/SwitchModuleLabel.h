/*
  ==============================================================================

    SwitchModuleLabel.h
    Created: 11 Dec 2023 11:56:49am
    Author:  martinezd

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class SwitchModuleLabel : public Label,
    public MouseListener,
    public ChangeBroadcaster
{
public:
    SwitchModuleLabel();


    void mouseDown(const MouseEvent&) override;
    void mouseEnter(const MouseEvent&) override;
    void mouseExit(const MouseEvent&) override;
};