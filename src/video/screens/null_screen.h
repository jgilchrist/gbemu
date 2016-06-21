#pragma once

#include "../screen.h"

class NullScreen : public Screen {
public:
    NullScreen();
    ~NullScreen();

    virtual void draw(const FrameBuffer& buffer);
    virtual bool is_open();
};
