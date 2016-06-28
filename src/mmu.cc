#include "mmu.h"

#include "boot.h"
#include "util/log.h"
#include "video/video.h"

#include <cstdlib>

MMU::MMU(Cartridge& inCartridge, Video& inVideo) :
    cartridge(inCartridge),
    video(inVideo)
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
    if (address.in_range(0x9000, 0x9FFF)) {
        return memory_read(address);
    }

    /* External (cartridge) RAM */
    if (address.in_range(0xA000, 0xBFFF)) {
        /* log_warn("Attempting to read from cartridge RAM"); */
        return memory_read(address);
    }

    /* Internal work RAM */
    if (address.in_range(0xC000, 0xDFFF)) {
        return memory_read(address);
    }

    if (address.in_range(0xE000, 0xFDFF)) {
        /* log_warn("Attempting to read from mirrored work RAM"); */
        auto mirrored_address = Address(address.value() - 0x2000);
        return memory_read(mirrored_address);
    }

    /* Mapped IO */
    if (address.in_range(0xFF00, 0xFF7F)) {
        return read_io(address);
    }

    /* Zero Page ram */
    if (address.in_range(0xFF80, 0xFFFE)) {
        return memory_read(address);
    }

    /* Interrupt Enable register */
    if (address.value() == 0xFFFF) {
        return memory_read(address);
    }

    log_error("Attempted to read from unmapped memory address %X", address.value());
    exit(1);
}

u8 MMU::memory_read(const Address address) const {
    return memory[address.value()];
}

u8 MMU::read_io(const Address address) const {
    switch (address.value()) {
        case 0xFF42:
            /* TODO */
            /* log_warn("Read from unknown address 0x%x", address.value()); */
            return 0xFF;

        case 0xFF44:
            /* TODO */
            /* log_warn("Read from unknown address 0x%x", address.value()); */
            return 0x90;

        /* Disable boot rom switch */
        case 0xFF50:
            return memory_read(address);

        default:
            log_error("Read from unknown IO address 0x%x", address.value());
            exit(1);
    }
}

void MMU::write(const Address address, const u8 byte) {
    if (address.in_range(0x0000, 0x7FFF)) {
        /* log_warn("Attempting to write to cartridge ROM"); */
    }

    /* VRAM */
    if (address.in_range(0x7FFF, 0x9FFF)) {
        memory_write(address, byte);
        return;
    }

    /* External (cartridge) RAM */
    if (address.in_range(0xA000, 0xBFFF)) {
        memory_write(address, byte);
        return;
    }

    /* Internal work RAM */
    if (address.in_range(0xC000, 0xDFFF)) {
        memory_write(address, byte);
        return;
    }

    /* Mirrored RAM */
    if (address.in_range(0xE000, 0xFDFF)) {
        /* log_warn("Attempting to write to mirrored work RAM"); */
        auto mirrored_address = Address(address.value() - 0x2000);
        memory_write(mirrored_address, byte);
        return;
    }

    /* Mapped IO */
    if (address.in_range(0xFF00, 0xFF7F)) {
        write_io(address, byte);
        return;
    }

    if (address.in_range(0xFEA0, 0xFEFF)) {
        /* log_warn("Attempting to write to unusable memory"); */
    }

    /* Zero Page ram */
    if (address.in_range(0xFF80, 0xFFFE)) {
        memory_write(address, byte);
        return;
    }

    /* Interrupt Enable register */
    if (address.value() == 0xFFFF) {
        memory_write(address, byte);
        return;
    }

    log_error("Attempted to write to unmapped memory address %X", address.value());
    exit(1);
}

void MMU::write_io(const Address address, const u8 byte) {
    switch (address.value()) {
        /* Serial data transfer (SB) */
        case 0xFF01:
            /* TODO */
            /* log_warn("%c", byte); */
            return;

        case 0xFF11:
            /* TODO */
            /* log_warn("Wrote to unknown address 0x%x", address.value()); */
            memory_write(address, byte);
            return;

        case 0xFF12:
            /* TODO */
            /* log_warn("Wrote to unknown address 0x%x", address.value()); */
            memory_write(address, byte);
            return;

        case 0xFF13:
            /* TODO */
            /* log_warn("Wrote to unknown address 0x%x", address.value()); */
            memory_write(address, byte);
            return;

        case 0xFF14:
            /* TODO */
            /* log_warn("Wrote to unknown address 0x%x", address.value()); */
            memory_write(address, byte);
            return;

        case 0xFF24:
            /* TODO */
            /* log_warn("Wrote to unknown address 0x%x", address.value()); */
            memory_write(address, byte);
            return;

        case 0xFF25:
            /* TODO */
            /* log_warn("Wrote to unknown address 0x%x", address.value()); */
            memory_write(address, byte);
            return;

        case 0xFF26:
            /* TODO */
            /* log_warn("Wrote to unknown address 0x%x", address.value()); */
            memory_write(address, byte);
            return;

            /* Switch on LCD */
        case 0xFF40:
            /* TODO */
            /* log_warn("Wrote to unknown address 0x%x", address.value()); */
            memory_write(address, byte);
            return;

            /* Vertical Scroll Register */
        case 0xFF42:
            /* TODO */
            /* log_warn("Wrote to unknown address 0x%x", address.value()); */
            memory_write(address, byte);
            return;

        case 0xFF44:
            /* TODO */
            /* log_warn("Wrote to unknown address 0x%x", address.value()); */
            memory_write(address, byte);
            return;

        case 0xFF47:
            /* TODO */
            /* log_warn("Wrote to unknown address 0x%x", address.value()); */
            memory_write(address, byte);
            return;

            /* Disable boot rom switch */
        case 0xFF50:
            /* TODO */
            memory_write(address, byte);
            return;
    }
}

void MMU::memory_write(const Address address, const u8 byte) {
    memory[address.value()] = byte;
}

void MMU::write_word(const Address address, const u16 word) {
}

bool MMU::boot_rom_active() const {
    return read(0xFF50) != 0x1;
}
