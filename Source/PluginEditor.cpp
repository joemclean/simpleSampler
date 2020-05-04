#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleSamplerAudioProcessorEditor::SimpleSamplerAudioProcessorEditor (SimpleSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    mLoadBButton.onClick = [&]() { processor.loadFile(); };
    addAndMakeVisible(mLoadBButton);
    
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
        
        auto roundedCornerPath = path.createPathWithRoundedCorners(5);
        g.strokePath(roundedCornerPath, PathStrokeType(2));
        
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
    
    const auto startX = 0.6f;
    const auto startY = 0.6f;
    const auto dialWidth = 0.1f;
    const auto dialHeight = 0.4f;
    
    mAttackSlider.setBoundsRelative(startX, startY, dialWidth, dialHeight);
    mDecaySlider.setBoundsRelative(startX + dialWidth, startY, dialWidth, dialHeight);
    mSustainSlider.setBoundsRelative(startX + dialWidth*2, startY, dialWidth, dialHeight);
    mReleaseSlider.setBoundsRelative(startX + dialWidth*3, startY, dialWidth, dialHeight);
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
            repaintWaveform = true;
        }
    }
    repaint();
}
