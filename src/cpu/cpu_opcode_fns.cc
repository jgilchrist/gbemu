#include "cpu.h"

#include "../bitwise.h"
#include "../util/log.h"

#include <cstdlib>

void unimplemented_opcode() {
    log_error("Unimplemented opcode");
    std::exit(1);
}


/* ADC */
inline void CPU::_opcode_adc(u8 value) {
    u8 reg = a.value();
    u8 carry = flag_carry_value();

    u16 result16 = reg + value + carry;

    set_flag_zero(reg == 0);
    set_flag_subtract(false);
    set_flag_half_carry(((reg ^ value ^ result16) & 0x10) != 0);
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
inline void CPU::_opcode_add(u8 reg, u8 value) {
    u16 result16 = reg + value;

    set_flag_zero(a.value() == 0);
    set_flag_subtract(false);
    set_flag_half_carry(((reg ^ value ^ result16) & 0x10) != 0);
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
    unimplemented_opcode();
}

void CPU::opcode_add_hl(const WordRegister& word_reg) {
    unimplemented_opcode();
}

void CPU::opcode_add_sp() {
    unimplemented_opcode();
}

void CPU::opcode_add_signed() {
    unimplemented_opcode();
}


/* AND */
void CPU::opcode_and() {
    unimplemented_opcode();
}

void CPU::opcode_and(ByteRegister& reg) {
    unimplemented_opcode();
}

void CPU::opcode_and(Address&& addr) {
    unimplemented_opcode();
}


/* BIT */
void CPU::_opcode_bit(const int bit, const u8 value) {
    set_flag_zero(!check_bit(value, bit));
    set_flag_subtract(false);
    set_flag_half_carry(true);
}

void CPU::opcode_bit(const int bit, ByteRegister& reg) {
    _opcode_bit(bit, reg.value());
}

void CPU::opcode_bit(const int bit, Address&& addr) {
    _opcode_bit(bit, mmu.read(addr));
}


/* CALL */
void CPU::opcode_call() {
    unimplemented_opcode();
}

void CPU::opcode_call(Condition condition) {
    unimplemented_opcode();
}


/* CCF */
void CPU::opcode_ccf() {
    unimplemented_opcode();
}


/* CP */
void CPU::opcode_cp() {
    unimplemented_opcode();
}

void CPU::opcode_cp(const ByteRegister& reg) {
    unimplemented_opcode();
}

void CPU::opcode_cp(const Address& addr) {
    unimplemented_opcode();
}


/* CPL */
void CPU::opcode_cpl() {
    unimplemented_opcode();
}


/* DAA */
void CPU::opcode_daa() {
    unimplemented_opcode();
}


/* DEC */
void CPU::opcode_dec(ByteRegister& reg) {
    unimplemented_opcode();
}

void CPU::opcode_dec(RegisterPair& reg) {
    unimplemented_opcode();
}

void CPU::opcode_dec(WordRegister& reg) {
    unimplemented_opcode();
}

void CPU::opcode_dec(Address&& addr) {
    unimplemented_opcode();
}


/* DI */
void CPU::opcode_di() {
    unimplemented_opcode();
}


/* EI */
void CPU::opcode_ei() {
    unimplemented_opcode();
}


/* INC */
void CPU::opcode_inc(ByteRegister& reg) {
    unimplemented_opcode();
}

void CPU::opcode_inc(RegisterPair& reg) {
    unimplemented_opcode();
}

void CPU::opcode_inc(WordRegister& addr) {
    unimplemented_opcode();
}

void CPU::opcode_inc(Address&& addr) {
    unimplemented_opcode();
}


/* JP */
void CPU::opcode_jp() {
    unimplemented_opcode();
}

void CPU::opcode_jp(Condition condition) {
    unimplemented_opcode();
}

void CPU::opcode_jp(const Address& addr) {
    unimplemented_opcode();
}


/* JR */
void CPU::opcode_jr() {
    s8 n = get_byte_from_pc();
    u16 old_pc = pc.value();

    u16 new_pc = old_pc + n;
    pc.set(new_pc);
}

void CPU::opcode_jr(Condition condition) {
    if (is_condition(condition)) {
        opcode_jr();
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
    mmu.write_word(address, word_reg.value());
}


void CPU::opcode_ld_to_addr(const ByteRegister &reg) {
    unimplemented_opcode();
}


/* LDD */
void CPU::opcode_ldd(ByteRegister& reg, const Address& address) {
    // TODO: clean up
    // two ways of doing ldd
    // address is always that of HL
    reg.set(mmu.read(address));
    hl.decrement();
}

void CPU::opcode_ldd(const Address& address, const ByteRegister& reg) {
    mmu.write(address, reg.value());
    hl.decrement();
}


/* LDH */
void CPU::opcode_ldh_into_a() {
    unimplemented_opcode();
}

void CPU::opcode_ldh_into_data() {
    unimplemented_opcode();
}

void CPU::opcode_ldh_into_c() {
    unimplemented_opcode();
}


/* LDHL */
void CPU::opcode_ldhl() {
    unimplemented_opcode();
}


/* LDI */
void CPU::opcode_ldi(const ByteRegister& reg, const Address& address) {
    unimplemented_opcode();
}

void CPU::opcode_ldi(const Address& address, const ByteRegister& reg) {
    unimplemented_opcode();
}


/* NOP */
void CPU::opcode_nop() {
    unimplemented_opcode();
}


/* OR */
void CPU::opcode_or() {
    unimplemented_opcode();
}

void CPU::opcode_or(const ByteRegister& reg) {
    unimplemented_opcode();
}

void CPU::opcode_or(const Address& addr) {
    unimplemented_opcode();
}


/* POP */
void CPU::opcode_pop(const RegisterPair& reg) {
    unimplemented_opcode();
}


/* PUSH */
void CPU::opcode_push(const RegisterPair& reg) {
    unimplemented_opcode();
}


/* RES */
void CPU::opcode_res(const int bit, ByteRegister& reg) {
    unimplemented_opcode();
}

void CPU::opcode_res(const int bit, Address&& addr) {
    unimplemented_opcode();
}


/* RET */
void CPU::opcode_ret() {
    unimplemented_opcode();
}

void CPU::opcode_ret(Condition condition) {
    unimplemented_opcode();
}


/* RETI */
void CPU::opcode_reti() {
    unimplemented_opcode();
}


/* RL */
void CPU::opcode_rl(ByteRegister& reg) {
    unimplemented_opcode();
}

void CPU::opcode_rl(Address&& addr) {
    unimplemented_opcode();
}


/* RLC */
void CPU::opcode_rlc(ByteRegister& reg) {
    unimplemented_opcode();
}

void CPU::opcode_rlc(Address&& addr) {
    unimplemented_opcode();
}


/* RR */
void CPU::opcode_rr(ByteRegister& reg) {
    unimplemented_opcode();
}

void CPU::opcode_rr(Address&& addr) {
    unimplemented_opcode();
}


/* RRC */
void CPU::opcode_rrc(ByteRegister& reg) {
    unimplemented_opcode();
}

void CPU::opcode_rrc(Address&& addr) {
    unimplemented_opcode();
}


/* RST */
// TODO: offset type
void CPU::opcode_rst(const u8 offset) {
    unimplemented_opcode();
}


/* SBC */
void CPU::opcode_sbc() {
    unimplemented_opcode();
}

void CPU::opcode_sbc(ByteRegister& reg) {
    unimplemented_opcode();
}

void CPU::opcode_sbc(Address&& addr) {
    unimplemented_opcode();
}


/* SCF */
void CPU::opcode_scf() {
    unimplemented_opcode();
}


/* SET */
void CPU::opcode_set(const int bit, ByteRegister& reg) {
    unimplemented_opcode();
}

void CPU::opcode_set(const int bit, Address&& addr) {
    unimplemented_opcode();
}


/* SLA */
void CPU::opcode_sla(ByteRegister& reg) {
    unimplemented_opcode();
}

void CPU::opcode_sla(Address&& addr) {
    unimplemented_opcode();
}


/* SRA */
void CPU::opcode_sra(ByteRegister& reg) {
    unimplemented_opcode();
}

void CPU::opcode_sra(Address&& addr) {
    unimplemented_opcode();
}


/* SRL */
void CPU::opcode_srl(ByteRegister& reg) {
    unimplemented_opcode();
}

void CPU::opcode_srl(Address&& addr) {
    unimplemented_opcode();
}


/* STOP */
void CPU::opcode_stop() {
    unimplemented_opcode();
}


/* SUB */
void CPU::opcode_sub() {
    unimplemented_opcode();
}

void CPU::opcode_sub(ByteRegister& reg) {
    unimplemented_opcode();
}

void CPU::opcode_sub(Address&& addr) {
    unimplemented_opcode();
}


/* SWAP */
void CPU::opcode_swap(ByteRegister& reg) {
    unimplemented_opcode();
}

void CPU::opcode_swap(Address&& addr) {
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
