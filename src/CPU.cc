#include "CPU.h"

void CPU::execute_opcode(const uint8_t opcode) {
    switch (opcode) {
        case 0x00:
            opcode_00();
        case 0x01:
            opcode_01();
        case 0x02:
            opcode_02();
        case 0x03:
            opcode_03();
        case 0x04:
            opcode_04();
        case 0x05:
            opcode_05();
        case 0x06:
            opcode_06();
        case 0x07:
            opcode_07();
        case 0x08:
            opcode_08();
        case 0x09:
            opcode_09();
        case 0x0A:
            opcode_0A();
        case 0x0B:
            opcode_0B();
        case 0x0C:
            opcode_0C();
        case 0x0D:
            opcode_0D();
        case 0x0E:
            opcode_0E();
        case 0x0F:
            opcode_0F();
        case 0x10:
            opcode_10();
        case 0x11:
            opcode_11();
        case 0x12:
            opcode_12();
        case 0x13:
            opcode_13();
        case 0x14:
            opcode_14();
        case 0x15:
            opcode_15();
        case 0x16:
            opcode_16();
        case 0x17:
            opcode_17();
        case 0x18:
            opcode_18();
        case 0x19:
            opcode_19();
        case 0x1A:
            opcode_1A();
        case 0x1B:
            opcode_1B();
        case 0x1C:
            opcode_1C();
        case 0x1D:
            opcode_1D();
        case 0x1E:
            opcode_1E();
        case 0x1F:
            opcode_1F();
        case 0x20:
            opcode_20();
        case 0x21:
            opcode_21();
        case 0x22:
            opcode_22();
        case 0x23:
            opcode_23();
        case 0x24:
            opcode_24();
        case 0x25:
            opcode_25();
        case 0x26:
            opcode_26();
        case 0x27:
            opcode_27();
        case 0x28:
            opcode_28();
        case 0x29:
            opcode_29();
        case 0x2A:
            opcode_2A();
        case 0x2B:
            opcode_2B();
        case 0x2C:
            opcode_2C();
        case 0x2D:
            opcode_2D();
        case 0x2E:
            opcode_2E();
        case 0x2F:
            opcode_2F();
        case 0x30:
            opcode_30();
        case 0x31:
            opcode_31();
        case 0x32:
            opcode_32();
        case 0x33:
            opcode_33();
        case 0x34:
            opcode_34();
        case 0x35:
            opcode_35();
        case 0x36:
            opcode_36();
        case 0x37:
            opcode_37();
        case 0x38:
            opcode_38();
        case 0x39:
            opcode_39();
        case 0x3A:
            opcode_3A();
        case 0x3B:
            opcode_3B();
        case 0x3C:
            opcode_3C();
        case 0x3D:
            opcode_3D();
        case 0x3E:
            opcode_3E();
        case 0x3F:
            opcode_3F();
        case 0x40:
            opcode_40();
        case 0x41:
            opcode_41();
        case 0x42:
            opcode_42();
        case 0x43:
            opcode_43();
        case 0x44:
            opcode_44();
        case 0x45:
            opcode_45();
        case 0x46:
            opcode_46();
        case 0x47:
            opcode_47();
        case 0x48:
            opcode_48();
        case 0x49:
            opcode_49();
        case 0x4A:
            opcode_4A();
        case 0x4B:
            opcode_4B();
        case 0x4C:
            opcode_4C();
        case 0x4D:
            opcode_4D();
        case 0x4E:
            opcode_4E();
        case 0x4F:
            opcode_4F();
        case 0x50:
            opcode_50();
        case 0x51:
            opcode_51();
        case 0x52:
            opcode_52();
        case 0x53:
            opcode_53();
        case 0x54:
            opcode_54();
        case 0x55:
            opcode_55();
        case 0x56:
            opcode_56();
        case 0x57:
            opcode_57();
        case 0x58:
            opcode_58();
        case 0x59:
            opcode_59();
        case 0x5A:
            opcode_5A();
        case 0x5B:
            opcode_5B();
        case 0x5C:
            opcode_5C();
        case 0x5D:
            opcode_5D();
        case 0x5E:
            opcode_5E();
        case 0x5F:
            opcode_5F();
        case 0x60:
            opcode_60();
        case 0x61:
            opcode_61();
        case 0x62:
            opcode_62();
        case 0x63:
            opcode_63();
        case 0x64:
            opcode_64();
        case 0x65:
            opcode_65();
        case 0x66:
            opcode_66();
        case 0x67:
            opcode_67();
        case 0x68:
            opcode_68();
        case 0x69:
            opcode_69();
        case 0x6A:
            opcode_6A();
        case 0x6B:
            opcode_6B();
        case 0x6C:
            opcode_6C();
        case 0x6D:
            opcode_6D();
        case 0x6E:
            opcode_6E();
        case 0x6F:
            opcode_6F();
        case 0x70:
            opcode_70();
        case 0x71:
            opcode_71();
        case 0x72:
            opcode_72();
        case 0x73:
            opcode_73();
        case 0x74:
            opcode_74();
        case 0x75:
            opcode_75();
        case 0x76:
            opcode_76();
        case 0x77:
            opcode_77();
        case 0x78:
            opcode_78();
        case 0x79:
            opcode_79();
        case 0x7A:
            opcode_7A();
        case 0x7B:
            opcode_7B();
        case 0x7C:
            opcode_7C();
        case 0x7D:
            opcode_7D();
        case 0x7E:
            opcode_7E();
        case 0x7F:
            opcode_7F();
        case 0x80:
            opcode_80();
        case 0x81:
            opcode_81();
        case 0x82:
            opcode_82();
        case 0x83:
            opcode_83();
        case 0x84:
            opcode_84();
        case 0x85:
            opcode_85();
        case 0x86:
            opcode_86();
        case 0x87:
            opcode_87();
        case 0x88:
            opcode_88();
        case 0x89:
            opcode_89();
        case 0x8A:
            opcode_8A();
        case 0x8B:
            opcode_8B();
        case 0x8C:
            opcode_8C();
        case 0x8D:
            opcode_8D();
        case 0x8E:
            opcode_8E();
        case 0x8F:
            opcode_8F();
        case 0x90:
            opcode_90();
        case 0x91:
            opcode_91();
        case 0x92:
            opcode_92();
        case 0x93:
            opcode_93();
        case 0x94:
            opcode_94();
        case 0x95:
            opcode_95();
        case 0x96:
            opcode_96();
        case 0x97:
            opcode_97();
        case 0x98:
            opcode_98();
        case 0x99:
            opcode_99();
        case 0x9A:
            opcode_9A();
        case 0x9B:
            opcode_9B();
        case 0x9C:
            opcode_9C();
        case 0x9D:
            opcode_9D();
        case 0x9E:
            opcode_9E();
        case 0x9F:
            opcode_9F();
        case 0xA0:
            opcode_A0();
        case 0xA1:
            opcode_A1();
        case 0xA2:
            opcode_A2();
        case 0xA3:
            opcode_A3();
        case 0xA4:
            opcode_A4();
        case 0xA5:
            opcode_A5();
        case 0xA6:
            opcode_A6();
        case 0xA7:
            opcode_A7();
        case 0xA8:
            opcode_A8();
        case 0xA9:
            opcode_A9();
        case 0xAA:
            opcode_AA();
        case 0xAB:
            opcode_AB();
        case 0xAC:
            opcode_AC();
        case 0xAD:
            opcode_AD();
        case 0xAE:
            opcode_AE();
        case 0xAF:
            opcode_AF();
        case 0xB0:
            opcode_B0();
        case 0xB1:
            opcode_B1();
        case 0xB2:
            opcode_B2();
        case 0xB3:
            opcode_B3();
        case 0xB4:
            opcode_B4();
        case 0xB5:
            opcode_B5();
        case 0xB6:
            opcode_B6();
        case 0xB7:
            opcode_B7();
        case 0xB8:
            opcode_B8();
        case 0xB9:
            opcode_B9();
        case 0xBA:
            opcode_BA();
        case 0xBB:
            opcode_BB();
        case 0xBC:
            opcode_BC();
        case 0xBD:
            opcode_BD();
        case 0xBE:
            opcode_BE();
        case 0xBF:
            opcode_BF();
        case 0xC0:
            opcode_C0();
        case 0xC1:
            opcode_C1();
        case 0xC2:
            opcode_C2();
        case 0xC3:
            opcode_C3();
        case 0xC4:
            opcode_C4();
        case 0xC5:
            opcode_C5();
        case 0xC6:
            opcode_C6();
        case 0xC7:
            opcode_C7();
        case 0xC8:
            opcode_C8();
        case 0xC9:
            opcode_C9();
        case 0xCA:
            opcode_CA();
        case 0xCB:
            opcode_CB();
        case 0xCC:
            opcode_CC();
        case 0xCD:
            opcode_CD();
        case 0xCE:
            opcode_CE();
        case 0xCF:
            opcode_CF();
        case 0xD0:
            opcode_D0();
        case 0xD1:
            opcode_D1();
        case 0xD2:
            opcode_D2();
        case 0xD3:
            opcode_D3();
        case 0xD4:
            opcode_D4();
        case 0xD5:
            opcode_D5();
        case 0xD6:
            opcode_D6();
        case 0xD7:
            opcode_D7();
        case 0xD8:
            opcode_D8();
        case 0xD9:
            opcode_D9();
        case 0xDA:
            opcode_DA();
        case 0xDB:
            opcode_DB();
        case 0xDC:
            opcode_DC();
        case 0xDD:
            opcode_DD();
        case 0xDE:
            opcode_DE();
        case 0xDF:
            opcode_DF();
        case 0xE0:
            opcode_E0();
        case 0xE1:
            opcode_E1();
        case 0xE2:
            opcode_E2();
        case 0xE3:
            opcode_E3();
        case 0xE4:
            opcode_E4();
        case 0xE5:
            opcode_E5();
        case 0xE6:
            opcode_E6();
        case 0xE7:
            opcode_E7();
        case 0xE8:
            opcode_E8();
        case 0xE9:
            opcode_E9();
        case 0xEA:
            opcode_EA();
        case 0xEB:
            opcode_EB();
        case 0xEC:
            opcode_EC();
        case 0xED:
            opcode_ED();
        case 0xEE:
            opcode_EE();
        case 0xEF:
            opcode_EF();
        case 0xF0:
            opcode_F0();
        case 0xF1:
            opcode_F1();
        case 0xF2:
            opcode_F2();
        case 0xF3:
            opcode_F3();
        case 0xF4:
            opcode_F4();
        case 0xF5:
            opcode_F5();
        case 0xF6:
            opcode_F6();
        case 0xF7:
            opcode_F7();
        case 0xF8:
            opcode_F8();
        case 0xF9:
            opcode_F9();
        case 0xFA:
            opcode_FA();
        case 0xFB:
            opcode_FB();
        case 0xFC:
            opcode_FC();
        case 0xFD:
            opcode_FD();
        case 0xFE:
            opcode_FE();
        case 0xFF:
            opcode_FF();
    }
}

