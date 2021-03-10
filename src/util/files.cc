#include "files.h"

#include "log.h"
#include <fstream>

std::vector<u8> read_bytes(const std::string& filename) {
    using std::ifstream;
    using std::ios;

    ifstream stream(filename.c_str(), ios::binary|ios::ate);

    if (!stream.good()) {
        fatal_error("Cannot read from file: %s", filename.c_str());
    }

    ifstream::pos_type position = stream.tellg();
    size_t file_size = static_cast<size_t>(position);

    std::vector<char> file_contents(file_size);

    stream.seekg(0, ios::beg);
    stream.read(&file_contents[0], static_cast<std::streamsize>(position));
    stream.close();

    auto data = std::vector<u8>(file_contents.begin(), file_contents.end());

    return data;
}
