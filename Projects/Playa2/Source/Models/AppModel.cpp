#include "AppModel.h"
#include "Schemas/AppSchema.h"

AppModel::AppModel (ValueTree theAppState) : appState (theAppState)
{
    appState.addListener (this);
    notifyUpdate();
}

AppModel::~AppModel() { appState.removeListener (this); }

void AppModel::addListener (IAppModel::Listener* listener)
{
    listeners.add (listener);
}

void AppModel::removeListener (IAppModel::Listener* listener)
{
    listeners.remove (listener);
}

IAppModel::DTO AppModel::getState() const
{
    DTO dto;
    dto.playing = appState.getProperty (AppSchema::playing, false);
    return dto;
}

void AppModel::notifyUpdate()
{
    listeners.call (&IAppModel::Listener::onStateUpdated, getState());
}

void AppModel::valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged,
                                         const Identifier&)
{
    if (treeWhosePropertyHasChanged != appState)
        return;
    notifyUpdate();
}

void AppModel::togglePlaying()
{
    appState.setProperty (AppSchema::playing,
                          ! appState.getProperty (AppSchema::playing, false),
                          nullptr);
}
