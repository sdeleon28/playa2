#include "AppModelFreeFunctionsTest.h"

#include "Models/AppModel.h"
#include "Models/AppModelFreeFunctions.h"

void AppModelFreeFunctionsTest::runTest() {
  testBasicModelCreation();
}

void AppModelFreeFunctionsTest::testBasicModelCreation() {
  std::vector<std::string> playlist{"path/to/song1.wav", "path/to/song2.wav",
                                    "path/to/song3.wav"};
  ValueTree appState{AppSchema::tag};
  AppModel appModel = AppModelFreeFunctions::createAppModel(appState, playlist);
  auto state = appModel.getState();
  EXPECT_EQUALS(state.playlist[0].path, "path/to/song1.wav");
  EXPECT_EQUALS(state.playlist[1].path, "path/to/song2.wav");
  EXPECT_EQUALS(state.playlist[2].path, "path/to/song3.wav");
}
