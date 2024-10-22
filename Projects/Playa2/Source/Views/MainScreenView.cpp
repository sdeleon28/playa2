#include "MainScreenView.h"

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

using namespace ftxui;

void MainScreenView::run() {
  auto screen = ScreenInteractive::TerminalOutput();
  MenuOption option;
  option.on_change = [this]() { setCurrentEntry(selected); };
  auto menu = Menu(&entries, &selected, option);

  auto component = Container::Vertical({
      menu,
  });

  auto renderer = Renderer(component, [&] {
    return vbox({text("Selected : " + entries[(unsigned long)selected]),
                 vbox({text("Playing : " + std::to_string(playing))}),
                 separator(), menu->Render()}) |
           border;
  });

  auto out = CatchEvent(renderer, [&](Event event) {
    if (event == Event::Character('p')) {
      /* screen.ExitLoopClosure()(); */
      togglePlay();
      return true;
    }
    return false;
  });

  screen.Loop(out);
}

void MainScreenView::update(const IAppModel::DTO& dto) {
  playing = dto.playing;
  entries.clear();
  for (auto& entry : dto.playlist)
    entries.push_back(entry.path);
}

void MainScreenView::createUi(IMainScreenPresenter& presenter) {
  togglePlay = [&presenter]() { presenter.togglePlay(); };
  setCurrentEntry = [&presenter](int e) { presenter.setCurrentEntry(e); };
}
