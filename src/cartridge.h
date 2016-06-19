#pragma once

#include "address.h"

#include <string>
#include <vector>

using namespace std;

namespace header {
    const int entry_point = 0x100;
    const int logo = 0x104;
    const int title = 0x134;
    const int manufacturer_code = 0x13F;
    const int cgb_flag = 0x143;
    const int new_license_code = 0x144;
    const int sgb_flag = 0x146;
    const int cartridge_type = 0x147;
    const int rom_size = 0x148;
    const int ram_size = 0x149;
    const int destination_code = 0x14A;
    const int old_license_code = 0x14B;
    const int version_number = 0x14C;
    const int header_checksum = 0x14D;
    const int global_checksum = 0x14E;
}

const int TITLE_LENGTH = 11;

class Cartridge {
public:
    Cartridge(string filename);

    u8 read(const Address address) const;

    /* Cartridge header information */
    string game_title() const;
    string game_designation() const;

private:
    vector<char> data;
};
