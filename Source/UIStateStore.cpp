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
	ReverbEnabledPtr = vts.getRawParameterValue("reverb_enabled");
}


void UIStateStore::SaveState(UIState& cs)
{
	if (cs.getCurrentModules().size() <= 0)
		return;

	String moduleStr;

	// First save the the number of modules that are open in the plugin instance
	moduleStr.append(String(cs.getCurrentModules().size()), 1);
	// Then, save the number value of each module that is open (1 = reverb, 2 = compressor, 3 = equalizer)
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

	// Then, save the number value of the module that the user has currently open
	if (currentModuleData.moduleName == Modules::Reverb)
		moduleStr.append("1", 1);
	else if (currentModuleData.moduleName == Modules::Compressor)
		moduleStr.append("2", 1);
	else if (currentModuleData.moduleName == Modules::Equalizer)
		moduleStr.append("3", 1);

	// Then finally append the position in where the current module is opened at
	moduleStr.append(String(currentModuleData.index), 1);

	// Save the module save string into the value tree
	*UIStateValPtr = moduleStr.getFloatValue();
}


UIState UIStateStore::loadState()
{
	int uiStateValTemp = UIStateValPtr->load();

	if (uiStateValTemp <= 0)
		return UIState();

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
	if (currentModuleVal == 1)
		currentModule.moduleName = Modules::Reverb;
	else if (currentModuleVal == 2)
		currentModule.moduleName = Modules::Compressor;
	else if (currentModuleVal == 3)
		currentModule.moduleName = Modules::Equalizer;
	currentModule.index = String::charToString(uiStateVal[amountOfModules + 2]).getIntValue();

	return UIState(currentModule, currentModules);

}