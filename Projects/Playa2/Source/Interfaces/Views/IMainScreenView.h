#pragma once

#include "Interfaces/Models/IAppModel.h"
#include "Interfaces/Presenters/IMainScreenPresenter.h"

class IMainScreenView
{
public:
    virtual ~IMainScreenView() = default;

    virtual void update (const IAppModel::DTO& themeDto) = 0;
    virtual void createUi (IMainScreenPresenter& presenter) = 0;
};


