/*
  ==============================================================================

    UIStateStore.cpp
    Created: 26 Jan 2024 1:51:12pm
    Author:  martinezd

  ==============================================================================
*/

#include "UIStateStore.h"

UIStateStore::UIStateStore(AudioProcessorValueTreeState& vts)
	: vts(vts)
{
	UIStateValPtr = vts.getRawParameterValue("ui_state_value");
}


void UIStateStore::SaveState(UIState& cs)
{
	String moduleStr;

	moduleStr.append(String(cs.getCurrentModules().size()), 1);
	for (auto mod : cs.getCurrentModules())
	{
		if (mod == Modules::Reverb)
			moduleStr.append("1", 1);
		else if (mod == Modules::Compressor)
			moduleStr.append("2", 1);
		else if (mod == Modules::Equalizer)
			moduleStr.append("3", 1);



	}
	auto currentModuleData = cs.getCurrentModule();

	if (currentModuleData.moduleName == Modules::Reverb)
		moduleStr.append("1", 1);
	else if (currentModuleData.moduleName == Modules::Compressor)
		moduleStr.append("2", 1);
	else if (currentModuleData.moduleName == Modules::Equalizer)
		moduleStr.append("3", 1);

	moduleStr.append(String(currentModuleData.index), 1);

	*UIStateValPtr = moduleStr.getFloatValue();
	
	vts.state.setProperty("ui_state_value", moduleStr.getFloatValue(), nullptr);	
}


UIState UIStateStore::loadState()
{
	int uiStateValTemp = UIStateValPtr->load();
	if (uiStateValTemp <= 0)
		return UIState();

	String uiStateVal(uiStateValTemp);
	int amountOfModules = String::charToString(uiStateVal[0]).getIntValue();

	StringArray currentModules;
	for (int i = 1; i < amountOfModules + 1; i++)
	{
		if (uiStateVal[i] == '1')
			currentModules.add(Modules::Reverb);
		else if (uiStateVal[i] == '2')
			currentModules.add(Modules::Compressor);
		else if (uiStateVal[i] == '3')
			currentModules.add(Modules::Equalizer);
	}

	int currentModuleVal = String::charToString(uiStateVal[amountOfModules + 1]).getIntValue();

	ModuleButtonData currentModule;
	if (uiStateVal[currentModuleVal] == '1')
		currentModule.moduleName = Modules::Reverb;
	else if (uiStateVal[currentModuleVal] == '2')
		currentModule.moduleName = Modules::Compressor;
	else if (uiStateVal[currentModuleVal] == '3')
		currentModule.moduleName = Modules::Equalizer;
	currentModule.index = String::charToString(uiStateVal[amountOfModules + 2]).getIntValue();

	return UIState(currentModule, currentModules);

}