#include "cpu.h"
#include "bitwise.h"

void CPU::execute_opcode(const uint8_t opcode) {
    switch (opcode) {
        case 0x00: opcode_00(); break;
        case 0x01: opcode_01(); break;
        case 0x02: opcode_02(); break;
        case 0x03: opcode_03(); break;
        case 0x04: opcode_04(); break;
        case 0x05: opcode_05(); break;
        case 0x06: opcode_06(); break;
        case 0x07: opcode_07(); break;
        case 0x08: opcode_08(); break;
        case 0x09: opcode_09(); break;
        case 0x0A: opcode_0A(); break;
        case 0x0B: opcode_0B(); break;
        case 0x0C: opcode_0C(); break;
        case 0x0D: opcode_0D(); break;
        case 0x0E: opcode_0E(); break;
        case 0x0F: opcode_0F(); break;
        case 0x10: opcode_10(); break;
        case 0x11: opcode_11(); break;
        case 0x12: opcode_12(); break;
        case 0x13: opcode_13(); break;
        case 0x14: opcode_14(); break;
        case 0x15: opcode_15(); break;
        case 0x16: opcode_16(); break;
        case 0x17: opcode_17(); break;
        case 0x18: opcode_18(); break;
        case 0x19: opcode_19(); break;
        case 0x1A: opcode_1A(); break;
        case 0x1B: opcode_1B(); break;
        case 0x1C: opcode_1C(); break;
        case 0x1D: opcode_1D(); break;
        case 0x1E: opcode_1E(); break;
        case 0x1F: opcode_1F(); break;
        case 0x20: opcode_20(); break;
        case 0x21: opcode_21(); break;
        case 0x22: opcode_22(); break;
        case 0x23: opcode_23(); break;
        case 0x24: opcode_24(); break;
        case 0x25: opcode_25(); break;
        case 0x26: opcode_26(); break;
        case 0x27: opcode_27(); break;
        case 0x28: opcode_28(); break;
        case 0x29: opcode_29(); break;
        case 0x2A: opcode_2A(); break;
        case 0x2B: opcode_2B(); break;
        case 0x2C: opcode_2C(); break;
        case 0x2D: opcode_2D(); break;
        case 0x2E: opcode_2E(); break;
        case 0x2F: opcode_2F(); break;
        case 0x30: opcode_30(); break;
        case 0x31: opcode_31(); break;
        case 0x32: opcode_32(); break;
        case 0x33: opcode_33(); break;
        case 0x34: opcode_34(); break;
        case 0x35: opcode_35(); break;
        case 0x36: opcode_36(); break;
        case 0x37: opcode_37(); break;
        case 0x38: opcode_38(); break;
        case 0x39: opcode_39(); break;
        case 0x3A: opcode_3A(); break;
        case 0x3B: opcode_3B(); break;
        case 0x3C: opcode_3C(); break;
        case 0x3D: opcode_3D(); break;
        case 0x3E: opcode_3E(); break;
        case 0x3F: opcode_3F(); break;
        case 0x40: opcode_40(); break;
        case 0x41: opcode_41(); break;
        case 0x42: opcode_42(); break;
        case 0x43: opcode_43(); break;
        case 0x44: opcode_44(); break;
        case 0x45: opcode_45(); break;
        case 0x46: opcode_46(); break;
        case 0x47: opcode_47(); break;
        case 0x48: opcode_48(); break;
        case 0x49: opcode_49(); break;
        case 0x4A: opcode_4A(); break;
        case 0x4B: opcode_4B(); break;
        case 0x4C: opcode_4C(); break;
        case 0x4D: opcode_4D(); break;
        case 0x4E: opcode_4E(); break;
        case 0x4F: opcode_4F(); break;
        case 0x50: opcode_50(); break;
        case 0x51: opcode_51(); break;
        case 0x52: opcode_52(); break;
        case 0x53: opcode_53(); break;
        case 0x54: opcode_54(); break;
        case 0x55: opcode_55(); break;
        case 0x56: opcode_56(); break;
        case 0x57: opcode_57(); break;
        case 0x58: opcode_58(); break;
        case 0x59: opcode_59(); break;
        case 0x5A: opcode_5A(); break;
        case 0x5B: opcode_5B(); break;
        case 0x5C: opcode_5C(); break;
        case 0x5D: opcode_5D(); break;
        case 0x5E: opcode_5E(); break;
        case 0x5F: opcode_5F(); break;
        case 0x60: opcode_60(); break;
        case 0x61: opcode_61(); break;
        case 0x62: opcode_62(); break;
        case 0x63: opcode_63(); break;
        case 0x64: opcode_64(); break;
        case 0x65: opcode_65(); break;
        case 0x66: opcode_66(); break;
        case 0x67: opcode_67(); break;
        case 0x68: opcode_68(); break;
        case 0x69: opcode_69(); break;
        case 0x6A: opcode_6A(); break;
        case 0x6B: opcode_6B(); break;
        case 0x6C: opcode_6C(); break;
        case 0x6D: opcode_6D(); break;
        case 0x6E: opcode_6E(); break;
        case 0x6F: opcode_6F(); break;
        case 0x70: opcode_70(); break;
        case 0x71: opcode_71(); break;
        case 0x72: opcode_72(); break;
        case 0x73: opcode_73(); break;
        case 0x74: opcode_74(); break;
        case 0x75: opcode_75(); break;
        case 0x76: opcode_76(); break;
        case 0x77: opcode_77(); break;
        case 0x78: opcode_78(); break;
        case 0x79: opcode_79(); break;
        case 0x7A: opcode_7A(); break;
        case 0x7B: opcode_7B(); break;
        case 0x7C: opcode_7C(); break;
        case 0x7D: opcode_7D(); break;
        case 0x7E: opcode_7E(); break;
        case 0x7F: opcode_7F(); break;
        case 0x80: opcode_80(); break;
        case 0x81: opcode_81(); break;
        case 0x82: opcode_82(); break;
        case 0x83: opcode_83(); break;
        case 0x84: opcode_84(); break;
        case 0x85: opcode_85(); break;
        case 0x86: opcode_86(); break;
        case 0x87: opcode_87(); break;
        case 0x88: opcode_88(); break;
        case 0x89: opcode_89(); break;
        case 0x8A: opcode_8A(); break;
        case 0x8B: opcode_8B(); break;
        case 0x8C: opcode_8C(); break;
        case 0x8D: opcode_8D(); break;
        case 0x8E: opcode_8E(); break;
        case 0x8F: opcode_8F(); break;
        case 0x90: opcode_90(); break;
        case 0x91: opcode_91(); break;
        case 0x92: opcode_92(); break;
        case 0x93: opcode_93(); break;
        case 0x94: opcode_94(); break;
        case 0x95: opcode_95(); break;
        case 0x96: opcode_96(); break;
        case 0x97: opcode_97(); break;
        case 0x98: opcode_98(); break;
        case 0x99: opcode_99(); break;
        case 0x9A: opcode_9A(); break;
        case 0x9B: opcode_9B(); break;
        case 0x9C: opcode_9C(); break;
        case 0x9D: opcode_9D(); break;
        case 0x9E: opcode_9E(); break;
        case 0x9F: opcode_9F(); break;
        case 0xA0: opcode_A0(); break;
        case 0xA1: opcode_A1(); break;
        case 0xA2: opcode_A2(); break;
        case 0xA3: opcode_A3(); break;
        case 0xA4: opcode_A4(); break;
        case 0xA5: opcode_A5(); break;
        case 0xA6: opcode_A6(); break;
        case 0xA7: opcode_A7(); break;
        case 0xA8: opcode_A8(); break;
        case 0xA9: opcode_A9(); break;
        case 0xAA: opcode_AA(); break;
        case 0xAB: opcode_AB(); break;
        case 0xAC: opcode_AC(); break;
        case 0xAD: opcode_AD(); break;
        case 0xAE: opcode_AE(); break;
        case 0xAF: opcode_AF(); break;
        case 0xB0: opcode_B0(); break;
        case 0xB1: opcode_B1(); break;
        case 0xB2: opcode_B2(); break;
        case 0xB3: opcode_B3(); break;
        case 0xB4: opcode_B4(); break;
        case 0xB5: opcode_B5(); break;
        case 0xB6: opcode_B6(); break;
        case 0xB7: opcode_B7(); break;
        case 0xB8: opcode_B8(); break;
        case 0xB9: opcode_B9(); break;
        case 0xBA: opcode_BA(); break;
        case 0xBB: opcode_BB(); break;
        case 0xBC: opcode_BC(); break;
        case 0xBD: opcode_BD(); break;
        case 0xBE: opcode_BE(); break;
        case 0xBF: opcode_BF(); break;
        case 0xC0: opcode_C0(); break;
        case 0xC1: opcode_C1(); break;
        case 0xC2: opcode_C2(); break;
        case 0xC3: opcode_C3(); break;
        case 0xC4: opcode_C4(); break;
        case 0xC5: opcode_C5(); break;
        case 0xC6: opcode_C6(); break;
        case 0xC7: opcode_C7(); break;
        case 0xC8: opcode_C8(); break;
        case 0xC9: opcode_C9(); break;
        case 0xCA: opcode_CA(); break;
        case 0xCB: opcode_CB(); break;
        case 0xCC: opcode_CC(); break;
        case 0xCD: opcode_CD(); break;
        case 0xCE: opcode_CE(); break;
        case 0xCF: opcode_CF(); break;
        case 0xD0: opcode_D0(); break;
        case 0xD1: opcode_D1(); break;
        case 0xD2: opcode_D2(); break;
        case 0xD3: opcode_D3(); break;
        case 0xD4: opcode_D4(); break;
        case 0xD5: opcode_D5(); break;
        case 0xD6: opcode_D6(); break;
        case 0xD7: opcode_D7(); break;
        case 0xD8: opcode_D8(); break;
        case 0xD9: opcode_D9(); break;
        case 0xDA: opcode_DA(); break;
        case 0xDB: opcode_DB(); break;
        case 0xDC: opcode_DC(); break;
        case 0xDD: opcode_DD(); break;
        case 0xDE: opcode_DE(); break;
        case 0xDF: opcode_DF(); break;
        case 0xE0: opcode_E0(); break;
        case 0xE1: opcode_E1(); break;
        case 0xE2: opcode_E2(); break;
        case 0xE3: opcode_E3(); break;
        case 0xE4: opcode_E4(); break;
        case 0xE5: opcode_E5(); break;
        case 0xE6: opcode_E6(); break;
        case 0xE7: opcode_E7(); break;
        case 0xE8: opcode_E8(); break;
        case 0xE9: opcode_E9(); break;
        case 0xEA: opcode_EA(); break;
        case 0xEB: opcode_EB(); break;
        case 0xEC: opcode_EC(); break;
        case 0xED: opcode_ED(); break;
        case 0xEE: opcode_EE(); break;
        case 0xEF: opcode_EF(); break;
        case 0xF0: opcode_F0(); break;
        case 0xF1: opcode_F1(); break;
        case 0xF2: opcode_F2(); break;
        case 0xF3: opcode_F3(); break;
        case 0xF4: opcode_F4(); break;
        case 0xF5: opcode_F5(); break;
        case 0xF6: opcode_F6(); break;
        case 0xF7: opcode_F7(); break;
        case 0xF8: opcode_F8(); break;
        case 0xF9: opcode_F9(); break;
        case 0xFA: opcode_FA(); break;
        case 0xFB: opcode_FB(); break;
        case 0xFC: opcode_FC(); break;
        case 0xFD: opcode_FD(); break;
        case 0xFE: opcode_FE(); break;
        case 0xFF: opcode_FF(); break;
    }
}

