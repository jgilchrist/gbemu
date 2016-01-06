#include "cpu.h"

/**
 * This section contains two-byte opcodes, which are triggered when prefixed with
 * the CB instruction above.
 */

void CPU::opcode_CB_00() {
    opcode_rlc(b);
}

void CPU::opcode_CB_01() {
    opcode_rlc(c);
}

void CPU::opcode_CB_02() {
    opcode_rlc(d);
}

void CPU::opcode_CB_03() {
    opcode_rlc(e);
}

void CPU::opcode_CB_04() {
    opcode_rlc(h);
}

void CPU::opcode_CB_05() {
    opcode_rlc(l);
}

void CPU::opcode_CB_06() {
    opcode_rlc(Address(hl));
}

void CPU::opcode_CB_07() {
    opcode_rlc(a);
}

void CPU::opcode_CB_08() {
    opcode_rrc(b);
}

void CPU::opcode_CB_09() {
    opcode_rrc(c);
}

void CPU::opcode_CB_0A() {
    opcode_rrc(d);
}

void CPU::opcode_CB_0B() {
    opcode_rrc(e);
}

void CPU::opcode_CB_0C() {
    opcode_rrc(h);
}

void CPU::opcode_CB_0D() {
    opcode_rrc(l);
}

void CPU::opcode_CB_0E() {
    opcode_rrc(Address(hl));
}

void CPU::opcode_CB_0F() {
    opcode_rrc(a);
}

void CPU::opcode_CB_10() {
    opcode_rl(b);
}

void CPU::opcode_CB_11() {
    opcode_rl(c);
}

void CPU::opcode_CB_12() {
    opcode_rl(d);
}

void CPU::opcode_CB_13() {
    opcode_rl(e);
}

void CPU::opcode_CB_14() {
    opcode_rl(h);
}

void CPU::opcode_CB_15() {
    opcode_rl(l);
}

void CPU::opcode_CB_16() {
    opcode_rl(Address(hl));
}

void CPU::opcode_CB_17() {
    opcode_rl(a);
}

void CPU::opcode_CB_18() {
    opcode_rr(b);
}

void CPU::opcode_CB_19() {
    opcode_rr(c);
}

void CPU::opcode_CB_1A() {
    opcode_rr(d);
}

void CPU::opcode_CB_1B() {
    opcode_rr(e);
}

void CPU::opcode_CB_1C() {
    opcode_rr(h);
}

void CPU::opcode_CB_1D() {
    opcode_rr(l);
}

void CPU::opcode_CB_1E() {
    opcode_rr(Address(hl));
}

void CPU::opcode_CB_1F() {
    opcode_rr(a);
}

void CPU::opcode_CB_20() {
    opcode_sla(b);
}

void CPU::opcode_CB_21() {
    opcode_sla(c);
}

void CPU::opcode_CB_22() {
    opcode_sla(d);
}

void CPU::opcode_CB_23() {
    opcode_sla(e);
}

void CPU::opcode_CB_24() {
    opcode_sla(h);
}

void CPU::opcode_CB_25() {
    opcode_sla(l);
}

void CPU::opcode_CB_26() {
    opcode_sla(Address(hl));
}

void CPU::opcode_CB_27() {
    opcode_sla(a);
}

void CPU::opcode_CB_28() {
    opcode_sra(b);
}

void CPU::opcode_CB_29() {
    opcode_sra(c);
}

void CPU::opcode_CB_2A() {
    opcode_sra(d);
}

void CPU::opcode_CB_2B() {
    opcode_sra(e);
}

void CPU::opcode_CB_2C() {
    opcode_sra(h);
}

void CPU::opcode_CB_2D() {
    opcode_sra(l);
}

void CPU::opcode_CB_2E() {
    opcode_sra(Address(hl));
}

void CPU::opcode_CB_2F() {
    opcode_sra(a);
}

void CPU::opcode_CB_30() {
    opcode_swap(b);
}

void CPU::opcode_CB_31() {
    opcode_swap(c);
}

void CPU::opcode_CB_32() {
    opcode_swap(d);
}

