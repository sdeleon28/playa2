#pragma once

#include "AudioPlayer.h"

class AudioCallback : public AudioProcessorPlayer {
 public:
  AudioCallback(ValueTree appState, AudioPlayer& player);
  ~AudioCallback() override;

 private:
  void pollPlayerState();

  ValueTree appState;
  AudioPlayer& player;
  AudioPlayer::State prevState;
};
