#pragma once

#include "../screen.h"

class NullScreen : public Screen {
public:
    ~NullScreen() override = default;

    void draw(const FrameBuffer& buffer, const uint scrollx, const uint scrolly) override;
    bool is_open() override;
};
