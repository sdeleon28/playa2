#include "AudioPlayer.h"

AudioPlayer::AudioPlayer() {
  formatManager.registerBasicFormats();
  juce::File file(
      "/Users/santi/Dropbox/artistas/joakien/live-2024/wav/06-la-ola.wav");
  reader = formatManager.createReaderFor(file);
}

AudioPlayer::~AudioPlayer() {
  delete reader;
}

const String AudioPlayer::getName() const {
  return "AudioPlayer";
}

void AudioPlayer::prepareToPlay(double sampleRate, int samplesPerBlock) {
  setRateAndBufferSizeDetails(sampleRate, samplesPerBlock);
}

void AudioPlayer::releaseResources() {}

double AudioPlayer::getTailLengthSeconds() const {
  return 0.0;
}

bool AudioPlayer::acceptsMidi() const {
  return false;
}

bool AudioPlayer::producesMidi() const {
  return false;
}

AudioProcessorEditor* AudioPlayer::createEditor() {
  return nullptr;
}

bool AudioPlayer::hasEditor() const {
  return false;
}

int AudioPlayer::getNumPrograms() {
  return 1;
}

int AudioPlayer::getCurrentProgram() {
  return 0;
}

void AudioPlayer::setCurrentProgram(int /* index */) {}

const String AudioPlayer::getProgramName(int /* index */) {
  return {};
}

void AudioPlayer::changeProgramName(int /* index */,
                                    const String& /* newName */) {}

void AudioPlayer::getStateInformation(juce::MemoryBlock& /* destData */) {}

void AudioPlayer::setStateInformation(const void* /* data */,
                                      int /* sizeInBytes */) {}

void AudioPlayer::play() {
  playing = true;
}

void AudioPlayer::stop() {
  /* resetState(); */
  playing = false;
}

void AudioPlayer::processBlock(AudioBuffer<float>& buffer,
                               MidiBuffer& /* midiMessages */) {
  if (!playing)
    return;
  reader->read(&buffer, 0,
               std::min(buffer.getNumSamples(),
                        (int)reader->lengthInSamples - currentSample),
               currentSample, true, true);
  currentSample += buffer.getNumSamples();
}

void AudioPlayer::resetState() {
  playing = false;
  currentSample = 0;
}

AudioPlayer::State AudioPlayer::getState() {
  State state;
  state.playing = playing;
  state.currentSample = currentSample;
  return state;
}
