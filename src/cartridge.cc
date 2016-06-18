#include "cartridge.h"

#include "util/files.h"
#include "util/log.h"

#include <vector>

Cartridge::Cartridge(string filename) {
    auto rom_data = read_bytes(filename);
    log_info("Loaded %d KB", rom_data.size() / 1024);

    data = rom_data;

    log_info("Info:")
    log_info("\tTitle: %s", game_title().c_str());
    log_info("\tmanufacturer_code: %d", data[0x13F]);
    log_info("\tcgb_flag: %d", data[0x143]);
    log_info("\tnew_license_code: %d", data[0x144]);
    log_info("\tsgb_flag: %d", data[0x146]);
    log_info("\tcartridge_type: %d", data[0x147]);
    log_info("\trom_size: %d", data[0x148]);
    log_info("\tram_size: %d", data[0x149]);
    log_info("\tdestination_code: %d", data[0x14A]);
    log_info("\told_license_code: %d", data[0x14B]);
    log_info("\tversion_number: %d", data[0x14C]);
    log_info("\theader_checksum: %d", data[0x14D]);
    log_info("\tglobal_checksum: %d", data[0x14E]);
}

string Cartridge::game_title() const {
    char name[TITLE_LENGTH] = {0};

    for (int i = 0; i < TITLE_LENGTH; i++) {
        name[i] = data[header::title + i];
    }

    return string(name);

}
