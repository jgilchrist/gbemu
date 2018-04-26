#include "mmu.h"

#include "boot.h"
#include "util/log.h"
#include "cpu/cpu.h"
#include "video/video.h"

#include <cstdlib>

MMU::MMU(Cartridge& inCartridge, CPU& inCPU, Video& inVideo) :
    cartridge(inCartridge),
    cpu(inCPU),
    video(inVideo)
{
    memory = std::vector<u8>(0x10000);
}

u8 MMU::read(const Address& address) const {
    if (address.in_range(0x0, 0x7FFF)) {
        if (address.in_range(0x0, 0xFF) && boot_rom_active()) {
            return bootDMG[address.value()];
        }
        return cartridge.read(address);
    }

    /* VRAM */
    if (address.in_range(0x8000, 0x9FFF)) {
        return memory_read(address);
    }

    /* External (cartridge) RAM */
    if (address.in_range(0xA000, 0xBFFF)) {
        log_unimplemented("Attempting to read from cartridge RAM");
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

    /* OAM */
    if (address.in_range(0xFE00, 0xFE9F)) {
        return memory_read(address);
    }

    if (address.in_range(0xFEA0, 0xFEFF)) {
        log_warn("Attempting to read from unusable memory 0x%x", address.value());
        /* TODO: does this always return 0? */
        return 0;
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
    if (address == 0xFFFF) {
        return cpu.interrupt_enabled.value();
    }

    fatal_error("Attempted to read from unmapped memory address 0x%X", address.value());
}

u8 MMU::memory_read(const Address& address) const {
    return memory.at(address.value());
}

u8 MMU::read_io(const Address& address) const {
    switch (address.value()) {
        case 0xFF00:
            log_unimplemented("Attempted to read joypad register");
            return 0xFF;

        case 0xFF01:
            log_unimplemented("Attempted to read serial transfer data");
            return 0xFF;

        case 0xFF02:
            log_unimplemented("Attempted to read serial transfer control");
            return 0xFF;

        case 0xFF0F:
            return cpu.interrupt_flag.value();

        case 0xFF40:
            return video.control_byte;

        case 0xFF41:
            log_unimplemented("Attempted to read LCD stat register");
            return 0xFF;

        case 0xFF42:
            return video.scroll_y.value();

        case 0xFF44:
            return video.line.value();

        case 0xFF4D:
            log_unimplemented("Attempted to read from 'Prepare Speed Switch' register");
            return 0x0;

        /* Disable boot rom switch */
        case 0xFF50:
            return memory_read(address);

        default:
            fatal_error("Read from unknown IO address 0x%x", address.value());
    }
}

void MMU::write(const Address& address, const u8 byte) {
    if (address.in_range(0x0000, 0x7FFF)) {
        log_warn("Attempting to write to cartridge ROM: %04X - 0x%X", address.value(), byte);
        return;
    }

    /* VRAM */
    if (address.in_range(0x8000, 0x9FFF)) {
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
        log_warn("Attempting to write to mirrored work RAM");
        auto mirrored_address = Address(address.value() - 0x2000);
        memory_write(mirrored_address, byte);
        return;
    }

    /* OAM */
    if (address.in_range(0xFE00, 0xFE9F)) {
        memory_write(address, byte);
        return;
    }

    if (address.in_range(0xFEA0, 0xFEFF)) {
        log_warn("Attempting to write to unusable memory 0x%x - 0x%x", address.value(), byte);
        return;
    }

    /* Mapped IO */
    if (address.in_range(0xFF00, 0xFF7F)) {
        write_io(address, byte);
        return;
    }

    /* Zero Page ram */
    if (address.in_range(0xFF80, 0xFFFE)) {
        memory_write(address, byte);
        return;
    }

    /* Interrupt Enable register */
    if (address == 0xFFFF) {
        cpu.interrupt_enabled.set(byte);
        return;
    }

    fatal_error("Attempted to write to unmapped memory address 0x%X", address.value());
}

void MMU::write_io(const Address& address, const u8 byte) {
    switch (address.value()) {
        case 0xFF00:
            /* TODO: Joypad */
            return;

        case 0xFF01:
            /* Serial data transfer (SB) */
            printf("%c", byte);
            fflush(stdout);
            return;

        case 0xFF02:
            /* Serial data transfer (SB) */
            return;

        case 0xFF07:
            /* TODO: Time control */
            return;

        case 0xFF0F:
            cpu.interrupt_flag.set(byte);
            return;

        /* TODO: Audio - Channel 1: Tone & Sweep */
        case 0xFF10:
        case 0xFF11:
        case 0xFF12:
        case 0xFF13:
        case 0xFF14:
            return;

        /* TODO: Audio - Channel 2: Tone */
        case 0xFF16:
        case 0xFF17:
        case 0xFF18:
        case 0xFF19:
            return;

        /* TODO: Audio - Channel 3: Wave Output */
        case 0xFF1A:
        case 0xFF1B:
        case 0xFF1C:
        case 0xFF1D:
        case 0xFF1E:
            return;

        /* TODO: Audio - Channel 4: Noise */
        case 0xFF20:
        case 0xFF21:
        case 0xFF22:
        case 0xFF23:
            return;

        /* TODO: Audio - Sound Control Registers */
        case 0xFF24:
            /* TODO */
            log_unimplemented("Wrote to channel control address 0x%x - 0x%x", address.value(), byte);
            return;

        case 0xFF25:
            /* TODO */
            log_unimplemented("Wrote to selection of sound output terminal address 0x%x - 0x%x", address.value(), byte);
            return;

        case 0xFF26:
            /* TODO */
            log_unimplemented("Wrote to sound on/off address 0x%x - 0x%x", address.value(), byte);
            return;

        /* TODO: Audio - Wave Pattern RAM */
        case 0xFF30:
        case 0xFF31:
        case 0xFF32:
        case 0xFF33:
        case 0xFF34:
        case 0xFF35:
        case 0xFF36:
        case 0xFF37:
        case 0xFF38:
        case 0xFF39:
        case 0xFF3A:
        case 0xFF3B:
        case 0xFF3C:
        case 0xFF3D:
        case 0xFF3E:
        case 0xFF3F:
            memory_write(address, byte);
            return;

        /* Switch on LCD */
        case 0xFF40:
            video.control_byte = byte;
            return;

        case 0xFF41:
            /* TODO */
            log_unimplemented("Wrote to LCD stat register 0x%x - 0x%x", address.value(), byte);
            return;

        /* Vertical Scroll Register */
        case 0xFF42:
            video.scroll_y.set(byte);
            return;

        /* Horizontal Scroll Register */
        case 0xFF43:
            video.scroll_x.set(byte);
            return;

        /* LY - Line Y coordinate */
        case 0xFF44:
            /* "Writing will reset the counter */
            log_unimplemented("Writing to FF44 will reset the line counter");
            return;

        case 0xFF47:
            video.bg_palette.set(byte);
            log_trace("Set video palette: 0x%x", byte);
            return;

        /* TODO: Object Palette 0/1 Data */
        case 0xFF48:
        case 0xFF49:
            log_unimplemented("Wrote to object palette data register 0x%x - 0x%x", address.value(), byte);
            return;

        case 0xFF4D:
            log_unimplemented("Attempted to write to 'Prepare Speed Switch' register");
            return;

        /* Disable boot rom switch */
        case 0xFF50:
            memory_write(address, byte);
            global_logger.enable_tracing();
            log_info("Boot rom was disabled");
            return;

        default:
            /* TODO */
            fatal_error("Wrote 0x%x to unknown address 0x%x", byte, address.value());
    }
}

void MMU::memory_write(const Address& address, const u8 byte) {
    memory.at(address.value()) = byte;
}

bool MMU::boot_rom_active() const {
    return read(0xFF50) != 0x1;
}