void CPU::opcode_00() {
}

void CPU::opcode_01() {
}

void CPU::opcode_02() {
}

void CPU::opcode_03() {
}

void CPU::opcode_04() {
}

void CPU::opcode_05() {
}

void CPU::opcode_06() {
}

void CPU::opcode_07() {
}

void CPU::opcode_08() {
}

void CPU::opcode_09() {
}

void CPU::opcode_0A() {
}

void CPU::opcode_0B() {
}

void CPU::opcode_0C() {
}

void CPU::opcode_0D() {
}

void CPU::opcode_0E() {
}

void CPU::opcode_0F() {
}

void CPU::opcode_10() {
}

void CPU::opcode_11() {
}

void CPU::opcode_12() {
}

void CPU::opcode_13() {
}

void CPU::opcode_14() {
}

void CPU::opcode_15() {
}

void CPU::opcode_16() {
}

void CPU::opcode_17() {
}

void CPU::opcode_18() {
}

void CPU::opcode_19() {
}

void CPU::opcode_1A() {
}

void CPU::opcode_1B() {
}

void CPU::opcode_1C() {
}

void CPU::opcode_1D() {
}

void CPU::opcode_1E() {
}

void CPU::opcode_1F() {
}

void CPU::opcode_20() {
}

void CPU::opcode_21() {
}

