/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

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
    
    TextButton mLoadBButton { "Load" };
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleSamplerAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSamplerAudioProcessorEditor)
};
