#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_core/juce_core.h>

#include "Audio/AudioEngine.h"
#include "Models/AppModel.h"
#include "Models/AppModelFreeFunctions.h"
#include "Presenters/MainScreenPresenter.h"
#include "Schemas/AppSchema.h"
#include "Views/MainScreenView.h"

#include "main.h"

std::vector<std::string> fileToLines(const std::string& filename) {
  std::ifstream file(filename);
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }
  return lines;
}

std::string parseLine(std::string& line) {
  std::string path, tempo;
  size_t pos = 0;
  pos = line.find(",");
  path = line.substr(0, pos);
  line.erase(0, pos + 1);
  tempo = line;
  return path;
}

int main(int argc, char* argv[]) {
  std::string filename;
  for (int i = 1; i < argc; ++i) {
    if (std::string(argv[i]) == "-f") {
      if (i + 1 < argc) {
        filename = argv[++i];
      } else {
        std::cerr << "-f requires a filename argument" << std::endl;
        return 1;
      }
    }
  }
  if (filename.empty()) {
    std::cerr << "No filename provided" << std::endl;
    return 1;
  }
  std::vector<std::string> lines = fileToLines(filename);
  std::vector<std::string> paths;
  for (std::string& line : lines)
    paths.push_back(parseLine(line));

  auto appState = ValueTree{AppSchema::tag};
  auto appModel = AppModelFreeFunctions::createAppModel(appState, paths);
  auto audioEngine = std::make_unique<AudioEngine>(appState);
  auto mainView = std::make_unique<MainScreenView>();
  auto mainScreenPresenter =
      std::make_unique<MainScreenPresenter>(appModel, *mainView);
  mainView->createUi(*mainScreenPresenter);
  if (!paths.empty())
    appModel.setCurrentEntry(0);
  mainView->run();
}
