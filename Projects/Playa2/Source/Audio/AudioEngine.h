#pragma once

#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_data_structures/juce_data_structures.h>
using namespace juce;

#include "Interfaces/Audio/IAudioEngine.h"

#include "Schemas/AppSchema.h"

#include "AudioPlayer.h"
#include "AudioCallback.h"

class AudioEngine final : public IAudioEngine, public ValueTree::Listener
{
public:
    AudioEngine (ValueTree appState);
    ~AudioEngine() override;

private:
    void valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged,
                                   const Identifier& property) override;

    ValueTree appState;
    AudioSourcePlayer audioSourcePlayer;
    AudioDeviceManager audioDeviceManager;
    TimeSliceThread previewThread { "audio file preview" };
    std::unique_ptr<MemoryAudioSource> memoryAudioSource = nullptr;

    static const unsigned int sampleRate = 44100;
    static const int numChannels = 2;
    static const int repetitions = 60;

    AudioPlayer player;
    AudioCallback audioCallback;
};