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

    addModuleButton = std::make_unique<TextButton>();

    lookAndFeel.setButtonFontHeight(40);
    addModuleButton->setButtonText("+");
    addModuleButton->addListener(this);

    moduleButtons.push_back(std::move(addModuleButton));
}


void ModuleButtonsComponent::resized()
{
    const auto bounds = getLocalBounds();
    auto xPosition = bounds.getX();
    auto yPosition = bounds.getY();


    //addModuleButton->setBounds(xPosition, yPosition, 122, 87);

    for (int i = 0; i < moduleButtons.size(); i++)
    {
        addAndMakeVisible(*moduleButtons[i]);

        auto margin = 20 * i;

        moduleButtons[i]->setBounds(xPosition + margin + (i * 122), yPosition, 122, 87);


    }
}


// Make a new custom button class that contains a property for current module name and also a x button to remove module
void ModuleButtonsComponent::buttonClicked(Button* button)
{
	if (button == moduleButtons[addModuleButtonIndex].get())
	{
        lookAndFeel.setButtonFontHeight(16);
        moduleButtons[addModuleButtonIndex]->setButtonText(moduleNames[addModuleButtonIndex]);
        currentModules.push_back(moduleNames[addModuleButtonIndex]);


        if (moduleButtons.size() < 3)
        {
            auto newModuleButton = std::make_unique<TextButton>();
            newModuleButton->setButtonText("+");
            newModuleButton->addListener(this);
            moduleButtons.push_back(std::move(newModuleButton));
            addModuleButtonIndex++;
        }
        
        
        resized();
    }
    else
    {
        if (moduleButtons.size() >= 3)
            return;

        for (int i = 0; i < moduleButtons.size(); i++)
        {
            if (button == moduleButtons[i].get())
            {
                auto currentModuleName = moduleNames[addModuleButtonIndex];

                button->setButtonText(currentModuleName);
            }
        }
    }
}
