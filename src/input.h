#pragma once

/* FIXME: Figure out why importing SFML/Keyboard.hpp doesn't work */
#include <SFML/Graphics.hpp>

#include "definitions.h"

class Input {
public:
    void on_key_pressed(int event);
    void on_key_released(int event);
    void write(u8 set);

    u8 get_input() const;

private:
    void on_key(int event, bool set);

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
