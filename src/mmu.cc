#include "mmu.h"

#include "boot.h"
#include "util/log.h"

MMU::MMU(Cartridge& inCartridge) :
    cartridge(inCartridge)
{

}

uint8_t MMU::read(const Address address) const {
    if (address.in_range(0x0, 0x7FFF)) {
        if (address.in_range(0x0, 0xFF) && boot_rom_active()) {
            return bootDMG[address.value()];
        }
        return cartridge.read(address);
    }

    return 0;
}

void MMU::write(const Address address, const uint8_t byte) const {
}

void MMU::write_word(const Address address, const uint16_t word) const {
}

bool MMU::boot_rom_active() const {
    return read(0xFF50) != 0x1;
}