void CPU::opcode_22() {
}

void CPU::opcode_23() {
}

void CPU::opcode_24() {
}

void CPU::opcode_25() {
}

void CPU::opcode_26() {
}

void CPU::opcode_27() {
}

void CPU::opcode_28() {
}

void CPU::opcode_29() {
}

void CPU::opcode_2A() {
}

void CPU::opcode_2B() {
}

void CPU::opcode_2C() {
}

void CPU::opcode_2D() {
}

void CPU::opcode_2E() {
}

void CPU::opcode_2F() {
}

void CPU::opcode_30() {
}

void CPU::opcode_31() {
}

void CPU::opcode_32() {
}

void CPU::opcode_33() {
}

void CPU::opcode_34() {
}

void CPU::opcode_35() {
}

void CPU::opcode_36() {
}

void CPU::opcode_37() {
}

void CPU::opcode_38() {
}

void CPU::opcode_39() {
}

void CPU::opcode_3A() {
}

void CPU::opcode_3B() {
}

void CPU::opcode_3C() {
}

void CPU::opcode_3D() {
}

void CPU::opcode_3E() {
}

void CPU::opcode_3F() {
}

void CPU::opcode_40() {
}

void CPU::opcode_41() {
}

void CPU::opcode_42() {
}

void CPU::opcode_43() {
}

