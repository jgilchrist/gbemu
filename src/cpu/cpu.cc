#include "cpu.h"
#include "../bitwise.h"

CPU::CPU() {}

void CPU::execute_opcode(const uint8_t opcode) {
    if (opcode != 0xCB) {
        execute_normal_opcode(opcode);
    } else {
        execute_cb_opcode(opcode);
    }
}

void CPU::execute_normal_opcode(const uint8_t opcode) {
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

void CPU::execute_cb_opcode(const uint8_t opcode) {
    uint8_t cb_opcode = get_byte_from_pc();

    switch (cb_opcode) {
        case 0x00: opcode_CB_00(); break;
        case 0x01: opcode_CB_01(); break;
        case 0x02: opcode_CB_02(); break;
        case 0x03: opcode_CB_03(); break;
        case 0x04: opcode_CB_04(); break;
        case 0x05: opcode_CB_05(); break;
        case 0x06: opcode_CB_06(); break;
        case 0x07: opcode_CB_07(); break;
        case 0x08: opcode_CB_08(); break;
        case 0x09: opcode_CB_09(); break;
        case 0x0A: opcode_CB_0A(); break;
        case 0x0B: opcode_CB_0B(); break;
        case 0x0C: opcode_CB_0C(); break;
        case 0x0D: opcode_CB_0D(); break;
        case 0x0E: opcode_CB_0E(); break;
        case 0x0F: opcode_CB_0F(); break;
        case 0x10: opcode_CB_10(); break;
        case 0x11: opcode_CB_11(); break;
        case 0x12: opcode_CB_12(); break;
        case 0x13: opcode_CB_13(); break;
        case 0x14: opcode_CB_14(); break;
        case 0x15: opcode_CB_15(); break;
        case 0x16: opcode_CB_16(); break;
        case 0x17: opcode_CB_17(); break;
        case 0x18: opcode_CB_18(); break;
        case 0x19: opcode_CB_19(); break;
        case 0x1A: opcode_CB_1A(); break;
        case 0x1B: opcode_CB_1B(); break;
        case 0x1C: opcode_CB_1C(); break;
        case 0x1D: opcode_CB_1D(); break;
        case 0x1E: opcode_CB_1E(); break;
        case 0x1F: opcode_CB_1F(); break;
        case 0x20: opcode_CB_20(); break;
        case 0x21: opcode_CB_21(); break;
        case 0x22: opcode_CB_22(); break;
        case 0x23: opcode_CB_23(); break;
        case 0x24: opcode_CB_24(); break;
        case 0x25: opcode_CB_25(); break;
        case 0x26: opcode_CB_26(); break;
        case 0x27: opcode_CB_27(); break;
        case 0x28: opcode_CB_28(); break;
        case 0x29: opcode_CB_29(); break;
        case 0x2A: opcode_CB_2A(); break;
        case 0x2B: opcode_CB_2B(); break;
        case 0x2C: opcode_CB_2C(); break;
        case 0x2D: opcode_CB_2D(); break;
        case 0x2E: opcode_CB_2E(); break;
        case 0x2F: opcode_CB_2F(); break;
        case 0x30: opcode_CB_30(); break;
        case 0x31: opcode_CB_31(); break;
        case 0x32: opcode_CB_32(); break;
        case 0x33: opcode_CB_33(); break;
        case 0x34: opcode_CB_34(); break;
        case 0x35: opcode_CB_35(); break;
        case 0x36: opcode_CB_36(); break;
        case 0x37: opcode_CB_37(); break;
        case 0x38: opcode_CB_38(); break;
        case 0x39: opcode_CB_39(); break;
        case 0x3A: opcode_CB_3A(); break;
        case 0x3B: opcode_CB_3B(); break;
        case 0x3C: opcode_CB_3C(); break;
        case 0x3D: opcode_CB_3D(); break;
        case 0x3E: opcode_CB_3E(); break;
        case 0x3F: opcode_CB_3F(); break;
        case 0x40: opcode_CB_40(); break;
        case 0x41: opcode_CB_41(); break;
        case 0x42: opcode_CB_42(); break;
        case 0x43: opcode_CB_43(); break;
        case 0x44: opcode_CB_44(); break;
        case 0x45: opcode_CB_45(); break;
        case 0x46: opcode_CB_46(); break;
        case 0x47: opcode_CB_47(); break;
        case 0x48: opcode_CB_48(); break;
        case 0x49: opcode_CB_49(); break;
        case 0x4A: opcode_CB_4A(); break;
        case 0x4B: opcode_CB_4B(); break;
        case 0x4C: opcode_CB_4C(); break;
        case 0x4D: opcode_CB_4D(); break;
        case 0x4E: opcode_CB_4E(); break;
        case 0x4F: opcode_CB_4F(); break;
        case 0x50: opcode_CB_50(); break;
        case 0x51: opcode_CB_51(); break;
        case 0x52: opcode_CB_52(); break;
        case 0x53: opcode_CB_53(); break;
        case 0x54: opcode_CB_54(); break;
        case 0x55: opcode_CB_55(); break;
        case 0x56: opcode_CB_56(); break;
        case 0x57: opcode_CB_57(); break;
        case 0x58: opcode_CB_58(); break;
        case 0x59: opcode_CB_59(); break;
        case 0x5A: opcode_CB_5A(); break;
        case 0x5B: opcode_CB_5B(); break;
        case 0x5C: opcode_CB_5C(); break;
        case 0x5D: opcode_CB_5D(); break;
        case 0x5E: opcode_CB_5E(); break;
        case 0x5F: opcode_CB_5F(); break;
        case 0x60: opcode_CB_60(); break;
        case 0x61: opcode_CB_61(); break;
        case 0x62: opcode_CB_62(); break;
        case 0x63: opcode_CB_63(); break;
        case 0x64: opcode_CB_64(); break;
        case 0x65: opcode_CB_65(); break;
        case 0x66: opcode_CB_66(); break;
        case 0x67: opcode_CB_67(); break;
        case 0x68: opcode_CB_68(); break;
        case 0x69: opcode_CB_69(); break;
        case 0x6A: opcode_CB_6A(); break;
        case 0x6B: opcode_CB_6B(); break;
        case 0x6C: opcode_CB_6C(); break;
        case 0x6D: opcode_CB_6D(); break;
        case 0x6E: opcode_CB_6E(); break;
        case 0x6F: opcode_CB_6F(); break;
        case 0x70: opcode_CB_70(); break;
        case 0x71: opcode_CB_71(); break;
        case 0x72: opcode_CB_72(); break;
        case 0x73: opcode_CB_73(); break;
        case 0x74: opcode_CB_74(); break;
        case 0x75: opcode_CB_75(); break;
        case 0x76: opcode_CB_76(); break;
        case 0x77: opcode_CB_77(); break;
        case 0x78: opcode_CB_78(); break;
        case 0x79: opcode_CB_79(); break;
        case 0x7A: opcode_CB_7A(); break;
        case 0x7B: opcode_CB_7B(); break;
        case 0x7C: opcode_CB_7C(); break;
        case 0x7D: opcode_CB_7D(); break;
        case 0x7E: opcode_CB_7E(); break;
        case 0x7F: opcode_CB_7F(); break;
        case 0x80: opcode_CB_80(); break;
        case 0x81: opcode_CB_81(); break;
        case 0x82: opcode_CB_82(); break;
        case 0x83: opcode_CB_83(); break;
        case 0x84: opcode_CB_84(); break;
        case 0x85: opcode_CB_85(); break;
        case 0x86: opcode_CB_86(); break;
        case 0x87: opcode_CB_87(); break;
        case 0x88: opcode_CB_88(); break;
        case 0x89: opcode_CB_89(); break;
        case 0x8A: opcode_CB_8A(); break;
        case 0x8B: opcode_CB_8B(); break;
        case 0x8C: opcode_CB_8C(); break;
        case 0x8D: opcode_CB_8D(); break;
        case 0x8E: opcode_CB_8E(); break;
        case 0x8F: opcode_CB_8F(); break;
        case 0x90: opcode_CB_90(); break;
        case 0x91: opcode_CB_91(); break;
        case 0x92: opcode_CB_92(); break;
        case 0x93: opcode_CB_93(); break;
        case 0x94: opcode_CB_94(); break;
        case 0x95: opcode_CB_95(); break;
        case 0x96: opcode_CB_96(); break;
        case 0x97: opcode_CB_97(); break;
        case 0x98: opcode_CB_98(); break;
        case 0x99: opcode_CB_99(); break;
        case 0x9A: opcode_CB_9A(); break;
        case 0x9B: opcode_CB_9B(); break;
        case 0x9C: opcode_CB_9C(); break;
        case 0x9D: opcode_CB_9D(); break;
        case 0x9E: opcode_CB_9E(); break;
        case 0x9F: opcode_CB_9F(); break;
        case 0xA0: opcode_CB_A0(); break;
        case 0xA1: opcode_CB_A1(); break;
        case 0xA2: opcode_CB_A2(); break;
        case 0xA3: opcode_CB_A3(); break;
        case 0xA4: opcode_CB_A4(); break;
        case 0xA5: opcode_CB_A5(); break;
        case 0xA6: opcode_CB_A6(); break;
        case 0xA7: opcode_CB_A7(); break;
        case 0xA8: opcode_CB_A8(); break;
        case 0xA9: opcode_CB_A9(); break;
        case 0xAA: opcode_CB_AA(); break;
        case 0xAB: opcode_CB_AB(); break;
        case 0xAC: opcode_CB_AC(); break;
        case 0xAD: opcode_CB_AD(); break;
        case 0xAE: opcode_CB_AE(); break;
        case 0xAF: opcode_CB_AF(); break;
        case 0xB0: opcode_CB_B0(); break;
        case 0xB1: opcode_CB_B1(); break;
        case 0xB2: opcode_CB_B2(); break;
        case 0xB3: opcode_CB_B3(); break;
        case 0xB4: opcode_CB_B4(); break;
        case 0xB5: opcode_CB_B5(); break;
        case 0xB6: opcode_CB_B6(); break;
        case 0xB7: opcode_CB_B7(); break;
        case 0xB8: opcode_CB_B8(); break;
        case 0xB9: opcode_CB_B9(); break;
        case 0xBA: opcode_CB_BA(); break;
        case 0xBB: opcode_CB_BB(); break;
        case 0xBC: opcode_CB_BC(); break;
        case 0xBD: opcode_CB_BD(); break;
        case 0xBE: opcode_CB_BE(); break;
        case 0xBF: opcode_CB_BF(); break;
        case 0xC0: opcode_CB_C0(); break;
        case 0xC1: opcode_CB_C1(); break;
        case 0xC2: opcode_CB_C2(); break;
        case 0xC3: opcode_CB_C3(); break;
        case 0xC4: opcode_CB_C4(); break;
        case 0xC5: opcode_CB_C5(); break;
        case 0xC6: opcode_CB_C6(); break;
        case 0xC7: opcode_CB_C7(); break;
        case 0xC8: opcode_CB_C8(); break;
        case 0xC9: opcode_CB_C9(); break;
        case 0xCA: opcode_CB_CA(); break;
        case 0xCB: opcode_CB_CB(); break;
        case 0xCC: opcode_CB_CC(); break;
        case 0xCD: opcode_CB_CD(); break;
        case 0xCE: opcode_CB_CE(); break;
        case 0xCF: opcode_CB_CF(); break;
        case 0xD0: opcode_CB_D0(); break;
        case 0xD1: opcode_CB_D1(); break;
        case 0xD2: opcode_CB_D2(); break;
        case 0xD3: opcode_CB_D3(); break;
        case 0xD4: opcode_CB_D4(); break;
        case 0xD5: opcode_CB_D5(); break;
        case 0xD6: opcode_CB_D6(); break;
        case 0xD7: opcode_CB_D7(); break;
        case 0xD8: opcode_CB_D8(); break;
        case 0xD9: opcode_CB_D9(); break;
        case 0xDA: opcode_CB_DA(); break;
        case 0xDB: opcode_CB_DB(); break;
        case 0xDC: opcode_CB_DC(); break;
        case 0xDD: opcode_CB_DD(); break;
        case 0xDE: opcode_CB_DE(); break;
        case 0xDF: opcode_CB_DF(); break;
        case 0xE0: opcode_CB_E0(); break;
        case 0xE1: opcode_CB_E1(); break;
        case 0xE2: opcode_CB_E2(); break;
        case 0xE3: opcode_CB_E3(); break;
        case 0xE4: opcode_CB_E4(); break;
        case 0xE5: opcode_CB_E5(); break;
        case 0xE6: opcode_CB_E6(); break;
        case 0xE7: opcode_CB_E7(); break;
        case 0xE8: opcode_CB_E8(); break;
        case 0xE9: opcode_CB_E9(); break;
        case 0xEA: opcode_CB_EA(); break;
        case 0xEB: opcode_CB_EB(); break;
        case 0xEC: opcode_CB_EC(); break;
        case 0xED: opcode_CB_ED(); break;
        case 0xEE: opcode_CB_EE(); break;
        case 0xEF: opcode_CB_EF(); break;
        case 0xF0: opcode_CB_F0(); break;
        case 0xF1: opcode_CB_F1(); break;
        case 0xF2: opcode_CB_F2(); break;
        case 0xF3: opcode_CB_F3(); break;
        case 0xF4: opcode_CB_F4(); break;
        case 0xF5: opcode_CB_F5(); break;
        case 0xF6: opcode_CB_F6(); break;
        case 0xF7: opcode_CB_F7(); break;
        case 0xF8: opcode_CB_F8(); break;
        case 0xF9: opcode_CB_F9(); break;
        case 0xFA: opcode_CB_FA(); break;
        case 0xFB: opcode_CB_FB(); break;
        case 0xFC: opcode_CB_FC(); break;
        case 0xFD: opcode_CB_FD(); break;
        case 0xFE: opcode_CB_FE(); break;
        case 0xFF: opcode_CB_FF(); break;
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


/**
 * This section contains helper functions for allowing succinct expression
 * of opcodes when writing the opcode_00-FF functions.
 */

/* ADC */
inline void CPU::opcode_adc() {
    // TODO
}

inline void CPU::opcode_adc(const ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_adc(const Address&& addr) {
    // TODO
}


/* ADD */
inline void CPU::opcode_add(ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_add(ByteRegister& reg, const ByteRegister& byte_reg) {
    // TODO
}

inline void CPU::opcode_add(ByteRegister& reg, const Address& addr) {
    // TODO
}


inline void CPU::opcode_add(RegisterPair& reg, const RegisterPair& reg_pair) {
    // TODO
}

inline void CPU::opcode_add(RegisterPair& reg, const WordRegister& word_reg) {
    // TODO
}

inline void CPU::opcode_add(WordRegister& reg) {
    // TODO
}

inline void CPU::opcode_add_signed() {
    // TODO
}


/* AND */
inline void CPU::opcode_and() {
    // TODO
}

inline void CPU::opcode_and(ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_and(Address&& addr) {
    // TODO
}


/* BIT */
inline void CPU::opcode_bit(const int bit, ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_bit(const int bit, Address&& addr) {
    // TODO
}


/* CALL */
inline void CPU::opcode_call() {
    // TODO
}

inline void CPU::opcode_call(Condition condition) {
    // TODO
}


/* CCF */
inline void CPU::opcode_ccf() {
    // TODO
}


/* CP */
inline void CPU::opcode_cp() {
    // TODO
}

inline void CPU::opcode_cp(const ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_cp(const Address& addr) {
    // TODO
}


/* CPL */
inline void CPU::opcode_cpl() {
    // TODO
}


/* DAA */
inline void CPU::opcode_daa() {
    // TODO
}


/* DEC */
inline void CPU::opcode_dec(ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_dec(RegisterPair& reg) {
    // TODO
}

inline void CPU::opcode_dec(WordRegister& reg) {
    // TODO
}

inline void CPU::opcode_dec(Address&& addr) {
    // TODO
}


/* DI */
inline void CPU::opcode_di() {
    // TODO
}


/* EI */
inline void CPU::opcode_ei() {
    // TODO
}


/* INC */
inline void CPU::opcode_inc(ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_inc(RegisterPair& reg) {
    // TODO
}

inline void CPU::opcode_inc(WordRegister& addr) {
    // TODO
}

inline void CPU::opcode_inc(Address&& addr) {
    // TODO
}


/* JP */
inline void CPU::opcode_jp() {
    // TODO
}

inline void CPU::opcode_jp(Condition condition) {
    // TODO
}

inline void CPU::opcode_jp(const Address& addr) {
    // TODO
}


/* JR */
inline void CPU::opcode_jr() {
    // TODO
}

inline void CPU::opcode_jr(Condition condition) {
    // TODO
}


/* HALT */
inline void CPU::opcode_halt() {
    // TODO
}


/* LD */
inline void CPU::opcode_ld(ByteRegister& reg) {
    uint8_t n = get_byte_from_pc();
    reg.set(n);
}

inline void CPU::opcode_ld(ByteRegister& reg, const ByteRegister& byte_reg) {
    reg.set(byte_reg.value());
}

inline void CPU::opcode_ld(ByteRegister& reg, const Address& address) {
    reg.set(mmu.read_byte(address));
}


inline void CPU::opcode_ld(RegisterPair& reg) {
    uint16_t nn = get_word_from_pc();
    reg.set(nn);
}


inline void CPU::opcode_ld(WordRegister& reg) {
    uint16_t nn = get_word_from_pc();
    reg.set(nn);
}

inline void CPU::opcode_ld(WordRegister& reg, const RegisterPair& reg_pair) {
    // TODO
}


inline void CPU::opcode_ld(const Address& address) {
    uint8_t n = get_byte_from_pc();
    mmu.write_byte(address, n);
}

inline void CPU::opcode_ld(const Address& address, const ByteRegister& byte_reg) {
    mmu.write_byte(address, byte_reg.value());
}

inline void CPU::opcode_ld(const Address& address, const WordRegister& word_reg) {
    mmu.write_word(address, word_reg.value());
}


inline void CPU::opcode_ld_to_addr(const ByteRegister &reg) {
    // TODO
}


/* LDD */
inline void CPU::opcode_ldd(const ByteRegister& reg, const Address& address) {
    // TODO
}

inline void CPU::opcode_ldd(const Address& address, const ByteRegister& reg) {
    // TODO
}


/* LDH */
inline void CPU::opcode_ldh() {
    // TODO
}

inline void CPU::opcode_ldh(const ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_ldh(const Address&& addr) {
    // TODO
}


/* LDHL */
inline void CPU::opcode_ldhl() {
    // TODO
}


/* LDI */
inline void CPU::opcode_ldi(const ByteRegister& reg, const Address& address) {
    // TODO
}

inline void CPU::opcode_ldi(const Address& address, const ByteRegister& reg) {
    // TODO
}


/* NOP */
inline void CPU::opcode_nop() {
    // TODO
}


/* OR */
inline void CPU::opcode_or() {
    // TODO
}

inline void CPU::opcode_or(const ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_or(const Address& addr) {
    // TODO
}


/* POP */
inline void CPU::opcode_pop(const RegisterPair& reg) {
    // TODO
}


/* PUSH */
inline void CPU::opcode_push(const RegisterPair& reg) {
    // TODO
}


/* RES */
inline void CPU::opcode_res(const int bit, ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_res(const int bit, Address&& addr) {
    // TODO
}


/* RET */
inline void CPU::opcode_ret() {
    // TODO
}

inline void CPU::opcode_ret(Condition condition) {
    // TODO
}


/* RETI */
inline void CPU::opcode_reti() {
    // TODO
}


/* RL */
inline void CPU::opcode_rl(ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_rl(Address&& addr) {
    // TODO
}


/* RLC */
inline void CPU::opcode_rlc(ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_rlc(Address&& addr) {
    // TODO
}


/* RR */
inline void CPU::opcode_rr(ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_rr(Address&& addr) {
    // TODO
}


/* RRC */
inline void CPU::opcode_rrc(ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_rrc(Address&& addr) {
    // TODO
}


/* RST */
// TODO: offset type
inline void CPU::opcode_rst(const uint8_t offset) {
    // TODO
}


/* SBC */
inline void CPU::opcode_sbc() {
    // TODO
}

inline void CPU::opcode_sbc(ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_sbc(Address&& addr) {
    // TODO
}


/* SCF */
inline void CPU::opcode_scf() {
    // TODO
}


/* SET */
inline void CPU::opcode_set(const int bit, ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_set(const int bit, Address&& addr) {
    // TODO
}


/* SLA */
inline void CPU::opcode_sla(ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_sla(Address&& addr) {
    // TODO
}


/* SRA */
inline void CPU::opcode_sra(ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_sra(Address&& addr) {
    // TODO
}


/* SRL */
inline void CPU::opcode_srl(ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_srl(Address&& addr) {
    // TODO
}


/* STOP */
inline void CPU::opcode_stop() {
    // TODO
}


/* SUB */
inline void CPU::opcode_sub() {
    // TODO
}

inline void CPU::opcode_sub(ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_sub(Address&& addr) {
    // TODO
}


/* SWAP */
inline void CPU::opcode_swap(ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_swap(Address&& addr) {
    // TODO
}


/* XOR */
inline void CPU::opcode_xor() {
    // TODO
}

inline void CPU::opcode_xor(const ByteRegister& reg) {
    // TODO
}

inline void CPU::opcode_xor(const Address& addr) {
    // TODO
}




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
    uint16_t nn = get_word_from_pc();
    opcode_ld(Address(nn), sp);
}

void CPU::opcode_09() {
    opcode_add(hl, bc);
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
    opcode_add(hl, de);
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
    opcode_add(hl, hl);
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
    opcode_add(hl, sp);
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
    opcode_add(a, b);
}

void CPU::opcode_81() {
    opcode_add(a, c);
}

void CPU::opcode_82() {
    opcode_add(a, d);
}

void CPU::opcode_83() {
    opcode_add(a, e);
}

void CPU::opcode_84() {
    opcode_add(a, h);
}

void CPU::opcode_85() {
    opcode_add(a, l);
}

void CPU::opcode_86() {
    opcode_add(a, Address(hl));
}

void CPU::opcode_87() {
    opcode_add(a, a);
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
    opcode_add(a);
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
    opcode_adc(a);
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
    opcode_sub(a);
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
    opcode_ldh(a);
}

void CPU::opcode_E1() {
    opcode_pop(hl);
}

void CPU::opcode_E2() {
    opcode_ldh(c);
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
    opcode_ldh(a);
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