inline uint8_t CPU::get_byte_from_pc() {
    uint8_t byte = mmu.read_byte(Address(pc));
    pc.increment();

    return byte;
}

inline uint16_t CPU::get_word_from_pc() {
    uint8_t high_byte = get_byte_from_pc();
    uint8_t low_byte = get_byte_from_pc();

    return compose_bytes(low_byte, high_byte);
}

inline void CPU::opcode_ld(ByteRegister &reg) {
    uint8_t n = get_byte_from_pc();
    reg.set(n);
}

inline void CPU::opcode_ld(ByteRegister &reg, const uint8_t value) {
    reg.set(value);
}

inline void CPU::opcode_ld(ByteRegister &reg, const ByteRegister &byte_reg) {
    reg.set(byte_reg.value());
}

inline void CPU::opcode_ld(ByteRegister &reg, const Address &address) {
    reg.set(mmu.read_byte(address));
}

inline void CPU::opcode_ld(WordRegister &reg) {
    uint16_t nn = get_word_from_pc();
    reg.set(nn);
}

inline void CPU::opcode_ld(WordRegister &reg, const uint16_t value) {
    reg.set(value);
}

inline void CPU::opcode_ld(RegisterPair &reg) {
    uint16_t nn = get_word_from_pc();
    reg.set(nn);
}