void CPU::opcode_44() {
}

void CPU::opcode_45() {
}

void CPU::opcode_46() {
}

void CPU::opcode_47() {
}

void CPU::opcode_48() {
}

void CPU::opcode_49() {
}

void CPU::opcode_4A() {
}

void CPU::opcode_4B() {
}

void CPU::opcode_4C() {
}

void CPU::opcode_4D() {
}

void CPU::opcode_4E() {
}

void CPU::opcode_4F() {
}

void CPU::opcode_50() {
}

void CPU::opcode_51() {
}

void CPU::opcode_52() {
}

void CPU::opcode_53() {
}

void CPU::opcode_54() {
}

void CPU::opcode_55() {
}

void CPU::opcode_56() {
}

void CPU::opcode_57() {
}

void CPU::opcode_58() {
}

void CPU::opcode_59() {
}

void CPU::opcode_5A() {
}

void CPU::opcode_5B() {
}

void CPU::opcode_5C() {
}

void CPU::opcode_5D() {
}

void CPU::opcode_5E() {
}

void CPU::opcode_5F() {
}

void CPU::opcode_60() {
}

void CPU::opcode_61() {
}

void CPU::opcode_62() {
}

void CPU::opcode_63() {
}

void CPU::opcode_64() {
}

void CPU::opcode_65() {
}

void CPU::opcode_66() {
}

void CPU::opcode_67() {
}

void CPU::opcode_68() {
}

void CPU::opcode_69() {
}

void CPU::opcode_6A() {
}

void CPU::opcode_6B() {
}

void CPU::opcode_6C() {
}

void CPU::opcode_6D() {
}

void CPU::opcode_6E() {
}

void CPU::opcode_6F() {
}

void CPU::opcode_70() {
}

void CPU::opcode_71() {
}

void CPU::opcode_72() {
}

void CPU::opcode_73() {
}

void CPU::opcode_74() {
}

void CPU::opcode_75() {
}

void CPU::opcode_76() {
}

void CPU::opcode_77() {
}

void CPU::opcode_78() {
}

void CPU::opcode_79() {
}

void CPU::opcode_7A() {
}

void CPU::opcode_7B() {
}

void CPU::opcode_7C() {
}

void CPU::opcode_7D() {
}

void CPU::opcode_7E() {
}

void CPU::opcode_7F() {
}

void CPU::opcode_80() {
}

void CPU::opcode_81() {
}

void CPU::opcode_82() {
}

void CPU::opcode_83() {
}

void CPU::opcode_84() {
}

void CPU::opcode_85() {
}

void CPU::opcode_86() {
}

void CPU::opcode_87() {
}

void CPU::opcode_88() {
}

void CPU::opcode_89() {
}

void CPU::opcode_8A() {
}

void CPU::opcode_8B() {
}

void CPU::opcode_8C() {
}

void CPU::opcode_8D() {
}

void CPU::opcode_8E() {
}

void CPU::opcode_8F() {
}

void CPU::opcode_90() {
}

void CPU::opcode_91() {
}

void CPU::opcode_92() {
}

void CPU::opcode_93() {
}

void CPU::opcode_94() {
}

void CPU::opcode_95() {
}

