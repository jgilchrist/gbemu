add_sources(
    address.cc
    debugger.cc
    gameboy.cc
    input.cc
    mmu.cc
    register.cc
    serial.cc
    timer.cc
)

add_subdirectory(cartridge)
add_subdirectory(cpu)
add_subdirectory(util)
add_subdirectory(video)
