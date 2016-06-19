#include "cpu.h"

#include "../bitwise.h"
#include "../util/log.h"

#include <stdexcept>

CPU::CPU(MMU& inMMU) :
    mmu(inMMU)
{
}

void CPU::tick() {
    log_trace("PC: 0x%x", pc.value());
    auto opcode = get_byte_from_pc();
    execute_opcode(opcode);
}

void CPU::execute_opcode(const u8 opcode) {
    if (opcode != 0xCB) {
        execute_normal_opcode(opcode);
    } else {
        execute_cb_opcode();
    }
}

u8 CPU::get_byte_from_pc() {
    u8 byte = mmu.read(Address(pc));
    pc.increment();

    return byte;
}

u16 CPU::get_word_from_pc() {
    u8 low_byte = get_byte_from_pc();
    u8 high_byte = get_byte_from_pc();

    return compose_bytes(low_byte, high_byte);
}

void CPU::set_flag_zero(bool b) {
    f.set(set_bit_to(f.value(), 7, b));
}

void CPU::set_flag_subtract(bool b) {
    f.set(set_bit_to(f.value(), 6, b));
}

void CPU::set_flag_half_carry(bool b) {
    f.set(set_bit_to(f.value(), 5, b));
}

void CPU::set_flag_carry(bool b) {
    f.set(set_bit_to(f.value(), 4, b));
}

void CPU::set_flags(Flags f) {
    set_flag_zero(f.zero);
    set_flag_subtract(f.subtract);
    set_flag_half_carry(f.half_carry);
    set_flag_carry(f.carry);
}

bool CPU::flag_zero() const {
    return check_bit(f.value(), 7);
}

bool CPU::flag_subtract() const {
    return check_bit(f.value(), 6);

}

bool CPU::flag_half_carry() const {
    return check_bit(f.value(), 5);

}

bool CPU::flag_carry() const {
    return check_bit(f.value(), 4);

}

bool CPU::is_condition(Condition condition) const {
    switch (condition) {
        case Condition::C:
            return flag_carry();
        case Condition::NC:
            return !flag_carry();
        case Condition::Z:
            return flag_zero();
        case Condition::NZ:
            return !flag_zero();
    }
}

u8 CPU::flag_half_carry_value() const {
    return static_cast<u8>(flag_half_carry() ? 1 : 0);

}

u8 CPU::flag_carry_value() const {
    return static_cast<u8>(flag_carry() ? 1 : 0);

}
