#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SimpleSamplerAudioProcessorEditor  : public AudioProcessorEditor,
                                           public FileDragAndDropTarget,
                                           public Slider::Listener
{
public:
    SimpleSamplerAudioProcessorEditor (SimpleSamplerAudioProcessor&);
    ~SimpleSamplerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    bool isInterestedInFileDrag (const StringArray& files) override;
    void filesDropped (const StringArray &files, int x, int y) override;
    
    void sliderValueChanged (Slider* slider) override;

private:
    
    TextButton mLoadBButton { "Load" };
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleSamplerAudioProcessor& processor;
    
    std::vector<float> mAudioPoints;
    
    Slider mAttackSlider, mDecaySlider, mSustainSlider, mReleaseSlider;
    Label mAttackLabel, mDecayLabel, mSustainLabel, mReleaseLabel;
    
    bool repaintWaveform { false };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSamplerAudioProcessorEditor)
};
