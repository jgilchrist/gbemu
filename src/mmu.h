#pragma once

#include "address.h"
#include "options.h"
#include "cartridge/cartridge.h"

#include <vector>
#include <memory>

class Video;
class CPU;
class Serial;
class Input;
class Timer;

class MMU {
public:
    MMU(Model& inModel, std::shared_ptr<Cartridge> inCartridge, CPU& inCPU, Video& inVideo, Input& input, Serial& serial, Timer& timer, Options& options);

    u8 read(const Address& address) const;
    void write(const Address& address, u8 byte);

private:
    bool boot_rom_active() const;

    u8 read_io(const Address& address) const;
    void write_io(const Address& address, u8 byte);

    void dma_transfer(const u8 byte);

    void set_wram_bank(u8 byte);
    u8 get_wram_bank() const;

    u16 calculate_wram_address(const Address& address) const;

    Model& model;
    std::shared_ptr<Cartridge> cartridge;
    CPU& cpu;
    Video& video;
    Input& input;
    Serial& serial;
    Timer& timer;
    Options& options;

    std::vector<u8> work_ram;
    std::vector<u8> oam_ram;
    std::vector<u8> high_ram;

    ByteRegister disable_boot_rom_switch;
    ByteRegister work_ram_bank;

    friend class Debugger;
};
