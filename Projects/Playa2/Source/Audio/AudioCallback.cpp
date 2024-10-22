#include "AudioCallback.h"

#include "Schemas/AppSchema.h"

AudioCallback::AudioCallback(ValueTree theAppState, AudioPlayer& thePlayer)
    : AudioProcessorPlayer(), appState(theAppState), player(thePlayer) {
  setProcessor(&player);
  std::thread([this]() {
    while (true) {
      pollPlayerState();
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }).detach();
}

AudioCallback::~AudioCallback() {}

void AudioCallback::pollPlayerState() {
  auto state = player.getState();
  if (state.currentSample != prevState.currentSample)
    appState.setProperty(AppSchema::currentSample, state.currentSample,
                         nullptr);
  if (state.playing != prevState.playing) {
    appState.setProperty(AppSchema::playing, state.playing, nullptr);
  }
  prevState = state;
}
