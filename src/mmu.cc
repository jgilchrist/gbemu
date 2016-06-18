#include "mmu.h"

#include "boot.h"
#include "util/log.h"

MMU::MMU(Cartridge& inCartridge) :
    cartridge(inCartridge)
{

}

uint8_t MMU::read(const Address address) const {
    if (address.in_range(0x0, 0x100)) {
        if (boot_rom_loaded) {
            return bootDMG[address.value()];
        }
    }

    return cartridge.read(address);
}

void MMU::write(const Address address, const uint8_t byte) const {
}

void MMU::write_word(const Address address, const uint16_t word) const {
}
