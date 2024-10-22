#include "AudioPlayer.h"

AudioPlayer::AudioPlayer() {
  formatManager.registerBasicFormats();
}

AudioPlayer::~AudioPlayer() {
  delete reader;
}

void AudioPlayer::setCurrentFile(const File& file) {
  stop();
  resetState();
  if (!file.existsAsFile())
    return;
  reader = formatManager.createReaderFor(file);
  if (!reader)
    return;
  audioFormatReaderSource.reset(new AudioFormatReaderSource(reader, true));
  resampler.reset(
      new ResamplingAudioSource(audioFormatReaderSource.get(), false, 2));
  resampler->prepareToPlay((int)sampleRate, samplesPerBlock);
  resampler->setResamplingRatio(reader->sampleRate / sampleRate);
  play();
}

const String AudioPlayer::getName() const {
  return "AudioPlayer";
}

void AudioPlayer::prepareToPlay(double theSampleRate, int theSamplesPerBlock) {
  setRateAndBufferSizeDetails(theSampleRate, theSamplesPerBlock);
  sampleRate = theSampleRate;
  samplesPerBlock = theSamplesPerBlock;
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
  if (!playing || !resampler)
    return;
  AudioSourceChannelInfo info(buffer);
  resampler->getNextAudioBlock(info);
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
