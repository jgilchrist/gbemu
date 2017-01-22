#pragma once

#include "../address.h"
#include "../clock.h"
#include "../cycles.h"
#include "../mmu.h"
#include "../register.h"

/**
 * The Gameboy CPU is a Z80 (8-bit) chip.
 */

enum class Condition {
    NZ,
    Z,
    NC,
    C,
};

namespace rst {
const uint rst1 = 0x00;
const uint rst2 = 0x08;
const uint rst3 = 0x10;
const uint rst4 = 0x18;
const uint rst5 = 0x20;
const uint rst6 = 0x28;
const uint rst7 = 0x30;
const uint rst8 = 0x38;
} // namespace rst

namespace interrupts {
const int vblank = 0x40;
const int lcdc_status = 0x48;
const int timer = 0x50;
const int serial = 0x58;
const int joypad = 0x60;
} // namespace interrupts


/* NOTE: CPU is not fully defined in this file.
 * In order to prevent this file from becoming extremely long, the
 * list of opcode functions from opcode_00 to opcode_FF and
 * opcode_CB_00 to opcode_CB_FF is defined in opcode_list.h */
class CPU {
public:
    CPU(MMU& inMMU);

    Cycles tick();

    Cycles execute_opcode(const u8 opcode);

    void execute_normal_opcode(const u8 opcode);
    void execute_cb_opcode();

private:
    Clock clock;
    MMU& mmu;

    bool interrupts_enabled = false;
    bool branch_taken = false;

    /* Basic registers */
    ByteRegister a, b, c, d, e, h, l;

    /* 'Group' registers for operations which use two registers as a word */
    RegisterPair af;
    RegisterPair bc;
    RegisterPair de;
    RegisterPair hl;

    /*
     * Flags set dependant on the result of the last operation
     *  0x80 - produced 0
     *  0x40 - was a subtraction
     *  0x20 - lower half of the byte overflowed 15
     *  0x10 - overflowed 255 or underflowed 0 for additions/subtractions
     */
    ByteRegister f;

    void set_flag_zero(bool set);
    void set_flag_subtract(bool set);
    void set_flag_half_carry(bool set);
    void set_flag_carry(bool set);
    void reset_flags();

    bool flag_zero() const;
    bool flag_subtract() const;
    bool flag_half_carry() const;
    bool flag_carry() const;

    /* Note: Not const because this also sets the 'branch_taken' member
     * variable if a branch is taken. This allows the correct cycle
     * count to be used */
    bool is_condition(Condition condition);

    u8 flag_half_carry_value() const;
    u8 flag_carry_value() const;

    /* Program counter */
    WordRegister pc;

    /* Stack pointer */
    WordRegister sp;

    u8 get_byte_from_pc();
    s8 get_signed_byte_from_pc();
    u16 get_word_from_pc();

    void stack_push(const WordRegister& reg);
    void stack_pop(WordRegister& reg);
    void stack_push(const RegisterPair& reg);
    void stack_pop(RegisterPair& reg);

    /* Opcode Helper Functions */

    /* ADC */
    void _opcode_adc(u8 value);

    void opcode_adc();
    void opcode_adc(const ByteRegister& reg);
    void opcode_adc(const Address&& addr);

    /* ADD */
    void _opcode_add(u8 reg, u8 value);

    void opcode_add_a();
    void opcode_add_a(const ByteRegister& reg);
    void opcode_add_a(const Address& addr);

    void opcode_add_hl(const RegisterPair& reg_pair);
    void opcode_add_hl(const WordRegister& word_reg);

    void opcode_add_sp();

    void opcode_add_signed();

    /* AND */
    void _opcode_and(u8 value);

    void opcode_and();
    void opcode_and(ByteRegister& reg);
    void opcode_and(Address&& addr);

    /* BIT */
    void _opcode_bit(const u8 bit, const u8 value);

    void opcode_bit(const u8 bit, ByteRegister& reg);
    void opcode_bit(const u8 bit, Address&& addr);

    /* CALL */
    void opcode_call();
    void opcode_call(Condition condition);

    /* CCF */
    void opcode_ccf();

    /* CP */
    void _opcode_cp(const u8 value);

    void opcode_cp();
    void opcode_cp(const ByteRegister& reg);
    void opcode_cp(const Address& addr);

    /* CPL */
    void opcode_cpl();

    /* DAA */
    void opcode_daa();

    /* DEC */
    void opcode_dec(ByteRegister& reg);
    void opcode_dec(RegisterPair& reg);
    void opcode_dec(WordRegister& reg);
    void opcode_dec(Address&& addr);

