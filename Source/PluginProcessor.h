#pragma once

#include <JuceHeader.h>
#include "../dsp/PappaDsp.h"


class PappaAudioProcessor  : public juce::AudioProcessor
{
public:
    PappaAudioProcessor();
    ~PappaAudioProcessor() override;
    juce::AudioProcessorEditor* createEditor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    #endif

    bool hasEditor() const override;
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

private:
    juce::AudioProcessorValueTreeState parameters;
    
    MapUI*  fUI;
    dsp*    fDSP;
    
    float** inputs;
    float** outputs;
    
    bool flagForAllocateMemory { true };
    bool flagForFreeMemory     { true };
    
    // pointers for parameters (read only)
    std::atomic<float>* flip     = nullptr;
    std::atomic<float>* mute     = nullptr;
    std::atomic<float>* feedback = nullptr;
    std::atomic<float>* cutoff   = nullptr;
    std::atomic<float>* q        = nullptr;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PappaAudioProcessor)
};
