#include "cartridge_info.h"

#include "util/log.h"

CartridgeType get_type(u8 type) {
    switch (type) {
        case 0x00:
        case 0x08:
        case 0x09:
            return CartridgeType::ROMOnly;

        case 0x01:
        case 0x02:
        case 0x03:
        case 0xFF:
            return CartridgeType::MBC1;

        case 0x05:
        case 0x06:
            return CartridgeType::MBC2;

        case 0x0F:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
            return CartridgeType::MBC3;

        case 0x15:
        case 0x16:
        case 0x17:
            return CartridgeType::MBC4;

        case 0x19:
        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x1E:
            return CartridgeType::MBC5;

        case 0x0B:
        case 0x0C:
        case 0x0D:
        case 0x20:
        case 0x22:
        case 0xFC:
        case 0xFD:
        case 0xFE:
            return CartridgeType::Unknown;

        default:
            log_error("Unknown cartridge type: %X", type);
            return CartridgeType::Unknown;
    }
}

std::string describe(CartridgeType type) {
    switch (type) {
        case CartridgeType::ROMOnly:
            return "ROM Only";
        case CartridgeType::MBC1:
            return "MBC1";
        case CartridgeType::MBC2:
            return "MBC2";
        case CartridgeType::MBC3:
            return "MBC3";
        case CartridgeType::MBC4:
            return "MBC4";
        case CartridgeType::MBC5:
            return "MBC5";
        case CartridgeType::Unknown:
            return "Unknown";
    }
}


std::string get_license(u16 old_license, u16 new_license) {
    /* TODO */
    unused(old_license, new_license);
    log_error("License not implemented");
    return "";
}


ROMSize get_rom_size(u8 size_code) {
    switch (size_code) {
        case 0x00:
            return ROMSize::KB32;
        case 0x01:
            return ROMSize::KB64;
        case 0x02:
            return ROMSize::KB128;
        case 0x03:
            return ROMSize::KB256;
        case 0x04:
            return ROMSize::KB512;
        case 0x05:
            return ROMSize::MB1;
        case 0x06:
            return ROMSize::MB2;
        case 0x07:
            return ROMSize::MB4;
        case 0x52:
            return ROMSize::MB1p1;
        case 0x53:
            return ROMSize::MB1p2;
        case 0x54:
            return ROMSize::MB1p5;
        default:
            log_error("Unknown ROM size: %X", size_code);
            return ROMSize::KB32;
    }
}

std::string describe(ROMSize size) {
    switch (size) {
        case ROMSize::KB32:
            return "32KB (no ROM banking)";
        case ROMSize::KB64:
            return "64KB (4 banks)";
        case ROMSize::KB128:
            return "128KB (8 banks)";
        case ROMSize::KB256:
            return "256KB (16 banks)";
        case ROMSize::KB512:
            return "512KB (32 banks)";
        case ROMSize::MB1:
            return "1MB (64 banks)";
        case ROMSize::MB2:
            return "2MB (128 banks)";
        case ROMSize::MB4:
            return "4MB (256 banks)";
        case ROMSize::MB1p1:
            return "1.1MB (72 banks)";
        case ROMSize::MB1p2:
            return "1.2MB (80 banks)";
        case ROMSize::MB1p5:
            return "1.5MB (96 banks)";
    }
}


RAMSize get_ram_size(u8 size_code) {
    switch (size_code) {
        case 0x00:
            return RAMSize::None;
        case 0x01:
            return RAMSize::KB2;
        case 0x02:
            return RAMSize::KB8;
        case 0x03:
            return RAMSize::KB32;
        case 0x04:
            return RAMSize::KB128;
        case 0x05:
            return RAMSize::KB64;
        default:
            log_error("Unknown RAM size: %X", size_code);
            return RAMSize::None;
    }
}

std::string describe(RAMSize size) {
    switch (size) {
        case RAMSize::None:
            return "No RAM";
        case RAMSize::KB2:
            return "2KB";
        case RAMSize::KB8:
            return "8KB";
        case RAMSize::KB32:
            return "32KB";
        case RAMSize::KB128:
            return "128KB";
        case RAMSize::KB64:
            return "64KB";
    }
}


Destination get_destination(u8 destination) {
    switch (destination) {
        case 0x00:
            return Destination::Japanese;
        case 0x01:
            return Destination::NonJapanese;
        default:
            log_error("Unknown destination: %X", destination);
            return Destination::NonJapanese;
    }
}

std::string describe(Destination destination) {
    switch (destination) {
        case Destination::Japanese:
            return "Japanese";
        case Destination::NonJapanese:
            return "Non-Japanese";
    }
}
