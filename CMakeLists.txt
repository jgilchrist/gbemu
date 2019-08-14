cmake_minimum_required(VERSION 3.0)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(add_warnings)
include(add_sources)

project(gbemu)

add_definitions(-std=c++17)
add_warnings()

declare_library(gbemu-core src)

# SFML target
# declare_executable(gbemu-sfml platforms/sfml)

# list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/platforms/sfml)
# find_package(SFML 2 REQUIRED system window graphics)
# include_directories(SYSTEM ${SFML_INCLUDE_DIR})
# target_link_libraries(gbemu-sfml gbemu-core ${SFML_LIBRARIES})

# SDL target
declare_executable(gbemu platforms/sdl)

find_package(SDL2 REQUIRED)
include_directories(SYSTEM ${SDL2_INCLUDE_DIRS})
target_link_libraries(gbemu gbemu-core ${SDL2_LIBRARIES})

# Test target
declare_executable(gbemu-test platforms/test)
target_link_libraries(gbemu-test gbemu-core)
