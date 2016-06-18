#include "cartridge.h"

#include "util/files.h"
#include "util/log.h"

Cartridge::Cartridge(std::string filename) {
    auto rom_data = read_bytes(filename);
    log_info("Loaded %d KB", rom_data.size() / 1024);
}
