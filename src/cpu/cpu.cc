#include "cpu.h"

#include "opcode_cycles.h"
#include "../util/bitwise.h"
#include "../util/log.h"

using bitwise::compose_bytes;

CPU::CPU(MMU& inMMU) :
    mmu(inMMU),
    af(a, f),
    bc(b, c),
    de(d, e),
    hl(h, l)
{
}

Cycles CPU::tick() {
    log_trace("PC: 0x%04X", pc.value());
    auto opcode = get_byte_from_pc();
    return execute_opcode(opcode);
}

Cycles CPU::execute_opcode(const u8 opcode) {
    branch_taken = false;

    if (opcode == 0xCB) {
        execute_cb_opcode();
        unsigned cycles = opcode_cycles_cb[opcode];
        return cycles;
    }

    execute_normal_opcode(opcode);

    unsigned cycles = !branch_taken
        ? opcode_cycles[opcode]
        : opcode_cycles_branched[opcode];

    return cycles;
}

u8 CPU::get_byte_from_pc() {
    u8 byte = mmu.read(Address(pc));
    pc.increment();

    return byte;
}

s8 CPU::get_signed_byte_from_pc() {
    u8 byte = get_byte_from_pc();
    return static_cast<s8>(byte);
}

u16 CPU::get_word_from_pc() {
    u8 low_byte = get_byte_from_pc();
    u8 high_byte = get_byte_from_pc();

    return compose_bytes(high_byte, low_byte);
}

void CPU::set_flag_zero(bool set) {
    f.set_bit_to(7, set);
}

void CPU::set_flag_subtract(bool set) {
    f.set_bit_to(6, set);
}

void CPU::set_flag_half_carry(bool set) {
    f.set_bit_to(5, set);
}

void CPU::set_flag_carry(bool set) {
    f.set_bit_to(4, set);
}

void CPU::reset_flags() {
    set_flag_zero(false);
    set_flag_subtract(false);
    set_flag_half_carry(false);
    set_flag_carry(false);
}

bool CPU::flag_zero() const {
    return f.check_bit(7);
}

bool CPU::flag_subtract() const {
    return f.check_bit(6);
}

bool CPU::flag_half_carry() const {
    return f.check_bit(5);
}

bool CPU::flag_carry() const {
    return f.check_bit(4);
}

bool CPU::is_condition(Condition condition) {
    bool should_branch;

    switch (condition) {
        case Condition::C:
            should_branch = flag_carry();
            break;
        case Condition::NC:
            should_branch = !flag_carry();
            break;
        case Condition::Z:
            should_branch = flag_zero();
            break;
        case Condition::NZ:
            should_branch = !flag_zero();
            break;
    }

    /* If the branch is taken, remember so that the correct processor cycles
     * can be used */
    branch_taken = should_branch;
    return should_branch;
}

u8 CPU::flag_half_carry_value() const {
    return static_cast<u8>(flag_half_carry() ? 1 : 0);
}

u8 CPU::flag_carry_value() const {
    return static_cast<u8>(flag_carry() ? 1 : 0);
}

void CPU::stack_push(const WordRegister& reg) {
    sp.decrement();
    mmu.write(Address(sp), reg.high());
    sp.decrement();
    mmu.write(Address(sp), reg.low());
}

void CPU::stack_pop(WordRegister& reg) {
    u8 low_byte = mmu.read(Address(sp));
    sp.increment();
    u8 high_byte = mmu.read(Address(sp));
    sp.increment();

    u16 value = compose_bytes(high_byte, low_byte);
    reg.set(value);
}

/* TODO: reduce duplication with a WordValue interface */
/* TODO: Should this write the value before decrementing the stack pointer? */
void CPU::stack_push(const RegisterPair& reg) {
    sp.decrement();
    mmu.write(Address(sp), reg.high());
    sp.decrement();
    mmu.write(Address(sp), reg.low());
}

void CPU::stack_pop(RegisterPair& reg) {
    u8 low_byte = mmu.read(Address(sp));
    sp.increment();
    u8 high_byte = mmu.read(Address(sp));
    sp.increment();

    u16 value = compose_bytes(high_byte, low_byte);
    reg.set(value);
}
