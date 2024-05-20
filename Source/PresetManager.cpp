/*
  ==============================================================================

    PresetManager.cpp
    Created: 20 May 2024 8:46:42am
    Author:  martinezd

  ==============================================================================
*/

#include "PresetManager.h"


PresetManager::PresetManager(AudioProcessorValueTreeState& vts) :
    moduleManager(vts),
    vts(vts)
{   
    PropertiesFile::Options options;
    options.applicationName = ProjectInfo::projectName;
    options.filenameSuffix = ".settings";
    options.osxLibrarySubFolder = "Application Support";
    options.folderName = File::getSpecialLocation(File::SpecialLocationType::userApplicationDataDirectory).
        getChildFile(ProjectInfo::projectName).getFullPathName();
    options.storageFormat = PropertiesFile::storeAsXML;

    appProps.setStorageParameters(options);

}

void PresetManager::loadPreset(String preset)
{
}
