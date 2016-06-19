#include "mmu.h"

#include "boot.h"
#include "util/log.h"

#include <cstdlib>

MMU::MMU(Cartridge& inCartridge) :
    cartridge(inCartridge)
{
    memory = std::vector<u8>(0xFFFF);
}

u8 MMU::read(const Address address) const {
    if (address.in_range(0x0, 0x7FFF)) {
        if (address.in_range(0x0, 0xFF) && boot_rom_active()) {
            return bootDMG[address.value()];
        }
        return cartridge.read(address);
    }

    /* VRAM */
    if (address.in_range(0x7FFF, 0x9FFF)) {
        return memory_read(address);
    }

    /* Disable boot rom switch */
    if (address.value() == 0xFF50) {
        return memory_read(address);
    }

    /* Zero Page ram */
    if (address.in_range(0xFF80, 0xFFFE)) {
        return memory_read(address);
    }

    log_error("Attempted to read from unmapped memory address %X", address.value());
    exit(1);
}

u8 MMU::memory_read(const Address address) const {
    return memory[address.value()];
}

void MMU::write(const Address address, const u8 byte) {
    if (address.in_range(0x0000, 0x7FFF)) {
        log_warn("Attempting to write to cartridge ROM");
    }

    /* VRAM */
    if (address.in_range(0x7FFF, 0x9FFF)) {
        memory_write(address, byte);
        return;
    }

    /* Disable boot rom switch */
    if (address.value() == 0xFF50) {
        memory_write(address, byte);
        return;
    }

    if (address.value() == 0xFF11) {
        log_warn("Wrote to unknown address 0x%x", address.value());
        memory_write(address, byte);
        return;
    }

    if (address.value() == 0xFF12) {
        log_warn("Wrote to unknown address 0x%x", address.value());
        memory_write(address, byte);
        return;
    }

    if (address.value() == 0xFF24) {
        log_warn("Wrote to unknown address 0x%x", address.value());
        memory_write(address, byte);
        return;
    }

    if (address.value() == 0xFF25) {
        log_warn("Wrote to unknown address 0x%x", address.value());
        memory_write(address, byte);
        return;
    }

    if (address.value() == 0xFF26) {
        log_warn("Wrote to unknown address 0x%x", address.value());
        memory_write(address, byte);
        return;
    }

    if (address.value() == 0xFF47) {
        log_warn("Wrote to unknown address 0x%x", address.value());
        memory_write(address, byte);
        return;
    }

    if (address.in_range(0xFEA0, 0xFEFF)) {
        log_warn("Attempting to write to unusable memory");
    }

    /* Zero Page ram */
    if (address.in_range(0xFF80, 0xFFFE)) {
        memory_write(address, byte);
        return;
    }

    log_error("Attempted to write to unmapped memory address %X", address.value());
    exit(1);
}

void MMU::memory_write(const Address address, const u8 byte) {
    memory[address.value()] = byte;
}

void MMU::write_word(const Address address, const u16 word) {
}

bool MMU::boot_rom_active() const {
    return read(0xFF50) != 0x1;
}
