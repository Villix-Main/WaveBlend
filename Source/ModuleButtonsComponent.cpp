/*
  ==============================================================================

    ModuleButtonsComponent.cpp
    Created: 12 Nov 2023 8:45:51pm
    Author:  Villi

  ==============================================================================
*/

#include "ModuleButtonsComponent.h"



ModuleButtonsComponent::ModuleButtonsComponent(UIState& currentState)
{
    setLookAndFeel(&lookAndFeel);


    addModuleButtonIsDrawn = false;
    moduleNames = { Modules::Reverb, Modules::Compressor, Modules::Equalizer };
    currentModules = {};
    moduleCount = 0;
    addModuleButtonIndex = 0;
    currentModule.index = -1;
  
    if (currentState.getCurrentModules().size() <= 0)
    {
        renderFromState(currentState);
    }

    drawAddModuleButton();
}

void ModuleButtonsComponent::renderFromState(UIState cs)
{
    currentModules.addArray(cs.getCurrentModules()); 

    for (String mod : currentModules)
    {
        auto newButton = std::make_unique<ModuleButton>();
        newButton->setButtonText(mod);
        newButton->addListener(this);
        moduleButtons.push_back(std::move(newButton));
        
        currentModules.add(mod);
        addModuleButtonIndex++;
        moduleCount++;
    }

    currentModule = cs.getCurrentModule();
    focusOnButton(currentModule.index, currentModule.moduleName);

    if (moduleCount >= 3)
        addModuleButtonIsDrawn = true;

    resized();
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
        moduleButtons[addModuleButtonIndex]->drawLabels();
        currentModules.add(newModule);
        moduleCount++;

        if (moduleCount > 1)
        {
            previousModule.index = addModuleButtonIndex - 1;
            previousModule.moduleName = moduleButtons[addModuleButtonIndex - 1]->getButtonText();
        }
        
        focusOnButton(addModuleButtonIndex, newModule);

        if (moduleButtons.size() < 3)
        {
            auto newModuleButton = std::make_unique<ModuleButton>(true);
            newModuleButton->setButtonText("+");
            newModuleButton->addListener(this);
            moduleButtons.push_back(std::move(newModuleButton));
            addModuleButtonIndex++;
        }

        moduleToRender = newModule;
        buttonAction = ModuleButtonAction::Add;
        sendChangeMessage();
        
        resized();
    }
    else
    {
        for (int i = 0; i < moduleButtons.size(); i++)
        {
            if (button == moduleButtons[i].get())
            {
                moduleToRender = moduleButtons[i]->getButtonText();

                focusOnButton(i, moduleButtons[i]->getButtonText());

                buttonAction = ModuleButtonAction::Switch;
                sendChangeMessage();
            }
        }
    }
}

void ModuleButtonsComponent::changeListenerCallback(ChangeBroadcaster* source)
{
    for (int i = 0; i < moduleButtons.size(); i++)
    {
        ModuleButtonAction ba = moduleButtons[i]->getButtonAction();

        if (ba == ModuleButtonAction::Remove)
        {
            if (moduleCount >= 3)
                addModuleButtonIsDrawn = false;
            else
                addModuleButtonIndex--;


            moduleCount--;
           
            if (moduleCount <= 0)
            {
                buttonAction = ModuleButtonAction::None;
            }
            else
                buttonAction = ModuleButtonAction::Remove;
             
            if (moduleButtons[i]->getButtonText() == currentModule.moduleName)
            {
                if (buttonAction != ModuleButtonAction::None)
                {
                    int leftOrRight = 1;
                    if (i == 0)
                        leftOrRight = -1;
                    currentModule.index = moduleCount >= 1 ? i - (1 * leftOrRight) : 0;
                    currentModule.moduleName = moduleButtons[currentModule.index]->getButtonText();

                    moduleToRender = currentModule.moduleName;
                    int priorIndex = currentModule.index;
                    focusOnButton(currentModule.index, currentModule.moduleName);
                    //currentModule = previousModule;


                }
                

                sendChangeMessage();
            }

            removeFromCurrentModules(moduleButtons[i]->getButtonText());
            moduleButtons[i].reset();
            moduleButtons.erase(moduleButtons.begin() + i);
            
            if (buttonAction == ModuleButtonAction::None)
            {
                addModuleButtonIndex = 0;
                addModuleButtonIsDrawn = false;

                moduleButtons.clear();
                currentModule.index = -1;
            }

            
            drawAddModuleButton();  



            
            resized();
        } 
        else if (ba == ModuleButtonAction::Switch)
        {
            if (moduleCount >= 3)
                return;

            for (int j = 0; j < moduleNames.size(); j++)
            {
                bool moduleExists = false;

                moduleExists = existsInCurrentModules(moduleNames[j]);

                if (moduleExists || (moduleNames[j] == previousModule.moduleName && moduleCount < 2))
                    continue;

                auto currentModule = moduleButtons[i]->getButtonText();
                previousModule.moduleName = currentModule;
                previousModule.index = i;
                moduleButtons[i]->setButtonText(moduleNames[j]);

                removeFromCurrentModules(currentModule);

                currentModules.add(moduleNames[j]);
                
                focusOnButton(i, moduleNames[j]);

                moduleButtons[i]->setButtonAction(ModuleButtonAction::None);
                moduleToRender = moduleNames[j];
                buttonAction = ModuleButtonAction::Switch;
                sendChangeMessage();

                break;
            }
        }
    }
}

String ModuleButtonsComponent::getModuleToRender()
{
    return this->moduleToRender;
}
ModuleButtonAction ModuleButtonsComponent::getButtonAction()
{
    return this->buttonAction;
}

void ModuleButtonsComponent::focusOnButton(int index, String name)
{
    for (int i = 0; i < moduleButtons.size(); i++)
        moduleButtons[i]->setAlpha(1.0);

    moduleButtons[index]->setAlpha(0.7);
    previousModule = currentModule;
    currentModule.index = index;
    currentModule.moduleName = name;
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
            currentModules.remove(i);
    }
}

