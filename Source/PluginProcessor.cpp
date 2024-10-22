#include "PluginProcessor.h"
#include "PluginEditor.h"


PappaAudioProcessor::PappaAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor (BusesProperties().withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
#endif
// initialize AudioProcessorValueTreeState
    , parameters(*this, nullptr, juce::Identifier("pappaParam"), {
        std::make_unique<juce::AudioParameterFloat> (juce::ParameterID {"flip",     1 }, "Flip",     juce::NormalisableRange<float>(0.0f, 255.0f, 1.0f), 0.0f),
        std::make_unique<juce::AudioParameterFloat> (juce::ParameterID {"mute",     1 }, "Mute",     juce::NormalisableRange<float>(0.0f, 255.0f, 1.0f), 0.0f),
        std::make_unique<juce::AudioParameterFloat> (juce::ParameterID {"feedback", 1 }, "Feedback", juce::NormalisableRange<float>(-70.0f, 36.0f), -70.0f),
        std::make_unique<juce::AudioParameterFloat> (juce::ParameterID {"cutoff",   1 }, "Cutoff",   juce::NormalisableRange<float>(0.0f, 1.0f), 0.0f),
        std::make_unique<juce::AudioParameterFloat> (juce::ParameterID {"q",        1 }, "Q",        juce::NormalisableRange<float>(0.0f, 25.0f), 0.0f)
    })
{
    flip     = parameters.getRawParameterValue("flip");
    mute     = parameters.getRawParameterValue("mute");
    feedback = parameters.getRawParameterValue("feedback");
    cutoff   = parameters.getRawParameterValue("cutoff");
    q        = parameters.getRawParameterValue("q");
}

PappaAudioProcessor::~PappaAudioProcessor() {}
juce::AudioProcessorEditor* PappaAudioProcessor::createEditor() { return new PappaAudioProcessorEditor (*this, parameters); }

//==============================================================================

void PappaAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}


void PappaAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    
    if (xmlState.get() != nullptr)
        if(xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================

void PappaAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // prepareToPlay() may be called twice by host.
    if (flagForAllocateMemory) {
        flagForAllocateMemory = false;
        
        fUI  = new MapUI();
        fDSP = new mydsp();
        
        fDSP->init(sampleRate);
        fDSP->buildUserInterface(fUI);

        inputs  = new float*[2];
        outputs = new float*[2];
        
        for (int channel = 0; channel < 2; ++channel) {
            inputs [channel] = new float[samplesPerBlock];
            outputs[channel] = new float[samplesPerBlock];
        }
    }
}

void PappaAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
        for (int i = 0; i < buffer.getNumSamples(); i++)
            inputs[channel][i] = *buffer.getWritePointer(channel,i);

    fUI->setParamValue("flip",     *flip);
    fUI->setParamValue("mute",     *mute);
    fUI->setParamValue("feedback", *feedback);
    fUI->setParamValue("cutoff",   *cutoff);
    fUI->setParamValue("q",        *q);
    
    fDSP->compute(buffer.getNumSamples(),inputs, outputs);
    fDSP->compute(buffer.getNumSamples(),inputs, outputs);

    for (int channel = 0; channel < totalNumOutputChannels; ++channel)
        for (int i = 0; i < buffer.getNumSamples(); i++)
            *buffer.getWritePointer(channel,i) = outputs[channel][i];
}

void PappaAudioProcessor::releaseResources()
{
    // releaseResources() may be called twice by host.
    if (flagForFreeMemory) {
        flagForFreeMemory = false;
        
        delete fDSP;
        delete fUI;

        for (int channel = 0; channel < 2; ++channel) {
            delete[] inputs [channel];
            delete[] outputs[channel];
        }
        delete[]  inputs;
        delete[]  outputs;
    }
}


//==============================================================================


#ifndef JucePlugin_PreferredChannelConfigurations
bool PappaAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}
#endif

const juce::String PappaAudioProcessor::getName() const { return JucePlugin_Name; }
bool PappaAudioProcessor::acceptsMidi() const { return false; }
bool PappaAudioProcessor::producesMidi() const { return false; }
bool PappaAudioProcessor::isMidiEffect() const { return false; }
double PappaAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int PappaAudioProcessor::getNumPrograms() { return 1; }
int PappaAudioProcessor::getCurrentProgram() { return 0; }
void PappaAudioProcessor::setCurrentProgram (int index) {}
const juce::String PappaAudioProcessor::getProgramName (int index) { return {}; }
void PappaAudioProcessor::changeProgramName (int index, const juce::String& newName) {}
bool PappaAudioProcessor::hasEditor() const { return true; }
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new PappaAudioProcessor(); }
