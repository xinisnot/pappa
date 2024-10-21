#include "PluginProcessor.h"
#include "PluginEditor.h"


PappaAudioProcessorEditor::PappaAudioProcessorEditor (PappaAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p),
      audioProcessor (p),
      valueTreeState(vts)
{
    sliderFlipAttachment    .reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "flip",     sliderFlip));
    sliderMuteAttachment    .reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "mute",     sliderMute));
    sliderFeedbackAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "feedback", sliderFeedback));
    sliderCutoffAttachment  .reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "cutoff",   sliderCutoff));
    sliderQAttachment       .reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "q",        sliderQ));
    
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
    
    sliderFlip.setLookAndFeel       (&luluDialLaf);
    sliderMute.setLookAndFeel       (&luluDialLaf);
    sliderFeedback.setLookAndFeel   (&luluDialLaf);
    sliderCutoff.setLookAndFeel     (&luluDialLaf);
    sliderQ.setLookAndFeel          (&luluDialLaf);

    setSize(400, 95);
}

PappaAudioProcessorEditor::~PappaAudioProcessorEditor()
{
    sliderFlip.setLookAndFeel       (nullptr);
    sliderMute.setLookAndFeel       (nullptr);
    sliderFeedback.setLookAndFeel   (nullptr);
    sliderCutoff.setLookAndFeel     (nullptr);
    sliderQ.setLookAndFeel          (nullptr);
}

void PappaAudioProcessorEditor::paint(juce::Graphics& g) { g.fillAll(juce::Colour (0xff2c3337)); }
void PappaAudioProcessorEditor::resized( ){}
