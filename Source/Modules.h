/*
  ==============================================================================

    Modules.h
    Created: 8 Dec 2023 10:50:29am
    Author:  martinezd

  ==============================================================================
*/

#pragma once

namespace Modules
{
    const String Reverb{ "Reverb" };
    const String Compressor{ "Compressor" };
    const String Equalizer{ "Equalizer" };
    const String None { "None" };
}

enum ModuleButtonAction
{
    Add,
    Switch,
    Remove,
    None
};