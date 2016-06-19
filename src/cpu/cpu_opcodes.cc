#include "cpu.h"

/**
 * This section contains functions which map to actual opcodes which are executed
 * by the Gameboy's processor.
 */

void CPU::opcode_00() {
    opcode_nop();
}

void CPU::opcode_01() {
    opcode_ld(bc);
}

void CPU::opcode_02() {
    opcode_ld(Address(bc), a);
}

void CPU::opcode_03() {
    opcode_inc(bc);
}

void CPU::opcode_04() {
    opcode_inc(b);
}

void CPU::opcode_05() {
    opcode_dec(b);
}

void CPU::opcode_06() {
    opcode_ld(b);
}

void CPU::opcode_07() {
    opcode_rlc(a);
}

void CPU::opcode_08() {
    u16 nn = get_word_from_pc();
    opcode_ld(Address(nn), sp);
}

void CPU::opcode_09() {
    opcode_add_hl(bc);
}

void CPU::opcode_0A() {
    opcode_ld(a, Address(bc));
}

void CPU::opcode_0B() {
    opcode_dec(bc);
}

void CPU::opcode_0C() {
    opcode_inc(c);
}

void CPU::opcode_0D() {
    opcode_dec(c);
}

void CPU::opcode_0E() {
    opcode_ld(c);
}

void CPU::opcode_0F() {
    opcode_rrc(a);
}

void CPU::opcode_10() {
    opcode_stop();
}

void CPU::opcode_11() {
    opcode_ld(de);
}

void CPU::opcode_12() {
    opcode_ld(Address(de), a);
}

void CPU::opcode_13() {
    opcode_inc(de);
}

void CPU::opcode_14() {
    opcode_inc(d);
}

void CPU::opcode_15() {
    opcode_dec(d);
}

void CPU::opcode_16() {
    opcode_ld(d);
}

void CPU::opcode_17() {
    opcode_rl(a);
}

void CPU::opcode_18() {
    opcode_jr();
}

void CPU::opcode_19() {
    opcode_add_hl(de);
}

void CPU::opcode_1A() {
    opcode_ld(a, Address(de));
}

void CPU::opcode_1B() {
    opcode_dec(de);
}

void CPU::opcode_1C() {
    opcode_inc(e);
}

void CPU::opcode_1D() {
    opcode_dec(e);
}

void CPU::opcode_1E() {
    opcode_ld(e);
}

void CPU::opcode_1F() {
    opcode_rr(a);
}

void CPU::opcode_20() {
    opcode_jr(Condition::NZ);
}

void CPU::opcode_21() {
    opcode_ld(hl);
}

void CPU::opcode_22() {
    opcode_ldi(Address(hl), a);
}

void CPU::opcode_23() {
    opcode_inc(hl);
}

void CPU::opcode_24() {
    opcode_inc(h);
}

void CPU::opcode_25() {
    opcode_inc(l);
}

void CPU::opcode_26() {
    opcode_ld(h);
}

void CPU::opcode_27() {
    opcode_daa();
}

void CPU::opcode_28() {
    opcode_jr(Condition::Z);
}

void CPU::opcode_29() {
    opcode_add_hl(hl);
}

void CPU::opcode_2A() {
    opcode_ldi(a, Address(hl));
}

void CPU::opcode_2B() {
    opcode_dec(hl);
}

void CPU::opcode_2C() {
    opcode_inc(l);
}

void CPU::opcode_2D() {
    opcode_dec(l);
}

void CPU::opcode_2E() {
    opcode_ld(l);
}

void CPU::opcode_2F() {
    opcode_cpl();
}

void CPU::opcode_30() {
    opcode_jr(Condition::NC);
}

void CPU::opcode_31() {
    opcode_ld(sp);
}

void CPU::opcode_32() {
    opcode_ldd(Address(hl), a);
}

void CPU::opcode_33() {
    opcode_inc(sp);
}

void CPU::opcode_34() {
    opcode_inc(Address(hl));
}

void CPU::opcode_35() {
    opcode_dec(Address(hl));
}

void CPU::opcode_36() {
    opcode_ld(Address(hl));
}

void CPU::opcode_37() {
    opcode_scf();
}

void CPU::opcode_38() {
    opcode_jr(Condition::C);
}

void CPU::opcode_39() {
    opcode_add_hl(sp);
}

void CPU::opcode_3A() {
    opcode_ldd(a, Address(hl));
}

void CPU::opcode_3B() {
    opcode_dec(sp);
}

void CPU::opcode_3C() {
    opcode_inc(a);
}

