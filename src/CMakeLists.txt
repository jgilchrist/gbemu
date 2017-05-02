add_sources(
    address.cc
    debugger.cc
    gameboy.cc
    main.cc
    mmu.cc
    register.cc
)

add_subdirectory(cartridge)
add_subdirectory(cpu)
add_subdirectory(util)
add_subdirectory(video)
