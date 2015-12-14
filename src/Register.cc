#include "Register.h"

Register::Register() {

}

void Register::set(const uint8_t byte) {
    val = byte;
}

uint8_t Register::value() {
    return val;
}

void Register::increment() {
    val += 1;
}

void Register::decrement() {
    val -= 1;
}
