#include "cpu.h"

#include "../util/bitwise.h"
#include "../util/log.h"

#include <cstdlib>

using bitwise::check_bit;

[[noreturn]] inline void unimplemented_opcode() {
    log_error("Unimplemented opcode");
    std::exit(1);
}


/* ADC */
void CPU::_opcode_adc(u8 value) {
    u8 reg = a.value();
    u8 carry = flag_carry_value();

    u16 result16 = reg + value + carry;

    set_flag_zero(reg == 0);
    set_flag_subtract(false);
    set_flag_half_carry((reg & 0xf) + (value & 0xf) + (carry & 0xf) > 0xf);
    set_flag_carry((result16 & 0x100) != 0);

    u8 result = static_cast<u8>(result16);
    a.set(result);
}

void CPU::opcode_adc() {
    _opcode_adc(get_byte_from_pc());
}

void CPU::opcode_adc(const ByteRegister& reg) {
    _opcode_adc(reg.value());
}

void CPU::opcode_adc(const Address&& addr) {
    _opcode_adc(mmu.read(addr));
}


/* ADD */
void CPU::_opcode_add(u8 reg, u8 value) {
    u16 result16 = reg + value;

    set_flag_zero(a.value() == 0);
    set_flag_subtract(false);
    set_flag_half_carry((reg & 0xf) + (value & 0xf) > 0xf);
    set_flag_carry((result16 & 0x100) != 0);

    u8 result = static_cast<u8>(result16);
    a.set(result);
}

void CPU::opcode_add_a() {
    _opcode_add(a.value(), get_byte_from_pc());
}

void CPU::opcode_add_a(const ByteRegister& reg) {
    _opcode_add(a.value(), reg.value());
}

void CPU::opcode_add_a(const Address& addr) {
    _opcode_add(a.value(), mmu.read(addr));
}


void CPU::opcode_add_hl(const RegisterPair& reg_pair) {
    u16 reg = hl.value();
    u16 value = reg_pair.value();

    u16 result16 = reg + value;

    set_flag_subtract(false);
    set_flag_half_carry((reg & 0xfff) + (value & 0xfff) > 0xfff);
    set_flag_carry((result16 & 0x10000) != 0);

    hl.set(result16);
}

void CPU::opcode_add_hl(const WordRegister& word_reg) {
    unused(word_reg);
    unimplemented_opcode();
}

void CPU::opcode_add_sp() {
    unimplemented_opcode();
}

void CPU::opcode_add_signed() {
    unimplemented_opcode();
}


/* AND */
void CPU::_opcode_and(u8 value) {
    u8 reg = a.value();

    u8 result = reg & value;

    set_flag_zero(result == 0);
    set_flag_half_carry(true);
    set_flag_carry(false);
    set_flag_subtract(false);

    a.set(result);
}

void CPU::opcode_and() {
    _opcode_and(get_byte_from_pc());
}

void CPU::opcode_and(ByteRegister& reg) {
    _opcode_and(reg.value());
}

void CPU::opcode_and(Address&& addr) {
    _opcode_and(mmu.read(addr));
}


/* BIT */
void CPU::_opcode_bit(const u8 bit, const u8 value) {
    set_flag_zero(!check_bit(value, bit));
    set_flag_subtract(false);
    set_flag_half_carry(true);
}

void CPU::opcode_bit(const u8 bit, ByteRegister& reg) {
    _opcode_bit(bit, reg.value());
}

void CPU::opcode_bit(const u8 bit, Address&& addr) {
    _opcode_bit(bit, mmu.read(addr));
}


/* CALL */
void CPU::opcode_call() {
    u16 address = get_word_from_pc();
    stack_push(pc);
    pc.set(address);
}

void CPU::opcode_call(Condition condition) {
    if (is_condition(condition)) {
        opcode_call();
    } else {
        /* Consume unused word argument */
        get_word_from_pc();
    }
}


/* CCF */
void CPU::opcode_ccf() {
    unimplemented_opcode();
}


/* CP */
void CPU::_opcode_cp(const u8 value) {
    u8 reg = a.value();
    u8 result = static_cast<u8>(reg - value);

    /* FIXME: Should this be set if the result is 0? */
    set_flag_zero(result == 0);
    set_flag_subtract(true);
    set_flag_half_carry((int)(reg & 0xf) - (int)(value & 0xf) < 0);
    set_flag_carry(reg < value);
}

void CPU::opcode_cp() {
    _opcode_cp(get_byte_from_pc());
}

void CPU::opcode_cp(const ByteRegister& reg) {
    _opcode_cp(reg.value());
}

void CPU::opcode_cp(const Address& addr) {
    _opcode_cp(mmu.read(addr));
}


