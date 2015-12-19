#ifndef EMULATOR_CPU_H
#define EMULATOR_CPU_H

#include <cstdint>
#include "../address.h"
#include "../clock.h"
#include "mmu.h"
#include "register.h"

/**
 * The Gameboy CPU is a Z80 (8-bit) chip.
 */

class CPU {
public:
    CPU();

    void execute_opcode(const uint8_t opcode);

private:
    Clock clock;
    MMU mmu;

    /* Basic registers */
    ByteRegister a, b, c, d, e, h, l;

    /* 'Group' registers for operations which use two registers as a word */
    RegisterPair bc = RegisterPair(b, c);
    RegisterPair de = RegisterPair(d, e);
    RegisterPair hl = RegisterPair(h, l);

    /*
     * Flags set dependant on the result of the last operation
     *  0x80 - produced 0
     *  0x40 - was a subtraction
     *  0x20 - lower half of the byte overflowed 15
     *  0x10 - overflowed 255 or underflowed 0 for additions/subtractions
     */
    ByteRegister f;

    /* Program counter */
    WordRegister pc;

    /* Stack pointer */
    WordRegister sp;

    uint8_t get_byte_from_pc();
    uint16_t get_word_from_pc();

    /* Opcode Helper Functions */

    /* ADC */
    void opcode_adc();
    void opcode_adc(const ByteRegister& reg);
    void opcode_adc(const Address&& addr);

    /* ADD */
    void opcode_add(ByteRegister& reg);
    void opcode_add(ByteRegister& reg, const ByteRegister& byte_reg);
    void opcode_add(ByteRegister& reg, const Address& addr);

    void opcode_add(RegisterPair& reg, const RegisterPair& reg_pair);
    void opcode_add(RegisterPair& reg, const WordRegister& word_reg);

    void opcode_add(WordRegister& reg);

    /* AND */
    void opcode_and();
    void opcode_and(ByteRegister& reg);
    void opcode_and(Address&& addr);

    /* BIT */
    void opcode_bit(const int bit, ByteRegister& reg);
    void opcode_bit(const int bit, Address& addr);

    /* CALL */
    void opcode_call();
    void opcode_call(const uint8_t condition);

    /* CCF */
    void opcode_ccf();

    /* CP */
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
    void opcode_jp(const int condition);
    void opcode_jp(const Address& addr);

    /* JR */
    void opcode_jr();
    void opcode_jr(const int condition);

    /* HALT */
    void opcode_halt();

    /* LD */
    void opcode_ld(ByteRegister& reg);
    void opcode_ld(ByteRegister& reg, const ByteRegister& byte_reg);
    void opcode_ld(ByteRegister& reg, const Address& address);

    void opcode_ld(RegisterPair& reg);

    void opcode_ld(WordRegister& reg);

    void opcode_ld(const Address& address);
    void opcode_ld(const Address& address, const ByteRegister& byte_reg);
    void opcode_ld(const Address& address, const WordRegister& word_reg);

    /* LDD */
    void opcode_ldd(const ByteRegister& reg, const Address& address);
    void opcode_ldd(const Address& address, const ByteRegister& reg);

    /* LDH */
    // TODO: Add a type to express an 8-bit offset
    void opcode_ldh(const ByteRegister& reg, const Address& address);
    void opcode_ldh(const Address& address, const ByteRegister& reg);

    /* LDHL */
    void opcode_ldhl(const WordRegister& reg);

    /* LDI */
    void opcode_ldi(const ByteRegister& reg, const Address& address);
    void opcode_ldi(const Address& address, const ByteRegister& reg);

    /* NOP */
    void opcode_nop();

    /* OR */
    void opcode_or();
    void opcode_or(const ByteRegister& reg);
    void opcode_or(const Address& addr);

    /* POP */
    void opcode_pop(const RegisterPair& reg);

    /* PUSH */
    void opcode_push(const RegisterPair& reg);

