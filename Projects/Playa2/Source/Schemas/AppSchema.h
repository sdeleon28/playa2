#pragma once

#include <juce_core/juce_core.h>
using namespace juce;

class AppSchema {
 public:
  static Identifier tag;
  static Identifier playing;
  static Identifier currentSample;
  static Identifier currentEntry;
  static Identifier reportedEntry;
  static Identifier playlistTag;
  static Identifier playlistEntryTag;
  static Identifier playlistEntryPath;
  static Identifier progress;
  static Identifier reportedProgress;
};
