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
    ModuleManager(AudioProcessorValueTreeState& vts);

    void RenderModule();

    void RemoveCurrentModule();

    void RemoveAndDontRender(String mod);

    void SetAndRenderModule(String mod);

    String GetCurrentModule(String modules);

private:
    std::vector<String> modules;

    std::unique_ptr<Component> currentModule;
    std::atomic<float>* reverbEnabledPtr = nullptr;
    std::atomic<float>* compressorEnabledPtr = nullptr;
    std::atomic<float>* equalizerEnabledPtr = nullptr;


    String currentModuleName;
    String previousModuleName;

    Rectangle<int> moduleBounds;
    
    AudioProcessorValueTreeState& vts;

    void setCurrentModule(String mod);
};