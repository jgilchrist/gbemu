#pragma once

#include "../screen.h"

class NullScreen : public Screen {
public:
    ~NullScreen() override = default;

    void clear() override;
    void draw(const FrameBuffer& buffer) override;
    void process_events() override;
    bool is_open() override;
};
