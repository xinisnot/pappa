#pragma once

#include <JuceHeader.h>
#include "LuluDial.h"
#include "LuluToggle.h"

class MainComponent  : public juce::Component, public juce::Slider::Listener
{
public:
    MainComponent();
    ~MainComponent() override;
    void paint(juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* sliderThatWasMoved) override;
    void updateSliderForParam(unsigned long index, double value);

private:
    LuluDial            sliderFlip;
    LuluDial            sliderMute;
    LuluDial            sliderFeedback;
    LuluDial            sliderCutoff;
    LuluDial            sliderQ;
    juce::Label         labelTitle              { "label", "pappa by @xinisnot" };
    LuluDialLaf         luluDialLaf             { false };
    juce::TooltipWindow tooltipWindow;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
