#include "AppModel.h"
#include "Schemas/AppSchema.h"

AppModel::AppModel(ValueTree theAppState) : appState(theAppState) {
  appState.addListener(this);
  notifyUpdate();
}

AppModel::~AppModel() {
  appState.removeListener(this);
}

void AppModel::addListener(IAppModel::Listener* listener) {
  listeners.add(listener);
}

void AppModel::removeListener(IAppModel::Listener* listener) {
  listeners.remove(listener);
}

IAppModel::DTO AppModel::getState() const {
  DTO dto;
  dto.playing = appState.getProperty(AppSchema::playing, false);
  auto playlist = appState.getChildWithName(AppSchema::playlistTag);
  for (auto child : playlist) {
    PlaylistEntry entry;
    entry.path = child.getProperty(AppSchema::playlistEntryPath, "")
                     .toString()
                     .toStdString();
    dto.playlist.push_back(entry);
  }
  if (dto.playlist.empty()) {
    PlaylistEntry entry;
    entry.path = "";
    dto.currentEntry = entry;
  } else {
    dto.currentEntry = dto.playlist[(unsigned long)appState
                                        .getProperty(AppSchema::currentEntry, 0)
                                        .toString()
                                        .getIntValue()];
  }
  dto.progress = appState.getProperty(AppSchema::progress, 0.0f);
  return dto;
}

void AppModel::notifyUpdate() {
  listeners.call(&IAppModel::Listener::onStateUpdated, getState());
}

void AppModel::valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged,
                                        const Identifier&) {
  if (treeWhosePropertyHasChanged != appState)
    return;
  notifyUpdate();
}

void AppModel::togglePlaying() {
  appState.setProperty(AppSchema::playing,
                       !appState.getProperty(AppSchema::playing, false),
                       nullptr);
}

void AppModel::setCurrentEntry(int e) {
  jassert(e <
          appState.getChildWithName(AppSchema::playlistTag).getNumChildren());
  appState.setProperty(AppSchema::currentEntry, e, nullptr);
}
