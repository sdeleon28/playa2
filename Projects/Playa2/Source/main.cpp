#include <functional>  // for function
#include <iostream>  // for basic_ostream::operator<<, operator<<, endl, basic_ostream, basic_ostream<>::__ostream_type, cout, ostream
#include <string>    // for string, basic_string, allocator
#include <vector>    // for vector

#include "ftxui/component/captured_mouse.hpp"      // for ftxui
#include "ftxui/component/component.hpp"           // for Menu
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/component_options.hpp"   // for MenuOption
#include "ftxui/component/component_options.hpp"   // for InputOption
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/util/ref.hpp"  // for Ref

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_core/juce_core.h>

#include "Schemas/AppSchema.h"
#include "Models/AppModel.h"
#include "Audio/AudioEngine.h"

int main() {
  using namespace ftxui;

  ValueTree appState { AppSchema::tag };

  auto appModel = std::make_unique<AppModel> (appState);
  auto audioEngine = std::make_unique<AudioEngine> (appState);
  /* themeModel = std::make_unique<ThemeModel>(); */
  /* mainView = std::make_unique<MainScreenViewWrapper>(); */
  /* mainScreenPresenter = std::make_unique<MainScreenPresenter> ( */
  /*     *appModel, *themeModel, *mainView); */

  auto screen = ScreenInteractive::TerminalOutput();

  std::vector<std::string> entries = {
      "entry 1",
      "entry 2",
      "entry 3",
  };
  int selected = 0;
  int changeCounter = 0;

  MenuOption option;
  option.on_change = [&changeCounter]() { changeCounter++; };
  auto menu = Menu(&entries, &selected, option);

  auto component = Container::Vertical({
      menu,
  });

  auto renderer = Renderer(component, [&] {
    return vbox({text("Selected : " + entries[(unsigned long)selected]),
                 separator(), menu->Render()}) |
           border;
  });

  auto out = CatchEvent(renderer, [&](Event event) {
    if (event == Event::Character('q')) {
      screen.ExitLoopClosure()();
      return true;
    }
    return false;
  });

  screen.Loop(out);
}