inline void CPU::opcode_ld(RegisterPair &reg, const uint16_t value) {
    reg.set(value);
}

inline void CPU::opcode_ld(const Address &address) {
    uint8_t n = get_byte_from_pc();
    mmu.write_byte(address, n);
}

inline void CPU::opcode_ld(const Address &address, const uint8_t value) {
    mmu.write_byte(address, value);
}

inline void CPU::opcode_ld(const Address &address, const uint16_t value) {
    mmu.write_word(address, value);
}

inline void CPU::opcode_ld(const Address &address, const ByteRegister &byte_reg) {
    mmu.write_byte(address, byte_reg.value());
}

inline void CPU::opcode_ld(const Address &address, const WordRegister &word_reg) {
    mmu.write_word(address, word_reg.value());
}

inline void CPU::opcode_inc(const Address &address) {
    uint8_t n = mmu.read_byte(address);
    n += 1;
    mmu.write_byte(address, n);
}

inline void CPU::opcode_dec(const Address &address) {
    uint8_t n = mmu.read_byte(address);
    n -= 1;
    mmu.write_byte(address, n);

}

void CPU::opcode_00() {
    /* NOP */
}

void CPU::opcode_01() {
    opcode_ld(bc);
}

void CPU::opcode_02() {
    opcode_ld(Address(bc), a);
}

