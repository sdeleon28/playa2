project(Playa2Tui VERSION 1.1.0)
set(TargetName ${PROJECT_NAME})

juce_add_console_app(${TargetName} PRODUCT_NAME "Playa2")
get_source_files_recursive(${CMAKE_CURRENT_SOURCE_DIR}/Source ${TargetName}_SOURCES)
target_sources(${TargetName} PRIVATE ${${TargetName}_SOURCES})

# add_executable(${TargetName} src/main.cpp)
target_include_directories(${TargetName} PRIVATE Source)
target_link_libraries(${TargetName}
  PRIVATE
    juce::juce_recommended_warning_flags
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags)
target_link_libraries(${TargetName}
  PRIVATE
    juce::juce_opengl
    juce::juce_dsp
    juce::juce_audio_utils)
target_compile_definitions(${TargetName}
  PUBLIC 
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_WEB_BROWSER=0)

target_link_libraries(${TargetName}
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component  # Not needed for this example.
)

if (EMSCRIPTEN)
  string(APPEND CMAKE_CXX_FLAGS " -s USE_PTHREADS")
  string(APPEND CMAKE_EXE_LINKER_FLAGS " -s ASYNCIFY")
  string(APPEND CMAKE_EXE_LINKER_FLAGS " -s PROXY_TO_PTHREAD")

  foreach(file "index.html" "run_webassembly.py")
    configure_file("src/${file}" ${file})
  endforeach(file)
endif()
