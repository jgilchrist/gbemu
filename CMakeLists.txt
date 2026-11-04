cmake_minimum_required(VERSION 3.10)
list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake
  ${CMAKE_CURRENT_SOURCE_DIR}/platforms/sfml
)

include(add_warnings)
include(add_sources)

project(gbemu)

add_warnings()

declare_library(gbemu-core src)
target_compile_features(gbemu-core PUBLIC cxx_std_17)

# SFML target
# find_package(SFML 2 COMPONENTS system window graphics)

# if (SFML_FOUND)
#   declare_executable(gbemu-sfml platforms/sfml)
#   include_directories(SYSTEM ${SFML_INCLUDE_DIR})
#   target_link_libraries(gbemu-sfml gbemu-core ${SFML_LIBRARIES})
# endif()

# SDL target
find_package(SDL3)

if (SDL3_FOUND)
  declare_executable(gbemu platforms/sdl)
  target_link_libraries(gbemu PRIVATE gbemu-core PRIVATE SDL3::SDL3)
endif()

# Test target
declare_executable(gbemu-test platforms/test)
target_link_libraries(gbemu-test gbemu-core)
