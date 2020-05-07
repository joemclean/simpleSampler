#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WaveformDisplay.h"
#include "ADSRControls.h"
#include "LogoComponent.h"

//==============================================================================
/**
*/
class SimpleSamplerAudioProcessorEditor  : public AudioProcessorEditor,
                                           public Timer
{
public:
    SimpleSamplerAudioProcessorEditor (SimpleSamplerAudioProcessor&);
    ~SimpleSamplerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void timerCallback() override;

private:
    SimpleSamplerAudioProcessor& processor;
    
    WaveformDisplay mWaveformDisplay;
    ADSRControls mADSRControls;
    LogoComponent mLogoComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSamplerAudioProcessorEditor)
};
