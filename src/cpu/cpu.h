#pragma once

#include "../address.h"
#include "../mmu.h"
#include "../register.h"
#include "../options.h"

enum class Condition {
    NZ,
    Z,
    NC,
    C,
};

namespace rst {
const u16 rst1 = 0x00;
const u16 rst2 = 0x08;
const u16 rst3 = 0x10;
const u16 rst4 = 0x18;
const u16 rst5 = 0x20;
const u16 rst6 = 0x28;
const u16 rst7 = 0x30;
const u16 rst8 = 0x38;
} // namespace rst

namespace interrupts {
const u16 vblank = 0x40;
const u16 lcdc_status = 0x48;
const u16 timer = 0x50;
const u16 serial = 0x58;
const u16 joypad = 0x60;
} // namespace interrupts


class CPU {
public:
    CPU(MMU& inMMU, Options& inOptions);

    Cycles tick();

    Cycles execute_opcode(u8 opcode, u16 opcode_pc);
    Cycles execute_normal_opcode(u8 opcode);
    Cycles execute_cb_opcode(u8 opcode);

    void trace_opcode(u8 opcode, u16 opcode_pc);
    void trace_normal_opcode(u8 opcode, u16 opcode_pc);
    void trace_cb_opcode(u8 opcode, u16 opcode_pc);

    ByteRegister interrupt_flag;
    ByteRegister interrupt_enabled;

private:
    void handle_interrupts();
    bool handle_interrupt(u8 interrupt_bit, u16 interrupt_vector, u8 fired_interrupts);

    MMU& mmu;
    Options& options;

    bool interrupts_enabled = false;
    bool halted = false;

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
    FlagRegister f;

    void set_flag_zero(bool set);
    void set_flag_subtract(bool set);
    void set_flag_half_carry(bool set);
    void set_flag_carry(bool set);

    /* Note: Not const because this also sets the 'branch_taken' member
     * variable if a branch is taken. This allows the correct cycle
     * count to be used */
    bool is_condition(Condition condition);

    /* Program counter */
    WordRegister pc;

    /* Stack pointer */
    WordRegister sp;

    u8 get_byte_from_pc();
    s8 get_signed_byte_from_pc();
    u16 get_word_from_pc();

    void stack_push(const WordValue& reg);
    void stack_pop(WordValue& reg);

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

    void _opcode_add_hl(u16 value);
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
    void _opcode_bit(u8 bit, u8 value);

    void opcode_bit(u8 bit, ByteRegister& reg);
    void opcode_bit(u8 bit, Address&& addr);

    /* CALL */
    void opcode_call();
    void opcode_call(Condition condition);

    /* CCF */
    void opcode_ccf();

    /* CP */
    void _opcode_cp(u8 value);

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
    // A, (reg)
    void opcode_ldh_c_into_a();

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
    void opcode_res(u8 bit, ByteRegister& reg);
    void opcode_res(u8 bit, Address&& addr);

    /* RET */
    void opcode_ret();
    void opcode_ret(Condition condition);

    /* RETI */
    void opcode_reti();

    /* RL */
    u8 _opcode_rl(u8 value);

    void opcode_rla();
    void opcode_rl(ByteRegister& reg);
    void opcode_rl(Address&& addr);

    /* RLC */
    u8 _opcode_rlc(u8 value);

    void opcode_rlca();
    void opcode_rlc(ByteRegister& reg);
    void opcode_rlc(Address&& addr);

    /* RR */
    u8 _opcode_rr(u8 value);

    void opcode_rra();
    void opcode_rr(ByteRegister& reg);
    void opcode_rr(Address&& addr);

    /* RRC */
    u8 _opcode_rrc(u8 value);

    void opcode_rrca();
    void opcode_rrc(ByteRegister& reg);
    void opcode_rrc(Address&& addr);

    /* RST */
    void opcode_rst(u8 offset);

    /* SBC */
    void _opcode_sbc(u8 value);

    void opcode_sbc();
    void opcode_sbc(ByteRegister& reg);
    void opcode_sbc(Address&& addr);

    /* SCF */
    void opcode_scf();

    /* SET */
    void opcode_set(u8 bit, ByteRegister& reg);
    void opcode_set(u8 bit, Address&& addr);

    /* SLA */
    u8 _opcode_sla(u8 value);

    void opcode_sla(ByteRegister& reg);
    void opcode_sla(Address&& addr);

    /* SRA */
    u8 _opcode_sra(u8 value);

    void opcode_sra(ByteRegister& reg);
    void opcode_sra(Address&& addr);

    /* SRL */
    u8 _opcode_srl(u8 value);

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
    u8 _opcode_swap(u8 value);

    void opcode_swap(ByteRegister& reg);
    void opcode_swap(Address&& addr);

    /* XOR */
    void _opcode_xor(u8 value);

    void opcode_xor();
    void opcode_xor(const ByteRegister& reg);
    void opcode_xor(const Address& addr);


