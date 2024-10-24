#pragma once

#include "Interfaces/Models/IAppModel.h"
#include "Interfaces/Presenters/IMainScreenPresenter.h"
#include "Interfaces/Views/IMainScreenView.h"

class MainScreenPresenter : public IMainScreenPresenter,
                            public IAppModel::Listener {
 public:
  MainScreenPresenter(IAppModel& appModel, IMainScreenView& view);
  ~MainScreenPresenter() override;

  void onStateUpdated(const IAppModel::DTO& dto) override;
  void togglePlay() override;
  void setCurrentEntry(int e) override;
  void setCurrentProgress(float p) override;

 private:
  IAppModel& appModel;
  IMainScreenView& view;
};
