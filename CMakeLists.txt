cmake_minimum_required(VERSION 3.9)

set(VERS 0.2.1)

project(catui
    VERSION ${VERS} 
    DESCRIPTION "A cat approved tui framework"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(catui STATIC
    src/base/buffer.cpp
    src/base/container.cpp
    src/base/cursor.cpp
    src/base/drawcalls.cpp
    src/base/drawing.cpp
    src/base/effects.cpp
    src/base/id.cpp
    src/base/input.cpp
    src/base/lifespan.cpp
    src/base/positional.cpp
    src/base/settings.cpp
    src/base/signals.cpp
    src/base/string.cpp
    src/base/string_iterator.cpp
    src/base/terminal.cpp
    src/base/vector.cpp
    src/base/window.cpp

    src/buffer/lockable.cpp
    src/buffer/scrollable.cpp

    src/composer/linenumbers.cpp

    src/container/horizontal.cpp

    src/renderer/fit.cpp

    src/window/inputfield.cpp 
    src/window/textfield.cpp
)

target_compile_features(catui PRIVATE cxx_std_20)
set_target_properties(catui PROPERTIES VERSION ${VERS})
set_target_properties(catui PROPERTIES SOVERSION 0)

set_target_properties(catui PROPERTIES VERSION ${VERS})

if(DEBUG)
    target_compile_options(catui PUBLIC -g)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif(DEBUG)

target_include_directories(catui PRIVATE .)

include(GNUInstallDirs)

install(DIRECTORY DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cat)
install(DIRECTORY DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cat/base)
install(DIRECTORY DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cat/buffer)
install(DIRECTORY DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cat/composer)
install(DIRECTORY DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cat/container)
install(DIRECTORY DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cat/renderer)
install(DIRECTORY DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cat/window)

install(TARGETS catui
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/inc/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cat
    FILES_MATCHING PATTERN "*.hpp"
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/inc/base/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cat/base
    FILES_MATCHING PATTERN "*.hpp"
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/catpkgs/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cat/buffer
    FILES_MATCHING PATTERN "*.hpp"
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/catpkgs/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cat/composer
    FILES_MATCHING PATTERN "*.hpp"
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/catpkgs/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cat/container
    FILES_MATCHING PATTERN "*.hpp"
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/catpkgs/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cat/renderer
    FILES_MATCHING PATTERN "*.hpp"
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/catpkgs/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cat/window
    FILES_MATCHING PATTERN "*.hpp"
)

