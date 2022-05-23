#pragma once

#include "definitions.h"
#include "options.h"

#include <functional>

using get_serial_data_callback_t = std::function<u8()>;

class Serial {
public:
    Serial(
        Options& inOptions
    ) : options(inOptions) {}

    void register_get_data_callback(const get_serial_data_callback_t& _serial_data_callback);

    auto read() const -> u8;
    void write(u8 byte);
    void write_control(u8 byte) const;

private:
    Options& options;
    u8 data;

    get_serial_data_callback_t get_serial_data_callback;
};
