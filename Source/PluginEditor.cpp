/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleSamplerAudioProcessorEditor::SimpleSamplerAudioProcessorEditor (SimpleSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    mLoadBButton.onClick = [&]() { processor.loadFile(); };
    addAndMakeVisible(mLoadBButton);
    
    setSize (600, 200);
}

SimpleSamplerAudioProcessorEditor::~SimpleSamplerAudioProcessorEditor()
{
}

//==============================================================================
void SimpleSamplerAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
    
    g.setColour (Colours::white);
    
    if (repaintWaveform)
    {
        Path path;
        mAudioPoints.clear();
        
        auto waveform = processor.getWaveform();
        auto xRatio = waveform.getNumSamples() / getWidth();
        auto buffer = waveform.getReadPointer(0);
        
        // scale on x axis
        for (int sample = 0; sample < waveform.getNumSamples(); sample+=xRatio)
        {
            mAudioPoints.push_back(buffer[sample]);
        }
        
        path.startNewSubPath(0, getHeight()/2);
        
        // scale on y axis
        for (int sample = 0; sample < mAudioPoints.size(); ++sample)
        {
            auto point = jmap<float> (mAudioPoints[sample], -1.0f, 1.0f, 200, 0);
            path.lineTo(sample, point);
        }
        
        g.strokePath(path, PathStrokeType(2));
        
        repaintWaveform = false;
    }
        
//    g.setColour(Colours::white);
//    g.setFont(15.0f);
//    if (processor.getNumSamplerSounds() > 0)
//    {
//        g.fillAll(Colours::blue);
//        g.drawText("Sound loaded", getWidth() /2 -50, getHeight() / 2 - 10, 100, 20, Justification::centred);
//    }
//    else {
//        g.drawText("Load a sound", getWidth() /2 -50, getHeight() / 2 - 10, 100, 20, Justification::centred);
//    }
}

void SimpleSamplerAudioProcessorEditor::resized()
{
    // mLoadBButton.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 50, 100, 100);
}

bool SimpleSamplerAudioProcessorEditor::isInterestedInFileDrag(const StringArray &files)
{
    for (auto file : files) {
        if (file.contains(".wav") || file.contains(".mp3") || file.contains(".aif")) {
            return true;
        }
    }
    return false;
}

void SimpleSamplerAudioProcessorEditor::filesDropped(const StringArray &files, int x, int y)
{
    for (auto file : files) {
        if (isInterestedInFileDrag (file)) {
            processor.loadFile (file);
        }
    }
    repaintWaveform = true;
    repaint();
}