void CPU::opcode_03() {
    bc.increment();
}

void CPU::opcode_04() {
    b.increment();
}

void CPU::opcode_05() {
    b.decrement();
}

void CPU::opcode_06() {
    opcode_ld(b);
}

void CPU::opcode_07() {
    /* TODO */
}

void CPU::opcode_08() {
    uint16_t nn = get_word_from_pc();
    opcode_ld(Address(nn), sp);
}

void CPU::opcode_09() {
    /* TODO */
}

void CPU::opcode_0A() {
    opcode_ld(a, Address(bc));
}

void CPU::opcode_0B() {
    bc.decrement();
}

void CPU::opcode_0C() {
    c.increment();
}

void CPU::opcode_0D() {
    c.decrement();
}

void CPU::opcode_0E() {
    opcode_ld(c);
}

void CPU::opcode_0F() {
    /* TODO */
}

void CPU::opcode_10() {
    /* TODO */
}

void CPU::opcode_11() {
    opcode_ld(de);
}

void CPU::opcode_12() {
    opcode_ld(Address(de), a);
}

void CPU::opcode_13() {
    de.increment();
}

void CPU::opcode_14() {
    d.increment();
}

void CPU::opcode_15() {
    d.decrement();
}

void CPU::opcode_16() {
    opcode_ld(d);
}

void CPU::opcode_17() {
    /* TODO */
}

void CPU::opcode_18() {
    /* TODO */
}

void CPU::opcode_19() {
    /* TODO */
}

void CPU::opcode_1A() {
    opcode_ld(a, Address(de));
}

void CPU::opcode_1B() {
    de.decrement();
}

void CPU::opcode_1C() {
    e.increment();
}

void CPU::opcode_1D() {
    e.decrement();
}

void CPU::opcode_1E() {
    opcode_ld(e);
}

void CPU::opcode_1F() {
    /* TODO */
}

void CPU::opcode_20() {
    /* TODO */
}

void CPU::opcode_21() {
    opcode_ld(hl);
}

void CPU::opcode_22() {
    /* TODO */
}

void CPU::opcode_23() {
    hl.increment();
}

void CPU::opcode_24() {
    h.increment();
}

void CPU::opcode_25() {
    h.decrement();
}

void CPU::opcode_26() {
    opcode_ld(h);
}

void CPU::opcode_27() {
    /* TODO */
}

