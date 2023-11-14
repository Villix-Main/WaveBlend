/*
  ==============================================================================

    ModuleButton.h
    Created: 14 Nov 2023 9:38:04am
    Author:  martinezd

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ModuleButton : public TextButton,
    public MouseListener,
    public ChangeBroadcaster
{
public:
    ModuleButton();

    void resized() override;


    void mouseDown(const MouseEvent&) override;
    //void mouseEnter(const MouseEvent&) override;

    bool getShouldRemoveButton();


private:
    Label removeLabel;
    bool shouldRemoveButton = false;
};