void CPU::opcode_96() {
}

void CPU::opcode_97() {
}

void CPU::opcode_98() {
}

void CPU::opcode_99() {
}

void CPU::opcode_9A() {
}

void CPU::opcode_9B() {
}

void CPU::opcode_9C() {
}

void CPU::opcode_9D() {
}

void CPU::opcode_9E() {
}

void CPU::opcode_9F() {
}

void CPU::opcode_A0() {
}

void CPU::opcode_A1() {
}

void CPU::opcode_A2() {
}

void CPU::opcode_A3() {
}

void CPU::opcode_A4() {
}

void CPU::opcode_A5() {
}

void CPU::opcode_A6() {
}

void CPU::opcode_A7() {
}

void CPU::opcode_A8() {
}

void CPU::opcode_A9() {
}

void CPU::opcode_AA() {
}

void CPU::opcode_AB() {
}

void CPU::opcode_AC() {
}

void CPU::opcode_AD() {
}

void CPU::opcode_AE() {
}

void CPU::opcode_AF() {
}

void CPU::opcode_B0() {
}

void CPU::opcode_B1() {
}

void CPU::opcode_B2() {
}

void CPU::opcode_B3() {
}

void CPU::opcode_B4() {
}

void CPU::opcode_B5() {
}

void CPU::opcode_B6() {
}

void CPU::opcode_B7() {
}

void CPU::opcode_B8() {
}

void CPU::opcode_B9() {
}

void CPU::opcode_BA() {
}

void CPU::opcode_BB() {
}

void CPU::opcode_BC() {
}

void CPU::opcode_BD() {
}

void CPU::opcode_BE() {
}

void CPU::opcode_BF() {
}

void CPU::opcode_C0() {
}

void CPU::opcode_C1() {
}

void CPU::opcode_C2() {
}

void CPU::opcode_C3() {
}

void CPU::opcode_C4() {
}

void CPU::opcode_C5() {
}

void CPU::opcode_C6() {
}

void CPU::opcode_C7() {
}

void CPU::opcode_C8() {
}

void CPU::opcode_C9() {
}

void CPU::opcode_CA() {
}

void CPU::opcode_CB() {
}

void CPU::opcode_CC() {
}

void CPU::opcode_CD() {
}

void CPU::opcode_CE() {
}

void CPU::opcode_CF() {
}

void CPU::opcode_D0() {
}

void CPU::opcode_D1() {
}

void CPU::opcode_D2() {
}

void CPU::opcode_D3() {
}

void CPU::opcode_D4() {
}

void CPU::opcode_D5() {
}

void CPU::opcode_D6() {
}

void CPU::opcode_D7() {
}

void CPU::opcode_D8() {
}

void CPU::opcode_D9() {
}

void CPU::opcode_DA() {
}

void CPU::opcode_DB() {
}

void CPU::opcode_DC() {
}

void CPU::opcode_DD() {
}

void CPU::opcode_DE() {
}

void CPU::opcode_DF() {
}

void CPU::opcode_E0() {
}

void CPU::opcode_E1() {
}

void CPU::opcode_E2() {
}

void CPU::opcode_E3() {
}

void CPU::opcode_E4() {
}

void CPU::opcode_E5() {
}

void CPU::opcode_E6() {
}

void CPU::opcode_E7() {
}

void CPU::opcode_E8() {
}

void CPU::opcode_E9() {
}

void CPU::opcode_EA() {
}

void CPU::opcode_EB() {
}

void CPU::opcode_EC() {
}

void CPU::opcode_ED() {
}

void CPU::opcode_EE() {
}

void CPU::opcode_EF() {
}

void CPU::opcode_F0() {
}

void CPU::opcode_F1() {
}

void CPU::opcode_F2() {
}

void CPU::opcode_F3() {
}

void CPU::opcode_F4() {
}

void CPU::opcode_F5() {
}

void CPU::opcode_F6() {
}

void CPU::opcode_F7() {
}

void CPU::opcode_F8() {
}

void CPU::opcode_F9() {
}

void CPU::opcode_FA() {
}

void CPU::opcode_FB() {
}

void CPU::opcode_FC() {
}

void CPU::opcode_FD() {
}

void CPU::opcode_FE() {
}

void CPU::opcode_FF() {
}
