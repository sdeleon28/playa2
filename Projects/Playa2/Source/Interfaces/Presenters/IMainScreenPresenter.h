#pragma once

class IMainScreenPresenter
{
public:
    virtual ~IMainScreenPresenter() = default;

    virtual void togglePlay() = 0;
};
