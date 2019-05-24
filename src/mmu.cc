#include "mmu.h"
#include "gameboy.h"
#include "boot.h"
#include "serial.h"
#include "input.h"
#include "timer.h"
#include "util/log.h"
#include "util/bitwise.h"
#include "cpu/cpu.h"
#include "video/video.h"

MMU::MMU(Gameboy& inGb, Options& inOptions) :
    gb(inGb),
    options(inOptions)
{
    work_ram = std::vector<u8>(0x8000);
    oam_ram = std::vector<u8>(0xA0);
    high_ram = std::vector<u8>(0x80);
}

auto MMU::read(const Address& address) const -> u8 {
    if (address.in_range(0x0, 0x7FFF)) {
        if (address.in_range(0x0, 0xFF) && boot_rom_active()) {
            return bootDMG[address.value()];
        }
        return gb.cartridge->read(address);
    }

    /* VRAM */
    if (address.in_range(0x8000, 0x9FFF)) {
        return gb.video.read(address.value() - 0x8000);
    }

    /* External (cartridge) RAM */
    if (address.in_range(0xA000, 0xBFFF)) {
        return gb.cartridge->read(address);
    }

    /* Internal work RAM */
    if (address.in_range(0xC000, 0xDFFF)) {
        return work_ram.at(address.value() - 0xC000);
    }

    if (address.in_range(0xE000, 0xFDFF)) {
        /* log_warn("Attempting to read from mirrored work RAM"); */
        return read(address.value() - 0x2000);
    }

    /* OAM */
    if (address.in_range(0xFE00, 0xFE9F)) {
        return oam_ram.at(address.value() - 0xFE00);
    }

    if (address.in_range(0xFEA0, 0xFEFF)) {
        log_warn("Attempting to read from unusable memory 0x%x", address.value());
        return 0xFF;
    }

    /* Mapped IO */
    if (address.in_range(0xFF00, 0xFF7F)) {
        return read_io(address);
    }

    /* Zero Page ram */
    if (address.in_range(0xFF80, 0xFFFE)) {
        return high_ram.at(address.value() - 0xFF80);
    }

    /* Interrupt Enable register */
    if (address == 0xFFFF) {
        return gb.cpu.interrupt_enabled.value();
    }

    fatal_error("Attempted to read from unmapped memory address 0x%X", address.value());
}

