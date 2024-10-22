#include "AppModelFreeFunctions.h"

namespace AppModelFreeFunctions {

AppModel createAppModel(ValueTree appState, std::vector<std::string>& playlistPaths) {
  auto playlist = ValueTree{AppSchema::playlistTag};
  for (auto& entry : playlistPaths) {
    ValueTree playlistEntry{AppSchema::playlistEntryTag};
    playlistEntry.setProperty(AppSchema::playlistEntryPath, String(entry),
                              nullptr);
    playlist.addChild(playlistEntry, -1, nullptr);
  }
  appState.appendChild(playlist, nullptr);
  return AppModel{appState};
}
}  // namespace AppModelFreeFunctions
