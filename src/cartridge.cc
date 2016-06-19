#include "cartridge.h"

#include "util/files.h"
#include "util/log.h"

Cartridge::Cartridge(std::string filename) {
    auto rom_data = read_bytes(filename);
    log_info("Loaded %d KB", rom_data.size() / 1024);

    // TODO: Is there a better way to convert a vector<char> to vector<uint8_t>?
    for (const auto v : rom_data) {
        data.push_back(static_cast<u8>(v));
    }

    log_info("\tTitle: %s", game_title().c_str());
    log_info("\tManufacturer: %d", data[0x13F]);
    log_info("\tSupports Color: %d", data[0x143]);
    log_info("\tCartridge Type: %d", data[0x147]);
    log_info("\tRom Size: %d", data[0x148]);
    log_info("\tRam Size: %d", data[0x149]);
    log_info("\tLicense Code: %d", data[0x144]);
    log_info("\tVersion Number: %d", data[0x14C]);
}

u8 Cartridge::read(const Address address) const {
    // TODO: check this address is in sensible bounds
    return data[address.value()];
}

std::string Cartridge::game_title() const {
    char name[TITLE_LENGTH] = {0};

    for (u8 i = 0; i < TITLE_LENGTH; i++) {
        name[i] = static_cast<char>(data[header::title + i]);
    }

    return std::string(name);

}