void CPU::opcode_CB_33() {
    opcode_swap(e);
}

void CPU::opcode_CB_34() {
    opcode_swap(h);
}

void CPU::opcode_CB_35() {
    opcode_swap(l);
}

void CPU::opcode_CB_36() {
    opcode_swap(Address(hl));
}

void CPU::opcode_CB_37() {
    opcode_swap(a);
}

void CPU::opcode_CB_38() {
    opcode_srl(b);
}

void CPU::opcode_CB_39() {
    opcode_srl(c);
}

void CPU::opcode_CB_3A() {
    opcode_srl(d);
}

void CPU::opcode_CB_3B() {
    opcode_srl(e);
}

void CPU::opcode_CB_3C() {
    opcode_srl(h);
}

void CPU::opcode_CB_3D() {
    opcode_srl(l);
}

void CPU::opcode_CB_3E() {
    opcode_srl(Address(hl));
}

void CPU::opcode_CB_3F() {
    opcode_srl(a);
}

void CPU::opcode_CB_40() {
    opcode_bit(0, b);
}

void CPU::opcode_CB_41() {
    opcode_bit(0, c);
}

void CPU::opcode_CB_42() {
    opcode_bit(0, d);
}

void CPU::opcode_CB_43() {
    opcode_bit(0, e);
}

void CPU::opcode_CB_44() {
    opcode_bit(0, h);
}

void CPU::opcode_CB_45() {
    opcode_bit(0, l);
}

void CPU::opcode_CB_46() {
    opcode_bit(0, Address(hl));
}

void CPU::opcode_CB_47() {
    opcode_bit(0, a);
}

void CPU::opcode_CB_48() {
    opcode_bit(1, b);
}

void CPU::opcode_CB_49() {
    opcode_bit(1, c);
}

void CPU::opcode_CB_4A() {
    opcode_bit(1, d);
}

void CPU::opcode_CB_4B() {
    opcode_bit(1, e);
}

void CPU::opcode_CB_4C() {
    opcode_bit(1, h);
}

void CPU::opcode_CB_4D() {
    opcode_bit(1, l);
}

void CPU::opcode_CB_4E() {
    opcode_bit(1, Address(hl));
}

void CPU::opcode_CB_4F() {
    opcode_bit(1, a);
}

void CPU::opcode_CB_50() {
    opcode_bit(2, b);
}

void CPU::opcode_CB_51() {
    opcode_bit(2, c);
}

void CPU::opcode_CB_52() {
    opcode_bit(2, d);
}

void CPU::opcode_CB_53() {
    opcode_bit(2, e);
}

void CPU::opcode_CB_54() {
    opcode_bit(2, h);
}

void CPU::opcode_CB_55() {
    opcode_bit(2, l);
}

void CPU::opcode_CB_56() {
    opcode_bit(2, Address(hl));
}

void CPU::opcode_CB_57() {
    opcode_bit(2, a);
}

void CPU::opcode_CB_58() {
    opcode_bit(3, b);
}

void CPU::opcode_CB_59() {
    opcode_bit(3, c);
}

void CPU::opcode_CB_5A() {
    opcode_bit(3, d);
}

void CPU::opcode_CB_5B() {
    opcode_bit(3, e);
}

void CPU::opcode_CB_5C() {
    opcode_bit(3, h);
}

void CPU::opcode_CB_5D() {
    opcode_bit(3, l);
}

void CPU::opcode_CB_5E() {
    opcode_bit(3, Address(hl));
}

void CPU::opcode_CB_5F() {
    opcode_bit(3, a);
}

void CPU::opcode_CB_60() {
    opcode_bit(4, b);
}

void CPU::opcode_CB_61() {
    opcode_bit(4, c);
}

void CPU::opcode_CB_62() {
    opcode_bit(4, d);
}

void CPU::opcode_CB_63() {
    opcode_bit(4, e);
}

void CPU::opcode_CB_64() {
    opcode_bit(4, h);
}

void CPU::opcode_CB_65() {
    opcode_bit(4, l);
}

