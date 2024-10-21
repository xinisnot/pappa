#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MainComponent.h"


class PappaAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PappaAudioProcessorEditor(PappaAudioProcessor&);
    ~PappaAudioProcessorEditor() override;
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    PappaAudioProcessor& audioProcessor;
    MainComponent mainComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PappaAudioProcessorEditor)
};
