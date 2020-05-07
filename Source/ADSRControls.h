/*
  ==============================================================================

    ADSRControls.h
    Created: 4 May 2020 8:45:18pm
    Author:  Joe McLean

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class ADSRControls    : public Component
{
public:
    ADSRControls(SimpleSamplerAudioProcessor& p);
    ~ADSRControls();

    void paint (Graphics&) override;
    void resized() override;

private:
    SimpleSamplerAudioProcessor& processor;
    
    Slider mAttackSlider, mDecaySlider, mSustainSlider, mReleaseSlider;
    Label mAttackLabel, mDecayLabel, mSustainLabel, mReleaseLabel;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mAttackAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mDecayAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mSustainAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mReleaseAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRControls)
};
