cmake_minimum_required(VERSION 3.4)

project(emulator)

add_definitions(-std=c++11 -Wall -Wextra -pedantic -g -ferror-limit=10000)

add_executable(emulator
    src/main.cc
    src/cpu.cc
    src/cpu.h
    src/gameboy.cc
    src/gameboy.h
    src/mmu.cc
    src/mmu.h
    src/clock.cc
    src/clock.h
    src/memory.cc
    src/memory.h
    src/registergroup.cc
    src/registergroup.h
    src/register.h
    src/address.cc
    src/address.h
    src/bitwise.h
)