void CPU::opcode_3D() {
    opcode_dec(a);
}

void CPU::opcode_3E() {
    opcode_ld(a);
}

void CPU::opcode_3F() {
    opcode_ccf();
}

void CPU::opcode_40() {
    opcode_ld(b, b);
}

void CPU::opcode_41() {
    opcode_ld(b, c);
}

void CPU::opcode_42() {
    opcode_ld(b, d);
}

void CPU::opcode_43() {
    opcode_ld(b, e);
}

void CPU::opcode_44() {
    opcode_ld(b, h);
}

void CPU::opcode_45() {
    opcode_ld(b, l);
}

void CPU::opcode_46() {
    opcode_ld(b, Address(hl));
}

void CPU::opcode_47() {
    opcode_ld(b, a);
}

void CPU::opcode_48() {
    opcode_ld(c, b);
}

void CPU::opcode_49() {
    opcode_ld(c, c);
}

void CPU::opcode_4A() {
    opcode_ld(c, d);
}

void CPU::opcode_4B() {
    opcode_ld(c, e);
}

void CPU::opcode_4C() {
    opcode_ld(c, h);
}

void CPU::opcode_4D() {
    opcode_ld(c, l);
}

void CPU::opcode_4E() {
    opcode_ld(c, Address(hl));
}

void CPU::opcode_4F() {
    opcode_ld(c, a);
}

void CPU::opcode_50() {
    opcode_ld(d, b);
}

void CPU::opcode_51() {
    opcode_ld(d, c);
}

void CPU::opcode_52() {
    opcode_ld(d, d);
}

void CPU::opcode_53() {
    opcode_ld(d, e);
}

void CPU::opcode_54() {
    opcode_ld(d, h);
}

void CPU::opcode_55() {
    opcode_ld(d, l);
}

void CPU::opcode_56() {
    opcode_ld(d, Address(hl));
}

void CPU::opcode_57() {
    opcode_ld(d, a);
}

void CPU::opcode_58() {
    opcode_ld(e, b);
}

void CPU::opcode_59() {
    opcode_ld(e, c);
}

void CPU::opcode_5A() {
    opcode_ld(e, d);
}

void CPU::opcode_5B() {
    opcode_ld(e, e);
}

void CPU::opcode_5C() {
    opcode_ld(e, h);
}

void CPU::opcode_5D() {
    opcode_ld(e, l);
}

void CPU::opcode_5E() {
    opcode_ld(e, Address(hl));
}

void CPU::opcode_5F() {
    opcode_ld(e, a);
}

void CPU::opcode_60() {
    opcode_ld(h, b);
}

void CPU::opcode_61() {
    opcode_ld(h, c);
}

void CPU::opcode_62() {
    opcode_ld(h, d);
}

void CPU::opcode_63() {
    opcode_ld(h, e);
}

void CPU::opcode_64() {
    opcode_ld(h, h);
}

void CPU::opcode_65() {
    opcode_ld(h, l);
}

void CPU::opcode_66() {
    opcode_ld(h, Address(hl));
}

void CPU::opcode_67() {
    opcode_ld(h, a);
}

void CPU::opcode_68() {
    opcode_ld(l, b);
}

void CPU::opcode_69() {
    opcode_ld(l, c);
}

void CPU::opcode_6A() {
    opcode_ld(l, d);
}

void CPU::opcode_6B() {
    opcode_ld(l, e);
}

void CPU::opcode_6C() {
    opcode_ld(l, h);
}

void CPU::opcode_6D() {
    opcode_ld(l, l);
}

void CPU::opcode_6E() {
    opcode_ld(l, Address(hl));
}

void CPU::opcode_6F() {
    opcode_ld(l, a);
}

void CPU::opcode_70() {
    opcode_ld(Address(hl), b);
}

void CPU::opcode_71() {
    opcode_ld(Address(hl), c);
}

void CPU::opcode_72() {
    opcode_ld(Address(hl), d);
}

void CPU::opcode_73() {
    opcode_ld(Address(hl), e);
}

void CPU::opcode_74() {
    opcode_ld(Address(hl), h);
}

void CPU::opcode_75() {
    opcode_ld(Address(hl), l);
}

void CPU::opcode_76() {
    opcode_halt();
}

void CPU::opcode_77() {
    opcode_ld(Address(hl), a);
}

void CPU::opcode_78() {
    opcode_ld(a, b);
}

void CPU::opcode_79() {
    opcode_ld(a, c);
}

void CPU::opcode_7A() {
    opcode_ld(a, d);
}

