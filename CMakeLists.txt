cmake_minimum_required(VERSION 3.4)

project(emulator)

add_definitions(-std=c++14 -Wall -Wextra -Wpedantic -g -ferror-limit=10000)
add_definitions(-Wno-unused-parameter)
add_definitions(-Wno-gnu-zero-variadic-macro-arguments)

add_executable(emulator
    src/address.cc
    src/clock.cc
    src/gameboy.cc
    src/main.cc
    src/cpu/cpu.cc
    src/cpu/cpu_opcodes.cc
    src/cpu/cpu_opcodes_cb.cc
    src/cpu/memory.cc
    src/cpu/mmu.cc
    src/cpu/register.cc
    src/util/log.cc
    src/util/string.cc
)
