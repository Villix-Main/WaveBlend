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

    addModuleButtonIsDrawn = false;
    moduleNames = { "Compressor", "Reverb", "Equalizer" };
    currentModules = {};
    moduleCount = 0;
    addModuleButtonIndex = 0;

    drawAddModuleButton();
}

void ModuleButtonsComponent::drawAddModuleButton()
{
    if (addModuleButtonIsDrawn)
        return;

    auto addModuleButton = std::make_unique<ModuleButton>(true);
    //lookAndFeel.setButtonFontHeight(40);
    addModuleButton->setButtonText("+");
    addModuleButton->addListener(this);

    moduleButtons.push_back(std::move(addModuleButton));

    addModuleButtonIsDrawn = true;
}

void ModuleButtonsComponent::resized()
{
    const auto bounds = getLocalBounds();
    auto xPosition = bounds.getX();
    auto yPosition = bounds.getY();

    for (int i = 0; i < moduleButtons.size(); i++)
    {
        addAndMakeVisible(*moduleButtons[i]);

        auto margin = 20 * i;
           

        moduleButtons[i]->setBounds(xPosition + margin + (i * 122), yPosition, 122, 87);
    }
}


void ModuleButtonsComponent::buttonClicked(Button* button)
{
	if (button == moduleButtons[addModuleButtonIndex].get() && moduleCount < 3)
	{ 
        lookAndFeel.setButtonFontHeight(16);

        String newModule;
        for (int i = 0; i < moduleNames.size(); i++)
        {
            if (!existsInCurrentModules(moduleNames[i]))
            {
                newModule = moduleNames[i];
                break;
            }
            else
                continue;
        }

        moduleButtons[addModuleButtonIndex]->setButtonText(newModule);
        moduleButtons[addModuleButtonIndex]->addChangeListener(this);
        moduleButtons[addModuleButtonIndex]->drawRemoveLabel();
        currentModules.push_back(newModule);
        moduleCount++;

        if (moduleButtons.size() < 3)
        {
            auto newModuleButton = std::make_unique<ModuleButton>(true);
            newModuleButton->setButtonText("+");
            newModuleButton->addListener(this);
            moduleButtons.push_back(std::move(newModuleButton));
            addModuleButtonIndex++;
        }
        
        
        resized();
    }
    else
    {
        if (moduleCount >= 3)
            return;
        
        for (int i = 0; i < moduleNames.size(); i++)
        {
            bool moduleExists = false;

            moduleExists = existsInCurrentModules(moduleNames[i]);

            if (moduleExists || (moduleNames[i] == previousModule && moduleCount < 2))
                continue;

            auto currentModule = button->getButtonText();
            previousModule = currentModule;
            button->setButtonText(moduleNames[i]);
            
            removeFromCurrentModules(currentModule);
            
            currentModules.push_back(moduleNames[i]);
            
            break;
        }
    }
}

void ModuleButtonsComponent::changeListenerCallback(ChangeBroadcaster* source)
{
    for (int i = 0; i < moduleButtons.size(); i++)
    {
        if (moduleButtons[i]->getToBeRemoved())
        {
            if (moduleCount >= 3)
                addModuleButtonIsDrawn = false;
            else
                addModuleButtonIndex--;

            removeFromCurrentModules(moduleButtons[i]->getButtonText());
            moduleButtons[i].reset();
            moduleButtons.erase(moduleButtons.begin() + i);
            moduleCount--;
           
            if (moduleCount <= 0)
            {
                addModuleButtonIndex = 0;
                moduleButtons.clear();
                addModuleButtonIsDrawn = false;

            }
            drawAddModuleButton();  

            resized();
        }
    }
}

bool ModuleButtonsComponent::existsInCurrentModules(String mod)
{
    for (int i = 0; i < currentModules.size(); i++)
    {
        if (currentModules[i] == mod)
            return true;
    }

    return false;
}

void ModuleButtonsComponent::removeFromCurrentModules(String mod)
{
    for (int i = 0; i < currentModules.size(); i++)
    {
        if (currentModules[i] == mod)
            currentModules.erase(currentModules.begin() + i);
    }
}