void CPU::opcode_7B() {
    opcode_ld(a, e);
}

void CPU::opcode_7C() {
    opcode_ld(a, h);
}

void CPU::opcode_7D() {
    opcode_ld(a, l);
}

void CPU::opcode_7E() {
    opcode_ld(a, Address(hl));
}

void CPU::opcode_7F() {
    opcode_ld(a, a);
}

void CPU::opcode_80() {
    opcode_add_a(b);
}

void CPU::opcode_81() {
    opcode_add_a(c);
}

void CPU::opcode_82() {
    opcode_add_a(d);
}

void CPU::opcode_83() {
    opcode_add_a(e);
}

void CPU::opcode_84() {
    opcode_add_a(h);
}

void CPU::opcode_85() {
    opcode_add_a(l);
}

void CPU::opcode_86() {
    opcode_add_a(Address(hl));
}

void CPU::opcode_87() {
    opcode_add_a(a);
}

void CPU::opcode_88() {
    opcode_adc(b);
}

void CPU::opcode_89() {
    opcode_adc(c);
}

void CPU::opcode_8A() {
    opcode_adc(d);
}

void CPU::opcode_8B() {
    opcode_adc(e);
}

void CPU::opcode_8C() {
    opcode_adc(h);
}

void CPU::opcode_8D() {
    opcode_adc(l);
}

void CPU::opcode_8E() {
    opcode_adc(Address(hl));
}

void CPU::opcode_8F() {
    opcode_adc(a);
}

void CPU::opcode_90() {
    opcode_sub(b);
}

void CPU::opcode_91() {
    opcode_sub(c);
}

void CPU::opcode_92() {
    opcode_sub(d);
}

void CPU::opcode_93() {
    opcode_sub(e);
}

void CPU::opcode_94() {
    opcode_sub(h);
}

void CPU::opcode_95() {
    opcode_sub(l);
}

void CPU::opcode_96() {
    opcode_sub(Address(hl));
}

void CPU::opcode_97() {
    opcode_sub(a);
}

void CPU::opcode_98() {
    opcode_sbc(b);
}

void CPU::opcode_99() {
    opcode_sbc(c);
}

void CPU::opcode_9A() {
    opcode_sbc(d);
}

void CPU::opcode_9B() {
    opcode_sbc(e);
}

void CPU::opcode_9C() {
    opcode_sbc(h);
}

void CPU::opcode_9D() {
    opcode_sbc(l);
}

void CPU::opcode_9E() {
    opcode_sbc(Address(hl));
}

void CPU::opcode_9F() {
    opcode_sbc(a);
}

void CPU::opcode_A0() {
    opcode_and(b);
}

void CPU::opcode_A1() {
    opcode_and(c);
}

void CPU::opcode_A2() {
    opcode_and(d);
}

void CPU::opcode_A3() {
    opcode_and(e);
}

void CPU::opcode_A4() {
    opcode_and(h);
}

void CPU::opcode_A5() {
    opcode_and(l);
}

void CPU::opcode_A6() {
    opcode_and(Address(hl));
}

void CPU::opcode_A7() {
    opcode_and(a);
}

void CPU::opcode_A8() {
    opcode_xor(b);
}

void CPU::opcode_A9() {
    opcode_xor(c);
}

void CPU::opcode_AA() {
    opcode_xor(d);
}

void CPU::opcode_AB() {
    opcode_xor(e);
}

void CPU::opcode_AC() {
    opcode_xor(h);
}

void CPU::opcode_AD() {
    opcode_xor(l);
}

void CPU::opcode_AE() {
    opcode_xor(Address(hl));
}

void CPU::opcode_AF() {
    opcode_xor(a);
}

void CPU::opcode_B0() {
    opcode_or(b);
}

void CPU::opcode_B1() {
    opcode_or(c);
}

void CPU::opcode_B2() {
    opcode_or(d);
}

void CPU::opcode_B3() {
    opcode_or(e);
}

void CPU::opcode_B4() {
    opcode_or(h);
}

void CPU::opcode_B5() {
    opcode_or(l);
}

void CPU::opcode_B6() {
    opcode_or(Address(hl));
}

void CPU::opcode_B7() {
    opcode_or(a);
}

void CPU::opcode_B8() {
    opcode_cp(b);
}

void CPU::opcode_B9() {
    opcode_cp(c);
}

void CPU::opcode_BA() {
    opcode_cp(d);
}

void CPU::opcode_BB() {
    opcode_cp(e);
}

void CPU::opcode_BC() {
    opcode_cp(h);
}

