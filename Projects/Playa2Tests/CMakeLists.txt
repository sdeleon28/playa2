project(Playa2Tests VERSION 1.1.0)
set(TargetName ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

juce_add_console_app(${TargetName} PRODUCT_NAME "Playa2Tests")

get_source_files_recursive(${CMAKE_CURRENT_SOURCE_DIR}/Source ${TargetName}_SOURCES)
target_sources(${TargetName} PRIVATE
  ${${TargetName}_SOURCES}
  ../Playa2/Source/Models/AppModelFreeFunctions.cpp
  ../Playa2/Source/Models/AppModel.cpp
  ../Playa2/Source/Schemas/AppSchema.cpp
  #../Playa2/Source/Presenters/MainScreenPresenter.cpp
  #../Playa2/Source/Audio/AudioEngine.cpp
  #../Playa2/Source/Audio/AudioPlayer.cpp
)

target_include_directories(${TargetName} PRIVATE Source)

target_link_libraries(${TargetName} PRIVATE
    juce::juce_core
    juce::juce_audio_processors
)

target_include_directories(${TargetName} PUBLIC 
  "${CMAKE_CURRENT_SOURCE_DIR}/../Playa2/Source"
)

juce_generate_juce_header(${TargetName})

target_compile_definitions(${TargetName} PUBLIC
    JACK_LOGGING_ENABLED=0
    JUCE_CONTENT_SHARING=0
    JUCE_COREAUDIO_LOGGING_ENABLED=0
    JUCE_COREGRAPHICS_DRAW_ASYNC=0
    JUCE_EXCEPTIONS_DISABLED=0
    JUCE_MODAL_LOOPS_PERMITTED=0
    JUCE_PLUGINHOST_VST3=0
    JUCE_PLUGINHOST_VST=0
    JUCE_USE_CURL=0
    JUCE_USE_FLAC=0
    JUCE_USE_LAME_AUDIO_FORMAT=0
    JUCE_USE_MP3AUDIOFORMAT=0
    JUCE_USE_OGGVORBIS=0
    JUCE_WASAPI_LOGGING=0
    JUCE_WEB_BROWSER=0
)
