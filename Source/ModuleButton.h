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
    ModuleButton(bool isAddModuleButton = false);

    void resized() override;


    void mouseDown(const MouseEvent&) override;
    //void mouseEnter(const MouseEvent&) override;

    bool getToBeRemoved();
    

private:
    Label removeLabel;
    bool toBeRemoved = false;
    bool isAddModuleButton = false;
};