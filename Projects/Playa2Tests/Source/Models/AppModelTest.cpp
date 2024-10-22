#include "AppModelTest.h"

#include "Models/AppModel.h"
#include "Models/AppModelFreeFunctions.h"

void AppModelTest::runTest() {
  testSetCurrentEntry();
}

void AppModelTest::testSetCurrentEntry() {
  std::vector<std::string> playlist{"path/to/song1.wav", "path/to/song2.wav",
                                    "path/to/song3.wav"};
  ValueTree appState{AppSchema::tag};
  AppModel appModel = AppModelFreeFunctions::createAppModel(appState, playlist);
  auto state = appModel.getState();
  appModel.setCurrentEntry(1);
  state = appModel.getState();
  EXPECT_EQUALS(state.currentEntry.path, "path/to/song2.wav");
}
