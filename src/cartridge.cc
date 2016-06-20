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

    u8 type_code = data[header::cartridge_type];
    u8 version_code = data[header::version_number];
    u8 rom_size_code = data[header::rom_size];
    u8 ram_size_code = data[header::ram_size];

    type = get_type(type_code);
    version = version_code;
    rom_size = get_rom_size(rom_size_code);
    ram_size = get_ram_size(ram_size_code);

    log_info("Title:\t\t %s (version %d)", game_title().c_str(), version);
    log_info("Cartridge:\t\t %s", describe(type).c_str());
    log_info("Rom Size:\t\t %s", describe(rom_size).c_str());
    log_info("Ram Size:\t\t %s", describe(ram_size).c_str());
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
