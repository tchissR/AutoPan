/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AutoPanAudioProcessorEditor::AutoPanAudioProcessorEditor (AutoPanAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    addAndMakeVisible(&amountSlider);
    amountSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    amountSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 20);
    amountSlider.setTextValueSuffix(" %");
    amountSlider.setRange(0, 100);
    amountSlider.onValueChange = [&]() {audioProcessor.setAmount(amountSlider.getValue()/100.f);};
    amountSlider.setValue(0);
    amountSlider.setNumDecimalPlacesToDisplay(2);
    amountSlider.setBounds(20, 20, 100, 100);
    
    addAndMakeVisible(&frequencySlider);
    frequencySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    frequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 20);
    frequencySlider.setTextValueSuffix(" Hz");
    frequencySlider.setRange(0.05f, 90.f);
    frequencySlider.setSkewFactorFromMidPoint(2.25f);
    frequencySlider.onValueChange = [&]() {audioProcessor.setFrequency(frequencySlider.getValue());};
    frequencySlider.setValue(1.f);
    frequencySlider.setNumDecimalPlacesToDisplay(2);
    frequencySlider.setBounds(140, 20, 100, 100);
    
    addAndMakeVisible(&phaseSlider);
    phaseSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    phaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 20);
    phaseSlider.setTextValueSuffix(juce::String::fromUTF8("\u00B0"));
    phaseSlider.setRange(0, 360);
    phaseSlider.onValueChange = [&]() {audioProcessor.setPhase(phaseSlider.getValue());};
    phaseSlider.setValue(180);
    phaseSlider.setNumDecimalPlacesToDisplay(0);
    phaseSlider.setBounds(260, 20, 100, 100);
}

AutoPanAudioProcessorEditor::~AutoPanAudioProcessorEditor()
{
}

//==============================================================================
void AutoPanAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void AutoPanAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
