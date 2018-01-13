#include "input.h"

#include "util/bitwise.h"

void Input::on_key_pressed(int keyCode) {
    on_key(keyCode, true);
}

void Input::on_key_released(int keyCode) {
    on_key(keyCode, false);
}

void Input::on_key(int keyCode, bool set) {
    if (keyCode == sf::Keyboard::Up) { up = set; }
    if (keyCode == sf::Keyboard::Down) { down = set; }
    if (keyCode == sf::Keyboard::Left) { left = set; }
    if (keyCode == sf::Keyboard::Right) { right = set; }
    if (keyCode == sf::Keyboard::X) { a = set; }
    if (keyCode == sf::Keyboard::Z) { b = set; }
    if (keyCode == sf::Keyboard::Return) { start = set; }
    if (keyCode == sf::Keyboard::BackSpace) { select = set; }
}

void Input::write(u8 set) {
    using bitwise::check_bit;

    direction_switch = !check_bit(set, 4);
    button_switch = !check_bit(set, 5);
}

u8 Input::get_input() const {
    using bitwise::set_bit_to;

    u8 buttons = 0b1111;

    if (direction_switch) {
        buttons = set_bit_to(buttons, 0, !right);
        buttons = set_bit_to(buttons, 1, !left);
        buttons = set_bit_to(buttons, 2, !up);
        buttons = set_bit_to(buttons, 3, !down);
    }

    if (button_switch) {
        buttons = set_bit_to(buttons, 0, !a);
        buttons = set_bit_to(buttons, 1, !b);
        buttons = set_bit_to(buttons, 2, !select);
        buttons = set_bit_to(buttons, 3, !start);
    }

    buttons = set_bit_to(buttons, 4, !direction_switch);
    buttons = set_bit_to(buttons, 5, !button_switch);

    return buttons;
}