auto MMU::read_io(const Address& address) const -> u8 {
    switch (address.value()) {
        case 0xFF00:
            return gb.input.get_input();

        case 0xFF01:
            return gb.serial.read();

        case 0xFF02:
            log_unimplemented("Attempted to read serial transfer control");
            return 0xFF;

        case 0xFF03:
            return unmapped_io_read(address);

        case 0xFF04:
            return gb.timer.get_divider();

        case 0xFF05:
            return gb.timer.get_timer();

        case 0xFF06:
            return gb.timer.get_timer_modulo();

        case 0xFF07:
            return gb.timer.get_timer_control();

        case 0xFF08:
        case 0xFF09:
        case 0xFF0A:
        case 0xFF0B:
        case 0xFF0C:
        case 0xFF0D:
        case 0xFF0E:
            return unmapped_io_read(address);

        case 0xFF0F:
            return gb.cpu.interrupt_flag.value();

        /* TODO: Audio - Channel 1: Tone & Sweep */
        case 0xFF10:
        case 0xFF11:
        case 0xFF12:
        case 0xFF13:
        case 0xFF14:
            return 0xFF;

        case 0xFF15:
            return unmapped_io_read(address);

        /* TODO: Audio - Channel 2: Tone */
        case 0xFF16:
        case 0xFF17:
        case 0xFF18:
        case 0xFF19:
            return 0xFF;

        /* TODO: Audio - Channel 3: Wave Output */
        case 0xFF1A:
        case 0xFF1B:
        case 0xFF1C:
        case 0xFF1D:
        case 0xFF1E:
        case 0xFF1F:
            return 0xFF;

        /* TODO: Audio - Channel 4: Noise */
        case 0xFF20:
        case 0xFF21:
        case 0xFF22:
        case 0xFF23:
            return 0xFF;

        /* TODO: Audio - Channel control/ON-OFF/Volume */
        case 0xFF24:
            return 0xFF;

        /* TODO: Audio - Selection of sound output terminal */
        case 0xFF25:
            return 0xFF;

        /* TODO: Audio - Sound on/off */
        case 0xFF26:
            return 0xFF;

        case 0xFF27:
        case 0xFF28:
        case 0xFF29:
        case 0xFF2A:
        case 0xFF2B:
        case 0xFF2C:
        case 0xFF2D:
        case 0xFF2E:
        case 0xFF2F:
            return unmapped_io_read(address);

        /* TODO: Audio - Wave pattern RAM */
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
            return 0xFF;

        case 0xFF40:
            return gb.video.control_byte;

        case 0xFF41:
            return gb.video.lcd_status.value();

        case 0xFF42:
            return gb.video.scroll_y.value();

        case 0xFF43:
            return gb.video.scroll_x.value();

        case 0xFF44:
            return gb.video.line.value();

        case 0xFF45:
            return gb.video.ly_compare.value();

        case 0xFF46:
            log_warn("Attempted to read from write-only DMA Transfer/Start Address (0xFF46)");
            return 0xFF;

        case 0xFF47:
            return gb.video.bg_palette.value();

        case 0xFF48:
            return gb.video.sprite_palette_0.value();

        case 0xFF49:
            return gb.video.sprite_palette_1.value();

        case 0xFF4A:
            return gb.video.window_y.value();

        case 0xFF4B:
            return gb.video.window_x.value();

        /* TODO: CGB mode behaviour */
        case 0xFF4C:
            return 0xFF;

        case 0xFF4D:
            log_unimplemented("Attempted to read from 'Prepare Speed Switch' register");
            return 0x0;

        case 0xFF4E:
        case 0xFF4F:
            return unmapped_io_read(address);

        /* Disable boot rom switch */
        case 0xFF50:
            return disable_boot_rom_switch.value();

        case 0xFF51:
            log_unimplemented("Attempted to read from VRAM DMA Source (hi)");
            return 0xFF;

        case 0xFF52:
            log_unimplemented("Attempted to read from VRAM DMA Source (lo)");
            return 0xFF;

        case 0xFF53:
            log_unimplemented("Attempted to read from VRAM DMA Destination (hi)");
            return 0xFF;

        case 0xFF54:
            log_unimplemented("Attempted to read from VRAM DMA Destination (lo)");
            return 0xFF;

        case 0xFF55:
            log_unimplemented("Attempted to read from VRAM DMA Length/Mode/Start");
            return 0xFF;

        case 0xFF56:
            log_unimplemented("Attempted to read from infrared port");
            return 0xFF;

        case 0xFF57:
        case 0xFF58:
        case 0xFF59:
        case 0xFF5A:
        case 0xFF5B:
        case 0xFF5C:
        case 0xFF5D:
        case 0xFF5E:
        case 0xFF5F:
        case 0xFF60:
        case 0xFF61:
        case 0xFF62:
        case 0xFF63:
        case 0xFF64:
        case 0xFF65:
        case 0xFF66:
        case 0xFF67:
            return unmapped_io_read(address);

        /* TODO: Background color palette spec/index */
        case 0xFF68:
            log_unimplemented("Attempted to read from CGB background color palette spec/index");
            return 0xFF;

        /* TODO: Background color palette data */
        case 0xFF69:
            log_unimplemented("Attempted to read from CGB background color data");
            return 0xFF;

        /* TODO: OBJ color palette spec/index */
        case 0xFF6A:
            log_unimplemented("Attempted to read from CGB OBJ color palette spec/index");
            return 0xFF;

        /* TODO: OBJ color palette data */
        case 0xFF6B:
            log_unimplemented("Attempted to read from CGB OBJ color palette data");
            return 0xFF;

        /* TODO: Object priority mode */
        case 0xFF6C:
            log_unimplemented("Attempted to read from CGB object priority mode");
            return 0xFF;

        case 0xFF6D:
        case 0xFF6E:
        case 0xFF6F:
            return unmapped_io_read(address);

        /* TODO: CGB WRAM bank */
        case 0xFF70:
            log_unimplemented("Attempted to read from CGB WRAM bank");
            return 0xFF;

        /* TODO: Some undocumented registers in this range */
        case 0xFF71:
        case 0xFF72:
        case 0xFF73:
        case 0xFF74:
        case 0xFF75:
        case 0xFF76:
        case 0xFF77:
        case 0xFF78:
        case 0xFF79:
        case 0xFF7A:
        case 0xFF7B:
        case 0xFF7C:
        case 0xFF7D:
        case 0xFF7E:
        case 0xFF7F:
            return unmapped_io_read(address);

        default:
            fatal_error("Unmapped IO address: 0x%x", address.value());
    }
}

