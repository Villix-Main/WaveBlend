/*
  ==============================================================================

    ModuleManager.cpp
    Created: 8 Dec 2023 10:42:09am
    Author:  martinezd

  ==============================================================================
*/

#include "ModuleManager.h"
#include "ReverbModule.h"
#include "CompressorModule.h"
#include "EqualizerModule.h"


ModuleManager::ModuleManager() :
    currentModuleName(Modules::None), previousModuleName(Modules::None)
{
}

void ModuleManager::SetAndRenderModule(String mod)
{
    setCurrentModule(mod);

    RenderModule();
}


void ModuleManager::RenderModule()
{
    if (currentModule == nullptr)
        return;

    addAndMakeVisible(*currentModule);
    currentModule->setBounds(getLocalBounds());

   
}

void ModuleManager::RemoveCurrentModule()
{
    setCurrentModule(previousModuleName);

    RenderModule();
}

String ModuleManager::GetCurrentModule(String modules)
{
    return currentModuleName;
}


void ModuleManager::setCurrentModule(String mod)
{
    currentModule.reset();
    

    if (mod == Modules::Reverb)
        currentModule = std::make_unique<ReverbModule>();
    else if (mod == Modules::Compressor)
        currentModule = std::make_unique<CompressorModule>();
    else if (mod == Modules::Equalizer)
        currentModule = std::make_unique<EqualizerModule>();


    previousModuleName = currentModuleName;
    currentModuleName = mod;
}