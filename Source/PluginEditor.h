#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WaveformDisplay.h"
#include "ADSRControls.h"

//==============================================================================
/**
*/
class SimpleSamplerAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    SimpleSamplerAudioProcessorEditor (SimpleSamplerAudioProcessor&);
    ~SimpleSamplerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    SimpleSamplerAudioProcessor& processor;
    
    WaveformDisplay mWaveformDisplay;
    ADSRControls mADSRControls;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSamplerAudioProcessorEditor)
};
