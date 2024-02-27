/*
  ==============================================================================

    SimpleFilter.cpp
    Created: 27 Feb 2024 9:13:44am
    Author:  martinezd

  ==============================================================================
*/

#include "SimpleFilter.h"



void SimpleFilter::setCutoffFrequency(float frequency)
{
    this->cutoffFrequency = frequency;
}

void SimpleFilter::setSampleRate(float sampleRate)
{
    this->sampleRate = sampleRate;
}


void SimpleFilter::processBlock(AudioBuffer<float>& buffer, MidiBuffer&, bool isHighpass)
{
	constexpr auto PI = 3.14159265358979323846;

	dnBuffer.resize(buffer.getNumChannels(), 0.f);
	const auto sign = isHighpass ? -1.f : 1.f;

	const auto tan = std::tan(PI * cutoffFrequency / sampleRate);
	const auto a1 = (tan - 1.f) / (tan + 1.f);

	for (auto channel = 0; channel < buffer.getNumChannels(); ++channel)
	{
		auto channelSamples = buffer.getWritePointer(channel);

		for (auto i = 0; i < buffer.getNumSamples(); ++i)
		{
			const auto inputSample = channelSamples[i];
			const auto allpassFilteredSample = a1 * inputSample + dnBuffer[channel];
			dnBuffer[channel] = inputSample - a1 * allpassFilteredSample;

			const auto filteredOutput = 0.5f * (inputSample + sign * allpassFilteredSample);

			channelSamples[i] = filteredOutput;
		}
	}
}