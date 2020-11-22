/*
  ==============================================================================

    AutoPan.h
    Created: 22 Nov 2020 3:07:59pm
    Author:  Mathis Raibaud

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class AutoPan : public juce::dsp::ProcessorBase
{
public:
    
    AutoPan();
    
    void prepare(const juce::dsp::ProcessSpec& spec) override;
    virtual void process (const juce::dsp::ProcessContextReplacing<float>& context) override;
    virtual void reset() override;
    
    void setFrequency(float frequency);
    
private:
    
    float sampleRate;
    std::array<juce::dsp::Oscillator<float>, 2> lfos;
    std::array<juce::dsp::Gain<float>, 2> gains;
    
};
