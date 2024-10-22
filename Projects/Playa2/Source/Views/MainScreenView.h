#pragma once

#include <functional>

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

#include "Interfaces/Presenters/IMainScreenPresenter.h"
#include "Interfaces/Views/IMainScreenView.h"

class MainScreenView : public IMainScreenView {
 public:
  MainScreenView();
  void run();

  void update(const IAppModel::DTO& dto) override;
  void createUi(IMainScreenPresenter& presenter) override;

 private:
  int selected = 0;
  bool playing = false;
  float progress = 0.f;

  ScreenInteractive screen = ScreenInteractive::TerminalOutput();
  ftxui::Component out;
  std::vector<std::string> entries = {};
  std::function<void()> togglePlay = nullptr;
  std::function<void(int)> setCurrentEntry = nullptr;
  std::function<void(float)> setCurrentProgress = nullptr;
};