void CPU::opcode_CB_66() {
    opcode_bit(4, Address(hl));
}

void CPU::opcode_CB_67() {
    opcode_bit(4, a);
}

void CPU::opcode_CB_68() {
    opcode_bit(5, b);
}

void CPU::opcode_CB_69() {
    opcode_bit(5, c);
}

void CPU::opcode_CB_6A() {
    opcode_bit(5, d);
}

void CPU::opcode_CB_6B() {
    opcode_bit(5, e);
}

void CPU::opcode_CB_6C() {
    opcode_bit(5, h);
}

void CPU::opcode_CB_6D() {
    opcode_bit(5, l);
}

void CPU::opcode_CB_6E() {
    opcode_bit(5, Address(hl));
}

void CPU::opcode_CB_6F() {
    opcode_bit(5, a);
}

void CPU::opcode_CB_70() {
    opcode_bit(6, b);
}

void CPU::opcode_CB_71() {
    opcode_bit(6, c);
}

void CPU::opcode_CB_72() {
    opcode_bit(6, d);
}

void CPU::opcode_CB_73() {
    opcode_bit(6, e);
}

void CPU::opcode_CB_74() {
    opcode_bit(6, h);
}

void CPU::opcode_CB_75() {
    opcode_bit(6, l);
}

void CPU::opcode_CB_76() {
    opcode_bit(6, Address(hl));
}

void CPU::opcode_CB_77() {
    opcode_bit(6, a);
}

void CPU::opcode_CB_78() {
    opcode_bit(7, b);
}

void CPU::opcode_CB_79() {
    opcode_bit(7, c);
}

void CPU::opcode_CB_7A() {
    opcode_bit(7, d);
}

void CPU::opcode_CB_7B() {
    opcode_bit(7, e);
}

void CPU::opcode_CB_7C() {
    opcode_bit(7, h);
}

void CPU::opcode_CB_7D() {
    opcode_bit(7, l);
}

void CPU::opcode_CB_7E() {
    opcode_bit(7, Address(hl));
}

void CPU::opcode_CB_7F() {
    opcode_bit(7, a);
}

void CPU::opcode_CB_80() {
    opcode_res(0, b);
}

void CPU::opcode_CB_81() {
    opcode_res(0, c);
}

void CPU::opcode_CB_82() {
    opcode_res(0, d);
}

void CPU::opcode_CB_83() {
    opcode_res(0, e);
}

void CPU::opcode_CB_84() {
    opcode_res(0, h);
}

void CPU::opcode_CB_85() {
    opcode_res(0, l);
}

void CPU::opcode_CB_86() {
    opcode_res(0, Address(hl));
}

void CPU::opcode_CB_87() {
    opcode_res(0, a);
}

void CPU::opcode_CB_88() {
    opcode_res(1, b);
}

void CPU::opcode_CB_89() {
    opcode_res(1, c);
}

void CPU::opcode_CB_8A() {
    opcode_res(1, d);
}

void CPU::opcode_CB_8B() {
    opcode_res(1, e);
}

void CPU::opcode_CB_8C() {
    opcode_res(1, h);
}

void CPU::opcode_CB_8D() {
    opcode_res(1, l);
}

void CPU::opcode_CB_8E() {
    opcode_res(1, Address(hl));
}

void CPU::opcode_CB_8F() {
    opcode_res(1, a);
}

void CPU::opcode_CB_90() {
    opcode_res(2, b);
}

void CPU::opcode_CB_91() {
    opcode_res(2, c);
}

void CPU::opcode_CB_92() {
    opcode_res(2, d);
}

void CPU::opcode_CB_93() {
    opcode_res(2, e);
}

void CPU::opcode_CB_94() {
    opcode_res(2, h);
}

void CPU::opcode_CB_95() {
    opcode_res(2, l);
}

void CPU::opcode_CB_96() {
    opcode_res(2, Address(hl));
}

void CPU::opcode_CB_97() {
    opcode_res(2, a);
}

void CPU::opcode_CB_98() {
    opcode_res(3, b);
}

void CPU::opcode_CB_99() {
    opcode_res(3, c);
}