    /* clang-format off */
    /* Opcodes */
    void opcode_00(); void opcode_01(); void opcode_02(); void opcode_03(); void opcode_04(); void opcode_05(); void opcode_06(); void opcode_07(); void opcode_08(); void opcode_09(); void opcode_0A(); void opcode_0B(); void opcode_0C(); void opcode_0D(); void opcode_0E(); void opcode_0F();
    void opcode_10(); void opcode_11(); void opcode_12(); void opcode_13(); void opcode_14(); void opcode_15(); void opcode_16(); void opcode_17(); void opcode_18(); void opcode_19(); void opcode_1A(); void opcode_1B(); void opcode_1C(); void opcode_1D(); void opcode_1E(); void opcode_1F();
    void opcode_20(); void opcode_21(); void opcode_22(); void opcode_23(); void opcode_24(); void opcode_25(); void opcode_26(); void opcode_27(); void opcode_28(); void opcode_29(); void opcode_2A(); void opcode_2B(); void opcode_2C(); void opcode_2D(); void opcode_2E(); void opcode_2F();
    void opcode_30(); void opcode_31(); void opcode_32(); void opcode_33(); void opcode_34(); void opcode_35(); void opcode_36(); void opcode_37(); void opcode_38(); void opcode_39(); void opcode_3A(); void opcode_3B(); void opcode_3C(); void opcode_3D(); void opcode_3E(); void opcode_3F();
    void opcode_40(); void opcode_41(); void opcode_42(); void opcode_43(); void opcode_44(); void opcode_45(); void opcode_46(); void opcode_47(); void opcode_48(); void opcode_49(); void opcode_4A(); void opcode_4B(); void opcode_4C(); void opcode_4D(); void opcode_4E(); void opcode_4F();
    void opcode_50(); void opcode_51(); void opcode_52(); void opcode_53(); void opcode_54(); void opcode_55(); void opcode_56(); void opcode_57(); void opcode_58(); void opcode_59(); void opcode_5A(); void opcode_5B(); void opcode_5C(); void opcode_5D(); void opcode_5E(); void opcode_5F();
    void opcode_60(); void opcode_61(); void opcode_62(); void opcode_63(); void opcode_64(); void opcode_65(); void opcode_66(); void opcode_67(); void opcode_68(); void opcode_69(); void opcode_6A(); void opcode_6B(); void opcode_6C(); void opcode_6D(); void opcode_6E(); void opcode_6F();
    void opcode_70(); void opcode_71(); void opcode_72(); void opcode_73(); void opcode_74(); void opcode_75(); void opcode_76(); void opcode_77(); void opcode_78(); void opcode_79(); void opcode_7A(); void opcode_7B(); void opcode_7C(); void opcode_7D(); void opcode_7E(); void opcode_7F();
    void opcode_80(); void opcode_81(); void opcode_82(); void opcode_83(); void opcode_84(); void opcode_85(); void opcode_86(); void opcode_87(); void opcode_88(); void opcode_89(); void opcode_8A(); void opcode_8B(); void opcode_8C(); void opcode_8D(); void opcode_8E(); void opcode_8F();
    void opcode_90(); void opcode_91(); void opcode_92(); void opcode_93(); void opcode_94(); void opcode_95(); void opcode_96(); void opcode_97(); void opcode_98(); void opcode_99(); void opcode_9A(); void opcode_9B(); void opcode_9C(); void opcode_9D(); void opcode_9E(); void opcode_9F();
    void opcode_A0(); void opcode_A1(); void opcode_A2(); void opcode_A3(); void opcode_A4(); void opcode_A5(); void opcode_A6(); void opcode_A7(); void opcode_A8(); void opcode_A9(); void opcode_AA(); void opcode_AB(); void opcode_AC(); void opcode_AD(); void opcode_AE(); void opcode_AF();
    void opcode_B0(); void opcode_B1(); void opcode_B2(); void opcode_B3(); void opcode_B4(); void opcode_B5(); void opcode_B6(); void opcode_B7(); void opcode_B8(); void opcode_B9(); void opcode_BA(); void opcode_BB(); void opcode_BC(); void opcode_BD(); void opcode_BE(); void opcode_BF();
    void opcode_C0(); void opcode_C1(); void opcode_C2(); void opcode_C3(); void opcode_C4(); void opcode_C5(); void opcode_C6(); void opcode_C7(); void opcode_C8(); void opcode_C9(); void opcode_CA(); void opcode_CB(); void opcode_CC(); void opcode_CD(); void opcode_CE(); void opcode_CF();
    void opcode_D0(); void opcode_D1(); void opcode_D2(); void opcode_D3(); void opcode_D4(); void opcode_D5(); void opcode_D6(); void opcode_D7(); void opcode_D8(); void opcode_D9(); void opcode_DA(); void opcode_DB(); void opcode_DC(); void opcode_DD(); void opcode_DE(); void opcode_DF();
    void opcode_E0(); void opcode_E1(); void opcode_E2(); void opcode_E3(); void opcode_E4(); void opcode_E5(); void opcode_E6(); void opcode_E7(); void opcode_E8(); void opcode_E9(); void opcode_EA(); void opcode_EB(); void opcode_EC(); void opcode_ED(); void opcode_EE(); void opcode_EF();
    void opcode_F0(); void opcode_F1(); void opcode_F2(); void opcode_F3(); void opcode_F4(); void opcode_F5(); void opcode_F6(); void opcode_F7(); void opcode_F8(); void opcode_F9(); void opcode_FA(); void opcode_FB(); void opcode_FC(); void opcode_FD(); void opcode_FE(); void opcode_FF();

