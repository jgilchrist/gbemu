#include "files.h"

#include <fstream>

std::vector<char> read_bytes(const std::string filename) {
    using namespace std;

    ifstream stream(filename.c_str(), ios::binary|ios::ate);
    ifstream::pos_type position = stream.tellg();

    std::vector<char> result(position);

    stream.seekg(0, ios::beg);
    stream.read(&result[0], position);

    return result;
}
