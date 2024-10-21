#include "PluginProcessor.h"
#include "PluginEditor.h"


PappaAudioProcessorEditor::PappaAudioProcessorEditor (PappaAudioProcessor& p) : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(mainComponent);
    setSize(mainComponent.getWidth(), mainComponent.getHeight());
}

PappaAudioProcessorEditor::~PappaAudioProcessorEditor()
{
}

void PappaAudioProcessorEditor::paint (juce::Graphics& g)
{
}

void PappaAudioProcessorEditor::resized()
{
}