void CPU::opcode_CB_9A() {
    opcode_res(3, d);
}

void CPU::opcode_CB_9B() {
    opcode_res(3, e);
}

void CPU::opcode_CB_9C() {
    opcode_res(3, h);
}

void CPU::opcode_CB_9D() {
    opcode_res(3, l);
}

void CPU::opcode_CB_9E() {
    opcode_res(3, Address(hl));
}

void CPU::opcode_CB_9F() {
    opcode_res(3, a);
}

void CPU::opcode_CB_A0() {
    opcode_res(4, b);
}

void CPU::opcode_CB_A1() {
    opcode_res(4, c);
}

void CPU::opcode_CB_A2() {
    opcode_res(4, d);
}

void CPU::opcode_CB_A3() {
    opcode_res(4, e);
}

void CPU::opcode_CB_A4() {
    opcode_res(4, h);
}

void CPU::opcode_CB_A5() {
    opcode_res(4, l);
}

void CPU::opcode_CB_A6() {
    opcode_res(4, Address(hl));
}

void CPU::opcode_CB_A7() {
    opcode_res(4, a);
}

void CPU::opcode_CB_A8() {
    opcode_res(5, b);
}

void CPU::opcode_CB_A9() {
    opcode_res(5, c);
}

void CPU::opcode_CB_AA() {
    opcode_res(5, d);
}

void CPU::opcode_CB_AB() {
    opcode_res(5, e);
}

void CPU::opcode_CB_AC() {
    opcode_res(5, h);
}

void CPU::opcode_CB_AD() {
    opcode_res(5, l);
}

void CPU::opcode_CB_AE() {
    opcode_res(5, Address(hl));
}

void CPU::opcode_CB_AF() {
    opcode_res(5, a);
}

void CPU::opcode_CB_B0() {
    opcode_res(6, b);
}

void CPU::opcode_CB_B1() {
    opcode_res(6, c);
}

void CPU::opcode_CB_B2() {
    opcode_res(6, d);
}

void CPU::opcode_CB_B3() {
    opcode_res(6, e);
}

void CPU::opcode_CB_B4() {
    opcode_res(6, h);
}

void CPU::opcode_CB_B5() {
    opcode_res(6, l);
}

void CPU::opcode_CB_B6() {
    opcode_res(6, Address(hl));
}

void CPU::opcode_CB_B7() {
    opcode_res(6, a);
}

void CPU::opcode_CB_B8() {
    opcode_res(7, b);
}

void CPU::opcode_CB_B9() {
    opcode_res(7, c);
}

void CPU::opcode_CB_BA() {
    opcode_res(7, d);
}

void CPU::opcode_CB_BB() {
    opcode_res(7, e);
}

void CPU::opcode_CB_BC() {
    opcode_res(7, h);
}

void CPU::opcode_CB_BD() {
    opcode_res(7, l);
}

void CPU::opcode_CB_BE() {
    opcode_res(7, Address(hl));
}

void CPU::opcode_CB_BF() {
    opcode_res(7, a);
}

void CPU::opcode_CB_C0() {
    opcode_set(0, b);
}

void CPU::opcode_CB_C1() {
    opcode_set(0, c);
}

void CPU::opcode_CB_C2() {
    opcode_set(0, d);
}

void CPU::opcode_CB_C3() {
    opcode_set(0, e);
}

void CPU::opcode_CB_C4() {
    opcode_set(0, h);
}

void CPU::opcode_CB_C5() {
    opcode_set(0, l);
}

void CPU::opcode_CB_C6() {
    opcode_set(0, Address(hl));
}

void CPU::opcode_CB_C7() {
    opcode_set(0, a);
}

void CPU::opcode_CB_C8() {
    opcode_set(1, b);
}

void CPU::opcode_CB_C9() {
    opcode_set(1, c);
}

void CPU::opcode_CB_CA() {
    opcode_set(1, d);
}

void CPU::opcode_CB_CB() {
    opcode_set(1, e);
}

void CPU::opcode_CB_CC() {
    opcode_set(1, h);
}

