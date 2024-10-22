#pragma once

#include <juce_core/juce_core.h>
#include <juce_data_structures/juce_data_structures.h>
#include <string>
using namespace juce;

#include "Models/AppModel.h"

namespace AppModelFreeFunctions {
AppModel createAppModel(ValueTree appState, std::vector<std::string>& playlistPaths);
}
