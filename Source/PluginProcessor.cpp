#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleSamplerAudioProcessor::SimpleSamplerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    mFormatManager.registerBasicFormats();
    
    for (int i = 0; i < mNumVoices; i++){
        mSampler.addVoice(new SamplerVoice());
    }
}

SimpleSamplerAudioProcessor::~SimpleSamplerAudioProcessor()
{
}

//==============================================================================
const String SimpleSamplerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleSamplerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleSamplerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleSamplerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimpleSamplerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleSamplerAudioProcessor::getNumPrograms()
{
    return 1;
}

int SimpleSamplerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleSamplerAudioProcessor::setCurrentProgram (int index)
{
}

const String SimpleSamplerAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimpleSamplerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SimpleSamplerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mSampler.setCurrentPlaybackSampleRate(sampleRate);
    
    updateADSR();
}

void SimpleSamplerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleSamplerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SimpleSamplerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    mSampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool SimpleSamplerAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* SimpleSamplerAudioProcessor::createEditor()
{
    return new SimpleSamplerAudioProcessorEditor (*this);
}

//==============================================================================
void SimpleSamplerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SimpleSamplerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void SimpleSamplerAudioProcessor::loadFile ()
{
    mSampler.clearSounds();
    
    FileChooser chooser {"Please load a file."};
    if (chooser.browseForFileToOpen())
    {
        auto file = chooser.getResult();
        mFormatReader = mFormatManager.createReaderFor (file);
    }
    
    BigInteger range;
    range.setRange(0, 128, true);
    
    mSampler.addSound(new SamplerSound( "Sample", *mFormatReader, range, 60, 0.01, 0.01, 360));
}

void SimpleSamplerAudioProcessor::loadFile(const String& path)
{
    mSampler.clearSounds();
    
    auto file = File (path);
    mFormatReader = mFormatManager.createReaderFor (file);
    
    auto sampleLength = static_cast<int>(mFormatReader->lengthInSamples);
    mWaveform.setSize(1, sampleLength);
    mFormatReader->read(&mWaveform, 0, sampleLength, 0, true, false);
    
    auto buffer = mWaveform.getReadPointer (0);
    
    for (int sample = 0; sample < mWaveform.getNumSamples(); ++sample)
    {
        DBG (buffer[sample]);
    }
    
    BigInteger range;
    range.setRange(0, 128, true);
    
    mSampler.addSound(new SamplerSound("Sample", *mFormatReader, range, 60, 0.01, 0.01, 360));
}

void SimpleSamplerAudioProcessor::updateADSR()
{
    for (int i = 0; i < mSampler.getNumSounds(); i++)
    {
        if (auto sound = dynamic_cast<SamplerSound*>(mSampler.getSound(i).get()))
        {
            sound->setEnvelopeParameters (mADSRParams);
        }
    }
    DBG ("A: " << attack << " D: " << decay << " S: " << sustain << " R: " << release);
}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleSamplerAudioProcessor();
}