void CPU::opcode_28() {
    /* TODO */
}

void CPU::opcode_29() {
    /* TODO */
}

void CPU::opcode_2A() {
    /* TODO */
}

void CPU::opcode_2B() {
    hl.decrement();
}

void CPU::opcode_2C() {
    l.increment();
}

void CPU::opcode_2D() {
    l.decrement();
}

void CPU::opcode_2E() {
    opcode_ld(l);
}

void CPU::opcode_2F() {
    /* TODO */
}

void CPU::opcode_30() {
    /* TODO */
}

void CPU::opcode_31() {
    opcode_ld(sp);
}

void CPU::opcode_32() {
    /* TODO */
}

void CPU::opcode_33() {
    sp.increment();
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
    /* TODO */
}

void CPU::opcode_38() {
    /* TODO */
}

void CPU::opcode_39() {
    /* TODO */
}

void CPU::opcode_3A() {
    /* TODO */
}

void CPU::opcode_3B() {
    sp.decrement();
}

void CPU::opcode_3C() {
    a.increment();
}

void CPU::opcode_3D() {
    a.decrement();
}

void CPU::opcode_3E() {
    opcode_ld(a);
}

void CPU::opcode_3F() {
    /* TODO */
}

void CPU::opcode_40() {
    /* TODO */
}

void CPU::opcode_41() {
    /* TODO */
}

void CPU::opcode_42() {
    /* TODO */
}

void CPU::opcode_43() {
    /* TODO */
}

void CPU::opcode_44() {
    /* TODO */
}

void CPU::opcode_45() {
    /* TODO */
}

void CPU::opcode_46() {
    /* TODO */
}

void CPU::opcode_47() {
    /* TODO */
}

void CPU::opcode_48() {
    /* TODO */
}

void CPU::opcode_49() {
    /* TODO */
}

void CPU::opcode_4A() {
    /* TODO */
}

void CPU::opcode_4B() {
    /* TODO */
}

void CPU::opcode_4C() {
    /* TODO */
}

void CPU::opcode_4D() {
    /* TODO */
}

void CPU::opcode_4E() {
    /* TODO */
}

void CPU::opcode_4F() {
    /* TODO */
}

void CPU::opcode_50() {
    /* TODO */
}

void CPU::opcode_51() {
    /* TODO */
}

void CPU::opcode_52() {
    /* TODO */
}

void CPU::opcode_53() {
    /* TODO */
}

void CPU::opcode_54() {
    /* TODO */
}

void CPU::opcode_55() {
    /* TODO */
}

void CPU::opcode_56() {
    /* TODO */
}

void CPU::opcode_57() {
    /* TODO */
}

void CPU::opcode_58() {
    /* TODO */
}

void CPU::opcode_59() {
    /* TODO */
}

void CPU::opcode_5A() {
    /* TODO */
}

void CPU::opcode_5B() {
    /* TODO */
}

void CPU::opcode_5C() {
    /* TODO */
}

void CPU::opcode_5D() {
    /* TODO */
}

void CPU::opcode_5E() {
    /* TODO */
}

void CPU::opcode_5F() {
    /* TODO */
}

void CPU::opcode_60() {
    /* TODO */
}

void CPU::opcode_61() {
    /* TODO */
}

void CPU::opcode_62() {
    /* TODO */
}

void CPU::opcode_63() {
    /* TODO */
}

void CPU::opcode_64() {
    /* TODO */
}

void CPU::opcode_65() {
    /* TODO */
}

void CPU::opcode_66() {
    /* TODO */
}

void CPU::opcode_67() {
    /* TODO */
}

void CPU::opcode_68() {
    /* TODO */
}

void CPU::opcode_69() {
    /* TODO */
}

void CPU::opcode_6A() {
    /* TODO */
}

void CPU::opcode_6B() {
    /* TODO */
}

void CPU::opcode_6C() {
    /* TODO */
}

void CPU::opcode_6D() {
    /* TODO */
}

void CPU::opcode_6E() {
    /* TODO */
}

void CPU::opcode_6F() {
    /* TODO */
}

void CPU::opcode_70() {
    /* TODO */
}

void CPU::opcode_71() {
    /* TODO */
}

void CPU::opcode_72() {
    /* TODO */
}

