/*
  ==============================================================================

    ModuleButtonsComponent.cpp
    Created: 12 Nov 2023 8:45:51pm
    Author:  Villi

  ==============================================================================
*/

#include "ModuleButtonsComponent.h"



ModuleButtonsComponent::ModuleButtonsComponent(AudioProcessorValueTreeState& vts)
{
    setLookAndFeel(&lookAndFeel);


    addModuleButtonIsDrawn = false;
    buttonAction = ModuleButtonAction::None;
    moduleNames = { Modules::Reverb, Modules::Compressor, Modules::Equalizer };
    currentModules = {};
	moduleButtons.clear();
    moduleCount = 0;
    addModuleButtonIndex = 0;
    currentModule.index = -1;

    currentSoloModulePtr = vts.getRawParameterValue("current_solo_module");
    reverbBypassPtr = vts.getRawParameterValue("reverb_bypass");
    compressorBypassPtr = vts.getRawParameterValue("compressor_bypass");
    equalizerBypassPtr = vts.getRawParameterValue("equalizer_bypass");
 /* 
    if (currentState.getCurrentModules().size() > 0)
    {
        renderFromState(currentState, 3);
    }*/

}

void ModuleButtonsComponent::renderFromState(UIState& cs)
{
	addModuleButtonIsDrawn = false;
	buttonAction = ModuleButtonAction::None;
	moduleNames = { Modules::Reverb, Modules::Compressor, Modules::Equalizer };
	currentModules = {};
    moduleButtons.clear();
	moduleCount = 0;
	addModuleButtonIndex = 0;
	currentModule.index = -1;

    currentModules.addArray(cs.getCurrentModules()); 

    if (currentModules.size() > 0)
    {
        for (String mod : currentModules)
        {
            auto newButton = std::make_unique<ModuleButton>();
            newButton->setButtonText(mod);
            newButton->addListener(this);
            newButton->addChangeListener(this);
            moduleButtons.push_back(std::move(newButton));

            moduleCount++;

            if (moduleButtons.size() < 3)
                addModuleButtonIndex++;
        }

        currentModule = cs.getCurrentModule();
        focusOnButton(currentModule.index, currentModule.moduleName);
        moduleToRender = currentModule.moduleName;
        buttonAction = ModuleButtonAction::Add;
        sendChangeMessage();

        if (moduleCount >= 3)
            addModuleButtonIsDrawn = true;


    }

    drawAddModuleButton();
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
                currentModules = {};
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
            }
            else  
            {
            }


            moduleToRemove = moduleButtons[i]->getButtonText();
            sendChangeMessage();

            removeFromCurrentModules(moduleButtons[i]->getButtonText());
            
            moduleButtons[i].reset();
            moduleButtons.erase(moduleButtons.begin() + i);
			currentModule.index--;

            
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

            String tempModToRemove = moduleButtons[i]->getButtonText();
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
                moduleToRemove = tempModToRemove;
                buttonAction = ModuleButtonAction::Switch;
                sendChangeMessage();

                break;
            }
        }
        else if (ba == ModuleButtonAction::Solo)
        {
            String moduleName = moduleButtons[i]->getButtonText();

            for (int j = 0; j < moduleButtons.size(); j++)
                if (j != i)
                    moduleButtons[j]->setSoloLabelToggle(false);

            if (moduleName == Modules::Reverb)
            {
                if (currentSoloModulePtr->load() == 1)
                    *currentSoloModulePtr = 0;
                else
                    *currentSoloModulePtr = 1;
            }
            else if (moduleName == Modules::Compressor)
            {
				if (currentSoloModulePtr->load() == 2)
					*currentSoloModulePtr = 0;
				else
					*currentSoloModulePtr = 2;
            }
            else if (moduleName == Modules::Equalizer)
            {
				if (currentSoloModulePtr->load() == 3)
					*currentSoloModulePtr = 0;
				else
					*currentSoloModulePtr = 3;
            }
            moduleButtons[i]->setButtonAction(ModuleButtonAction::None);

        }
        else if (ba == ModuleButtonAction::Bypass)
        {
            String moduleName = moduleButtons[i]->getButtonText();


			if (moduleName == Modules::Reverb)
			{
				if (reverbBypassPtr->load() == 1)
					*reverbBypassPtr = 0;
				else
					*reverbBypassPtr = 1;
			}
			else if (moduleName == Modules::Compressor)
			{
				if (compressorBypassPtr->load() == 2)
					*compressorBypassPtr = 0;
				else
					*compressorBypassPtr = 2;
			}
			else if (moduleName == Modules::Equalizer)
			{
				if (equalizerBypassPtr->load() == 3)
					*equalizerBypassPtr = 0;
				else
					*equalizerBypassPtr = 3;
			}
			moduleButtons[i]->setButtonAction(ModuleButtonAction::None);
        }
    }
}

StringArray& ModuleButtonsComponent::getCurrentModules()
{
    return this->currentModules;
}

ModuleButtonData ModuleButtonsComponent::getCurrentModule()
{
    return this->currentModule;
}

String ModuleButtonsComponent::getModuleToRender()
{
    return this->moduleToRender;
}
String ModuleButtonsComponent::getModuleToRemove()
{
    return this->moduleToRemove;
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


