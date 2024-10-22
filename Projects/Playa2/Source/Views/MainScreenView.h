#pragma once

#include <functional>

#include "Interfaces/Presenters/IMainScreenPresenter.h"
#include "Interfaces/Views/IMainScreenView.h"

class MainScreenView : public IMainScreenView {
 public:
  MainScreenView() = default;
  void run();

  void update(const IAppModel::DTO& dto) override;
  void createUi(IMainScreenPresenter& presenter) override;

 private:
  int selected = 0;
  int changeCounter = 0;
  bool playing = false;

  std::vector<std::string> entries = {};
  std::function<void()> togglePlay = nullptr;
  std::function<void(int)> setCurrentEntry = nullptr;
};
