/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
WaveBlendAudioProcessorEditor::WaveBlendAudioProcessorEditor (WaveBlendAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Set Look And Feel of plugin
    setLookAndFeel(&lookAndFeel);

    barLabelFont.setHeight(12);

    // Output Db Slider
    addAndMakeVisible(outputDbSlider);
    outputDbSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    outputDbSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 14);
    outputDbSlider.setRange(-15.0f, 0.f);
    //outputDbAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "output_db", outputDbSlider));
    
    // Output Db Label
    addAndMakeVisible(outputDbLabel);
    outputDbLabel.setFont(barLabelFont);
    outputDbLabel.setText("Output", dontSendNotification);
    outputDbLabel.setJustificationType(Justification::centred);
    outputDbLabel.attachToComponent(&outputDbSlider, false);

    // Mix Slider
    addAndMakeVisible(mixSlider);
    mixSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mixSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 14);
    mixSlider.setRange(0, 100);
    //mixSliderAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "mix", mixSlider));
    
    // Mix Label
    addAndMakeVisible(mixLabel);
    mixLabel.setFont(barLabelFont);
    mixLabel.setText("Mix", dontSendNotification);
    mixLabel.setJustificationType(Justification::centred);
    mixLabel.attachToComponent(&mixSlider, false);

    
    // Plugin Preset Menu
    addAndMakeVisible(pluginPresetMenu);
    pluginPresetMenu.setText("Presets");
    pluginPresetMenu.addItem("<Default>", 1);
    pluginPresetMenu.addItem("Drum Room", 2);
    pluginPresetMenu.addItem("Piano", 3);
    pluginPresetMenu.addItem("Clean Vocals", 4);
    pluginPresetMenu.addItem("Flute", 5);

    addAndMakeVisible(moduleManager);

    //addAndMakeVisible(rm);

    // Add Module Button
	/*addAndMakeVisible(addModule);
	lookAndFeel.setButtonFontHeight(40);
	addModule.setButtonText("+");*/
    
    addAndMakeVisible(moduleButtons);
    moduleButtons.addChangeListener(this);
    

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (860, 560);
}

WaveBlendAudioProcessorEditor::~WaveBlendAudioProcessorEditor()
{
}

//==============================================================================
void WaveBlendAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colour(0xff495D6A));


    ColourGradient rectGradient = ColourGradient{
        Colour(WBColors::SecondaryGrey),
        topBar.getBottomLeft().toFloat(),
        Colour(WBColors::SecondaryLightGrey),
        topBar.getTopRight().toFloat(),
        false
    };


    titleFont.setHeight(22);
    titleFont.setBold(true);


    DropShadow(Colour(0x6c323232),
        11, { -4, 8 }).drawForRectangle(g, topBar);


    g.setGradientFill(rectGradient);
    g.drawRect(topBar, 1);
    g.fillRect(topBar);



    g.setColour(Colours::white);
    g.setFont(titleFont);
    g.drawFittedText("WaveBlend", topBar.reduced(50, 0), Justification::left, 1);

    // The line between the add module buttons and the module knobs
    Path moduleLine;
    moduleLine.addRectangle(25.f, 190, 810, 1);

    g.setColour(Colour(0xff5B7586));
    g.fillPath(moduleLine);
}

void WaveBlendAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto bounds = getLocalBounds();

    topBar = bounds.removeFromTop(69);

    pluginPresetMenu.setBounds(253, 20, 197, 30);
   
    outputDbSlider.setBounds(742, 19, 53, 45);
    mixSlider.setBounds(785, 19, 53, 45);

    //addModule.setBounds(44, 86, 122, 87);
    moduleButtons.setBounds(44, 86, 500, 87);

    moduleManager.setBounds(0, 190, bounds.getWidth(), 370);

    //rm.setBounds(0, 190, bounds.getWidth(), 370);

}

void WaveBlendAudioProcessorEditor::changeListenerCallback(ChangeBroadcaster* source)
{
    auto moduleToRender= moduleButtons.getModuleToRender();
    auto buttonAction = moduleButtons.getButtonAction();

    switch (buttonAction)
    {
    case ModuleButtonAction::Add:
        moduleManager.SetAndRenderModule(moduleToRender);
        break;
    case ModuleButtonAction::Switch:
        moduleManager.SetAndRenderModule(moduleToRender);
        break;
    case ModuleButtonAction::Remove:
        moduleManager.SetAndRenderModule(moduleToRender);
        break;
    case ModuleButtonAction::None:
        moduleManager.RemoveAndDontRender();
        break;

    }

}
