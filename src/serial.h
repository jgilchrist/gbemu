#pragma once

#include "definitions.h"

class Serial {
public:
    Serial(bool _should_print) : should_print(_should_print) {}

    u8 read() const;
    void write(u8 byte);
    void write_control(u8 byte);

private:
    u8 data;

    bool should_print;
};
