#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
using namespace juce;

class AudioPlayer final : public AudioProcessor, public ValueTree::Listener {
 public:
  struct State {
    bool playing = false;
    int currentSample = 0;
    int currentEntry = 0;
    float progress = 0.f;
  };

  AudioPlayer(ValueTree appState);
  ~AudioPlayer() override;

  const String getName() const override;
  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;
  double getTailLengthSeconds() const override;
  bool acceptsMidi() const override;
  bool producesMidi() const override;
  AudioProcessorEditor* createEditor() override;
  bool hasEditor() const override;
  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram(int index) override;
  const String getProgramName(int index) override;
  void changeProgramName(int index, const String& newName) override;
  void getStateInformation(juce::MemoryBlock& destData) override;
  void setStateInformation(const void* data, int sizeInBytes) override;
  void processBlock(AudioBuffer<float>& buffer,
                    MidiBuffer& midiMessages) override;
  void play();
  void pause();
  void stop();
  void playNextTrack();

  State getState();
  void resetState();
  std::pair<float*, int> makeBufferLenPair(const char* clickBinary,
                                           int clickSize);
  void setCurrentFile(const File& file);
  void setCurrentProgress(float progress);

 private:
  void valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged,
                                const Identifier& property) override;

  ValueTree appState;
  std::mutex playbackLock;
  double sampleRate = 44100;
  int samplesPerBlock = 512;
  std::unique_ptr<AudioFormatReaderSource> audioFormatReaderSource;
  std::unique_ptr<ResamplingAudioSource> resampler;
  AudioFormatReader* reader = nullptr;
  AudioFormatManager formatManager;
  std::atomic<bool> playing = true;
  std::atomic<int> currentSample = 0;
  std::string currentFilePath;
  int currentEntry = 0;
};
