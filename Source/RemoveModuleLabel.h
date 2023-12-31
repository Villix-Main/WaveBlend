/*
  ==============================================================================

    RemoveModuleLabel.h
    Created: 14 Nov 2023 1:32:40pm
    Author:  martinezd

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class RemoveModuleLabel : public Label,
    public MouseListener,
    public ChangeBroadcaster
{
public:
    RemoveModuleLabel();


    void mouseDown(const MouseEvent&) override;
    void mouseEnter(const MouseEvent&) override;
    void mouseExit(const MouseEvent&) override;
};