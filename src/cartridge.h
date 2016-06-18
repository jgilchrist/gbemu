#pragma once

#include <string>
#include <vector>

class Cartridge {
public:
    Cartridge(std::string filename);

private:
    std::vector<char> data;
};
