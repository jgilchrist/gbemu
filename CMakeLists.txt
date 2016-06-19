cmake_minimum_required(VERSION 3.4)

project(emulator)

add_definitions(-std=c++14)
add_definitions(-stdlib=libc++)
add_definitions(-g)
add_definitions(-ferror-limit=10000)

add_definitions(-Weverything)
add_definitions(-Wall -Wextra -Wpedantic)

# Disable unnecessary warnings from -Weverything
add_definitions(-Wno-c++98-compat)
add_definitions(-Wno-c++98-compat-pedantic)

# Temporarily silence warnings during development
add_definitions(-Wno-unused-parameter)
add_definitions(-Wno-unused-private-field)
add_definitions(-Wno-unused-function)

add_executable(emulator
    src/address.cc
    src/cartridge.cc
    src/clock.cc
    src/gameboy.cc
    src/main.cc
    src/mmu.cc
    src/cpu/cpu.cc
    src/cpu/cpu_opcodes.cc
    src/cpu/cpu_opcodes_cb.cc
    src/cpu/cpu_opcode_mapping.cc
    src/cpu/cpu_opcode_fns.cc
    src/cpu/register.cc
    src/util/files.cc
    src/util/log.cc
    src/util/string.cc
)
