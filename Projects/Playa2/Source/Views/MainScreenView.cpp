#include "MainScreenView.h"

#include <functional>  // for function
#include <iostream>  // for basic_ostream::operator<<, operator<<, endl, basic_ostream, basic_ostream<>::__ostream_type, cout, ostream
#include <string>    // for string, basic_string, allocator
#include <vector>    // for vector

MainScreenView::MainScreenView() {}

void MainScreenView::run() {
  MenuOption option;
  option.on_change = [this]() { setCurrentEntry(selected); };
  auto menu = Menu(&entries, &selected, option);

  auto component = Container::Vertical({
      menu,
  });

  auto renderer = Renderer(component, [&] {
    return vbox({gauge(progress), separator(), menu->Render()}) | border;
  });

  std::vector<char> nums = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
  out = CatchEvent(renderer, [&](Event event) {
    if (event == Event::Character('g')) {
      setCurrentEntry(0);
      return true;
    }
    if (event == Event::Character('G')) {
      setCurrentEntry((int)entries.size() - 1);
      return true;
    }
    if (event == Event::Character(' ')) {
      togglePlay();
      return true;
    }
    int i = 0;
    for (auto c : nums) {
      if (event == Event::Character(c) && (int)entries.size() > i) {
        setCurrentEntry(i);
        return true;
      }
      i++;
    }
    if (event == Event::Custom) {
      // Re-render the UI here
      return true;
    }
    return false;
  });

  screen.Loop(out);
}

#include <fstream>
#define LOG(msg)                                           \
  {                                                        \
    std::ofstream ofs("/tmp/log.txt", std::ios_base::app); \
    ofs << msg << std::endl;                               \
    ofs.close();                                           \
  }

void MainScreenView::update(const IAppModel::DTO& dto) {
  playing = dto.playing;
  entries.clear();
  for (auto& entry : dto.playlist)
    entries.push_back(entry.path);
  if (std::abs(progress - dto.progress) > 0.001) {
    progress = dto.progress;
    // After updating progress, trigger a UI update
    screen.PostEvent(Event::Custom);
  }
  if (dto.currentEntry.path != entries[(size_t)selected]) {
    for (size_t i = 0; i < entries.size(); ++i) {
      if (entries[i] == dto.currentEntry.path) {
        selected = (int)i;
        break;
      }
    }
  }
}

void MainScreenView::createUi(IMainScreenPresenter& presenter) {
  togglePlay = [&presenter]() { presenter.togglePlay(); };
  setCurrentEntry = [&presenter](int e) { presenter.setCurrentEntry(e); };
}