    /* CB Opcodes */
    void opcode_CB_00(); void opcode_CB_01(); void opcode_CB_02(); void opcode_CB_03(); void opcode_CB_04(); void opcode_CB_05(); void opcode_CB_06(); void opcode_CB_07(); void opcode_CB_08(); void opcode_CB_09(); void opcode_CB_0A(); void opcode_CB_0B(); void opcode_CB_0C(); void opcode_CB_0D(); void opcode_CB_0E(); void opcode_CB_0F();
    void opcode_CB_10(); void opcode_CB_11(); void opcode_CB_12(); void opcode_CB_13(); void opcode_CB_14(); void opcode_CB_15(); void opcode_CB_16(); void opcode_CB_17(); void opcode_CB_18(); void opcode_CB_19(); void opcode_CB_1A(); void opcode_CB_1B(); void opcode_CB_1C(); void opcode_CB_1D(); void opcode_CB_1E(); void opcode_CB_1F();
    void opcode_CB_20(); void opcode_CB_21(); void opcode_CB_22(); void opcode_CB_23(); void opcode_CB_24(); void opcode_CB_25(); void opcode_CB_26(); void opcode_CB_27(); void opcode_CB_28(); void opcode_CB_29(); void opcode_CB_2A(); void opcode_CB_2B(); void opcode_CB_2C(); void opcode_CB_2D(); void opcode_CB_2E(); void opcode_CB_2F();
    void opcode_CB_30(); void opcode_CB_31(); void opcode_CB_32(); void opcode_CB_33(); void opcode_CB_34(); void opcode_CB_35(); void opcode_CB_36(); void opcode_CB_37(); void opcode_CB_38(); void opcode_CB_39(); void opcode_CB_3A(); void opcode_CB_3B(); void opcode_CB_3C(); void opcode_CB_3D(); void opcode_CB_3E(); void opcode_CB_3F();
    void opcode_CB_40(); void opcode_CB_41(); void opcode_CB_42(); void opcode_CB_43(); void opcode_CB_44(); void opcode_CB_45(); void opcode_CB_46(); void opcode_CB_47(); void opcode_CB_48(); void opcode_CB_49(); void opcode_CB_4A(); void opcode_CB_4B(); void opcode_CB_4C(); void opcode_CB_4D(); void opcode_CB_4E(); void opcode_CB_4F();
    void opcode_CB_50(); void opcode_CB_51(); void opcode_CB_52(); void opcode_CB_53(); void opcode_CB_54(); void opcode_CB_55(); void opcode_CB_56(); void opcode_CB_57(); void opcode_CB_58(); void opcode_CB_59(); void opcode_CB_5A(); void opcode_CB_5B(); void opcode_CB_5C(); void opcode_CB_5D(); void opcode_CB_5E(); void opcode_CB_5F();
    void opcode_CB_60(); void opcode_CB_61(); void opcode_CB_62(); void opcode_CB_63(); void opcode_CB_64(); void opcode_CB_65(); void opcode_CB_66(); void opcode_CB_67(); void opcode_CB_68(); void opcode_CB_69(); void opcode_CB_6A(); void opcode_CB_6B(); void opcode_CB_6C(); void opcode_CB_6D(); void opcode_CB_6E(); void opcode_CB_6F();
    void opcode_CB_70(); void opcode_CB_71(); void opcode_CB_72(); void opcode_CB_73(); void opcode_CB_74(); void opcode_CB_75(); void opcode_CB_76(); void opcode_CB_77(); void opcode_CB_78(); void opcode_CB_79(); void opcode_CB_7A(); void opcode_CB_7B(); void opcode_CB_7C(); void opcode_CB_7D(); void opcode_CB_7E(); void opcode_CB_7F();
    void opcode_CB_80(); void opcode_CB_81(); void opcode_CB_82(); void opcode_CB_83(); void opcode_CB_84(); void opcode_CB_85(); void opcode_CB_86(); void opcode_CB_87(); void opcode_CB_88(); void opcode_CB_89(); void opcode_CB_8A(); void opcode_CB_8B(); void opcode_CB_8C(); void opcode_CB_8D(); void opcode_CB_8E(); void opcode_CB_8F();
    void opcode_CB_90(); void opcode_CB_91(); void opcode_CB_92(); void opcode_CB_93(); void opcode_CB_94(); void opcode_CB_95(); void opcode_CB_96(); void opcode_CB_97(); void opcode_CB_98(); void opcode_CB_99(); void opcode_CB_9A(); void opcode_CB_9B(); void opcode_CB_9C(); void opcode_CB_9D(); void opcode_CB_9E(); void opcode_CB_9F();
    void opcode_CB_A0(); void opcode_CB_A1(); void opcode_CB_A2(); void opcode_CB_A3(); void opcode_CB_A4(); void opcode_CB_A5(); void opcode_CB_A6(); void opcode_CB_A7(); void opcode_CB_A8(); void opcode_CB_A9(); void opcode_CB_AA(); void opcode_CB_AB(); void opcode_CB_AC(); void opcode_CB_AD(); void opcode_CB_AE(); void opcode_CB_AF();
    void opcode_CB_B0(); void opcode_CB_B1(); void opcode_CB_B2(); void opcode_CB_B3(); void opcode_CB_B4(); void opcode_CB_B5(); void opcode_CB_B6(); void opcode_CB_B7(); void opcode_CB_B8(); void opcode_CB_B9(); void opcode_CB_BA(); void opcode_CB_BB(); void opcode_CB_BC(); void opcode_CB_BD(); void opcode_CB_BE(); void opcode_CB_BF();
    void opcode_CB_C0(); void opcode_CB_C1(); void opcode_CB_C2(); void opcode_CB_C3(); void opcode_CB_C4(); void opcode_CB_C5(); void opcode_CB_C6(); void opcode_CB_C7(); void opcode_CB_C8(); void opcode_CB_C9(); void opcode_CB_CA(); void opcode_CB_CB(); void opcode_CB_CC(); void opcode_CB_CD(); void opcode_CB_CE(); void opcode_CB_CF();
    void opcode_CB_D0(); void opcode_CB_D1(); void opcode_CB_D2(); void opcode_CB_D3(); void opcode_CB_D4(); void opcode_CB_D5(); void opcode_CB_D6(); void opcode_CB_D7(); void opcode_CB_D8(); void opcode_CB_D9(); void opcode_CB_DA(); void opcode_CB_DB(); void opcode_CB_DC(); void opcode_CB_DD(); void opcode_CB_DE(); void opcode_CB_DF();
    void opcode_CB_E0(); void opcode_CB_E1(); void opcode_CB_E2(); void opcode_CB_E3(); void opcode_CB_E4(); void opcode_CB_E5(); void opcode_CB_E6(); void opcode_CB_E7(); void opcode_CB_E8(); void opcode_CB_E9(); void opcode_CB_EA(); void opcode_CB_EB(); void opcode_CB_EC(); void opcode_CB_ED(); void opcode_CB_EE(); void opcode_CB_EF();
    void opcode_CB_F0(); void opcode_CB_F1(); void opcode_CB_F2(); void opcode_CB_F3(); void opcode_CB_F4(); void opcode_CB_F5(); void opcode_CB_F6(); void opcode_CB_F7(); void opcode_CB_F8(); void opcode_CB_F9(); void opcode_CB_FA(); void opcode_CB_FB(); void opcode_CB_FC(); void opcode_CB_FD(); void opcode_CB_FE(); void opcode_CB_FF();
    /* clang-format on */

