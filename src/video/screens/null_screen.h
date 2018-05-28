#pragma once

#include "../screen.h"

class NullScreen : public Screen {
public:
    ~NullScreen() override = default;

    void draw(const FrameBuffer& buffer) override;
    bool is_open() override;
};
