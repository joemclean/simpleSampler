/*
  ==============================================================================

    WaveformDisplay.h
    Created: 4 May 2020 11:36:11am
    Author:  Joe McLean

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class WaveformDisplay    : public Component,
                           public FileDragAndDropTarget
{
public:
    WaveformDisplay(SimpleSamplerAudioProcessor& p);
    ~WaveformDisplay();

    void paint (Graphics&) override;
    void resized() override;
    
    bool isInterestedInFileDrag (const StringArray& files) override;
    void filesDropped (const StringArray &files, int x, int y) override;

private:
    
    TextButton mLoadButton { "Browse for a file" };
    
    std::vector<float> mAudioPoints;
    
    SimpleSamplerAudioProcessor& processor;
    
    String mFilename { "" };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
