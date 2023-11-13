/*
  ==============================================================================

    ModuleButtonsComponent.cpp
    Created: 12 Nov 2023 8:45:51pm
    Author:  Villi

  ==============================================================================
*/

#include "ModuleButtonsComponent.h"

ModuleButtonsComponent::ModuleButtonsComponent()
{
    setLookAndFeel(&lookAndFeel);

    addAndMakeVisible(addModuleButton);
    lookAndFeel.setButtonFontHeight(40);
    addModuleButton.setButtonText("+");
    addModuleButton.addListener(this);
}


void ModuleButtonsComponent::resized()
{
    const auto bounds = getLocalBounds();

    addModuleButton.setBounds(bounds);
}

void ModuleButtonsComponent::buttonClicked(Button* button)
{
	if (button == &addModuleButton)
	{
		addModuleButton.setButtonText("clicked");
	}
}
