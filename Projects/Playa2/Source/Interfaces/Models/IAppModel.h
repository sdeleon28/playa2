#pragma once

#include <juce_core/juce_core.h>
using namespace juce;

#include "Schemas/AppSchema.h"

class IAppModel
{
public:
    virtual ~IAppModel() = default;

    struct DTO
    {
        bool playing;
    };

    class Listener
    {
    public:
        virtual ~Listener() = default;

        virtual void onStateUpdated (const DTO& newState) = 0;
    };

    virtual void addListener (Listener* listener) = 0;
    virtual void removeListener (Listener* listener) = 0;

    virtual void togglePlaying() = 0;
    virtual DTO getState() const = 0;
};
