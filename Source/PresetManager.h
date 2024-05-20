/*
  ==============================================================================

    PresetManager.h
    Created: 20 May 2024 8:46:42am
    Author:  martinezd

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ModuleManager.h"

class PresetManager
{
public:
    PresetManager(AudioProcessorValueTreeState& vts);

    void setupPresetFile();
    void loadPreset(String presetId);

private:
    ModuleManager moduleManager;
    ApplicationProperties appProps;

    AudioProcessorValueTreeState& vts;
};