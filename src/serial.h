#pragma once

#include "definitions.h"

class Serial {
public:
    u8 read() const;
    void write(u8 byte);
    void write_control(u8 byte);

private:
    u8 data;
};
