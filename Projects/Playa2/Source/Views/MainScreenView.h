#pragma once

#include <functional>

#include "Interfaces/Views/IMainScreenView.h"
#include "Interfaces/Presenters/IMainScreenPresenter.h"

class MainScreenView : public IMainScreenView
{
public:
    MainScreenView() = default;
    void run();

    void update(const IAppModel::DTO& dto) override;
    void createUi(IMainScreenPresenter& presenter) override;
private:
    int selected = 0;
    int changeCounter = 0;
    bool playing = false;

    std::function<void()> togglePlay = nullptr;
};
