/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WaveBlendLookAndFeel.h"
#include "ModuleButtonsComponent.h"
#include "ReverbModule.h"
#include "ModuleManager.h"


//==============================================================================
/**
*/
class WaveBlendAudioProcessorEditor  : public juce::AudioProcessorEditor,
    public ChangeListener
{
public:
    WaveBlendAudioProcessorEditor (WaveBlendAudioProcessor&, AudioProcessorValueTreeState& vts);
    ~WaveBlendAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void changeListenerCallback(ChangeBroadcaster* source);


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WaveBlendAudioProcessor& audioProcessor;

    // Look And Feel of Plugin
    WaveBlendLookAndFeel lookAndFeel;

    // Font of Title on Bar
    Font titleFont;
    // Font of output/mix labels
    Font barLabelFont;

    // Top Bar Rectangle
    Rectangle<int> topBar;


    // Output Db Slider
    ModuleSlider outputSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> outputAttachment;

    // Mix Slider
    ModuleSlider mixSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mixAttachment;

    // Plugin Preset Dropdown Menu
    ComboBox pluginPresetMenu;
    
    // Add Module Button
	//TextButton addModule;
    
    ModuleButtonsComponent moduleButtons;

    ModuleManager moduleManager;

    //ReverbModule rm;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveBlendAudioProcessorEditor)
};
