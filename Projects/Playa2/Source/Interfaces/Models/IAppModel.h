#pragma once

#include <juce_core/juce_core.h>
using namespace juce;

#include "Schemas/AppSchema.h"

class IAppModel
{
public:
    virtual ~IAppModel() = default;

    // TODO: This will hold other playlist metadata like the tempo, key, etc.
    struct PlaylistEntry
    {
        std::string path;
    };

    struct DTO
    {
        bool playing;
        PlaylistEntry currentEntry;
        std::vector<PlaylistEntry> playlist;
    };

    class Listener
    {
    public:
        virtual ~Listener() = default;

        virtual void onStateUpdated (const DTO& newState) = 0;
    };

    virtual void addListener (Listener* listener) = 0;
    virtual void removeListener (Listener* listener) = 0;

    virtual void setCurrentEntry(int e) = 0;
    virtual void togglePlaying() = 0;
    virtual DTO getState() const = 0;
};
