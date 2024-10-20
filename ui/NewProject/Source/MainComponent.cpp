#include <JuceHeader.h>
#include "MainComponent.h"


MainComponent::MainComponent()
{
    setSize(400, 95);
    addAndMakeVisible(sliderFlip);
    addAndMakeVisible(sliderMute);
    addAndMakeVisible(sliderFeedback);
    addAndMakeVisible(sliderCutoff);
    addAndMakeVisible(sliderQ);
    addAndMakeVisible(labelTitle);
    
    sliderFlip.setBounds    (0,   0,   80,  80);
    sliderMute.setBounds    (80,  0,   80,  80);
    sliderFeedback.setBounds(160, 0,   80,  80);
    sliderCutoff.setBounds  (240, 0,   80,  80);
    sliderQ.setBounds       (320, 0,   80,  80);
    labelTitle.setBounds    (0,   80,  400, 15);


    labelTitle.setFont(juce::FontOptions(11.00f, juce::Font::plain));
    labelTitle.setJustificationType (juce::Justification::topRight);
    labelTitle.setEditable(false, false, false);
    labelTitle.setColour(juce::Label::backgroundColourId, juce::Colour (0x00000000));
    labelTitle.setColour(juce::Label::textColourId, juce::Colour(0xff606060));
    
    sliderFlip.setTitle             ("flip");
    sliderMute.setTitle             ("mute");
    sliderFeedback.setTitle         ("feedback");
    sliderCutoff.setTitle           ("cutoff");
    sliderQ.setTitle                ("q");
    
    sliderFlip.setName              ("flip");
    sliderMute.setName              ("mute");
    sliderFeedback.setName          ("feedback");
    sliderCutoff.setName            ("cutoff");
    sliderQ.setName                 ("q");
    
    sliderFlip.setTooltip           ("[flip]");
    sliderMute.setTooltip           ("[mute]");
    sliderFeedback.setTooltip       ("[feedback]");
    sliderCutoff.setTooltip         ("[cutoff]");
    sliderQ.setTooltip              ("[q]");
    
    sliderFlip.setLookAndFeel       (&luluDialLaf);
    sliderMute.setLookAndFeel       (&luluDialLaf);
    sliderFeedback.setLookAndFeel   (&luluDialLaf);
    sliderCutoff.setLookAndFeel     (&luluDialLaf);
    sliderQ.setLookAndFeel          (&luluDialLaf);

    sliderFlip.addListener          (this);
    sliderMute.addListener          (this);
    sliderFeedback.addListener      (this);
    sliderCutoff.addListener        (this);
    sliderQ.addListener             (this);
}

MainComponent::~MainComponent()
{
    sliderFlip.setLookAndFeel       (nullptr);
    sliderMute.setLookAndFeel       (nullptr);
    sliderFeedback.setLookAndFeel   (nullptr);
    sliderCutoff.setLookAndFeel     (nullptr);
    sliderQ.setLookAndFeel          (nullptr);
}



void MainComponent::sliderValueChanged(juce::Slider* sliderThatWasMoved)
{
}


void MainComponent::updateSliderForParam(unsigned long index, double value)
{
}


void MainComponent::paint(juce::Graphics& g) { g.fillAll(juce::Colour (0xff2c3337)); }
void MainComponent::resized() {}
