#include "AudioCallback.h"

#include "Schemas/AppSchema.h"

AudioCallback::AudioCallback (ValueTree theAppState,
                              AudioPlayer& thePlayer)
    : AudioProcessorPlayer(),
      appState (theAppState),
      player (thePlayer)
{
    setProcessor (&player);
    startTimerHz (60);
}

AudioCallback::~AudioCallback() { stopTimer(); }

void AudioCallback::timerCallback()
{
    auto state = player.getState();
    if (state.currentSample != prevState.currentSample)
        appState.setProperty (
            AppSchema::currentSample, state.currentSample, nullptr);
    if (state.playing != prevState.playing)
        appState.setProperty (AppSchema::playing, state.playing, nullptr);
    prevState = state;
}
