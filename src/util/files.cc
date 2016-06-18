#include <fstream>

std::vector<char> read_bytes(const char* filename) {
    ifstream stream(filename, ios::binary|ios::ate);
    ifstream::pos_type position = stream.tellg();

    std::vector<char> result(position);

    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], position);

    return result;
}