    /* clang-format off */
    /* Tracing Opcodes */
    void trace_opcode_00(u8 opcode, u16 opcode_pc); void trace_opcode_01(u8 opcode, u16 opcode_pc); void trace_opcode_02(u8 opcode, u16 opcode_pc); void trace_opcode_03(u8 opcode, u16 opcode_pc); void trace_opcode_04(u8 opcode, u16 opcode_pc); void trace_opcode_05(u8 opcode, u16 opcode_pc); void trace_opcode_06(u8 opcode, u16 opcode_pc); void trace_opcode_07(u8 opcode, u16 opcode_pc); void trace_opcode_08(u8 opcode, u16 opcode_pc); void trace_opcode_09(u8 opcode, u16 opcode_pc); void trace_opcode_0A(u8 opcode, u16 opcode_pc); void trace_opcode_0B(u8 opcode, u16 opcode_pc); void trace_opcode_0C(u8 opcode, u16 opcode_pc); void trace_opcode_0D(u8 opcode, u16 opcode_pc); void trace_opcode_0E(u8 opcode, u16 opcode_pc); void trace_opcode_0F(u8 opcode, u16 opcode_pc);
    void trace_opcode_10(u8 opcode, u16 opcode_pc); void trace_opcode_11(u8 opcode, u16 opcode_pc); void trace_opcode_12(u8 opcode, u16 opcode_pc); void trace_opcode_13(u8 opcode, u16 opcode_pc); void trace_opcode_14(u8 opcode, u16 opcode_pc); void trace_opcode_15(u8 opcode, u16 opcode_pc); void trace_opcode_16(u8 opcode, u16 opcode_pc); void trace_opcode_17(u8 opcode, u16 opcode_pc); void trace_opcode_18(u8 opcode, u16 opcode_pc); void trace_opcode_19(u8 opcode, u16 opcode_pc); void trace_opcode_1A(u8 opcode, u16 opcode_pc); void trace_opcode_1B(u8 opcode, u16 opcode_pc); void trace_opcode_1C(u8 opcode, u16 opcode_pc); void trace_opcode_1D(u8 opcode, u16 opcode_pc); void trace_opcode_1E(u8 opcode, u16 opcode_pc); void trace_opcode_1F(u8 opcode, u16 opcode_pc);
    void trace_opcode_20(u8 opcode, u16 opcode_pc); void trace_opcode_21(u8 opcode, u16 opcode_pc); void trace_opcode_22(u8 opcode, u16 opcode_pc); void trace_opcode_23(u8 opcode, u16 opcode_pc); void trace_opcode_24(u8 opcode, u16 opcode_pc); void trace_opcode_25(u8 opcode, u16 opcode_pc); void trace_opcode_26(u8 opcode, u16 opcode_pc); void trace_opcode_27(u8 opcode, u16 opcode_pc); void trace_opcode_28(u8 opcode, u16 opcode_pc); void trace_opcode_29(u8 opcode, u16 opcode_pc); void trace_opcode_2A(u8 opcode, u16 opcode_pc); void trace_opcode_2B(u8 opcode, u16 opcode_pc); void trace_opcode_2C(u8 opcode, u16 opcode_pc); void trace_opcode_2D(u8 opcode, u16 opcode_pc); void trace_opcode_2E(u8 opcode, u16 opcode_pc); void trace_opcode_2F(u8 opcode, u16 opcode_pc);
    void trace_opcode_30(u8 opcode, u16 opcode_pc); void trace_opcode_31(u8 opcode, u16 opcode_pc); void trace_opcode_32(u8 opcode, u16 opcode_pc); void trace_opcode_33(u8 opcode, u16 opcode_pc); void trace_opcode_34(u8 opcode, u16 opcode_pc); void trace_opcode_35(u8 opcode, u16 opcode_pc); void trace_opcode_36(u8 opcode, u16 opcode_pc); void trace_opcode_37(u8 opcode, u16 opcode_pc); void trace_opcode_38(u8 opcode, u16 opcode_pc); void trace_opcode_39(u8 opcode, u16 opcode_pc); void trace_opcode_3A(u8 opcode, u16 opcode_pc); void trace_opcode_3B(u8 opcode, u16 opcode_pc); void trace_opcode_3C(u8 opcode, u16 opcode_pc); void trace_opcode_3D(u8 opcode, u16 opcode_pc); void trace_opcode_3E(u8 opcode, u16 opcode_pc); void trace_opcode_3F(u8 opcode, u16 opcode_pc);
    void trace_opcode_40(u8 opcode, u16 opcode_pc); void trace_opcode_41(u8 opcode, u16 opcode_pc); void trace_opcode_42(u8 opcode, u16 opcode_pc); void trace_opcode_43(u8 opcode, u16 opcode_pc); void trace_opcode_44(u8 opcode, u16 opcode_pc); void trace_opcode_45(u8 opcode, u16 opcode_pc); void trace_opcode_46(u8 opcode, u16 opcode_pc); void trace_opcode_47(u8 opcode, u16 opcode_pc); void trace_opcode_48(u8 opcode, u16 opcode_pc); void trace_opcode_49(u8 opcode, u16 opcode_pc); void trace_opcode_4A(u8 opcode, u16 opcode_pc); void trace_opcode_4B(u8 opcode, u16 opcode_pc); void trace_opcode_4C(u8 opcode, u16 opcode_pc); void trace_opcode_4D(u8 opcode, u16 opcode_pc); void trace_opcode_4E(u8 opcode, u16 opcode_pc); void trace_opcode_4F(u8 opcode, u16 opcode_pc);
    void trace_opcode_50(u8 opcode, u16 opcode_pc); void trace_opcode_51(u8 opcode, u16 opcode_pc); void trace_opcode_52(u8 opcode, u16 opcode_pc); void trace_opcode_53(u8 opcode, u16 opcode_pc); void trace_opcode_54(u8 opcode, u16 opcode_pc); void trace_opcode_55(u8 opcode, u16 opcode_pc); void trace_opcode_56(u8 opcode, u16 opcode_pc); void trace_opcode_57(u8 opcode, u16 opcode_pc); void trace_opcode_58(u8 opcode, u16 opcode_pc); void trace_opcode_59(u8 opcode, u16 opcode_pc); void trace_opcode_5A(u8 opcode, u16 opcode_pc); void trace_opcode_5B(u8 opcode, u16 opcode_pc); void trace_opcode_5C(u8 opcode, u16 opcode_pc); void trace_opcode_5D(u8 opcode, u16 opcode_pc); void trace_opcode_5E(u8 opcode, u16 opcode_pc); void trace_opcode_5F(u8 opcode, u16 opcode_pc);
    void trace_opcode_60(u8 opcode, u16 opcode_pc); void trace_opcode_61(u8 opcode, u16 opcode_pc); void trace_opcode_62(u8 opcode, u16 opcode_pc); void trace_opcode_63(u8 opcode, u16 opcode_pc); void trace_opcode_64(u8 opcode, u16 opcode_pc); void trace_opcode_65(u8 opcode, u16 opcode_pc); void trace_opcode_66(u8 opcode, u16 opcode_pc); void trace_opcode_67(u8 opcode, u16 opcode_pc); void trace_opcode_68(u8 opcode, u16 opcode_pc); void trace_opcode_69(u8 opcode, u16 opcode_pc); void trace_opcode_6A(u8 opcode, u16 opcode_pc); void trace_opcode_6B(u8 opcode, u16 opcode_pc); void trace_opcode_6C(u8 opcode, u16 opcode_pc); void trace_opcode_6D(u8 opcode, u16 opcode_pc); void trace_opcode_6E(u8 opcode, u16 opcode_pc); void trace_opcode_6F(u8 opcode, u16 opcode_pc);
    void trace_opcode_70(u8 opcode, u16 opcode_pc); void trace_opcode_71(u8 opcode, u16 opcode_pc); void trace_opcode_72(u8 opcode, u16 opcode_pc); void trace_opcode_73(u8 opcode, u16 opcode_pc); void trace_opcode_74(u8 opcode, u16 opcode_pc); void trace_opcode_75(u8 opcode, u16 opcode_pc); void trace_opcode_76(u8 opcode, u16 opcode_pc); void trace_opcode_77(u8 opcode, u16 opcode_pc); void trace_opcode_78(u8 opcode, u16 opcode_pc); void trace_opcode_79(u8 opcode, u16 opcode_pc); void trace_opcode_7A(u8 opcode, u16 opcode_pc); void trace_opcode_7B(u8 opcode, u16 opcode_pc); void trace_opcode_7C(u8 opcode, u16 opcode_pc); void trace_opcode_7D(u8 opcode, u16 opcode_pc); void trace_opcode_7E(u8 opcode, u16 opcode_pc); void trace_opcode_7F(u8 opcode, u16 opcode_pc);
    void trace_opcode_80(u8 opcode, u16 opcode_pc); void trace_opcode_81(u8 opcode, u16 opcode_pc); void trace_opcode_82(u8 opcode, u16 opcode_pc); void trace_opcode_83(u8 opcode, u16 opcode_pc); void trace_opcode_84(u8 opcode, u16 opcode_pc); void trace_opcode_85(u8 opcode, u16 opcode_pc); void trace_opcode_86(u8 opcode, u16 opcode_pc); void trace_opcode_87(u8 opcode, u16 opcode_pc); void trace_opcode_88(u8 opcode, u16 opcode_pc); void trace_opcode_89(u8 opcode, u16 opcode_pc); void trace_opcode_8A(u8 opcode, u16 opcode_pc); void trace_opcode_8B(u8 opcode, u16 opcode_pc); void trace_opcode_8C(u8 opcode, u16 opcode_pc); void trace_opcode_8D(u8 opcode, u16 opcode_pc); void trace_opcode_8E(u8 opcode, u16 opcode_pc); void trace_opcode_8F(u8 opcode, u16 opcode_pc);
    void trace_opcode_90(u8 opcode, u16 opcode_pc); void trace_opcode_91(u8 opcode, u16 opcode_pc); void trace_opcode_92(u8 opcode, u16 opcode_pc); void trace_opcode_93(u8 opcode, u16 opcode_pc); void trace_opcode_94(u8 opcode, u16 opcode_pc); void trace_opcode_95(u8 opcode, u16 opcode_pc); void trace_opcode_96(u8 opcode, u16 opcode_pc); void trace_opcode_97(u8 opcode, u16 opcode_pc); void trace_opcode_98(u8 opcode, u16 opcode_pc); void trace_opcode_99(u8 opcode, u16 opcode_pc); void trace_opcode_9A(u8 opcode, u16 opcode_pc); void trace_opcode_9B(u8 opcode, u16 opcode_pc); void trace_opcode_9C(u8 opcode, u16 opcode_pc); void trace_opcode_9D(u8 opcode, u16 opcode_pc); void trace_opcode_9E(u8 opcode, u16 opcode_pc); void trace_opcode_9F(u8 opcode, u16 opcode_pc);
    void trace_opcode_A0(u8 opcode, u16 opcode_pc); void trace_opcode_A1(u8 opcode, u16 opcode_pc); void trace_opcode_A2(u8 opcode, u16 opcode_pc); void trace_opcode_A3(u8 opcode, u16 opcode_pc); void trace_opcode_A4(u8 opcode, u16 opcode_pc); void trace_opcode_A5(u8 opcode, u16 opcode_pc); void trace_opcode_A6(u8 opcode, u16 opcode_pc); void trace_opcode_A7(u8 opcode, u16 opcode_pc); void trace_opcode_A8(u8 opcode, u16 opcode_pc); void trace_opcode_A9(u8 opcode, u16 opcode_pc); void trace_opcode_AA(u8 opcode, u16 opcode_pc); void trace_opcode_AB(u8 opcode, u16 opcode_pc); void trace_opcode_AC(u8 opcode, u16 opcode_pc); void trace_opcode_AD(u8 opcode, u16 opcode_pc); void trace_opcode_AE(u8 opcode, u16 opcode_pc); void trace_opcode_AF(u8 opcode, u16 opcode_pc);
    void trace_opcode_B0(u8 opcode, u16 opcode_pc); void trace_opcode_B1(u8 opcode, u16 opcode_pc); void trace_opcode_B2(u8 opcode, u16 opcode_pc); void trace_opcode_B3(u8 opcode, u16 opcode_pc); void trace_opcode_B4(u8 opcode, u16 opcode_pc); void trace_opcode_B5(u8 opcode, u16 opcode_pc); void trace_opcode_B6(u8 opcode, u16 opcode_pc); void trace_opcode_B7(u8 opcode, u16 opcode_pc); void trace_opcode_B8(u8 opcode, u16 opcode_pc); void trace_opcode_B9(u8 opcode, u16 opcode_pc); void trace_opcode_BA(u8 opcode, u16 opcode_pc); void trace_opcode_BB(u8 opcode, u16 opcode_pc); void trace_opcode_BC(u8 opcode, u16 opcode_pc); void trace_opcode_BD(u8 opcode, u16 opcode_pc); void trace_opcode_BE(u8 opcode, u16 opcode_pc); void trace_opcode_BF(u8 opcode, u16 opcode_pc);
    void trace_opcode_C0(u8 opcode, u16 opcode_pc); void trace_opcode_C1(u8 opcode, u16 opcode_pc); void trace_opcode_C2(u8 opcode, u16 opcode_pc); void trace_opcode_C3(u8 opcode, u16 opcode_pc); void trace_opcode_C4(u8 opcode, u16 opcode_pc); void trace_opcode_C5(u8 opcode, u16 opcode_pc); void trace_opcode_C6(u8 opcode, u16 opcode_pc); void trace_opcode_C7(u8 opcode, u16 opcode_pc); void trace_opcode_C8(u8 opcode, u16 opcode_pc); void trace_opcode_C9(u8 opcode, u16 opcode_pc); void trace_opcode_CA(u8 opcode, u16 opcode_pc); void trace_opcode_CB(u8 opcode, u16 opcode_pc); void trace_opcode_CC(u8 opcode, u16 opcode_pc); void trace_opcode_CD(u8 opcode, u16 opcode_pc); void trace_opcode_CE(u8 opcode, u16 opcode_pc); void trace_opcode_CF(u8 opcode, u16 opcode_pc);
    void trace_opcode_D0(u8 opcode, u16 opcode_pc); void trace_opcode_D1(u8 opcode, u16 opcode_pc); void trace_opcode_D2(u8 opcode, u16 opcode_pc); void trace_opcode_D3(u8 opcode, u16 opcode_pc); void trace_opcode_D4(u8 opcode, u16 opcode_pc); void trace_opcode_D5(u8 opcode, u16 opcode_pc); void trace_opcode_D6(u8 opcode, u16 opcode_pc); void trace_opcode_D7(u8 opcode, u16 opcode_pc); void trace_opcode_D8(u8 opcode, u16 opcode_pc); void trace_opcode_D9(u8 opcode, u16 opcode_pc); void trace_opcode_DA(u8 opcode, u16 opcode_pc); void trace_opcode_DB(u8 opcode, u16 opcode_pc); void trace_opcode_DC(u8 opcode, u16 opcode_pc); void trace_opcode_DD(u8 opcode, u16 opcode_pc); void trace_opcode_DE(u8 opcode, u16 opcode_pc); void trace_opcode_DF(u8 opcode, u16 opcode_pc);
    void trace_opcode_E0(u8 opcode, u16 opcode_pc); void trace_opcode_E1(u8 opcode, u16 opcode_pc); void trace_opcode_E2(u8 opcode, u16 opcode_pc); void trace_opcode_E3(u8 opcode, u16 opcode_pc); void trace_opcode_E4(u8 opcode, u16 opcode_pc); void trace_opcode_E5(u8 opcode, u16 opcode_pc); void trace_opcode_E6(u8 opcode, u16 opcode_pc); void trace_opcode_E7(u8 opcode, u16 opcode_pc); void trace_opcode_E8(u8 opcode, u16 opcode_pc); void trace_opcode_E9(u8 opcode, u16 opcode_pc); void trace_opcode_EA(u8 opcode, u16 opcode_pc); void trace_opcode_EB(u8 opcode, u16 opcode_pc); void trace_opcode_EC(u8 opcode, u16 opcode_pc); void trace_opcode_ED(u8 opcode, u16 opcode_pc); void trace_opcode_EE(u8 opcode, u16 opcode_pc); void trace_opcode_EF(u8 opcode, u16 opcode_pc);
    void trace_opcode_F0(u8 opcode, u16 opcode_pc); void trace_opcode_F1(u8 opcode, u16 opcode_pc); void trace_opcode_F2(u8 opcode, u16 opcode_pc); void trace_opcode_F3(u8 opcode, u16 opcode_pc); void trace_opcode_F4(u8 opcode, u16 opcode_pc); void trace_opcode_F5(u8 opcode, u16 opcode_pc); void trace_opcode_F6(u8 opcode, u16 opcode_pc); void trace_opcode_F7(u8 opcode, u16 opcode_pc); void trace_opcode_F8(u8 opcode, u16 opcode_pc); void trace_opcode_F9(u8 opcode, u16 opcode_pc); void trace_opcode_FA(u8 opcode, u16 opcode_pc); void trace_opcode_FB(u8 opcode, u16 opcode_pc); void trace_opcode_FC(u8 opcode, u16 opcode_pc); void trace_opcode_FD(u8 opcode, u16 opcode_pc); void trace_opcode_FE(u8 opcode, u16 opcode_pc); void trace_opcode_FF(u8 opcode, u16 opcode_pc);