    /* RES */
    void opcode_res(const int bit, ByteRegister& reg);
    void opcode_res(const int bit, Address& addr);

    /* RET */
    void opcode_ret();
    void opcode_ret(const int condition);

    /* RETI */
    void opcode_reti();

    /* RL */
    void opcode_rl(ByteRegister& reg);
    void opcode_rl(Address&& addr);

    /* RLC */
    void opcode_rlc(ByteRegister& reg);
    void opcode_rlc(Address&& addr);

    /* RR */
    void opcode_rr(ByteRegister& reg);
    void opcode_rr(Address&& addr);

    /* RRC */
    void opcode_rrc(ByteRegister& reg);
    void opcode_rrc(Address&& addr);

    /* RST */
    // TODO: offset type
    void opcode_rst(const uint8_t offset);

    /* SBC */
    void opcode_sbc(ByteRegister& reg);
    void opcode_sbc(Address&& addr);

    /* SCF */
    void opcode_scf();

    /* SET */
    void opcode_set(const int bit, ByteRegister& reg);
    void opcode_set(const int bit, Address& addr);

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
    void opcode_sub();
    void opcode_sub(ByteRegister& reg);
    void opcode_sub(Address&& addr);

    /* SWAP */
    void opcode_swap(ByteRegister& reg);
    void opcode_swap(Address&& addr);

    /* XOR */
    void opcode_xor();
    void opcode_xor(const ByteRegister& reg);
    void opcode_xor(const Address& addr);

    /* Opcodes */
    void opcode_00();
    void opcode_01();
    void opcode_02();
    void opcode_03();
    void opcode_04();
    void opcode_05();
    void opcode_06();
    void opcode_07();
    void opcode_08();
    void opcode_09();
    void opcode_0A();
    void opcode_0B();
    void opcode_0C();
    void opcode_0D();
    void opcode_0E();
    void opcode_0F();

    void opcode_10();
    void opcode_11();
    void opcode_12();
    void opcode_13();
    void opcode_14();
    void opcode_15();
    void opcode_16();
    void opcode_17();
    void opcode_18();
    void opcode_19();
    void opcode_1A();
    void opcode_1B();
    void opcode_1C();
    void opcode_1D();
    void opcode_1E();
    void opcode_1F();

    void opcode_20();
    void opcode_21();
    void opcode_22();
    void opcode_23();
    void opcode_24();
    void opcode_25();
    void opcode_26();
    void opcode_27();
    void opcode_28();
    void opcode_29();
    void opcode_2A();
    void opcode_2B();
    void opcode_2C();
    void opcode_2D();
    void opcode_2E();
    void opcode_2F();

    void opcode_30();
    void opcode_31();
    void opcode_32();
    void opcode_33();
    void opcode_34();
    void opcode_35();
    void opcode_36();
    void opcode_37();
    void opcode_38();
    void opcode_39();
    void opcode_3A();
    void opcode_3B();
    void opcode_3C();
    void opcode_3D();
    void opcode_3E();
    void opcode_3F();

    void opcode_40();
    void opcode_41();
    void opcode_42();
    void opcode_43();
    void opcode_44();
    void opcode_45();
    void opcode_46();
    void opcode_47();
    void opcode_48();
    void opcode_49();
    void opcode_4A();
    void opcode_4B();
    void opcode_4C();
    void opcode_4D();
    void opcode_4E();
    void opcode_4F();

    void opcode_50();
    void opcode_51();
    void opcode_52();
    void opcode_53();
    void opcode_54();
    void opcode_55();
    void opcode_56();
    void opcode_57();
    void opcode_58();
    void opcode_59();
    void opcode_5A();
    void opcode_5B();
    void opcode_5C();
    void opcode_5D();
    void opcode_5E();
    void opcode_5F();

