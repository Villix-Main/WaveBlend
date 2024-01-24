/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaveBlendAudioProcessor::WaveBlendAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#else
    :
#endif
    parameters(*this, nullptr, Identifier("WaveBlend"),
        {
            /* UI State Parameters */
            std::make_unique<AudioParameterBool>("reverb_enabled", "Reverb Enabled", false),
            std::make_unique<AudioParameterBool>("compressor_enabled", "Compressor Enabled", false),
            std::make_unique<AudioParameterBool>("equalizer_enabled", "Equalizer Enabled", false),
            std::make_unique<AudioParameterFloat>("module_buttons_order", "Module Buttons Order", 
            NormalisableRange{0.f, 999999999.f, 1.f}, 0),

            /* Main Plugin Parameters */
            std::make_unique<AudioParameterFloat>("plugin_output", "Output",
            NormalisableRange{-20.f, 10.f, .05f}, 0.f),
            std::make_unique<AudioParameterFloat>("plugin_mix", "Mix",
            NormalisableRange{0.f, 100.f, .5f}, 100.f),


            /* Reverb Module Parameters */
            std::make_unique<AudioParameterFloat>("decay", "Decay",
            NormalisableRange{0.2f, 15.f, 0.05f}, 2.f),
            std::make_unique<AudioParameterFloat>("predelay", "Predelay",
            NormalisableRange{0.f, 500.f, 1.f}, 0.f),
            std::make_unique<AudioParameterFloat>("distance", "Distance",
            NormalisableRange{0.f, 100.f, 1.f}, 0.f),
            std::make_unique<AudioParameterFloat>("width", "width",
            NormalisableRange{0.f, 100.f, 1.f}, 50.f),
            std::make_unique<AudioParameterFloat>("reverb_lowcut_frequency", "Lowcut Frequency",
            NormalisableRange{20.f, 2000.f, 1.f, 0.2f, false}, 20.f),
            std::make_unique<AudioParameterFloat>("reverb_highcut_frequency", "Highcut Frequency",
            NormalisableRange{200.f, 20000.f, 1.f, 0.2f, false}, 20000.f),
            std::make_unique<AudioParameterFloat>("reverb_mix", "Mix",
            NormalisableRange{0.f, 100.f, 1.f}, 100.f),

            /* Compressor Module Parameters */
            std::make_unique<AudioParameterFloat>("threshold", "Threshold",
            NormalisableRange{-25.f, 0.f, 0.05f}, -3.f),
            std::make_unique<AudioParameterFloat>("ratio", "Ratio",
            NormalisableRange{1.f, 30.f, 0.5f}, 2.f),
            std::make_unique<AudioParameterFloat>("attack", "Attack",
            NormalisableRange{5.f, 80.f, 0.5f}, 15.f),
            std::make_unique<AudioParameterFloat>("release", "Release",
            NormalisableRange{2.f, 500.f, 0.5f}, 50.f),
            std::make_unique<AudioParameterFloat>("lowcut_sidechain", "Lowcut Frequency",
            NormalisableRange{20.f, 2000.f, 1.f, 0.2f, false}, 20.f),
            std::make_unique<AudioParameterFloat>("highcut_sidechain", "Highcut Frequency",
            NormalisableRange{200.f, 20000.f, 1.f, 0.2f, false}, 20000.f),
            std::make_unique<AudioParameterFloat>("compressor_mix", "Mix",
            NormalisableRange{0.f, 100.f, 1.f}, 100.f),
            std::make_unique<AudioParameterFloat>("compressor_output", "Output",
            NormalisableRange{-15.f, 10.f, 0.05f}, 0.f),

            /* Equalizer Module Parameter */
            std::make_unique<AudioParameterFloat>("equalizer_mix", "Mix",
            NormalisableRange{0.f, 100.f, 1.f}, 100.f),
            std::make_unique<AudioParameterFloat>("equalizer_output", "Output",
            NormalisableRange{-15.f, 10.f, 0.05f}, 0.f)

        })
{
        // UI State
        reverbEnabledParamter = parameters.getRawParameterValue("reverb_enabled");
        compressorEnabledParamter = parameters.getRawParameterValue("compressor_enabled");
        equalizerEnabledParamter = parameters.getRawParameterValue("equalizer_enabled");
        moduleButtonsOrder = parameters.getRawParameterValue("module_buttons_order");

        // Main Plugin Parameters
        pluginOutputParameter = parameters.getRawParameterValue("plugin_output");
        pluginMixParameter = parameters.getRawParameterValue("plugin_mix");


        // Reverb Parameters
        decayParamater = parameters.getRawParameterValue("decay");
        predelayParamater = parameters.getRawParameterValue("predelay");
        distanceParamater = parameters.getRawParameterValue("distance");
        widthParamater = parameters.getRawParameterValue("width");
        reverbLowCutParamater = parameters.getRawParameterValue("reverb_lowcut_frequency");
        reverbHighCutParamater = parameters.getRawParameterValue("reverb_highcut_frequency");
        reverbMixParamater = parameters.getRawParameterValue("reverb_mix");

        // Compressor Parameters
        thresholdParameter = parameters.getRawParameterValue("threshold");
        predelayParamater = parameters.getRawParameterValue("ratio");
        attackParameter = parameters.getRawParameterValue("attack");
        releaseParamter = parameters.getRawParameterValue("release");
        lowCutSidechainParameter = parameters.getRawParameterValue("lowcut_sidechain");
        highCutSidechainParameter = parameters.getRawParameterValue("highcut_sidechain");
        compressorMixParameter = parameters.getRawParameterValue("compressor_mix");
        compressorOutputParameter = parameters.getRawParameterValue("compressor_output");

        // Equalizer Parameters
        equalizerMixParameter = parameters.getRawParameterValue("equalizer_mix");
        equalizerOutputParameter = parameters.getRawParameterValue("equalizer_output");
}

