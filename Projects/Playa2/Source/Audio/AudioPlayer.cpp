#include "AudioPlayer.h"

#include "Schemas/AppSchema.h"

AudioPlayer::AudioPlayer(ValueTree theAppState) : appState(theAppState) {
  appState.addListener(this);
  formatManager.registerBasicFormats();
}

AudioPlayer::~AudioPlayer() {
  appState.removeListener(this);
  delete reader;
}

void AudioPlayer::setCurrentFile(const File& file) {
  stop();
  resetState();
  currentFilePath = file.getFullPathName().toStdString();
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

void AudioPlayer::pause() {
  playing = false;
}

void AudioPlayer::stop() {
  resetState();
  playing = false;
}

void AudioPlayer::playNextTrack() {
  stop();
  auto playlist = appState.getChildWithName(AppSchema::playlistTag);
  auto child = playlist.getChild(currentEntry + 1);
  auto path = child.getProperty(AppSchema::playlistEntryPath, "")
                  .toString()
                  .toStdString();
  setCurrentFile(File(path));
  currentEntry++;
  play();
}

void AudioPlayer::processBlock(AudioBuffer<float>& buffer,
                               MidiBuffer& /* midiMessages */) {
  if (!playing || !resampler)
    return;
  AudioSourceChannelInfo info(buffer);
  resampler->getNextAudioBlock(info);
  currentSample += buffer.getNumSamples();
  float ratio = (float)reader->sampleRate / (float)sampleRate;
  if ((float)currentSample > (float)reader->lengthInSamples / ratio) {
    playNextTrack();
  }
}

void AudioPlayer::setCurrentProgress(float progress) {
  pause();
  jassert(progress >= 0.f && progress <= 1.f);
  int64 newPosition =
      static_cast<int64>((float)reader->lengthInSamples * progress);
  audioFormatReaderSource->setNextReadPosition(newPosition);
  float ratio = (float)reader->sampleRate / (float)sampleRate;
  currentSample = (int)((float)newPosition / ratio);
  play();
}

void AudioPlayer::resetState() {
  playing = false;
  currentSample = 0;
}

AudioPlayer::State AudioPlayer::getState() {
  State state;
  state.playing = playing;
  state.currentSample = currentSample;
  state.currentEntry = currentEntry;
  if (!reader)
    return state;
  float ratio = (float)reader->sampleRate / (float)sampleRate;
  auto lengthInSamples = (float)reader->lengthInSamples / ratio;
  state.progress = (float)currentSample / lengthInSamples;
  return state;
}

void AudioPlayer::valueTreePropertyChanged(
    ValueTree& treeWhosePropertyHasChanged,
    const Identifier& property) {
  if (treeWhosePropertyHasChanged != appState)
    return;
  if (property == AppSchema::playing)
    appState[AppSchema::playing] ? play() : pause();
  if (property == AppSchema::currentEntry) {
    auto playlist = appState.getChildWithName(AppSchema::playlistTag);
    currentEntry = (int)appState[AppSchema::currentEntry];
    auto child = playlist.getChild(currentEntry);
    auto path = child.getProperty(AppSchema::playlistEntryPath, "")
                    .toString()
                    .toStdString();
    setCurrentFile(File(path));
  }
  if (property == AppSchema::progress) {
    setCurrentProgress(appState[AppSchema::progress]);
  }
}
