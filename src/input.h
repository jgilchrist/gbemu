#pragma once

#include "definitions.h"

enum class GbButton {
    Up,
    Down,
    Left,
    Right,
    A,
    B,
    Select,
    Start,
};

class Input {
public:
    void button_pressed(GbButton button);
    void button_released(GbButton button);
    void write(u8 set);

    u8 get_input() const;

private:
    void set_button(GbButton button, bool set);

    bool up;
    bool down;
    bool left;
    bool right;
    bool a;
    bool b;
    bool select;
    bool start;

    bool button_switch;
    bool direction_switch;
};
