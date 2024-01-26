/*
  ==============================================================================

    UIStateStore.h
    Created: 26 Jan 2024 1:51:12pm
    Author:  martinezd

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Modules.h"
#include "UIState.h"

class UIStateStore
{
public:
	UIStateStore(AudioProcessorValueTreeState& vts);

	void SaveState(UIState& cs);

	UIState loadState();

private:
	//UIState currentState;
	std::atomic<float>* UIStateValPtr = nullptr;
	AudioProcessorValueTreeState& vts;
};
