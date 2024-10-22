#include "AudioEngine.h"

#include "Schemas/AppSchema.h"

AudioEngine::AudioEngine(ValueTree theAppState)
    : appState(theAppState), audioCallback(theAppState, player) {
  appState.addListener(this);
  audioDeviceManager.initialise(0, 2, nullptr, true, {}, nullptr);

  DBG("Device name: "
      << audioDeviceManager.getCurrentAudioDevice()->getName());
  player.prepareToPlay(
      audioDeviceManager.getCurrentAudioDevice()->getCurrentSampleRate(), 4096);
  audioDeviceManager.addAudioCallback(&audioCallback);
}

AudioEngine::~AudioEngine() {
  appState.removeListener(this);
  audioDeviceManager.removeAudioCallback(&audioCallback);
}

// I probably don't need this at this level
void AudioEngine::valueTreePropertyChanged(
    ValueTree& treeWhosePropertyHasChanged,
    const Identifier& property) {
  if (treeWhosePropertyHasChanged != appState)
    return;
  if (property == AppSchema::playing)
    appState[AppSchema::playing] ? player.play() : player.stop();
  if (property == AppSchema::currentEntry) {
    auto playlist = appState.getChildWithName(AppSchema::playlistTag);
    auto child = playlist.getChild((int)appState[AppSchema::currentEntry]);
    auto path = child.getProperty(AppSchema::playlistEntryPath, "")
                    .toString()
                    .toStdString();
    player.setCurrentFile(File(path));
  }
}
