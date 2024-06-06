/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


static AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    auto percentFormat = [](float value, int) {
        return String(value, 1) + " %";
        };

    AudioProcessorValueTreeState::ParameterLayout layout
    {
            /* UI State Parameters */
            std::make_unique<AudioParameterBool>("reverb_enabled", "Reverb Enabled", false),
            std::make_unique<AudioParameterBool>("compressor_enabled", "Compressor Enabled", false),
            std::make_unique<AudioParameterBool>("equalizer_enabled", "Equalizer Enabled", false),
            std::make_unique<AudioParameterFloat>("current_solo_module", "Current Solo Module",
            NormalisableRange{0.f, 4.f, 1.f}, 0.f),
            std::make_unique<AudioParameterBool>("reverb_bypass", "Reverb Bypass", false),
            std::make_unique<AudioParameterBool>("compressor_bypass", "Compressor Bypass", false),
            std::make_unique<AudioParameterBool>("equalizer_bypass", "Equalizer Bypass", false),
            std::make_unique<AudioParameterFloat>("ui_state_value", "UI State Value",
            NormalisableRange{0.f, 999999999.f, 1.f}, 0.f), 

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
			std::make_unique<AudioParameterFloat>("damping", "Damping",
			NormalisableRange{0.f, 100.f, 1.f}, 0.f, String(), AudioProcessorParameter::genericParameter,
            percentFormat, nullptr),
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
			NormalisableRange{-25.f, 20.f, 0.05f}, 0.f),

			/* Equalizer Module Parameter */
			std::make_unique<AudioParameterFloat>("equalizer_sub_hz", "Equalizer Sub Hz",
			NormalisableRange{-5.f, 5.f, .05f}, 0.f),
			std::make_unique<AudioParameterFloat>("equalizer_40_hz", "Equalizer 40 Hz",
			NormalisableRange{-5.f, 5.f, .05f}, 0.f),
			std::make_unique<AudioParameterFloat>("equalizer_160_hz", "Equalizer 160 Hz",
			NormalisableRange{-5.f, 5.f, .05f}, 0.f),
			std::make_unique<AudioParameterFloat>("equalizer_650_hz", "Equalizer 650 Hz",
			NormalisableRange{-5.f, 5.f, .05f}, 0.f),
			std::make_unique<AudioParameterFloat>("equalizer_2500_hz", "Equalizer 2500 Hz",
			NormalisableRange{-5.f, 5.f, .05f}, 0.f),
			std::make_unique<AudioParameterFloat>("equalizer_air_gain", "Equalizer Air Gain",
			NormalisableRange{0.f, 10.f, .1f}, 0.f),
			std::make_unique<AudioParameterFloat>("equalizer_air_band", "Equalizer Air Band",
			NormalisableRange{2.5f, 21.f, .1f},2.5f),
			std::make_unique<AudioParameterFloat>("equalizer_mix", "Mix",
			NormalisableRange{0.f, 100.f, 1.f}, 100.f),
			std::make_unique<AudioParameterFloat>("equalizer_output", "Output",
			NormalisableRange{-15.f, 10.f, 0.05f}, 0.f)
    };

    return layout;
}


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
    parameters(*this, nullptr, Identifier("WaveBlend"), createParameterLayout())
{
        // UI State
        reverbEnabledParamter = parameters.getRawParameterValue("reverb_enabled");
        compressorEnabledParamter = parameters.getRawParameterValue("compressor_enabled");
        equalizerEnabledParamter = parameters.getRawParameterValue("equalizer_enabled");
        currentSoloModuleParameter = parameters.getRawParameterValue("current_solo_module");
        reverbBypassParameter = parameters.getRawParameterValue("reverb_bypass");
        compressorBypassParameter = parameters.getRawParameterValue("compressor_bypass");
        equalizerBypassParameter = parameters.getRawParameterValue("equalizer_bypass");
        uiStateValue = parameters.getRawParameterValue("ui_state_value");

        // Main Plugin Parameters
        pluginOutputParameter = parameters.getRawParameterValue("plugin_output");
        pluginMixParameter = parameters.getRawParameterValue("plugin_mix");


        // Reverb Parameters
        decayParamater = parameters.getRawParameterValue("decay");
        predelayParamater = parameters.getRawParameterValue("predelay");
        dampingParameter = parameters.getRawParameterValue("damping");
        widthParamater = parameters.getRawParameterValue("width");
        reverbLowCutParamater = parameters.getRawParameterValue("reverb_lowcut_frequency");
        reverbHighCutParamater = parameters.getRawParameterValue("reverb_highcut_frequency");
        reverbMixParamater = parameters.getRawParameterValue("reverb_mix");

        // Compressor Parameters
        thresholdParameter = parameters.getRawParameterValue("threshold");
        ratioParameter = parameters.getRawParameterValue("ratio");
        predelayParamater = parameters.getRawParameterValue("ratio");
        attackParameter = parameters.getRawParameterValue("attack");
        releaseParamter = parameters.getRawParameterValue("release");
        lowCutSidechainParameter = parameters.getRawParameterValue("lowcut_sidechain");
        highCutSidechainParameter = parameters.getRawParameterValue("highcut_sidechain");
        compressorMixParameter = parameters.getRawParameterValue("compressor_mix");
        compressorOutputParameter = parameters.getRawParameterValue("compressor_output");

        // Equalizer Parameters
        hzSubParameter = parameters.getRawParameterValue("equalizer_sub_hz");
        hz40Parameter = parameters.getRawParameterValue("equalizer_40_hz");
        hz160Parameter = parameters.getRawParameterValue("equalizer_160_hz");
        hz650Parameter = parameters.getRawParameterValue("equalizer_650_hz");
        hz2500Parameter = parameters.getRawParameterValue("equalizer_2500_hz");
        airGainParameter = parameters.getRawParameterValue("equalizer_air_gain");
        airBandParameter = parameters.getRawParameterValue("equalizer_air_band");
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
    this->sampleRate = sampleRate;

    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    reverb.prepare(spec);
    compressor.prepare(spec);

    pluginMixer.prepare(spec);
    reverbMixer.prepare(spec);
    compressorMixer.prepare(spec);
    equalizerMixer.prepare(spec);
    
    finalLimiter.prepare(spec);
    finalLimiter.setRelease(50);
    finalLimiter.setThreshold(-0.03);
    
    reverbLowPassFilter.setSampleRate(sampleRate);
    reverbHighPassFilter.setSampleRate(sampleRate);

    compressorGain.prepare(spec);
    pluginGain.prepare(spec);

    filter.prepare(spec);


    // Plugin State parameter listeners
    parameters.addParameterListener("reverb_enabled", this);
    parameters.addParameterListener("compressor_enabled", this);
    parameters.addParameterListener("equalizer_enabled", this);
    parameters.addParameterListener("current_solo_module", this);
    parameters.addParameterListener("reverb_bypass", this);
    parameters.addParameterListener("compressor_bypass", this);
    parameters.addParameterListener("equalizer_bypass", this);
    parameters.addParameterListener("ui_state_value", this);

    // Reverb parameter listeners
    parameters.addParameterListener("decay", this);
    parameters.addParameterListener("predelay", this);
    parameters.addParameterListener("damping", this);
    parameters.addParameterListener("width", this);
    parameters.addParameterListener("reverb_lowcut_frequency", this);
    parameters.addParameterListener("reverb_highcut_frequency", this);
    parameters.addParameterListener("reverb_mix", this);

    // Compressor parameter listeners
    parameters.addParameterListener("threshold", this);
    parameters.addParameterListener("ratio", this);
    parameters.addParameterListener("attack", this);
    parameters.addParameterListener("release", this);
    parameters.addParameterListener("lowcut_sidechain", this);
    parameters.addParameterListener("highcut_sidechain", this);
    parameters.addParameterListener("compressor_mix", this);
    parameters.addParameterListener("compressor_output", this);

    // Equalizer parameter listeners
	parameters.addParameterListener("equalizer_sub_hz", this);
	parameters.addParameterListener("equalizer_40_hz", this);
	parameters.addParameterListener("equalizer_160_hz", this);
	parameters.addParameterListener("equalizer_650_hz", this);
	parameters.addParameterListener("equalizer_2500_hz", this);
	parameters.addParameterListener("equalizer_air_gain", this);
	parameters.addParameterListener("equalizer_air_band", this);


    //*reverbEnabledParamter = lastReverbEnableState;   
    setReverbParams();

	currentBandCoefficent = dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, 20, 1.1, 1.0);
	*filter.get<0>().state = *currentBandCoefficent;
	currentBandCoefficent = dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 40, 1.1, 1.0);
	*filter.get<1>().state = *currentBandCoefficent;
	currentBandCoefficent = dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 160, 1.1, 1.0);
	*filter.get<2>().state = *currentBandCoefficent;
	currentBandCoefficent = dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 650, 1.1, 1.0);
	*filter.get<3>().state = *currentBandCoefficent;
	currentBandCoefficent = dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 2500, 1.1, 1.0);
	*filter.get<4>().state = *currentBandCoefficent;
	currentBandCoefficent = dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, 2500, 1.1, 1.0);
	*filter.get<5>().state = *currentBandCoefficent;
}

void WaveBlendAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    lastReverbEnableState = reverbEnabledParamter->load();
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
	if (parameterID.contains("equalizer_sub_hz"))
	{
		currentBandCoefficent = dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, 20, 1.1, 1 + convertToGainFactor(newValue));
		*filter.get<0>().state = *currentBandCoefficent;
	}
	else if (parameterID.contains("equalizer_40_hz"))
	{
		currentBandCoefficent = dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 40, 1.1, 1 + convertToGainFactor(newValue));
		*filter.get<1>().state = *currentBandCoefficent;
	}
	else if (parameterID.contains("equalizer_160_hz"))
	{
		currentBandCoefficent = dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 160, 1.1, 1 + convertToGainFactor(newValue));
		*filter.get<2>().state = *currentBandCoefficent;
	}
	else if (parameterID.contains("equalizer_650_hz"))
	{
		currentBandCoefficent = dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 650, 1.1, 1 + convertToGainFactor(newValue));
		*filter.get<3>().state = *currentBandCoefficent;
	}
	else if (parameterID.contains("equalizer_2500_hz"))
	{
		currentBandCoefficent = dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 2500, 1.1, 1 + convertToGainFactor(newValue));
		*filter.get<4>().state = *currentBandCoefficent;
	}
    else if (parameterID.contains("equalizer_air_gain") || parameterID.contains("equalizer_air_band"))
	{
		float cutoffFreq = airBandParameter->load() * 1000;
        float gainFactor = airGainParameter->load() * 0.09f;
		currentBandCoefficent = dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, cutoffFreq, 1.1, 1 + gainFactor);
		*filter.get<5>().state = *currentBandCoefficent;
	}


	setReverbParams();

	setCompressorParams();

}
float WaveBlendAudioProcessor::convertToGainFactor(float gain)
{
	if (gain < 0)
		return gain * 0.09f;
    else
        return gain * .15f;
}


