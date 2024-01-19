/*
  ==============================================================================

    UIState.h
    Created: 18 Jan 2024 11:11:02am
    Author:  martinezd

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ModuleButtonData.h"


class UIState
{
public:
    UIState();
    //UIState(StringArray currentMods, String currentMod, char orderOfModules);
    
    String isChangeInState();

    StringArray getCurrentModules();
    ModuleButtonData getCurrentModule();
    
private:
    StringArray currentModules;

    ModuleButtonData currentModule;
    String newestModule;

    char orderOfModules[3];

    bool changeInState;
};