cmake_minimum_required(VERSION 3.0)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

project(emulator)
include(add_sources)

# C++ definitions
add_definitions(-std=c++14)
add_definitions(-Weverything -Wall -Wextra -Wpedantic)
include(silence_weverything)

add_subdirectory(src)

declare_executable(emulator)

# Find and link dependencies
find_package(SFML 2 REQUIRED system window graphics)
include_directories(SYSTEM ${SFML_INCLUDE_DIR})
target_link_libraries(emulator ${SFML_LIBRARIES})

# FIXME: Temporarily silence warnings during development
add_definitions(-Wno-missing-noreturn)
