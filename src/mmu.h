#pragma once

#include "address.h"
#include "cartridge.h"

#include <vector>

/* TODO: Can this forward declaration be avoided by
 * avoiding a dependency cycle between Video/MMU? */
class Video;

class MMU {
public:
    MMU(Cartridge& inCartridge, Video& inVideo);

    u8 read(const Address address) const;
    void write(const Address address, const u8 byte);

private:
    bool boot_rom_active() const;

    u8 read_io(const Address address) const;
    void write_io(const Address address, const u8 byte);

    u8 memory_read(const Address address) const;
    void memory_write(const Address address, const u8 byte);

    Cartridge& cartridge;
    Video& video;
    std::vector<u8> memory;

    u8 serial_byte = 0;
    bool should_write_serial = false;

    friend class Debugger;
};