auto MMU::unmapped_io_read(const Address& address) const -> u8 {
    log_warn("Attempting to read from unused IO address 0x%x", address.value());
    return 0xFF;
}

void MMU::write(const Address& address, const u8 byte) {
    if (address.in_range(0x0000, 0x7FFF)) {
        gb.cartridge->write(address, byte);
        return;
    }

    /* VRAM */
    if (address.in_range(0x8000, 0x9FFF)) {
        gb.video.write(address.value() - 0x8000, byte);
        return;
    }

    /* External (cartridge) RAM */
    if (address.in_range(0xA000, 0xBFFF)) {
        gb.cartridge->write(address, byte);
        return;
    }

    /* Internal work RAM */
    if (address.in_range(0xC000, 0xDFFF)) {
        work_ram.at(address.value() - 0xC000) = byte;
        return;
    }

    /* Mirrored RAM */
    if (address.in_range(0xE000, 0xFDFF)) {
        log_warn("Attempting to write to mirrored work RAM");
        write(address.value() - 0x2000, byte);
        return;
    }

    /* OAM */
    if (address.in_range(0xFE00, 0xFE9F)) {
        oam_ram.at(address.value() - 0xFE00) = byte;
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
        high_ram.at(address.value() - 0xFF80) = byte;
        return;
    }

    /* Interrupt Enable register */
    if (address == 0xFFFF) {
        gb.cpu.interrupt_enabled.set(byte);
        return;
    }

    fatal_error("Attempted to write to unmapped memory address 0x%X", address.value());
}

