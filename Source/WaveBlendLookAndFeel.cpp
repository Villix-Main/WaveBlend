/*
  ==============================================================================

    WaveBlendLookAndFeel.cpp
    Created: 6 Nov 2023 1:51:31pm
    Author:  martinezd

  ==============================================================================
*/

#include "WaveBlendLookAndFeel.h"


void WaveBlendLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPosProportional, float rotaryStartAngle,
    float rotaryEndAngle, juce::Slider&) 
{
    auto radius = (float)juce::jmin(width / 2, height / 2) - 4.0f;
    auto centreX = (float)x + (float)width * 0.5f;
    auto centreY = (float)y + (float)height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    // Fill of slider
    g.setColour(WBColors::SecondaryGrey);
    g.fillEllipse(rx, ry, rw, rw);

    // Outline of slider
    g.setColour(juce::Colour(0xff707070));
    g.drawEllipse(rx, ry, rw, rw, 1.0f);
    
    
    // Pointer
    juce::Path p;
    auto pointerLength = radius * 0.8;
    auto pointerThickness = 2.0f;
    p.addRectangle(-pointerThickness * 0.5f, -radius * 0.8, pointerThickness, pointerLength);
    p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

    // Pointer Color
    g.setColour(juce::Colour(0xffC2C0C0));
    g.fillPath(p);
}

void WaveBlendLookAndFeel::drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    auto buttonArea = button.getLocalBounds().toFloat();
    auto edge = 2;


    // Background color, checks for mouse clicks and hover
    float alpha = (shouldDrawButtonAsHighlighted || shouldDrawButtonAsDown) ? 0.8f : 1;
    int alphaHex = jmap(alpha, 0.f, 1.f, 0.f, 255.f);
    g.setColour(Colour::fromRGBA(140, 162, 176, alphaHex));
    g.fillRoundedRectangle(buttonArea, 16);
}

void WaveBlendLookAndFeel::drawButtonText(Graphics& g, TextButton& button, bool, bool)
{
    Font font;
    font.setHeight(buttonFontHeight);
    g.setFont(font);
    g.setColour(WBColors::PrimaryGrey);

    const int yIndent = button.proportionOfHeight(0.1f);
    const int cornerSize = jmin(button.getHeight(), button.getWidth()) / 2;

    const int leftIndent = cornerSize / (button.isConnectedOnLeft() ?
        yIndent * 2 : yIndent);
    const int rightIndent = cornerSize / (button.isConnectedOnRight() ?
        yIndent * 2 : yIndent);
    const int textWidth = button.getWidth() - leftIndent - rightIndent;

    if (textWidth > 0)
        g.drawFittedText(button.getButtonText(),
            leftIndent, yIndent, textWidth, button.getHeight() - yIndent * 2,
            Justification::centred, 2, 0.5f);
}

void WaveBlendLookAndFeel::drawComboBox(Graphics& g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox& cb)
{
    Rectangle<int> mainBox(cb.getLocalBounds());

    Label l;
    l.setText("^", NotificationType::dontSendNotification);

    g.setColour(WBColors::PrimaryGrey);
    g.fillRoundedRectangle(mainBox.toFloat(), 16);
    g.setColour(Colour(0xffC2C0C0));

    Font f;
    f.setBold(true);
    f.setHeight(20);
    g.setFont(f);

    g.drawText("v", mainBox.reduced(10, 0), Justification::centredRight, true);
    
}

void WaveBlendLookAndFeel::positionComboBoxText(ComboBox& cb, Label& l)
{
    auto bounds = cb.getLocalBounds();
    bounds.setX(bounds.getX() + 10);
    l.setBounds(bounds);
}

Font WaveBlendLookAndFeel::getLabelFont(Label& label)
{
    Font sliderTextBoxFont;
    sliderTextBoxFont.setHeight(12);

    if (dynamic_cast<Slider*>(label.getParentComponent()))
        return sliderTextBoxFont;

    return LookAndFeel_V4::getLabelFont(label);
 
}

void WaveBlendLookAndFeel::setButtonFontHeight(int fh) { this->buttonFontHeight = fh; }
