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

class ModuleManager : public Component
{
public:
    ModuleManager();

    void RenderModule();

    void RemoveCurrentModule();

    void SetAndRenderModule(String module);

    String GetCurrentModule(String modules);

private:
    std::vector<String> modules;

    std::unique_ptr<Component> currentModule;

    String currentModuleName;
    String previousModuleName;

    Rectangle<int> moduleBounds;

    void setCurrentModule(String mod);
};