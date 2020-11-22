/*
  ==============================================================================

    AutoPan.cpp
    Created: 22 Nov 2020 3:07:59pm
    Author:  Mathis Raibaud

  ==============================================================================
*/

#include "AutoPan.h"

AutoPan::AutoPan()
{
    lfos[0].initialise([] (float x) { return 0.5f + 0.5f * std::sin(x) ; } );
    lfos[1].initialise([] (float x) { return 0.5f + 0.5f * std::sin(x + juce::MathConstants<float>::pi) ; } );
    lfos[0].setFrequency(2.f);
    lfos[1].setFrequency(2.f);
}

void AutoPan::prepare(const juce::dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate;
    
    for (int i = 0; i < 2; ++i)
    {
        lfos[i].prepare(spec);
        gains[i].prepare(spec);
    }
}

void AutoPan::process(const juce::dsp::ProcessContextReplacing<float> &context)
{
    const auto& inputBlock = context.getInputBlock();
    auto& outputBlock      = context.getOutputBlock();
    const auto numChannels = outputBlock.getNumChannels();
    const auto numSamples  = outputBlock.getNumSamples();
    
    jassert (inputBlock.getNumChannels() == numChannels);
    jassert (inputBlock.getNumChannels() == 2);
    jassert (inputBlock.getNumSamples()  == numSamples);
    
    for (size_t channel = 0; channel < numChannels; ++channel)
    {
        auto* inputSamples = inputBlock.getChannelPointer (channel);
        auto* outputSamples = outputBlock.getChannelPointer (channel);
        
        auto& lfo = lfos[channel];
        auto& gain = gains[channel];

        for (size_t i = 0; i < numSamples; ++i)
        {
            auto lfoValue = lfo.processSample(0);
            auto gainDecibels = juce::jmap(lfoValue, 0.f, 1.f, -100.f, 0.f);
            gain.setGainDecibels(gainDecibels);
            
            outputSamples[i] = gain.processSample(inputSamples[i]);
        }
    }
}

void AutoPan::setFrequency(float frequency)
{
    jassert(juce::isPositiveAndBelow(frequency, sampleRate));
    
    for (auto& lfo : lfos)
        lfo.setFrequency(frequency);
}

void AutoPan::reset()
{
    for (auto& lfo : lfos)
        lfo.reset();
    
    for (auto& gain : gains)
        gain.reset();
}
