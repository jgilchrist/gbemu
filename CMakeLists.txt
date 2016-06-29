cmake_minimum_required(VERSION 3.4)

project(emulator)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/etc/build)

add_definitions(-std=c++14)
add_definitions(-stdlib=libc++)

add_definitions(-Weverything)
add_definitions(-Wall -Wextra -Wpedantic)

find_package(SFML 2 REQUIRED system window graphics)

# Disable unnecessary warnings from -Weverything
add_definitions(-Wno-c++98-compat)
add_definitions(-Wno-c++98-compat-pedantic)
add_definitions(-Wno-padded)
add_definitions(-Wno-global-constructors)
add_definitions(-Wno-gnu-zero-variadic-macro-arguments)
add_definitions(-Wno-format-nonliteral)
add_definitions(-Wno-exit-time-destructors)
add_definitions(-Wno-weak-vtables)

# Temporarily silence warnings during development
add_definitions(-Wno-unused-parameter)
add_definitions(-Wno-unused-private-field)
add_definitions(-Wno-unused-function)
add_definitions(-Wno-missing-noreturn)

add_executable(emulator
    src/address.cc
    src/cartridge.cc
    src/cartridge_info.cc
    src/clock.cc
    src/gameboy.cc
    src/register.cc
    src/main.cc
    src/mmu.cc

    src/cpu/cpu.cc
    src/cpu/cpu_opcodes.cc
    src/cpu/cpu_opcodes_cb.cc
    src/cpu/cpu_opcode_mapping.cc
    src/cpu/cpu_opcode_fns.cc

    src/video/video.cc
    src/video/framebuffer.cc

    src/util/files.cc
    src/util/log.cc
    src/util/string.cc

    src/video/screens/null_screen.cc
    src/video/screens/sfml_screen.cc
)

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(emulator ${SFML_LIBRARIES})
