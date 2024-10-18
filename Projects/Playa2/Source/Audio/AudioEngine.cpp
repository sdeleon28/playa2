#include "AudioEngine.h"

#include "Schemas/AppSchema.h"

AudioEngine::AudioEngine (ValueTree theAppState)
    : appState (theAppState), audioCallback (theAppState, rampProcessor)
{
    appState.addListener (this);
    audioDeviceManager.initialise (0, 2, nullptr, true, {}, nullptr);
    DBG ("Device name: "
         << audioDeviceManager.getCurrentAudioDevice()->getName());
    audioDeviceManager.addAudioCallback (&audioCallback);
}

AudioEngine::~AudioEngine()
{
    appState.removeListener (this);
    audioDeviceManager.removeAudioCallback (&audioCallback);
}

// I probably don't need this at this level
void AudioEngine::valueTreePropertyChanged (
    ValueTree& treeWhosePropertyHasChanged,
    const Identifier& property)
{
    if (treeWhosePropertyHasChanged != appState)
        return;
    // TODO
}
