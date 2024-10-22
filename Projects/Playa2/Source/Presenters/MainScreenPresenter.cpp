#include "MainScreenPresenter.h"

MainScreenPresenter::MainScreenPresenter(IAppModel& theAppModel,
                                         IMainScreenView& theView)
    : appModel(theAppModel), view(theView) {
  appModel.addListener(this);
  onStateUpdated(appModel.getState());
}

MainScreenPresenter::~MainScreenPresenter() {
  appModel.removeListener(this);
}

void MainScreenPresenter::onStateUpdated(const IAppModel::DTO& dto) {
  view.update(dto);
}

void MainScreenPresenter::togglePlay() {
  appModel.togglePlaying();
}

void MainScreenPresenter::setCurrentEntry(int e) {
  appModel.setCurrentEntry(e);
}

void MainScreenPresenter::setCurrentProgress(float p) {
  appModel.setCurrentProgress(p);
}
