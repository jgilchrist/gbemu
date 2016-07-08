#include "files.h"

#include "log.h"
#include <fstream>

std::vector<char> read_bytes(const std::string filename) {
    using std::ifstream;
    using std::ios;

    ifstream stream(filename.c_str(), ios::binary|ios::ate);
    ifstream::pos_type position = stream.tellg();
    size_t file_size = static_cast<size_t>(position);

    if (file_size == -1) {
        log_error("Cannot read from file: %s", filename.c_str());
        exit(1);
    }

    std::vector<char> result(file_size);

    stream.seekg(0, ios::beg);
    stream.read(&result[0], position);
    stream.close();

    return result;
}
