/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "UIState.h"
#include "SimpleFilter.h"

//==============================================================================
/**
*/
class WaveBlendAudioProcessor  : public juce::AudioProcessor,
    private AudioProcessorValueTreeState::Listener
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

    void parameterChanged(const String& parameterID, float newValue);
    void setReverbParams();
    void setCompressorParams();
    
    // Current UIState of plugin
    UIState currentState;
    std::atomic<float>* reverbEnabledParamter = nullptr;
    std::atomic<float>* compressorEnabledParamter = nullptr;
    std::atomic<float>* equalizerEnabledParamter = nullptr;
    std::atomic<float>* currentSoloModuleParameter = nullptr;
    std::atomic<float>* reverbBypassParameter = nullptr;
    std::atomic<float>* compressorBypassParameter = nullptr;
    std::atomic<float>* equalizerBypassParameter = nullptr;
    std::atomic<float>* uiStateValue = nullptr;
    bool lastReverbEnableState = false;

    // Main Plugin Parameters
    std::atomic<float>* pluginOutputParameter = nullptr;
    std::atomic<float>* pluginMixParameter = nullptr;

    // Reverb Module Parameters
    std::atomic<float>* decayParamater = nullptr;
    std::atomic<float>* predelayParamater = nullptr;
    std::atomic<float>* dampingParameter = nullptr;
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
    std::atomic<float>* hzSubParameter = nullptr;
    std::atomic<float>* hz40Parameter = nullptr;
    std::atomic<float>* hz160Parameter = nullptr;
    std::atomic<float>* hz650Parameter = nullptr;
    std::atomic<float>* hz2500Parameter = nullptr;
    std::atomic<float>* airGainParameter = nullptr;
    std::atomic<float>* airBandParameter = nullptr;
    std::atomic<float>* equalizerMixParameter = nullptr;
    std::atomic<float>* equalizerOutputParameter = nullptr;

    dsp::IIR::Coefficients<float>::Ptr currentBandCoefficent;
    //dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> filter;

    using FilterBand = dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>>;
    dsp::ProcessorChain<FilterBand, FilterBand, FilterBand, FilterBand, FilterBand> filter;

    AudioSampleBuffer wBuffer;

    dsp::Reverb reverb;
    dsp::Reverb::Parameters revParams;

    dsp::Compressor<float> compressor;


    SimpleFilter reverbLowPassFilter;
    SimpleFilter reverbHighPassFilter;

    // Mixers
    dsp::DryWetMixer<float> pluginMixer;
    dsp::DryWetMixer<float> reverbMixer;
    dsp::DryWetMixer<float> compressorMixer;
    dsp::DryWetMixer<float> equalizerMixer;
    
    // Output Gain
    dsp::Gain<float> compressorGain;
    dsp::Gain<float> pluginGain;

    // Main limiter
    dsp::Limiter<float> finalLimiter;

    // Sample rate
    double sampleRate;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveBlendAudioProcessor)
};
