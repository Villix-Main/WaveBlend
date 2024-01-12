/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class WaveBlendAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    WaveBlendAudioProcessor();
    ~WaveBlendAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    AudioProcessorValueTreeState parameters;
    
    // Reverb Module Parameters
    std::atomic<float>* decayParamater = nullptr;
    std::atomic<float>* predelayParamater = nullptr;
    std::atomic<float>* distanceParamater = nullptr;
    std::atomic<float>* widthParamater = nullptr;
    std::atomic<float>* reverbLowCutParamater = nullptr;
    std::atomic<float>* reverbHighCutParamater = nullptr;
    std::atomic<float>* reverbMixParamater = nullptr;

    // Compressor Module Parameters
    std::atomic<float>* thresholdParameter = nullptr;
    std::atomic<float>* ratioParameter = nullptr;
    std::atomic<float>* attackParameter = nullptr;
    std::atomic<float>* releaseParamter = nullptr;
    std::atomic<float>* lowCutSidechainParameter = nullptr;
    std::atomic<float>* highCutSidechainParameter = nullptr;
    std::atomic<float>* compressorMixParameter = nullptr;
    std::atomic<float>* compressorOutputParameter = nullptr;

    // Equalizer Module Parameters
    std::atomic<float>* equalizerMixParameter = nullptr;
    std::atomic<float>* equalizerOutputParameter = nullptr;

    AudioSampleBuffer wBuffer;

    Reverb reverbL;
    Reverb reverbR;
    Reverb::Parameters reverbLParameters;
    Reverb::Parameters reverbRParameters;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveBlendAudioProcessor)
};
