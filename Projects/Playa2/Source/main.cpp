
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_core/juce_core.h>

#include "Audio/AudioEngine.h"
#include "Models/AppModel.h"
#include "Presenters/MainScreenPresenter.h"
#include "Schemas/AppSchema.h"
#include "Views/MainScreenView.h"

int main() {
  ValueTree appState{AppSchema::tag};

  auto appModel = std::make_unique<AppModel>(appState);
  auto audioEngine = std::make_unique<AudioEngine>(appState);
  /* themeModel = std::make_unique<ThemeModel>(); */
  auto mainView = std::make_unique<MainScreenView>();
  auto mainScreenPresenter =
      std::make_unique<MainScreenPresenter>(*appModel, *mainView);
  mainView->createUi(*mainScreenPresenter);
  mainView->run();
}
