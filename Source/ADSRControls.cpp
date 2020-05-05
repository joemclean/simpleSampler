/*
  ==============================================================================

    ADSRControls.cpp
    Created: 4 May 2020 8:45:18pm
    Author:  Joe McLean

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRControls.h"

//==============================================================================
ADSRControls::ADSRControls(SimpleSamplerAudioProcessor& p) : processor(p)
{
    // Attack Slider
    mAttackSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mAttackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    addAndMakeVisible(mAttackSlider);
    
    mAttackLabel.setFont(10.0f);
    mAttackLabel.setText("Attack", NotificationType::dontSendNotification);
    mAttackLabel.setJustificationType(Justification::centredTop);
    mAttackLabel.attachToComponent(&mAttackSlider, false);
    
    mAttackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "ATTACK", mAttackSlider);
    
    // Decay Slider
    mDecaySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mDecaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    addAndMakeVisible(mDecaySlider);
    
    mDecayLabel.setFont(10.0f);
    mDecayLabel.setText("Decay", NotificationType::dontSendNotification);
    mDecayLabel.setJustificationType(Justification::centredTop);
    mDecayLabel.attachToComponent(&mDecaySlider, false);
    
    mDecayAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "DECAY", mDecaySlider);
    
    // Sustain Slider
    mSustainSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mSustainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    addAndMakeVisible(mSustainSlider);
    
    mSustainLabel.setFont(10.0f);
    mSustainLabel.setText("Sustain", NotificationType::dontSendNotification);
    mSustainLabel.setJustificationType(Justification::centredTop);
    mSustainLabel.attachToComponent(&mSustainSlider, false);
    
    mSustainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "SUSTAIN", mSustainSlider);

    // Release Slider
    mReleaseSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mReleaseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    addAndMakeVisible(mReleaseSlider);
    
    mReleaseLabel.setFont(10.0f);
    mReleaseLabel.setText("Release", NotificationType::dontSendNotification);
    mReleaseLabel.setJustificationType(Justification::centredTop);
    mReleaseLabel.attachToComponent(&mReleaseSlider, false);
    
    mReleaseAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "RELEASE", mReleaseSlider);
}

ADSRControls::~ADSRControls()
{
}

void ADSRControls::paint (Graphics& g)
{
    const auto startX = 0.0f;
    const auto startY = 0.0f;
    const auto dialWidth = 0.2f;
    const auto dialHeight = 1.0f;
    
    mAttackSlider.setBoundsRelative(startX, startY, dialWidth, dialHeight);
    mDecaySlider.setBoundsRelative(startX + dialWidth, startY, dialWidth, dialHeight);
    mSustainSlider.setBoundsRelative(startX + dialWidth*2, startY, dialWidth, dialHeight);
    mReleaseSlider.setBoundsRelative(startX + dialWidth*3, startY, dialWidth, dialHeight);  // draw some placeholder text
}

void ADSRControls::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