void WaveBlendAudioProcessor::setReverbParams()
{
    revParams.damping = jmap(dampingParameter->load(), 0.f, 100.f, 0.f, 1.0f);
    revParams.roomSize = jmap(decayParamater->load(), 0.2f, 15.f, 0.f, 1.0f);
    revParams.width = jmap(widthParamater->load(), 0.f, 100.f, 0.f, 1.0f);
    revParams.wetLevel = 1.0;
    revParams.dryLevel = 0.0;
    //revParams.dryLevel = 1.f - (reverbMixParamater->load() * 0.01);
}
void WaveBlendAudioProcessor::setCompressorParams()
{
    compressor.setThreshold(thresholdParameter->load());
    compressor.setRatio(ratioParameter->load());
    compressor.setAttack(attackParameter->load());
    compressor.setRelease(releaseParamter->load());
}

void WaveBlendAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    
    AudioBuffer<float> wetBuff;
    wetBuff.makeCopyOf(buffer, false);

    AudioBuffer<float> revBuff;
    revBuff.makeCopyOf(wetBuff, false);


    dsp::AudioBlock<float> wetBlock(wetBuff);
    dsp::ProcessContextReplacing<float> wetCtx(wetBlock);

    dsp::AudioBlock<float> revBlock(revBuff);
    dsp::ProcessContextReplacing<float> revCtx(revBlock);

    dsp::AudioBlock<float> dryBlock(buffer);
    dsp::ProcessContextReplacing<float> dryCtx(dryBlock);
    
    int currentSoloModule = currentSoloModuleParameter->load();
    // Processor the reverb first if its currently enabled and opened
    if (reverbEnabledParamter->load() && !reverbBypassParameter->load() && (currentSoloModule == 0 || currentSoloModule == 1))
    {
        reverb.setParameters(revParams);

        reverb.process(revCtx);
        

		reverbLowPassFilter.setCutoffFrequency(reverbHighCutParamater->load());
        reverbLowPassFilter.processBlock(revBuff, midiMessages, false);
        reverbHighPassFilter.setCutoffFrequency(reverbLowCutParamater->load());
        reverbHighPassFilter.processBlock(revBuff, midiMessages, true);
        

		reverbMixer.pushDrySamples(revCtx.getOutputBlock());
		reverbMixer.setWetMixProportion(1.f - (reverbMixParamater->load() * 0.01));
		reverbMixer.setWetLatency(getLatencySamples());
		reverbMixer.setMixingRule(dsp::DryWetMixingRule::linear);
		reverbMixer.mixWetSamples(wetCtx.getOutputBlock());
    } 
    
	AudioBuffer<float> compressorBuff;
	compressorBuff.makeCopyOf(wetBuff, false);

	dsp::AudioBlock<float> compressorBlock(compressorBuff);
	dsp::ProcessContextReplacing<float> compressorCtx(compressorBlock);

    // Then process the compressor if its enabled and opened
    if (compressorEnabledParamter->load() && !compressorBypassParameter->load() && (currentSoloModule == 0 || currentSoloModule == 2))
    {
        compressor.process(compressorCtx);

        compressorGain.setGainDecibels(compressorOutputParameter->load());
        compressorGain.process(compressorCtx);
        

        compressorMixer.pushDrySamples(compressorCtx.getOutputBlock());
        compressorMixer.setWetMixProportion(1.f - (compressorMixParameter->load() * 0.01));
        compressorMixer.setWetLatency(getLatencySamples());
        compressorMixer.setMixingRule(dsp::DryWetMixingRule::balanced);
        compressorMixer.mixWetSamples(wetCtx.getOutputBlock());    
    }

	AudioBuffer<float> equalizerBuff;
	equalizerBuff.makeCopyOf(wetBuff, false);

	dsp::AudioBlock<float> equalizerBlock(equalizerBuff);
	dsp::ProcessContextReplacing<float> equalizerCtx(equalizerBlock);

    // Then finally the equalizer if its opened and enabled
	if (equalizerEnabledParamter->load() && !equalizerBypassParameter->load() && (currentSoloModule == 0 || currentSoloModule == 3))
	{
		filter.process(equalizerCtx);

		equalizerMixer.pushDrySamples(equalizerCtx.getOutputBlock());
		equalizerMixer.setWetMixProportion(1.f - (equalizerMixParameter->load() * 0.01));
		equalizerMixer.setWetLatency(getLatencySamples());
		equalizerMixer.setMixingRule(dsp::DryWetMixingRule::balanced);
		equalizerMixer.mixWetSamples(wetCtx.getOutputBlock());

	}

    // Process the mixing of the orignal signal and the plugin signal together
    pluginMixer.pushDrySamples(wetCtx.getOutputBlock());
    pluginMixer.setWetMixProportion(1.f - (pluginMixParameter->load() * 0.01));
    pluginMixer.setWetLatency(getLatencySamples());
    pluginMixer.setMixingRule(dsp::DryWetMixingRule::linear);
    pluginMixer.mixWetSamples(dryCtx.getOutputBlock());
        
    
    /*filter.setCutoffFrequency(500);
    filter.processBlock(buffer, midiMessages);*/

    // Set final gain
    pluginGain.setGainDecibels(pluginOutputParameter->load() - 3.9);
    pluginGain.process(dryCtx);
    
    // Add a limiter to make sure final gain does not exceed the ceiling
    finalLimiter.process(dryCtx);
    /*
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
    auto t = reverbEnabledParamter->load();
	for (auto* childElement = xml->getFirstChildElement(); childElement != nullptr; childElement = childElement->getNextElement())
	{
		//String test = childElement->getAttributeValue(0);

		auto elementTagName = childElement->getTagName();

		if (childElement->getStringAttribute("id") == "ui_state_value")
		{
            childElement->setAttribute("value", *uiStateValue);
		}

        if (childElement->getStringAttribute("id") == "reverb_enabled")
        {
            childElement->setAttribute("value", *reverbEnabledParamter);
        }

        if (childElement->getStringAttribute("id") == "compressor_enabled")
        {
            childElement->setAttribute("value", *compressorEnabledParamter);
        }

        if (childElement->getStringAttribute("id") == "current_solo_module")
        {
            childElement->setAttribute("value", *currentSoloModuleParameter);
        }

	}

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