/* CPL */
void CPU::opcode_cpl() {
    u8 reg = a.value();
    u8 result = !reg;
    a.set(result);

    set_flag_subtract(true);
    set_flag_half_carry(true);
}


/* DAA */
void CPU::opcode_daa() {
    unimplemented_opcode();
}


/* DEC */
void CPU::opcode_dec(ByteRegister& reg) {
    reg.decrement();

    set_flag_zero(reg.value() == 0);
    set_flag_subtract(true);
    set_flag_half_carry((reg.value() & 0x0F) == 0x0F);
}

void CPU::opcode_dec(RegisterPair& reg) {
    reg.decrement();

    set_flag_zero(reg.value() == 0);
    set_flag_subtract(true);
    set_flag_half_carry((reg.value() & 0x0F) == 0x0F);
}

void CPU::opcode_dec(WordRegister& reg) {
    reg.decrement();

    set_flag_zero(reg.value() == 0);
    set_flag_subtract(true);
    set_flag_half_carry((reg.value() & 0x0F) == 0x0F);
}

void CPU::opcode_dec(Address&& addr) {
    u8 value = mmu.read(addr);
    u8 result = static_cast<u8>(value - 1);
    mmu.write(addr, result);

    set_flag_zero(result == 0);
    set_flag_subtract(true);
    set_flag_half_carry((result & 0x0F) == 0x0F);
}


/* DI */
void CPU::opcode_di() {
    interrupts_enabled = false;
}


/* EI */
void CPU::opcode_ei() {
    interrupts_enabled = true;
}


/* INC */
void CPU::opcode_inc(ByteRegister& reg) {
    reg.increment();

    set_flag_zero(reg.value() == 0);
    set_flag_subtract(false);
    set_flag_half_carry((reg.value() & 0x0F) == 0x00);
}

void CPU::opcode_inc(RegisterPair& reg) {
    reg.increment();

    set_flag_zero(reg.value() == 0);
    set_flag_subtract(false);
    set_flag_half_carry((reg.value() & 0x0F) == 0x00);
}

void CPU::opcode_inc(WordRegister& reg) {
    reg.increment();

    set_flag_zero(reg.value() == 0);
    set_flag_subtract(false);
    set_flag_half_carry((reg.value() & 0x0F) == 0x00);
}

void CPU::opcode_inc(Address&& addr) {
    u8 value = mmu.read(addr);
    u8 result = static_cast<u8>(value + 1);
    mmu.write(addr, result);

    set_flag_zero(result == 0);
    set_flag_subtract(false);
    set_flag_half_carry((result & 0x0F) == 0x00);
}


/* JP */
void CPU::opcode_jp() {
    u16 address = get_word_from_pc();
    pc.set(address);
}

void CPU::opcode_jp(Condition condition) {
    if (is_condition(condition)) {
        opcode_jp();
    } else {
        /* Consume unused word argument */
        get_word_from_pc();
    }
}

void CPU::opcode_jp(const Address& addr) {
    /* FIXME: Should this jump to HL, or the address at HL? */
    unused(addr);
    pc.set(hl.value());
}


/* JR */
void CPU::opcode_jr() {
    s8 offset = get_signed_byte_from_pc();
    u16 old_pc = pc.value();

    u16 new_pc = static_cast<u16>(old_pc + offset);
    pc.set(new_pc);
}

void CPU::opcode_jr(Condition condition) {
    if (is_condition(condition)) {
        opcode_jr();
    } else {
        /* Consume unused argument */
        get_signed_byte_from_pc();
    }
}


/* HALT */
void CPU::opcode_halt() {
    unimplemented_opcode();
}


/* LD */
void CPU::opcode_ld(ByteRegister& reg) {
    u8 n = get_byte_from_pc();
    reg.set(n);
}

void CPU::opcode_ld(ByteRegister& reg, const ByteRegister& byte_reg) {
    reg.set(byte_reg.value());
}

void CPU::opcode_ld(ByteRegister& reg, const Address& address) {
    reg.set(mmu.read(address));
}


void CPU::opcode_ld(RegisterPair& reg) {
    u16 nn = get_word_from_pc();
    reg.set(nn);
}


void CPU::opcode_ld(WordRegister& reg) {
    u16 nn = get_word_from_pc();
    reg.set(nn);
}

void CPU::opcode_ld(WordRegister& reg, const RegisterPair& reg_pair) {
    unused(reg, reg_pair);
    unimplemented_opcode();
}


void CPU::opcode_ld(const Address& address) {
    u8 n = get_byte_from_pc();
    mmu.write(address, n);
}

void CPU::opcode_ld(const Address& address, const ByteRegister& byte_reg) {
    mmu.write(address, byte_reg.value());
}

void CPU::opcode_ld(const Address& address, const WordRegister& word_reg) {
    /* FIXME: low then high, or high then low? */
    mmu.write(address, word_reg.low());
    mmu.write(address + 1, word_reg.high());
}


