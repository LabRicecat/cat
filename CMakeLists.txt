cmake_minimum_required(VERSION 3.9)

set(VERS 0.0.6)

project(catui
    VERSION ${VERS} 
    DESCRIPTION "A cat approved tui framework"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(catui SHARED
    src/buffer.cpp
    src/config.cpp
    src/drawcalls.cpp
    src/drawing.cpp
    src/effects.cpp
    src/id.cpp
    src/input.cpp
    src/library.cpp
    src/lifespan.cpp
    src/signals.cpp
    src/string.cpp
    src/string_iterator.cpp
    src/terminal.cpp
    src/vector.cpp
    src/window.cpp

    catpkgs/inipp/inipp.hpp
)

target_compile_features(catui PRIVATE cxx_std_20)
set_target_properties(catui PROPERTIES VERSION ${VERS})
set_target_properties(catui PROPERTIES SOVERSION 0)

set_target_properties(catui PROPERTIES VERSION ${VERS})

target_include_directories(catui PRIVATE catpkgs/inipp)
target_include_directories(catui PRIVATE .)

include(GNUInstallDirs)

install(DIRECTORY DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cat)
install(DIRECTORY DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cat/catpkgs)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/inc/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cat
    FILES_MATCHING PATTERN "*.hpp"
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/catpkgs/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cat/catpkgs
    FILES_MATCHING PATTERN "*.hpp"
)
