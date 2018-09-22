add_sources(
    address
    debugger
    gameboy
    input
    mmu
    register
    serial
    timer
)

add_subdirectory(cartridge)
add_subdirectory(cpu)
add_subdirectory(util)
add_subdirectory(video)
