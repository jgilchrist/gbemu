cmake_minimum_required(VERSION 3.0)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(add_warnings)
include(add_sources)

project(emulator)

add_definitions(-std=c++17)
add_warnings()

add_subdirectory(src)

declare_executable(emulator)

find_package(SFML 2 REQUIRED system window graphics)
include_directories(SYSTEM ${SFML_INCLUDE_DIR})
target_link_libraries(emulator ${SFML_LIBRARIES})