void CPU::opcode_73() {
    /* TODO */
}

void CPU::opcode_74() {
    /* TODO */
}

void CPU::opcode_75() {
    /* TODO */
}

void CPU::opcode_76() {
    /* TODO */
}

void CPU::opcode_77() {
    /* TODO */
}

void CPU::opcode_78() {
    /* TODO */
}

void CPU::opcode_79() {
    /* TODO */
}

void CPU::opcode_7A() {
    /* TODO */
}

void CPU::opcode_7B() {
    /* TODO */
}

void CPU::opcode_7C() {
    /* TODO */
}

void CPU::opcode_7D() {
    /* TODO */
}

void CPU::opcode_7E() {
    /* TODO */
}

void CPU::opcode_7F() {
    /* TODO */
}

void CPU::opcode_80() {
    /* TODO */
}

void CPU::opcode_81() {
    /* TODO */
}

void CPU::opcode_82() {
    /* TODO */
}

void CPU::opcode_83() {
    /* TODO */
}

void CPU::opcode_84() {
    /* TODO */
}

void CPU::opcode_85() {
    /* TODO */
}

void CPU::opcode_86() {
    /* TODO */
}

void CPU::opcode_87() {
    /* TODO */
}

void CPU::opcode_88() {
    /* TODO */
}

void CPU::opcode_89() {
    /* TODO */
}

void CPU::opcode_8A() {
    /* TODO */
}

void CPU::opcode_8B() {
    /* TODO */
}

void CPU::opcode_8C() {
    /* TODO */
}

void CPU::opcode_8D() {
    /* TODO */
}

void CPU::opcode_8E() {
    /* TODO */
}

void CPU::opcode_8F() {
    /* TODO */
}

void CPU::opcode_90() {
    /* TODO */
}

void CPU::opcode_91() {
    /* TODO */
}

void CPU::opcode_92() {
    /* TODO */
}

void CPU::opcode_93() {
    /* TODO */
}

void CPU::opcode_94() {
    /* TODO */
}

void CPU::opcode_95() {
    /* TODO */
}

void CPU::opcode_96() {
    /* TODO */
}

void CPU::opcode_97() {
    /* TODO */
}

void CPU::opcode_98() {
    /* TODO */
}

void CPU::opcode_99() {
    /* TODO */
}

void CPU::opcode_9A() {
    /* TODO */
}

void CPU::opcode_9B() {
    /* TODO */
}

void CPU::opcode_9C() {
    /* TODO */
}

void CPU::opcode_9D() {
    /* TODO */
}

void CPU::opcode_9E() {
    /* TODO */
}

void CPU::opcode_9F() {
    /* TODO */
}

void CPU::opcode_A0() {
    /* TODO */
}

void CPU::opcode_A1() {
    /* TODO */
}

void CPU::opcode_A2() {
    /* TODO */
}

void CPU::opcode_A3() {
    /* TODO */
}

void CPU::opcode_A4() {
    /* TODO */
}

void CPU::opcode_A5() {
    /* TODO */
}

void CPU::opcode_A6() {
    /* TODO */
}

void CPU::opcode_A7() {
    /* TODO */
}

void CPU::opcode_A8() {
    /* TODO */
}

void CPU::opcode_A9() {
    /* TODO */
}

void CPU::opcode_AA() {
    /* TODO */
}

void CPU::opcode_AB() {
    /* TODO */
}

void CPU::opcode_AC() {
    /* TODO */
}

void CPU::opcode_AD() {
    /* TODO */
}

void CPU::opcode_AE() {
    /* TODO */
}

void CPU::opcode_AF() {
    /* TODO */
}

void CPU::opcode_B0() {
    /* TODO */
}

void CPU::opcode_B1() {
    /* TODO */
}

void CPU::opcode_B2() {
    /* TODO */
}

void CPU::opcode_B3() {
    /* TODO */
}

void CPU::opcode_B4() {
    /* TODO */
}

void CPU::opcode_B5() {
    /* TODO */
}

void CPU::opcode_B6() {
    /* TODO */
}

void CPU::opcode_B7() {
    /* TODO */
}

void CPU::opcode_B8() {
    /* TODO */
}

void CPU::opcode_B9() {
    /* TODO */
}

