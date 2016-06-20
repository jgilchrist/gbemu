#pragma once

#include "address.h"
#include "cartridge_info.h"

#include <string>
#include <vector>

class Cartridge {
public:
    Cartridge(std::string filename);

    u8 read(const Address address) const;

    std::string game_title() const;

private:
    std::vector<u8> data;

    std::string title;

    /* Cartridge information */
    CartridgeType type;
    Destination destination;
    ROMSize rom_size;
    RAMSize ram_size;
    std::string license_code;
    u8 version;

    u16 header_checksum;
    u16 global_checksum;

    bool supports_cgb;
    bool supports_sgb;
};
