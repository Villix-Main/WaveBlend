/*
  ==============================================================================

    ModuleManager.h
    Created: 8 Dec 2023 10:42:09am
    Author:  martinezd

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Modules.h"

class ModuleManager
{
public:
    ModuleManager(Rectangle<int> bounds);

    void AddModule(Modules mod);

    void RenderModule(Modules mod);

    void RemoveAndUnrenderModule(Modules mod);

    void SetCurrentModule(Modules module);
    Modules GetCurrentModule(Modules modules);

private:
    std::vector<Modules> modules;
    Modules currentModule;

    Rectangle<int> moduleBounds;
};