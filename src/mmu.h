#pragma once

#include "address.h"
#include "cartridge/cartridge.h"

#include <vector>

class Video;
class CPU;
class Serial;

class MMU {
public:
    MMU(Cartridge& inCartridge, CPU& inCPU, Video& inVideo, Serial& serial);

    u8 read(const Address& address) const;
    void write(const Address& address, u8 byte);

private:
    bool boot_rom_active() const;

    u8 read_io(const Address& address) const;
    void write_io(const Address& address, u8 byte);

    u8 memory_read(const Address& address) const;
    void memory_write(const Address& address, u8 byte);

    Cartridge& cartridge;
    CPU& cpu;
    Video& video;
    Serial& serial;
    std::vector<u8> memory;

    friend class Debugger;
};
