/*
  ==============================================================================

    UIState.h
    Created: 18 Jan 2024 11:11:02am
    Author:  martinezd

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class UIState
{
public:
    UIState();
    UIState(StringArray currentMods, String currentMod, char orderOfModules);

private:
    StringArray currentModules;

    String currentModule;

    char orderOfModules[];
};