    /* CB Opcodes */
    void trace_opcode_CB_00(u8 opcode, u16 opcode_pc); void trace_opcode_CB_01(u8 opcode, u16 opcode_pc); void trace_opcode_CB_02(u8 opcode, u16 opcode_pc); void trace_opcode_CB_03(u8 opcode, u16 opcode_pc); void trace_opcode_CB_04(u8 opcode, u16 opcode_pc); void trace_opcode_CB_05(u8 opcode, u16 opcode_pc); void trace_opcode_CB_06(u8 opcode, u16 opcode_pc); void trace_opcode_CB_07(u8 opcode, u16 opcode_pc); void trace_opcode_CB_08(u8 opcode, u16 opcode_pc); void trace_opcode_CB_09(u8 opcode, u16 opcode_pc); void trace_opcode_CB_0A(u8 opcode, u16 opcode_pc); void trace_opcode_CB_0B(u8 opcode, u16 opcode_pc); void trace_opcode_CB_0C(u8 opcode, u16 opcode_pc); void trace_opcode_CB_0D(u8 opcode, u16 opcode_pc); void trace_opcode_CB_0E(u8 opcode, u16 opcode_pc); void trace_opcode_CB_0F(u8 opcode, u16 opcode_pc);
    void trace_opcode_CB_10(u8 opcode, u16 opcode_pc); void trace_opcode_CB_11(u8 opcode, u16 opcode_pc); void trace_opcode_CB_12(u8 opcode, u16 opcode_pc); void trace_opcode_CB_13(u8 opcode, u16 opcode_pc); void trace_opcode_CB_14(u8 opcode, u16 opcode_pc); void trace_opcode_CB_15(u8 opcode, u16 opcode_pc); void trace_opcode_CB_16(u8 opcode, u16 opcode_pc); void trace_opcode_CB_17(u8 opcode, u16 opcode_pc); void trace_opcode_CB_18(u8 opcode, u16 opcode_pc); void trace_opcode_CB_19(u8 opcode, u16 opcode_pc); void trace_opcode_CB_1A(u8 opcode, u16 opcode_pc); void trace_opcode_CB_1B(u8 opcode, u16 opcode_pc); void trace_opcode_CB_1C(u8 opcode, u16 opcode_pc); void trace_opcode_CB_1D(u8 opcode, u16 opcode_pc); void trace_opcode_CB_1E(u8 opcode, u16 opcode_pc); void trace_opcode_CB_1F(u8 opcode, u16 opcode_pc);
    void trace_opcode_CB_20(u8 opcode, u16 opcode_pc); void trace_opcode_CB_21(u8 opcode, u16 opcode_pc); void trace_opcode_CB_22(u8 opcode, u16 opcode_pc); void trace_opcode_CB_23(u8 opcode, u16 opcode_pc); void trace_opcode_CB_24(u8 opcode, u16 opcode_pc); void trace_opcode_CB_25(u8 opcode, u16 opcode_pc); void trace_opcode_CB_26(u8 opcode, u16 opcode_pc); void trace_opcode_CB_27(u8 opcode, u16 opcode_pc); void trace_opcode_CB_28(u8 opcode, u16 opcode_pc); void trace_opcode_CB_29(u8 opcode, u16 opcode_pc); void trace_opcode_CB_2A(u8 opcode, u16 opcode_pc); void trace_opcode_CB_2B(u8 opcode, u16 opcode_pc); void trace_opcode_CB_2C(u8 opcode, u16 opcode_pc); void trace_opcode_CB_2D(u8 opcode, u16 opcode_pc); void trace_opcode_CB_2E(u8 opcode, u16 opcode_pc); void trace_opcode_CB_2F(u8 opcode, u16 opcode_pc);
    void trace_opcode_CB_30(u8 opcode, u16 opcode_pc); void trace_opcode_CB_31(u8 opcode, u16 opcode_pc); void trace_opcode_CB_32(u8 opcode, u16 opcode_pc); void trace_opcode_CB_33(u8 opcode, u16 opcode_pc); void trace_opcode_CB_34(u8 opcode, u16 opcode_pc); void trace_opcode_CB_35(u8 opcode, u16 opcode_pc); void trace_opcode_CB_36(u8 opcode, u16 opcode_pc); void trace_opcode_CB_37(u8 opcode, u16 opcode_pc); void trace_opcode_CB_38(u8 opcode, u16 opcode_pc); void trace_opcode_CB_39(u8 opcode, u16 opcode_pc); void trace_opcode_CB_3A(u8 opcode, u16 opcode_pc); void trace_opcode_CB_3B(u8 opcode, u16 opcode_pc); void trace_opcode_CB_3C(u8 opcode, u16 opcode_pc); void trace_opcode_CB_3D(u8 opcode, u16 opcode_pc); void trace_opcode_CB_3E(u8 opcode, u16 opcode_pc); void trace_opcode_CB_3F(u8 opcode, u16 opcode_pc);
    void trace_opcode_CB_40(u8 opcode, u16 opcode_pc); void trace_opcode_CB_41(u8 opcode, u16 opcode_pc); void trace_opcode_CB_42(u8 opcode, u16 opcode_pc); void trace_opcode_CB_43(u8 opcode, u16 opcode_pc); void trace_opcode_CB_44(u8 opcode, u16 opcode_pc); void trace_opcode_CB_45(u8 opcode, u16 opcode_pc); void trace_opcode_CB_46(u8 opcode, u16 opcode_pc); void trace_opcode_CB_47(u8 opcode, u16 opcode_pc); void trace_opcode_CB_48(u8 opcode, u16 opcode_pc); void trace_opcode_CB_49(u8 opcode, u16 opcode_pc); void trace_opcode_CB_4A(u8 opcode, u16 opcode_pc); void trace_opcode_CB_4B(u8 opcode, u16 opcode_pc); void trace_opcode_CB_4C(u8 opcode, u16 opcode_pc); void trace_opcode_CB_4D(u8 opcode, u16 opcode_pc); void trace_opcode_CB_4E(u8 opcode, u16 opcode_pc); void trace_opcode_CB_4F(u8 opcode, u16 opcode_pc);
    void trace_opcode_CB_50(u8 opcode, u16 opcode_pc); void trace_opcode_CB_51(u8 opcode, u16 opcode_pc); void trace_opcode_CB_52(u8 opcode, u16 opcode_pc); void trace_opcode_CB_53(u8 opcode, u16 opcode_pc); void trace_opcode_CB_54(u8 opcode, u16 opcode_pc); void trace_opcode_CB_55(u8 opcode, u16 opcode_pc); void trace_opcode_CB_56(u8 opcode, u16 opcode_pc); void trace_opcode_CB_57(u8 opcode, u16 opcode_pc); void trace_opcode_CB_58(u8 opcode, u16 opcode_pc); void trace_opcode_CB_59(u8 opcode, u16 opcode_pc); void trace_opcode_CB_5A(u8 opcode, u16 opcode_pc); void trace_opcode_CB_5B(u8 opcode, u16 opcode_pc); void trace_opcode_CB_5C(u8 opcode, u16 opcode_pc); void trace_opcode_CB_5D(u8 opcode, u16 opcode_pc); void trace_opcode_CB_5E(u8 opcode, u16 opcode_pc); void trace_opcode_CB_5F(u8 opcode, u16 opcode_pc);
    void trace_opcode_CB_60(u8 opcode, u16 opcode_pc); void trace_opcode_CB_61(u8 opcode, u16 opcode_pc); void trace_opcode_CB_62(u8 opcode, u16 opcode_pc); void trace_opcode_CB_63(u8 opcode, u16 opcode_pc); void trace_opcode_CB_64(u8 opcode, u16 opcode_pc); void trace_opcode_CB_65(u8 opcode, u16 opcode_pc); void trace_opcode_CB_66(u8 opcode, u16 opcode_pc); void trace_opcode_CB_67(u8 opcode, u16 opcode_pc); void trace_opcode_CB_68(u8 opcode, u16 opcode_pc); void trace_opcode_CB_69(u8 opcode, u16 opcode_pc); void trace_opcode_CB_6A(u8 opcode, u16 opcode_pc); void trace_opcode_CB_6B(u8 opcode, u16 opcode_pc); void trace_opcode_CB_6C(u8 opcode, u16 opcode_pc); void trace_opcode_CB_6D(u8 opcode, u16 opcode_pc); void trace_opcode_CB_6E(u8 opcode, u16 opcode_pc); void trace_opcode_CB_6F(u8 opcode, u16 opcode_pc);
    void trace_opcode_CB_70(u8 opcode, u16 opcode_pc); void trace_opcode_CB_71(u8 opcode, u16 opcode_pc); void trace_opcode_CB_72(u8 opcode, u16 opcode_pc); void trace_opcode_CB_73(u8 opcode, u16 opcode_pc); void trace_opcode_CB_74(u8 opcode, u16 opcode_pc); void trace_opcode_CB_75(u8 opcode, u16 opcode_pc); void trace_opcode_CB_76(u8 opcode, u16 opcode_pc); void trace_opcode_CB_77(u8 opcode, u16 opcode_pc); void trace_opcode_CB_78(u8 opcode, u16 opcode_pc); void trace_opcode_CB_79(u8 opcode, u16 opcode_pc); void trace_opcode_CB_7A(u8 opcode, u16 opcode_pc); void trace_opcode_CB_7B(u8 opcode, u16 opcode_pc); void trace_opcode_CB_7C(u8 opcode, u16 opcode_pc); void trace_opcode_CB_7D(u8 opcode, u16 opcode_pc); void trace_opcode_CB_7E(u8 opcode, u16 opcode_pc); void trace_opcode_CB_7F(u8 opcode, u16 opcode_pc);
    void trace_opcode_CB_80(u8 opcode, u16 opcode_pc); void trace_opcode_CB_81(u8 opcode, u16 opcode_pc); void trace_opcode_CB_82(u8 opcode, u16 opcode_pc); void trace_opcode_CB_83(u8 opcode, u16 opcode_pc); void trace_opcode_CB_84(u8 opcode, u16 opcode_pc); void trace_opcode_CB_85(u8 opcode, u16 opcode_pc); void trace_opcode_CB_86(u8 opcode, u16 opcode_pc); void trace_opcode_CB_87(u8 opcode, u16 opcode_pc); void trace_opcode_CB_88(u8 opcode, u16 opcode_pc); void trace_opcode_CB_89(u8 opcode, u16 opcode_pc); void trace_opcode_CB_8A(u8 opcode, u16 opcode_pc); void trace_opcode_CB_8B(u8 opcode, u16 opcode_pc); void trace_opcode_CB_8C(u8 opcode, u16 opcode_pc); void trace_opcode_CB_8D(u8 opcode, u16 opcode_pc); void trace_opcode_CB_8E(u8 opcode, u16 opcode_pc); void trace_opcode_CB_8F(u8 opcode, u16 opcode_pc);
    void trace_opcode_CB_90(u8 opcode, u16 opcode_pc); void trace_opcode_CB_91(u8 opcode, u16 opcode_pc); void trace_opcode_CB_92(u8 opcode, u16 opcode_pc); void trace_opcode_CB_93(u8 opcode, u16 opcode_pc); void trace_opcode_CB_94(u8 opcode, u16 opcode_pc); void trace_opcode_CB_95(u8 opcode, u16 opcode_pc); void trace_opcode_CB_96(u8 opcode, u16 opcode_pc); void trace_opcode_CB_97(u8 opcode, u16 opcode_pc); void trace_opcode_CB_98(u8 opcode, u16 opcode_pc); void trace_opcode_CB_99(u8 opcode, u16 opcode_pc); void trace_opcode_CB_9A(u8 opcode, u16 opcode_pc); void trace_opcode_CB_9B(u8 opcode, u16 opcode_pc); void trace_opcode_CB_9C(u8 opcode, u16 opcode_pc); void trace_opcode_CB_9D(u8 opcode, u16 opcode_pc); void trace_opcode_CB_9E(u8 opcode, u16 opcode_pc); void trace_opcode_CB_9F(u8 opcode, u16 opcode_pc);
    void trace_opcode_CB_A0(u8 opcode, u16 opcode_pc); void trace_opcode_CB_A1(u8 opcode, u16 opcode_pc); void trace_opcode_CB_A2(u8 opcode, u16 opcode_pc); void trace_opcode_CB_A3(u8 opcode, u16 opcode_pc); void trace_opcode_CB_A4(u8 opcode, u16 opcode_pc); void trace_opcode_CB_A5(u8 opcode, u16 opcode_pc); void trace_opcode_CB_A6(u8 opcode, u16 opcode_pc); void trace_opcode_CB_A7(u8 opcode, u16 opcode_pc); void trace_opcode_CB_A8(u8 opcode, u16 opcode_pc); void trace_opcode_CB_A9(u8 opcode, u16 opcode_pc); void trace_opcode_CB_AA(u8 opcode, u16 opcode_pc); void trace_opcode_CB_AB(u8 opcode, u16 opcode_pc); void trace_opcode_CB_AC(u8 opcode, u16 opcode_pc); void trace_opcode_CB_AD(u8 opcode, u16 opcode_pc); void trace_opcode_CB_AE(u8 opcode, u16 opcode_pc); void trace_opcode_CB_AF(u8 opcode, u16 opcode_pc);
    void trace_opcode_CB_B0(u8 opcode, u16 opcode_pc); void trace_opcode_CB_B1(u8 opcode, u16 opcode_pc); void trace_opcode_CB_B2(u8 opcode, u16 opcode_pc); void trace_opcode_CB_B3(u8 opcode, u16 opcode_pc); void trace_opcode_CB_B4(u8 opcode, u16 opcode_pc); void trace_opcode_CB_B5(u8 opcode, u16 opcode_pc); void trace_opcode_CB_B6(u8 opcode, u16 opcode_pc); void trace_opcode_CB_B7(u8 opcode, u16 opcode_pc); void trace_opcode_CB_B8(u8 opcode, u16 opcode_pc); void trace_opcode_CB_B9(u8 opcode, u16 opcode_pc); void trace_opcode_CB_BA(u8 opcode, u16 opcode_pc); void trace_opcode_CB_BB(u8 opcode, u16 opcode_pc); void trace_opcode_CB_BC(u8 opcode, u16 opcode_pc); void trace_opcode_CB_BD(u8 opcode, u16 opcode_pc); void trace_opcode_CB_BE(u8 opcode, u16 opcode_pc); void trace_opcode_CB_BF(u8 opcode, u16 opcode_pc);
    void trace_opcode_CB_C0(u8 opcode, u16 opcode_pc); void trace_opcode_CB_C1(u8 opcode, u16 opcode_pc); void trace_opcode_CB_C2(u8 opcode, u16 opcode_pc); void trace_opcode_CB_C3(u8 opcode, u16 opcode_pc); void trace_opcode_CB_C4(u8 opcode, u16 opcode_pc); void trace_opcode_CB_C5(u8 opcode, u16 opcode_pc); void trace_opcode_CB_C6(u8 opcode, u16 opcode_pc); void trace_opcode_CB_C7(u8 opcode, u16 opcode_pc); void trace_opcode_CB_C8(u8 opcode, u16 opcode_pc); void trace_opcode_CB_C9(u8 opcode, u16 opcode_pc); void trace_opcode_CB_CA(u8 opcode, u16 opcode_pc); void trace_opcode_CB_CB(u8 opcode, u16 opcode_pc); void trace_opcode_CB_CC(u8 opcode, u16 opcode_pc); void trace_opcode_CB_CD(u8 opcode, u16 opcode_pc); void trace_opcode_CB_CE(u8 opcode, u16 opcode_pc); void trace_opcode_CB_CF(u8 opcode, u16 opcode_pc);
    void trace_opcode_CB_D0(u8 opcode, u16 opcode_pc); void trace_opcode_CB_D1(u8 opcode, u16 opcode_pc); void trace_opcode_CB_D2(u8 opcode, u16 opcode_pc); void trace_opcode_CB_D3(u8 opcode, u16 opcode_pc); void trace_opcode_CB_D4(u8 opcode, u16 opcode_pc); void trace_opcode_CB_D5(u8 opcode, u16 opcode_pc); void trace_opcode_CB_D6(u8 opcode, u16 opcode_pc); void trace_opcode_CB_D7(u8 opcode, u16 opcode_pc); void trace_opcode_CB_D8(u8 opcode, u16 opcode_pc); void trace_opcode_CB_D9(u8 opcode, u16 opcode_pc); void trace_opcode_CB_DA(u8 opcode, u16 opcode_pc); void trace_opcode_CB_DB(u8 opcode, u16 opcode_pc); void trace_opcode_CB_DC(u8 opcode, u16 opcode_pc); void trace_opcode_CB_DD(u8 opcode, u16 opcode_pc); void trace_opcode_CB_DE(u8 opcode, u16 opcode_pc); void trace_opcode_CB_DF(u8 opcode, u16 opcode_pc);
    void trace_opcode_CB_E0(u8 opcode, u16 opcode_pc); void trace_opcode_CB_E1(u8 opcode, u16 opcode_pc); void trace_opcode_CB_E2(u8 opcode, u16 opcode_pc); void trace_opcode_CB_E3(u8 opcode, u16 opcode_pc); void trace_opcode_CB_E4(u8 opcode, u16 opcode_pc); void trace_opcode_CB_E5(u8 opcode, u16 opcode_pc); void trace_opcode_CB_E6(u8 opcode, u16 opcode_pc); void trace_opcode_CB_E7(u8 opcode, u16 opcode_pc); void trace_opcode_CB_E8(u8 opcode, u16 opcode_pc); void trace_opcode_CB_E9(u8 opcode, u16 opcode_pc); void trace_opcode_CB_EA(u8 opcode, u16 opcode_pc); void trace_opcode_CB_EB(u8 opcode, u16 opcode_pc); void trace_opcode_CB_EC(u8 opcode, u16 opcode_pc); void trace_opcode_CB_ED(u8 opcode, u16 opcode_pc); void trace_opcode_CB_EE(u8 opcode, u16 opcode_pc); void trace_opcode_CB_EF(u8 opcode, u16 opcode_pc);
    void trace_opcode_CB_F0(u8 opcode, u16 opcode_pc); void trace_opcode_CB_F1(u8 opcode, u16 opcode_pc); void trace_opcode_CB_F2(u8 opcode, u16 opcode_pc); void trace_opcode_CB_F3(u8 opcode, u16 opcode_pc); void trace_opcode_CB_F4(u8 opcode, u16 opcode_pc); void trace_opcode_CB_F5(u8 opcode, u16 opcode_pc); void trace_opcode_CB_F6(u8 opcode, u16 opcode_pc); void trace_opcode_CB_F7(u8 opcode, u16 opcode_pc); void trace_opcode_CB_F8(u8 opcode, u16 opcode_pc); void trace_opcode_CB_F9(u8 opcode, u16 opcode_pc); void trace_opcode_CB_FA(u8 opcode, u16 opcode_pc); void trace_opcode_CB_FB(u8 opcode, u16 opcode_pc); void trace_opcode_CB_FC(u8 opcode, u16 opcode_pc); void trace_opcode_CB_FD(u8 opcode, u16 opcode_pc); void trace_opcode_CB_FE(u8 opcode, u16 opcode_pc); void trace_opcode_CB_FF(u8 opcode, u16 opcode_pc);
    /* clang-format on */

    friend class Debugger;
};
