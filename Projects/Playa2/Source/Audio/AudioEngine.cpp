#include "AudioEngine.h"

#include "Schemas/AppSchema.h"

AudioEngine::AudioEngine(ValueTree theAppState)
    : appState(theAppState),
      player(appState),
      audioCallback(theAppState, player) {
  audioDeviceManager.initialise(0, 2, nullptr, true, {}, nullptr);

  DBG("Device name: " << audioDeviceManager.getCurrentAudioDevice()->getName());
  player.prepareToPlay(
      audioDeviceManager.getCurrentAudioDevice()->getCurrentSampleRate(), 4096);
  audioDeviceManager.addAudioCallback(&audioCallback);
}

AudioEngine::~AudioEngine() {
  audioDeviceManager.removeAudioCallback(&audioCallback);
}