void MMU::write_io(const Address& address, const u8 byte) {
    switch (address.value()) {
        case 0xFF00:
            gb.input.write(byte);
            return;

        case 0xFF01:
            /* Serial data transfer (SB) */
            gb.serial.write(byte);
            return;

        case 0xFF02:
            /* Serial data transfer (SB) */
            gb.serial.write_control(byte);
            return;

        case 0xFF03:
            return unmapped_io_write(address, byte);

        case 0xFF04:
            gb.timer.reset_divider();
            return;

        case 0xFF05:
            gb.timer.set_timer(byte);
            return;

        case 0xFF06:
            gb.timer.set_timer_modulo(byte);
            return;

        case 0xFF07:
            gb.timer.set_timer_control(byte);
            return;

        case 0xFF08:
        case 0xFF09:
        case 0xFF0A:
        case 0xFF0B:
        case 0xFF0C:
        case 0xFF0D:
        case 0xFF0E:
            return unmapped_io_write(address, byte);

        case 0xFF0F:
            gb.cpu.interrupt_flag.set(byte);
            return;

        /* TODO: Audio - Channel 1: Tone & Sweep */
        case 0xFF10:
        case 0xFF11:
        case 0xFF12:
        case 0xFF13:
        case 0xFF14:
            return;

        case 0xFF15:
            return unmapped_io_write(address, byte);

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

        case 0xFF1F:
            return unmapped_io_write(address, byte);

        /* TODO: Audio - Channel 4: Noise */
        case 0xFF20:
        case 0xFF21:
        case 0xFF22:
        case 0xFF23:
            return;

        /* TODO: Audio - Channel control/ON-OFF/Volume */
        case 0xFF24:
            return;

        /* TODO: Audio - Selection of sound output terminal */
        case 0xFF25:
            return;

        /* TODO: Audio - Sound on/off */
        case 0xFF26:
            log_unimplemented("Wrote to sound on/off address 0x%x - 0x%x", address.value(), byte);
            return;

        case 0xFF27:
        case 0xFF28:
        case 0xFF29:
        case 0xFF2A:
        case 0xFF2B:
        case 0xFF2C:
        case 0xFF2D:
        case 0xFF2E:
        case 0xFF2F:
            return unmapped_io_write(address, byte);

        /* TODO: Audio - Wave pattern RAM */
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
            return;

        /* Switch on LCD */
        case 0xFF40:
            gb.video.control_byte = byte;
            return;

        case 0xFF41:
            gb.video.lcd_status.set(byte);
            return;

        /* Vertical Scroll Register */
        case 0xFF42:
            gb.video.scroll_y.set(byte);
            return;

        /* Horizontal Scroll Register */
        case 0xFF43:
            gb.video.scroll_x.set(byte);
            return;

        /* LY - Line Y coordinate */
        case 0xFF44:
            /* "Writing will reset the counter */
            gb.video.line.set(0x0);
            return;

        case 0xFF45:
            gb.video.ly_compare.set(byte);
            return;

        case 0xFF46:
            dma_transfer(byte);
            return;

        case 0xFF47:
            gb.video.bg_palette.set(byte);
            log_trace("Set video palette: 0x%x", byte);
            return;

        case 0xFF48:
            gb.video.sprite_palette_0.set(byte);
            log_trace("Set sprite palette 0: 0x%x", byte);
            return;

        case 0xFF49:
            gb.video.sprite_palette_1.set(byte);
            log_trace("Set sprite palette 1: 0x%x", byte);
            return;

        case 0xFF4A:
            gb.video.window_y.set(byte);
            return;

        case 0xFF4B:
            gb.video.window_x.set(byte);
            return;

        /* TODO: CGB mode behaviour */
        case 0xFF4C:
            return;

        case 0xFF4D:
            log_unimplemented("Attempted to write to 'Prepare Speed Switch' register");
            return;

        case 0xFF4E:
        case 0xFF4F:
            return unmapped_io_write(address, byte);

        /* Disable boot rom switch */
        case 0xFF50:
            disable_boot_rom_switch.set(byte);
            global_logger.enable_tracing();
            log_debug("Boot rom was disabled");
            return;

        case 0xFF51:
            log_unimplemented("Attempted to write to VRAM DMA Source (hi)");
            return;

        case 0xFF52:
            log_unimplemented("Attempted to write to VRAM DMA Source (lo)");
            return;

        case 0xFF53:
            log_unimplemented("Attempted to write to VRAM DMA Destination (hi)");
            return;

        case 0xFF54:
            log_unimplemented("Attempted to write to VRAM DMA Destination (lo)");
            return;

        case 0xFF55:
            log_unimplemented("Attempted to write to VRAM DMA Length/Mode/Start");
            return;

        case 0xFF56:
            log_unimplemented("Attempted to write to infrared port");
            return;

        case 0xFF57:
        case 0xFF58:
        case 0xFF59:
        case 0xFF5A:
        case 0xFF5B:
        case 0xFF5C:
        case 0xFF5D:
        case 0xFF5E:
        case 0xFF5F:
        case 0xFF60:
        case 0xFF61:
        case 0xFF62:
        case 0xFF63:
        case 0xFF64:
        case 0xFF65:
        case 0xFF66:
        case 0xFF67:
            return unmapped_io_write(address, byte);

        /* TODO: Background color palette spec/index */
        case 0xFF68:
            log_unimplemented("Attempted to write to CGB background color palette spec/index");
            return;

        /* TODO: Background color palette data */
        case 0xFF69:
            log_unimplemented("Attempted to write to CGB background color data");
            return;

        /* TODO: OBJ color palette spec/index */
        case 0xFF6A:
            log_unimplemented("Attempted to write to CGB OBJ color palette spec/index");
            return;

        /* TODO: OBJ color palette data */
        case 0xFF6B:
            log_unimplemented("Attempted to write to CGB OBJ color palette data");
            return;

        /* TODO: Object priority mode */
        case 0xFF6C:
            log_unimplemented("Attempted to write to CGB object priority mode");
            return;

        case 0xFF6D:
        case 0xFF6E:
        case 0xFF6F:
            return unmapped_io_write(address, byte);

        /* TODO: CGB WRAM bank */
        case 0xFF70:
            log_unimplemented("Attempted to write to CGB WRAM bank");
            return;

        /* TODO: Some undocumented registers in this range */
        case 0xFF71:
        case 0xFF72:
        case 0xFF73:
        case 0xFF74:
        case 0xFF75:
        case 0xFF76:
        case 0xFF77:
        case 0xFF78:
        case 0xFF79:
        case 0xFF7A:
        case 0xFF7B:
        case 0xFF7C:
        case 0xFF7D:
        case 0xFF7E:
        case 0xFF7F:
            return unmapped_io_write(address, byte);

        default:
            fatal_error("Unmapped IO address: 0x%x", address.value());
    }
}

void MMU::unmapped_io_write(const Address& address, const u8 byte) {
    log_warn("Attempting to write to unused IO address 0x%x - 0x%x", address.value(), byte);
}

auto MMU::boot_rom_active() const -> bool { return read(0xFF50) != 0x1; }

void MMU::dma_transfer(const u8 byte) {
    Address start_address = byte * 0x100;

    for (u8 i = 0x0; i <= 0x9F; i++) {
        Address from_address = start_address.value() + i;
        Address to_address = 0xFE00 + i;

        u8 value_at_address = read(from_address);
        write(to_address, value_at_address);
    }
}
