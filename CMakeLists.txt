cmake_minimum_required (VERSION 3.22)

project(Playa2
  LANGUAGES CXX
  VERSION 1.0.0
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/arthursonzogni/ftxui.git
  GIT_TAG        v5.0.0
  GIT_PROGRESS   TRUE
  GIT_SHALLOW    TRUE
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(ftxui)
# ------------------------------------------------------------------------------

function(get_source_files_recursive DIR OUTPUT_VAR)
    file(GLOB_RECURSE new_source_files
        LIST_DIRECTORIES false
        "${DIR}/*.cpp"
        "${DIR}/*.c"
        "${DIR}/*.cc"
        "${DIR}/*.cxx"
        "${DIR}/*.h"
        "${DIR}/*.hpp"
    )
    set(${OUTPUT_VAR} ${new_source_files} PARENT_SCOPE)
endfunction()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_subdirectory(submodules/JUCE)
add_subdirectory(Projects/Playa2)
add_subdirectory(Projects/Playa2Tests)
