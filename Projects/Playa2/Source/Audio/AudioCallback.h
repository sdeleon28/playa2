#pragma once

#include "AudioPlayer.h"

class AudioCallback : public AudioProcessorPlayer, public Timer
{
public:
    AudioCallback (ValueTree appState, AudioPlayer& player);
    ~AudioCallback() override;
    void timerCallback() override;

private:
    ValueTree appState;
    AudioPlayer& player;
    AudioPlayer::State prevState;
};