    void opcode_60();
    void opcode_61();
    void opcode_62();
    void opcode_63();
    void opcode_64();
    void opcode_65();
    void opcode_66();
    void opcode_67();
    void opcode_68();
    void opcode_69();
    void opcode_6A();
    void opcode_6B();
    void opcode_6C();
    void opcode_6D();
    void opcode_6E();
    void opcode_6F();

    void opcode_70();
    void opcode_71();
    void opcode_72();
    void opcode_73();
    void opcode_74();
    void opcode_75();
    void opcode_76();
    void opcode_77();
    void opcode_78();
    void opcode_79();
    void opcode_7A();
    void opcode_7B();
    void opcode_7C();
    void opcode_7D();
    void opcode_7E();
    void opcode_7F();

    void opcode_80();
    void opcode_81();
    void opcode_82();
    void opcode_83();
    void opcode_84();
    void opcode_85();
    void opcode_86();
    void opcode_87();
    void opcode_88();
    void opcode_89();
    void opcode_8A();
    void opcode_8B();
    void opcode_8C();
    void opcode_8D();
    void opcode_8E();
    void opcode_8F();

    void opcode_90();
    void opcode_91();
    void opcode_92();
    void opcode_93();
    void opcode_94();
    void opcode_95();
    void opcode_96();
    void opcode_97();
    void opcode_98();
    void opcode_99();
    void opcode_9A();
    void opcode_9B();
    void opcode_9C();
    void opcode_9D();
    void opcode_9E();
    void opcode_9F();

    void opcode_A0();
    void opcode_A1();
    void opcode_A2();
    void opcode_A3();
    void opcode_A4();
    void opcode_A5();
    void opcode_A6();
    void opcode_A7();
    void opcode_A8();
    void opcode_A9();
    void opcode_AA();
    void opcode_AB();
    void opcode_AC();
    void opcode_AD();
    void opcode_AE();
    void opcode_AF();

    void opcode_B0();
    void opcode_B1();
    void opcode_B2();
    void opcode_B3();
    void opcode_B4();
    void opcode_B5();
    void opcode_B6();
    void opcode_B7();
    void opcode_B8();
    void opcode_B9();
    void opcode_BA();
    void opcode_BB();
    void opcode_BC();
    void opcode_BD();
    void opcode_BE();
    void opcode_BF();

    void opcode_C0();
    void opcode_C1();
    void opcode_C2();
    void opcode_C3();
    void opcode_C4();
    void opcode_C5();
    void opcode_C6();
    void opcode_C7();
    void opcode_C8();
    void opcode_C9();
    void opcode_CA();
    void opcode_CB();
    void opcode_CC();
    void opcode_CD();
    void opcode_CE();
    void opcode_CF();

    void opcode_D0();
    void opcode_D1();
    void opcode_D2();
    void opcode_D3();
    void opcode_D4();
    void opcode_D5();
    void opcode_D6();
    void opcode_D7();
    void opcode_D8();
    void opcode_D9();
    void opcode_DA();
    void opcode_DB();
    void opcode_DC();
    void opcode_DD();
    void opcode_DE();
    void opcode_DF();

    void opcode_E0();
    void opcode_E1();
    void opcode_E2();
    void opcode_E3();
    void opcode_E4();
    void opcode_E5();
    void opcode_E6();
    void opcode_E7();
    void opcode_E8();
    void opcode_E9();
    void opcode_EA();
    void opcode_EB();
    void opcode_EC();
    void opcode_ED();
    void opcode_EE();
    void opcode_EF();

    void opcode_F0();
    void opcode_F1();
    void opcode_F2();
    void opcode_F3();
    void opcode_F4();
    void opcode_F5();
    void opcode_F6();
    void opcode_F7();
    void opcode_F8();
    void opcode_F9();
    void opcode_FA();
    void opcode_FB();
    void opcode_FC();
    void opcode_FD();
    void opcode_FE();
    void opcode_FF();
};

#endif
