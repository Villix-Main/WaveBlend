/*
  ==============================================================================

    UIState.cpp
    Created: 18 Jan 2024 11:11:02am
    Author:  martinezd

  ==============================================================================
*/

#include "UIState.h"

UIState::UIState(ModuleButtonData currentMod, StringArray currentMods) :
    currentModule(currentMod), currentModules(currentMods)
{

}

UIState::UIState()
{

}



String UIState::isChangeInState()
{
    return "";
}

StringArray& UIState::getCurrentModules()
{
    return this->currentModules;
}

ModuleButtonData UIState::getCurrentModule()
{
    return this->currentModule;
}
