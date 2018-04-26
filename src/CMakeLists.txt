add_sources(
    address
    debugger
    gameboy
    main
    mmu
    register
    serial
)

add_subdirectory(cartridge)
add_subdirectory(cpu)
add_subdirectory(util)
add_subdirectory(video)
