#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleSamplerAudioProcessorEditor::SimpleSamplerAudioProcessorEditor (SimpleSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), mWaveformDisplay(p), mADSRControls(p)
{
    addAndMakeVisible(mWaveformDisplay);
    addAndMakeVisible(mADSRControls);
    addAndMakeVisible(mLogoComponent);
    
    startTimerHz(30);
    
    setSize (600, 300);
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
    mWaveformDisplay.setBoundsRelative(0.0f, 0.0f, 1.0f, 0.65);
    mLogoComponent.setBoundsRelative(0.0, 0.65, 0.4, 0.35);
    mADSRControls.setBoundsRelative(0.5, 0.65, 0.5, 0.35);
}

void SimpleSamplerAudioProcessorEditor::timerCallback()
{
    repaint();
}