void CPU::opcode_BD() {
    opcode_cp(l);
}

void CPU::opcode_BE() {
    opcode_cp(Address(hl));
}

void CPU::opcode_BF() {
    opcode_cp(a);
}

void CPU::opcode_C0() {
    opcode_ret(Condition::NZ);
}

void CPU::opcode_C1() {
    opcode_pop(bc);
}

void CPU::opcode_C2() {
    opcode_jp(Condition::NZ);
}

void CPU::opcode_C3() {
    opcode_jp();
}

void CPU::opcode_C4() {
    opcode_call(Condition::NZ);
}

void CPU::opcode_C5() {
    opcode_push(bc);
}

void CPU::opcode_C6() {
    opcode_add_a();
}

void CPU::opcode_C7() {
    opcode_rst(0);
}

void CPU::opcode_C8() {
    opcode_ret(Condition::Z);
}

void CPU::opcode_C9() {
    opcode_ret();
}

void CPU::opcode_CA() {
    opcode_jp(Condition::Z);
}

void CPU::opcode_CB() {
    // TODO: External Ops
}

void CPU::opcode_CC() {
    opcode_call(Condition::Z);
}

void CPU::opcode_CD() {
    opcode_call();
}

void CPU::opcode_CE() {
    opcode_adc();
}

void CPU::opcode_CF() {
    opcode_rst(8);
}

void CPU::opcode_D0() {
    opcode_ret(Condition::NC);
}

void CPU::opcode_D1() {
    opcode_pop(de);
}

void CPU::opcode_D2() {
    opcode_jp(Condition::NC);
}

void CPU::opcode_D3() {
    // Undefined
}

void CPU::opcode_D4() {
    opcode_call(Condition::NC);
}

void CPU::opcode_D5() {
    opcode_push(de);
}

void CPU::opcode_D6() {
    opcode_sub();
}

void CPU::opcode_D7() {
    opcode_rst(10);
}

void CPU::opcode_D8() {
    opcode_ret(Condition::C);
}

void CPU::opcode_D9() {
    opcode_reti();
}

void CPU::opcode_DA() {
    opcode_jp(Condition::C);
}

void CPU::opcode_DB() {
    // Undefined
}

void CPU::opcode_DC() {
    opcode_call(Condition::C);
}

void CPU::opcode_DD() {
    // Undefined
}

void CPU::opcode_DE() {
    opcode_sbc();
}

void CPU::opcode_DF() {
    opcode_rst(18);
}

void CPU::opcode_E0() {
    opcode_ldh_into_data();
}

void CPU::opcode_E1() {
    opcode_pop(hl);
}

void CPU::opcode_E2() {
    opcode_ldh_into_c();
}

void CPU::opcode_E3() {
    // Undefined
}

void CPU::opcode_E4() {
    // Undefined
}

void CPU::opcode_E5() {
    opcode_push(hl);
}

void CPU::opcode_E6() {
    opcode_and();
}

void CPU::opcode_E7() {
    opcode_rst(20);
}

void CPU::opcode_E8() {
    opcode_add_signed();
}

void CPU::opcode_E9() {
    opcode_jp(Address(hl));
}

void CPU::opcode_EA() {
    opcode_ld_to_addr(a);
}

void CPU::opcode_EB() {
    // Undefined
}

void CPU::opcode_EC() {
    // Undefined
}

void CPU::opcode_ED() {
    // Undefined
}

void CPU::opcode_EE() {
    opcode_xor();
}

void CPU::opcode_EF() {
    opcode_rst(28);
}

void CPU::opcode_F0() {
    opcode_ldh_into_a();
}

void CPU::opcode_F1() {
    opcode_pop(af);
}

void CPU::opcode_F2() {
    // Undefined
}

void CPU::opcode_F3() {
    opcode_di();
}

void CPU::opcode_F4() {
    // Undefined
}

void CPU::opcode_F5() {
    opcode_push(af);
}

void CPU::opcode_F6() {
    opcode_or();
}

void CPU::opcode_F7() {
    opcode_rst(30);
}

void CPU::opcode_F8() {
    opcode_ldhl();
}

void CPU::opcode_F9() {
    opcode_ld(sp, hl);
}

void CPU::opcode_FA() {
    opcode_ld(a);
}

void CPU::opcode_FB() {
    opcode_ei();
}

void CPU::opcode_FC() {
    // Undefined
}

void CPU::opcode_FD() {
    // Undefined
}

void CPU::opcode_FE() {
    opcode_cp();
}

void CPU::opcode_FF() {
    opcode_rst(38);
}