void CPU::opcode_ld_to_addr(const ByteRegister &reg) {
    u16 address = get_word_from_pc();
    mmu.write(Address(address), reg.value());
}


/* LDD */
void CPU::opcode_ldd(ByteRegister& reg, const Address& address) {
    /* TODO: clean up
     * two ways of doing ldd
     * address is always that of HL */
    reg.set(mmu.read(address));
    hl.decrement();
}

void CPU::opcode_ldd(const Address& address, const ByteRegister& reg) {
    mmu.write(address, reg.value());
    hl.decrement();
}


/* LDH */
void CPU::opcode_ldh_into_a() {
    u8 offset = get_byte_from_pc();
    auto address = Address(0xFF00 + offset);

    u8 value = mmu.read(address);
    a.set(value);
}

void CPU::opcode_ldh_into_data() {
    u8 offset = get_byte_from_pc();
    auto address = Address(0xFF00 + offset);

    mmu.write(address, a.value());
}

void CPU::opcode_ldh_into_c() {
    u8 offset = c.value();
    auto address = Address(0xFF00 + offset);

    mmu.write(address, a.value());
}


/* LDHL */
void CPU::opcode_ldhl() {
    unimplemented_opcode();
}


/* LDI */
void CPU::opcode_ldi(ByteRegister& reg, const Address& address) {
    reg.set(mmu.read(address));
    hl.increment();
}

void CPU::opcode_ldi(const Address& address, const ByteRegister& reg) {
    mmu.write(address, reg.value());
    hl.increment();
}


/* NOP */
void CPU::opcode_nop() {
    /* Do nothing */
}


/* OR */
void CPU::_opcode_or(u8 value) {
    u8 reg = a.value();

    u8 result = reg | value;

    set_flag_zero(result == 0);
    set_flag_half_carry(false);
    set_flag_carry(false);
    set_flag_subtract(false);

    a.set(result);
}

void CPU::opcode_or() {
    _opcode_or(get_byte_from_pc());
}

void CPU::opcode_or(const ByteRegister& reg) {
    _opcode_or(reg.value());
}

void CPU::opcode_or(const Address& addr) {
    _opcode_or(mmu.read(addr));
}


/* POP */
void CPU::opcode_pop(RegisterPair& reg) {
    stack_pop(reg);
}


/* PUSH */
void CPU::opcode_push(const RegisterPair& reg) {
    stack_push(reg);
}


/* RES */
void CPU::opcode_res(const int bit, ByteRegister& reg) {
    unused(bit, reg);
    unimplemented_opcode();
}

void CPU::opcode_res(const int bit, Address&& addr) {
    unused(bit, addr);
    unimplemented_opcode();
}


/* RET */
void CPU::opcode_ret() {
    stack_pop(pc);
}

void CPU::opcode_ret(Condition condition) {
    if (is_condition(condition)) {
        opcode_ret();
    }
}


/* RETI */
void CPU::opcode_reti() {
    unimplemented_opcode();
}


/* RL */
void CPU::opcode_rla() {
    opcode_rl(a);
    set_flag_zero(false);
}

void CPU::opcode_rl(ByteRegister& reg) {
    u8 carry = flag_carry_value();
    u8 value = reg.value();

    bool will_carry = check_bit(value, 7);
    set_flag_carry(will_carry);

    u8 result = static_cast<u8>(value << 1);
    result |= carry;

    set_flag_zero(result == 0);

    set_flag_subtract(false);
    set_flag_half_carry(false);

    reg.set(result);
}

void CPU::opcode_rl(Address&& addr) {
    u8 old_carry = flag_carry_value();
    u8 value = mmu.read(addr);

    /* TODO: in other emulators, flags are only reset if carry flag is not set */

    bool will_carry = check_bit(value, 7);
    set_flag_carry(will_carry);

    u8 result = static_cast<u8>(value << 1);
    result |= old_carry;

    set_flag_zero(result == 0);

    set_flag_subtract(false);
    set_flag_half_carry(false);

    mmu.write(addr, result);
}


/* RLC */
void CPU::opcode_rlca() {
    unimplemented_opcode();
}

void CPU::opcode_rlc(ByteRegister& reg) {
    unused(reg);
    unimplemented_opcode();
}

void CPU::opcode_rlc(Address&& addr) {
    unused(addr);
    unimplemented_opcode();
}


/* RR */
void CPU::opcode_rra() {
    opcode_rr(a);
    set_flag_zero(false);
}

void CPU::opcode_rr(ByteRegister& reg) {
    u8 carry = flag_carry_value();
    u8 value = reg.value();

    bool will_carry = check_bit(value, 0);
    set_flag_carry(will_carry);

    u8 result = static_cast<u8>(value >> 1);
    result |= (carry << 7);

    set_flag_zero(result == 0);

    set_flag_subtract(false);
    set_flag_half_carry(false);

    reg.set(result);
}

