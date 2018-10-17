cmake_minimum_required(VERSION 3.0)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/platforms/sfml)

include(add_warnings)
include(add_sources)

project(gbemu)

add_definitions(-std=c++17)
add_warnings()

declare_library(gbemu-core src)

# SFML target
declare_executable(gbemu platforms/sfml)

find_package(SFML 2 REQUIRED system window graphics)
include_directories(SYSTEM ${SFML_INCLUDE_DIR})
target_link_libraries(gbemu gbemu-core ${SFML_LIBRARIES})

# Test target
declare_executable(gbemu-test platforms/test)
target_link_libraries(gbemu-test gbemu-core)