void CPU::opcode_BA() {
    /* TODO */
}

void CPU::opcode_BB() {
    /* TODO */
}

void CPU::opcode_BC() {
    /* TODO */
}

void CPU::opcode_BD() {
    /* TODO */
}

void CPU::opcode_BE() {
    /* TODO */
}

void CPU::opcode_BF() {
    /* TODO */
}

void CPU::opcode_C0() {
    /* TODO */
}

void CPU::opcode_C1() {
    /* TODO */
}

void CPU::opcode_C2() {
    /* TODO */
}

void CPU::opcode_C3() {
    /* TODO */
}

void CPU::opcode_C4() {
    /* TODO */
}

void CPU::opcode_C5() {
    /* TODO */
}

void CPU::opcode_C6() {
    /* TODO */
}

void CPU::opcode_C7() {
    /* TODO */
}

void CPU::opcode_C8() {
    /* TODO */
}

void CPU::opcode_C9() {
    /* TODO */
}

void CPU::opcode_CA() {
    /* TODO */
}

void CPU::opcode_CB() {
    /* TODO */
}

void CPU::opcode_CC() {
    /* TODO */
}

void CPU::opcode_CD() {
    /* TODO */
}

void CPU::opcode_CE() {
    /* TODO */
}

void CPU::opcode_CF() {
    /* TODO */
}

void CPU::opcode_D0() {
    /* TODO */
}

void CPU::opcode_D1() {
    /* TODO */
}

void CPU::opcode_D2() {
    /* TODO */
}

void CPU::opcode_D3() {
    /* TODO */
}

void CPU::opcode_D4() {
    /* TODO */
}

void CPU::opcode_D5() {
    /* TODO */
}

void CPU::opcode_D6() {
    /* TODO */
}

void CPU::opcode_D7() {
    /* TODO */
}

void CPU::opcode_D8() {
    /* TODO */
}

void CPU::opcode_D9() {
    /* TODO */
}

void CPU::opcode_DA() {
    /* TODO */
}

void CPU::opcode_DB() {
    /* TODO */
}

void CPU::opcode_DC() {
    /* TODO */
}

void CPU::opcode_DD() {
    /* TODO */
}

void CPU::opcode_DE() {
    /* TODO */
}

void CPU::opcode_DF() {
    /* TODO */
}

void CPU::opcode_E0() {
    /* TODO */
}

void CPU::opcode_E1() {
    /* TODO */
}

void CPU::opcode_E2() {
    /* TODO */
}

void CPU::opcode_E3() {
    /* TODO */
}

void CPU::opcode_E4() {
    /* TODO */
}

void CPU::opcode_E5() {
    /* TODO */
}

void CPU::opcode_E6() {
    /* TODO */
}

void CPU::opcode_E7() {
    /* TODO */
}

void CPU::opcode_E8() {
    /* TODO */
}

void CPU::opcode_E9() {
    /* TODO */
}

void CPU::opcode_EA() {
    /* TODO */
}

void CPU::opcode_EB() {
    /* TODO */
}

void CPU::opcode_EC() {
    /* TODO */
}

void CPU::opcode_ED() {
    /* TODO */
}

void CPU::opcode_EE() {
    /* TODO */
}

void CPU::opcode_EF() {
    /* TODO */
}

void CPU::opcode_F0() {
    /* TODO */
}

void CPU::opcode_F1() {
    /* TODO */
}

void CPU::opcode_F2() {
    /* TODO */
}

void CPU::opcode_F3() {
    /* TODO */
}

void CPU::opcode_F4() {
    /* TODO */
}

void CPU::opcode_F5() {
    /* TODO */
}

void CPU::opcode_F6() {
    /* TODO */
}

void CPU::opcode_F7() {
    /* TODO */
}

void CPU::opcode_F8() {
    /* TODO */
}

void CPU::opcode_F9() {
    /* TODO */
}

void CPU::opcode_FA() {
    /* TODO */
}

void CPU::opcode_FB() {
    /* TODO */
}

void CPU::opcode_FC() {
    /* TODO */
}

void CPU::opcode_FD() {
    /* TODO */
}

void CPU::opcode_FE() {
    /* TODO */
}

void CPU::opcode_FF() {
    /* TODO */
}