    /* DI */
    void opcode_di();

    /* EI */
    void opcode_ei();

    /* INC */
    void opcode_inc(ByteRegister& reg);
    void opcode_inc(RegisterPair& reg);
    void opcode_inc(WordRegister& reg);
    void opcode_inc(Address&& addr);

    /* JP */
    void opcode_jp();
    void opcode_jp(Condition condition);
    void opcode_jp(const Address& addr);

    /* JR */
    void opcode_jr();
    void opcode_jr(Condition condition);

    /* HALT */
    void opcode_halt();

    /* LD */
    void opcode_ld(ByteRegister& reg);
    void opcode_ld(ByteRegister& reg, const ByteRegister& byte_reg);
    void opcode_ld(ByteRegister& reg, const Address& address);

    void opcode_ld(RegisterPair& reg);

    void opcode_ld(WordRegister& reg);
    void opcode_ld(WordRegister& reg, const RegisterPair& reg_pair);

    void opcode_ld(const Address& address);
    void opcode_ld(const Address& address, const ByteRegister& byte_reg);
    void opcode_ld(const Address& address, const WordRegister& word_reg);

    // (nn), A
    void opcode_ld_to_addr(const ByteRegister& reg);
    void opcode_ld_from_addr(ByteRegister& reg);

    /* LDD */
    u8 _opcode_ldd(u8 value);

    void opcode_ldd(ByteRegister& reg, const Address& address);
    void opcode_ldd(const Address& address, const ByteRegister& reg);

    /* LDH */
    // A, (n)
    void opcode_ldh_into_a();
    // (n), A
    void opcode_ldh_into_data();
    // (reg), A
    void opcode_ldh_into_c();

    /* LDHL */
    void opcode_ldhl();

    /* LDI */
    void opcode_ldi(ByteRegister& reg, const Address& address);
    void opcode_ldi(const Address& address, const ByteRegister& reg);

    /* NOP */
    void opcode_nop();

    /* OR */
    void _opcode_or(u8 value);

    void opcode_or();
    void opcode_or(const ByteRegister& reg);
    void opcode_or(const Address& addr);

    /* POP */
    void opcode_pop(RegisterPair& reg);

    /* PUSH */
    void opcode_push(const RegisterPair& reg);

    /* RES */
    void opcode_res(const int bit, ByteRegister& reg);
    void opcode_res(const int bit, Address&& addr);

    /* RET */
    void opcode_ret();
    void opcode_ret(Condition condition);

    /* RETI */
    void opcode_reti();

    /* RL */
    void opcode_rla();
    void opcode_rl(ByteRegister& reg);
    void opcode_rl(Address&& addr);

    /* RLC */
    void opcode_rlca();
    void opcode_rlc(ByteRegister& reg);
    void opcode_rlc(Address&& addr);

    /* RR */
    void opcode_rra();
    void opcode_rr(ByteRegister& reg);
    void opcode_rr(Address&& addr);

    /* RRC */
    void opcode_rrca();
    void opcode_rrc(ByteRegister& reg);
    void opcode_rrc(Address&& addr);

    /* RST */
    /* TODO: offset type */
    void opcode_rst(const u8 offset);

    /* SBC */
    void opcode_sbc();
    void opcode_sbc(ByteRegister& reg);
    void opcode_sbc(Address&& addr);

    /* SCF */
    void opcode_scf();

    /* SET */
    void opcode_set(const int bit, ByteRegister& reg);
    void opcode_set(const int bit, Address&& addr);

    /* SLA */
    void opcode_sla(ByteRegister& reg);
    void opcode_sla(Address&& addr);

    /* SRA */
    void opcode_sra(ByteRegister& reg);
    void opcode_sra(Address&& addr);

    /* SRL */
    void opcode_srl(ByteRegister& reg);
    void opcode_srl(Address&& addr);

    /* STOP */
    void opcode_stop();

    /* SUB */
    void _opcode_sub(u8 value);

    void opcode_sub();
    void opcode_sub(ByteRegister& reg);
    void opcode_sub(Address&& addr);

    /* SWAP */
    void opcode_swap(ByteRegister& reg);
    void opcode_swap(Address&& addr);

    /* XOR */
    void _opcode_xor(u8 value);

    void opcode_xor();
    void opcode_xor(const ByteRegister& reg);
    void opcode_xor(const Address& addr);

#include "opcode_list.h"

    friend class Debugger;
};
