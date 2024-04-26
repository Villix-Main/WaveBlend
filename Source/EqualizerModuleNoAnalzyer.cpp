/*
  ==============================================================================

    EqualizerModule.cpp
    Created: 8 Dec 2023 10:29:42am
    Author:  martinezd

  ==============================================================================
*/

/*
#include "EqualizerModule.h"
#include "WaveBlendColors.h"


EqualizerModule::EqualizerModule(AudioProcessorValueTreeState& vts) :
    mixSlider("Mix", 0, 100),
    outputSlider("Output", -15, 10)
{
    f.setHeight(15);

    // Mix Slider
    addAndMakeVisible(mixSlider);
    mixAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "equalizer_mix", mixSlider));

    // Output Slider
    addAndMakeVisible(outputSlider);
    outputAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(vts, "equalizer_output", outputSlider));
}

void EqualizerModule::paint(Graphics& g)
{
    auto bounds = getLocalBounds();

    Path graphLine1;
    graphLine1.addRectangle(90, 0, 1, 224);
    Path graphLine2;
    graphLine2.addRectangle(145, 0, 1, 224);
    Path graphLine3;
    graphLine3.addRectangle(280, 0, 1, 224);
    Path graphLine4;
    graphLine4.addRectangle(375, 0, 1, 224);
    Path graphLine5;
    graphLine5.addRectangle(440, 0, 1, 224);
    Path graphLine6;
    graphLine6.addRectangle(575, 0, 1, 224);
    Path graphLine7;
    graphLine7.addRectangle(670, 0, 1, 224);
    Path graphLine8;
    graphLine8.addRectangle(735, 0, 1, 224);

    Path bottomGraphLine;
    bottomGraphLine.addRectangle(25, 224, 810, 1);

    g.setColour(Colour(0xff707070));
    g.fillPath(graphLine1);
    g.fillPath(graphLine2);
    g.fillPath(graphLine3);
    g.fillPath(graphLine4);
    g.fillPath(graphLine5);
    g.fillPath(graphLine6);
    g.fillPath(graphLine7);
    g.fillPath(graphLine8);

    g.setColour(WBColors::SecondaryGrey);
    g.fillPath(bottomGraphLine);

    g.setFont(15);
    g.setColour(WBColors::MoreLightGrey);
    g.drawFittedText("60", { 93, 206, 20, 20 }, Justification::top, 1);
    g.drawFittedText("100", { 148, 206, 20, 20 }, Justification::top, 1);
    g.drawFittedText("300", { 283, 206, 20, 20 }, Justification::top, 1);
    g.drawFittedText("600", { 378, 206, 20, 20 }, Justification::top, 1);
    g.drawFittedText("1k", { 443, 206, 20, 20 }, Justification::top, 1);
    g.drawFittedText("3k", { 578, 206, 20, 20 }, Justification::top, 1);
    g.drawFittedText("6k", { 673, 206, 20, 20 }, Justification::top, 1);
    g.drawFittedText("10k", { 738, 206, 20, 20 }, Justification::top, 1);

    g.drawFittedText("dB", { 7, 7, 20, 20 }, Justification::top, 1);
    g.drawFittedText("-20", { 7, 42, 20, 20 }, Justification::top, 1);
    g.drawFittedText("-40", { 7, 77, 20, 20 }, Justification::top, 1);
    g.drawFittedText("-60", { 7, 112, 20, 20 }, Justification::top, 1);
    g.drawFittedText("-80", { 7, 147, 20, 20 }, Justification::top, 1);
    g.drawFittedText("-100", { 7, 182, 25, 25 }, Justification::top, 1);

    auto w = bounds.getWidth();
    g.drawFittedText("dB", { 830, 7, 20, 20 }, Justification::top, 1);
    g.drawFittedText("4", { 830, 26, 20, 20 }, Justification::centredTop, 1);
    g.drawFittedText("2", { 830, 54, 20, 20 }, Justification::centredTop, 1);
    g.drawFittedText("0", { 830, 82, 20, 20 }, Justification::centredTop, 1);
    g.drawFittedText("-2", { 830, 110, 20, 20 }, Justification::centredTop, 1);
    g.drawFittedText("-4", { 830, 138, 20, 20 }, Justification::centredTop, 1);
    g.drawFittedText("-6", { 830, 166, 20, 20 }, Justification::centredTop, 1);
    g.drawFittedText("-8", { 830, 194, 20, 20 }, Justification::centredTop, 1);




}

void EqualizerModule::resized()
{
    const auto bounds = this->getLocalBounds();

    outputSlider.setBounds(720, 270, 50, 70);
    mixSlider.setBounds(780, 270, 50, 70);
}
*/