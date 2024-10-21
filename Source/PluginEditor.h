#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LuluDial.h"


class PappaAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PappaAudioProcessorEditor (PappaAudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~PappaAudioProcessorEditor() override;
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    PappaAudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& valueTreeState;
    
    LuluDialLaf         luluDialLaf { false };
    LuluDial            sliderFlip;
    LuluDial            sliderMute;
    LuluDial            sliderFeedback;
    LuluDial            sliderCutoff;
    LuluDial            sliderQ;
    juce::Label         labelTitle  { "label", "pappa by @xinisnot" };
    juce::TooltipWindow tooltipWindow;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderFlipAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderMuteAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderFeedbackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderCutoffAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderQAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PappaAudioProcessorEditor)
};
