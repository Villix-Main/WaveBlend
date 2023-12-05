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

    drawAddModuleButton();


    //addAndMakeVisible(test);
    //test.setButtonText("test");
    //
    //test.addChangeListener(this);
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

    
    //addModuleButton->setBounds(xPosition, yPosition, 122, 87);
    //test.setBounds(xPosition, yPosition, 122, 87);

    for (int i = 0; i < moduleButtons.size(); i++)
    {
        addAndMakeVisible(*moduleButtons[i]);

        auto margin = 20 * i;
           

        moduleButtons[i]->setBounds(xPosition + margin + (i * 122), yPosition, 122, 87);


    }
}


void ModuleButtonsComponent::buttonClicked(Button* button)
{
	if (button == moduleButtons[addModuleButtonIndex].get())
	{ 
        lookAndFeel.setButtonFontHeight(16);

        moduleButtons[addModuleButtonIndex]->setButtonText(moduleNames[addModuleButtonIndex]);
        moduleButtons[addModuleButtonIndex]->addChangeListener(this);
        moduleButtons[addModuleButtonIndex]->drawRemoveLabel();
        currentModules.push_back(moduleNames[addModuleButtonIndex]);
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
        button->setButtonText("test");
        if (moduleButtons.size() >= 3)
            return;
        
        for (int i = 0; i < moduleNames.size(); i++)
        {
            bool moduleExists;

            for (int j = 0; i < currentModules.size(); i++)
            {
                if (moduleNames[i] == currentModules[j])
                    moduleExists = true;
            }

            if (moduleExists)
                continue;

            button->setButtonText(moduleNames[i]);
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
