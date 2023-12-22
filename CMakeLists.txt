cmake_minimum_required(VERSION 3.24)
project(MusicLibrary VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include(UpdateSubmodules.cmake)

include(CTest)

add_subdirectory(external)

add_executable(MusicLibrary
        src/main.cpp
        src/Song.cpp
        src/MusicLibrary.cpp
        src/UserInterface.cpp
        src/AudioPlayer.cpp
        src/Playlist.cpp
        src/Album.cpp 
        src/FileManager.cpp
)

enable_testing()

file(GLOB TEST_FILES "tests/*.cpp")
add_executable(runUnitTests ${TEST_FILES})

target_link_libraries(runUnitTests gtest gtest_main pthread)

find_package(SFML REQUIRED audio)
set(Taglib_DIR "/usr/local/bin/taglib-config.cmake")
find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

target_link_libraries(MusicLibrary PRIVATE sfml-system sfml-audio sfml-window sfml-graphics sfml-network tag z ${CURSES_LIBRARY})

add_test(NAME checkAlbum COMMAND runUnitTests)