void CPU::opcode_rr(Address&& addr) {
    u8 carry = flag_carry_value();
    u8 value = mmu.read(addr);

    bool will_carry = check_bit(value, 0);
    set_flag_carry(will_carry);

    u8 result = static_cast<u8>(value >> 1);
    result |= (carry << 7);

    set_flag_zero(result == 0);

    set_flag_subtract(false);
    set_flag_half_carry(false);

    mmu.write(addr, result);
}


/* RRC */
void CPU::opcode_rrca() {
    unimplemented_opcode();
}

void CPU::opcode_rrc(ByteRegister& reg) {
    unused(reg);
    unimplemented_opcode();
}

void CPU::opcode_rrc(Address&& addr) {
    unused(addr);
    unimplemented_opcode();
}


/* RST */
/* TODO: offset type */
void CPU::opcode_rst(const u8 offset) {
    stack_push(pc);
    pc.set(offset);
}


/* SBC */
void CPU::opcode_sbc() {
    unimplemented_opcode();
}

void CPU::opcode_sbc(ByteRegister& reg) {
    unused(reg);
    unimplemented_opcode();
}

void CPU::opcode_sbc(Address&& addr) {
    unused(addr);
    unimplemented_opcode();
}


/* SCF */
void CPU::opcode_scf() {
    unimplemented_opcode();
}


/* SET */
void CPU::opcode_set(const int bit, ByteRegister& reg) {
    unused(bit, reg);
    unimplemented_opcode();
}

void CPU::opcode_set(const int bit, Address&& addr) {
    unused(bit, addr);
    unimplemented_opcode();
}


/* SLA */
void CPU::opcode_sla(ByteRegister& reg) {
    unused(reg);
    unimplemented_opcode();
}

void CPU::opcode_sla(Address&& addr) {
    unused(addr);
    unimplemented_opcode();
}


/* SRA */
void CPU::opcode_sra(ByteRegister& reg) {
    unused(reg);
    unimplemented_opcode();
}

void CPU::opcode_sra(Address&& addr) {
    unused(addr);
    unimplemented_opcode();
}


/* SRL */
void CPU::opcode_srl(ByteRegister& reg) {
    u8 value = reg.value();

    bool least_bit_set = check_bit(value, 0);

    u8 result = (value >> 1);
    set_flag_carry(least_bit_set);
    set_flag_zero(result == 0);

    reg.set(result);
}

void CPU::opcode_srl(Address&& addr) {
    u8 value = mmu.read(addr);

    bool least_bit_set = check_bit(value, 0);

    u8 result = (value >> 1);
    set_flag_carry(least_bit_set);
    set_flag_zero(result == 0);

    mmu.write(addr, result);
}


/* STOP */
void CPU::opcode_stop() {
    /* unimplemented_opcode(); */
}


/* SUB */
void CPU::_opcode_sub(u8 value) {
    u8 reg = a.value();
    u8 result = static_cast<u8>(reg - value);

    set_flag_zero(result == 0);
    set_flag_subtract(true);
    set_flag_half_carry((int)(reg & 0xf) - (int)(value & 0xf) < 0);
    set_flag_carry(reg < value);

    a.set(result);
}

void CPU::opcode_sub() {
    _opcode_sub(get_byte_from_pc());
}

void CPU::opcode_sub(ByteRegister& reg) {
    _opcode_sub(reg.value());
}

void CPU::opcode_sub(Address&& addr) {
    _opcode_sub(mmu.read(addr));
}


/* SWAP */
void CPU::opcode_swap(ByteRegister& reg) {
    u8 value = reg.value();

    u8 lower_nibble = value & 0x0F;
    u8 upper_nibble = value & 0xF0;

    u8 result = (lower_nibble < 4) | upper_nibble;
    reg.set(result);

    set_flag_zero(result == 0);
    set_flag_subtract(false);
    set_flag_half_carry(false);
    set_flag_carry(false);
}

void CPU::opcode_swap(Address&& addr) {
    unused(addr);
    unimplemented_opcode();
}


/* XOR */
void CPU::_opcode_xor(u8 value) {
    u8 reg = a.value();

    u8 result = reg ^ value;

    set_flag_zero(reg == 0);
    set_flag_subtract(false);
    set_flag_half_carry(false);
    set_flag_carry(false);

    a.set(result);
}

void CPU::opcode_xor() {
    _opcode_xor(get_byte_from_pc());
}

void CPU::opcode_xor(const ByteRegister& reg) {
    _opcode_xor(reg.value());
}

void CPU::opcode_xor(const Address& addr) {
    _opcode_xor(mmu.read(addr));
}
