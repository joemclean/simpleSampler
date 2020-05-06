#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleSamplerAudioProcessorEditor::SimpleSamplerAudioProcessorEditor (SimpleSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), mWaveformDisplay(p), mADSRControls(p)
{
    addAndMakeVisible(mWaveformDisplay);
    addAndMakeVisible(mADSRControls);
    
    startTimerHz(30);
    
    setSize (600, 400);
}

SimpleSamplerAudioProcessorEditor::~SimpleSamplerAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void SimpleSamplerAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void SimpleSamplerAudioProcessorEditor::resized()
{
    mWaveformDisplay.setBoundsRelative(0.0f, 0.25f, 1.0f, 0.5f);
    mADSRControls.setBoundsRelative(0.6, 0.75, 0.4, 0.25);
}

void SimpleSamplerAudioProcessorEditor::timerCallback()
{
    repaint();
}
