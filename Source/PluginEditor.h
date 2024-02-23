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



class XMLReader
{
public:
	UIState getUIState()
	{
		File f = getXmlFile();

		ModuleButtonData currentModule;
		StringArray currentModules;

		if (f.exists())
		{
			XmlDocument dataDoc{ f };
			loadedXml = juce::parseXML(f);
            //loadedXml = juce::parseXML(String(BinaryData::current_ui_state_xml, BinaryData::current_ui_state_xmlSize));
            

			for (auto* childElement = loadedXml->getFirstChildElement(); childElement != nullptr; childElement = childElement->getNextElement())
			{
				//String test = childElement->getAttributeValue(0);

				auto elementTagName = childElement->getTagName();

                if (elementTagName == "CurrentModule")
                {
                    currentModule.index = childElement->getAttributeValue(0).getIntValue();
                    currentModule.moduleName = childElement->getAttributeValue(1);
                }

				if (elementTagName == "CurrentModules")
				{
					for (auto* innerElements = childElement->getFirstChildElement(); innerElements != nullptr; innerElements = innerElements->getNextElement())
					{
                        auto currentVal = innerElements->getAttributeValue(0);

                        if (!currentVal.isEmpty())
						    currentModules.add(innerElements->getAttributeValue(0));
					}
				}
			}
		}


        UIState currentState(currentModule, currentModules);
        return currentState;
	}

    void setUIState(UIState& cs)
    {
		File f = getXmlFile();

        if (f.exists())
        {
			XmlDocument dataDoc{ f };
			loadedXml = juce::parseXML(f);
            
            ModuleButtonData buttonData = cs.getCurrentModule();

			for (auto* childElement = loadedXml->getFirstChildElement(); childElement != nullptr; childElement = childElement->getNextElement())
			{
                auto elementTagName = childElement->getTagName();

				if (elementTagName == "CurrentModule")
				{
                    childElement->setAttribute("index", buttonData.index);
                    childElement->setAttribute("name", buttonData.moduleName);
				}

				if (elementTagName == "CurrentModules")
				{
					StringArray currentMods = cs.getCurrentModules();
                    
                    auto innerElement = childElement->getFirstChildElement();
					/*	for (int i = 0; i < currentMods.size(); i++)
						{
							innerElement->setAttribute("module", currentMods[i]);
							innerElement = innerElement->getNextElement();
						}*/

                    int index = -1;
					for (auto* innerElements = childElement->getFirstChildElement(); innerElements != nullptr; innerElements = innerElements->getNextElement())
					{
                        if (++index < currentMods.size())
                            innerElements->setAttribute("module", currentMods[index]);
                        else
                            innerElements->setAttribute("module", String());
					}
				}
			}

            File appdir = File::getCurrentWorkingDirectory();
            File xmlFile = appdir.getChildFile("current_state.xml");
            loadedXml->writeToFile(xmlFile, String());
            //auto stream = juce::MemoryInputStream(BinaryData::current_ui_state_xml, BinaryData::current_ui_state_xmlSize, true);
        }
    }

	

private:
	std::unique_ptr<XmlElement> loadedXml;

	File getXmlFile()
	{
		File appDir = File::getCurrentWorkingDirectory();
		File xmlFile = appDir.getChildFile("current_state.xml");
		return xmlFile;
	}
};



//==============================================================================
/**
*/
class WaveBlendAudioProcessorEditor  : public juce::AudioProcessorEditor,
    public ChangeListener, private AudioProcessorValueTreeState::Listener
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

    void parameterChanged(const String& parameterID, float newValue);

    // Look And Feel of Plugin
    WaveBlendLookAndFeel lookAndFeel;

    // Font of Title on Bar
    Font titleFont;
    // Font of output/mix labels
    Font barLabelFont;

    // Top Bar Rectangle
    Rectangle<int> topBar;
    UIState tests;

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

    std::atomic<float>* idk = nullptr;
    
    ModuleButtonsComponent moduleButtons;

    ModuleManager moduleManager;

    XMLReader stateXMLReader;
    UIStateStore uiStateStore;

    //ReverbModule rm;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveBlendAudioProcessorEditor)
};