WaveBlendAudioProcessor::~WaveBlendAudioProcessor()
{
}

//==============================================================================
const juce::String WaveBlendAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WaveBlendAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WaveBlendAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WaveBlendAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WaveBlendAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WaveBlendAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WaveBlendAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WaveBlendAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String WaveBlendAudioProcessor::getProgramName (int index)
{
    return {};
}

void WaveBlendAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void WaveBlendAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    dsp::ProcessSpec spec;

    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    reverb.prepare(spec);

    parameters.addParameterListener("reverb_enabled", this);
    parameters.addParameterListener("compressor_enabled", this);
    parameters.addParameterListener("equalizer_enabled", this);

    parameters.addParameterListener("decay", this);
    parameters.addParameterListener("predelay", this);
    parameters.addParameterListener("distance", this);
    parameters.addParameterListener("width", this);
    parameters.addParameterListener("reverb_lowcut_frequency", this);
    parameters.addParameterListener("reverb_highcut_frequency", this);
    parameters.addParameterListener("reverb_mix", this);
    setReverbParams();
}

void WaveBlendAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WaveBlendAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void WaveBlendAudioProcessor::parameterChanged(const String& parameterID, float newValue)
{
    if (parameterID.contains("enabled"))
    {

    }

    setReverbParams();
}

void WaveBlendAudioProcessor::setReverbParams()
{
    revParams.damping = 0.7f;
    revParams.roomSize = jmap(decayParamater->load(), 0.2f, 15.f, 0.f, 1.0f);
    revParams.width = jmap(widthParamater->load(), 0.f, 100.f, 0.f, 1.0f);
    revParams.wetLevel = reverbMixParamater->load() * 0.01;
    revParams.dryLevel = 1.0f;
}

void WaveBlendAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    if (reverbEnabledParamter->load())
    {
        reverb.setParameters(revParams);

        dsp::AudioBlock<float> block(buffer);
        dsp::ProcessContextReplacing<float> ctx(block);
        reverb.process(ctx);
    }

    /*
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        
    }*/


}

//==============================================================================
bool WaveBlendAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* WaveBlendAudioProcessor::createEditor()
{
    return new WaveBlendAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void WaveBlendAudioProcessor::getStateInformation (juce::MemoryBlock& destData) 
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void WaveBlendAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(ValueTree::fromXml(*xmlState));
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WaveBlendAudioProcessor();
}
