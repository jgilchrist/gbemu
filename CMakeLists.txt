cmake_minimum_required(VERSION 3.4)

project(emulator)

add_definitions(-std=c++14 -Wall -Wextra -Wpedantic -g -ferror-limit=10000)
add_definitions(-Wno-unused-parameter)
add_definitions(-Wno-gnu-zero-variadic-macro-arguments)

add_executable(emulator
    src/address.cc
    src/address.h
    src/bitwise.h
    src/clock.cc
    src/clock.h
    src/gameboy.cc
    src/gameboy.h
    src/main.cc
    src/cpu/cpu.cc
    src/cpu/cpu_opcodes.cc
    src/cpu/cpu_opcodes_cb.cc
    src/cpu/cpu.h
    src/cpu/memory.cc
    src/cpu/memory.h
    src/cpu/mmu.cc
    src/cpu/mmu.h
    src/cpu/register.cc
    src/cpu/register.h
    src/util/log.cc
    src/util/string.cc
)
