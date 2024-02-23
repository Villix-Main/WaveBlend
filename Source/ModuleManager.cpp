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


ModuleManager::ModuleManager(AudioProcessorValueTreeState& vts) :
    currentModuleName(Modules::None), previousModuleName(Modules::None),
    vts(vts)
{
	reverbEnabledPtr = vts.getRawParameterValue("reverb_enabled");
	compressorEnabledPtr = vts.getRawParameterValue("compressor_enabled");
	equalizerEnabledPtr = vts.getRawParameterValue("equalizer_enabled");
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

void ModuleManager::RemoveAndDontRender(String mod)
{
    if (mod == Modules::Reverb)
    {
        if (reverbEnabledPtr != nullptr)
            *reverbEnabledPtr = 0;
    } 
    else if (mod == Modules::Compressor)
    {
        if (compressorEnabledPtr != nullptr)
            *compressorEnabledPtr = 0;
    }
    else if (mod == Modules::Equalizer)
    {
        if (equalizerEnabledPtr != nullptr)
            *equalizerEnabledPtr = 0;
    }


    currentModule.reset();
}

String ModuleManager::GetCurrentModule(String modules)
{
    return currentModuleName;
}


void ModuleManager::setCurrentModule(String mod)
{
    currentModule.reset();
    

    if (mod == Modules::Reverb)
    {
        currentModule = std::make_unique<ReverbModule>(vts);
        *reverbEnabledPtr = 1;
    }
    else if (mod == Modules::Compressor)
    {
        currentModule = std::make_unique<CompressorModule>(vts);
        *compressorEnabledPtr = 1;
    }
    else if (mod == Modules::Equalizer)
        currentModule = std::make_unique<EqualizerModule>(vts);


    previousModuleName = currentModuleName;
    currentModuleName = mod;
}