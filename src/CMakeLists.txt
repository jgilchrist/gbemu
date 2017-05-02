add_sources(
    address.cc
    cartridge.cc
    cartridge_info.cc
    debugger.cc
    gameboy.cc
    main.cc
    mmu.cc
    register.cc
)

add_subdirectory(cpu)
add_subdirectory(util)
add_subdirectory(video)