void CPU::opcode_CB_CD() {
    opcode_set(1, l);
}

void CPU::opcode_CB_CE() {
    opcode_set(1, Address(hl));
}

void CPU::opcode_CB_CF() {
    opcode_set(1, a);
}

void CPU::opcode_CB_D0() {
    opcode_set(2, b);
}

void CPU::opcode_CB_D1() {
    opcode_set(2, c);
}

void CPU::opcode_CB_D2() {
    opcode_set(2, d);
}

void CPU::opcode_CB_D3() {
    opcode_set(2, e);
}

void CPU::opcode_CB_D4() {
    opcode_set(2, h);
}

void CPU::opcode_CB_D5() {
    opcode_set(2, l);
}

void CPU::opcode_CB_D6() {
    opcode_set(2, Address(hl));
}

void CPU::opcode_CB_D7() {
    opcode_set(2, a);
}

void CPU::opcode_CB_D8() {
    opcode_set(3, b);
}

void CPU::opcode_CB_D9() {
    opcode_set(3, c);
}

void CPU::opcode_CB_DA() {
    opcode_set(3, d);
}

void CPU::opcode_CB_DB() {
    opcode_set(3, e);
}

void CPU::opcode_CB_DC() {
    opcode_set(3, h);
}

void CPU::opcode_CB_DD() {
    opcode_set(3, l);
}

void CPU::opcode_CB_DE() {
    opcode_set(3, Address(hl));
}

void CPU::opcode_CB_DF() {
    opcode_set(3, a);
}

void CPU::opcode_CB_E0() {
    opcode_set(4, b);
}

void CPU::opcode_CB_E1() {
    opcode_set(4, c);
}

void CPU::opcode_CB_E2() {
    opcode_set(4, d);
}

void CPU::opcode_CB_E3() {
    opcode_set(4, e);
}

void CPU::opcode_CB_E4() {
    opcode_set(4, h);
}

void CPU::opcode_CB_E5() {
    opcode_set(4, l);
}

void CPU::opcode_CB_E6() {
    opcode_set(4, Address(hl));
}

void CPU::opcode_CB_E7() {
    opcode_set(4, a);
}

void CPU::opcode_CB_E8() {
    opcode_set(5, b);
}

void CPU::opcode_CB_E9() {
    opcode_set(5, c);
}

void CPU::opcode_CB_EA() {
    opcode_set(5, d);
}

void CPU::opcode_CB_EB() {
    opcode_set(5, e);
}

void CPU::opcode_CB_EC() {
    opcode_set(5, h);
}

void CPU::opcode_CB_ED() {
    opcode_set(5, l);
}

void CPU::opcode_CB_EE() {
    opcode_set(5, Address(hl));
}

void CPU::opcode_CB_EF() {
    opcode_set(5, a);
}

void CPU::opcode_CB_F0() {
    opcode_set(6, b);
}

void CPU::opcode_CB_F1() {
    opcode_set(6, c);
}

void CPU::opcode_CB_F2() {
    opcode_set(6, d);
}

void CPU::opcode_CB_F3() {
    opcode_set(6, e);
}

void CPU::opcode_CB_F4() {
    opcode_set(6, h);
}

void CPU::opcode_CB_F5() {
    opcode_set(6, l);
}

void CPU::opcode_CB_F6() {
    opcode_set(6, Address(hl));
}

void CPU::opcode_CB_F7() {
    opcode_set(6, a);
}

void CPU::opcode_CB_F8() {
    opcode_set(7, b);
}

void CPU::opcode_CB_F9() {
    opcode_set(7, c);
}

void CPU::opcode_CB_FA() {
    opcode_set(7, d);
}

void CPU::opcode_CB_FB() {
    opcode_set(7, e);
}

void CPU::opcode_CB_FC() {
    opcode_set(7, h);
}

void CPU::opcode_CB_FD() {
    opcode_set(7, l);
}

void CPU::opcode_CB_FE() {
    opcode_set(7, Address(hl));
}

void CPU::opcode_CB_FF() {
    opcode_set(7, a);
}
