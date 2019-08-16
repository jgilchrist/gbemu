#include "cpu.h"

#include "opcode_cycles.h"
#include "../util/bitwise.h"
#include "../util/log.h"

using bitwise::compose_bytes;

CPU::CPU(MMU& inMMU, Options& inOptions) :
    mmu(inMMU),
    options(inOptions),
    af(a, f),
    bc(b, c),
    de(d, e),
    hl(h, l)
{
}

Cycles CPU::tick() {
    handle_interrupts();

    if (halted) { return 1; }

    u16 opcode_pc = pc.value();
    auto opcode = get_byte_from_pc();
    auto cycles = execute_opcode(opcode, opcode_pc);
    return cycles;
}

Cycles CPU::execute_opcode(const u8 opcode, u16 opcode_pc) {
    branch_taken = false;

    if (opcode == 0xCB) {
        u8 cb_opcode = get_byte_from_pc();
        if (global_logger.is_tracing_enabled()) { trace_cb_opcode(cb_opcode, opcode_pc); }
        return execute_cb_opcode(cb_opcode);
    }

    if (global_logger.is_tracing_enabled()) { trace_normal_opcode(opcode, opcode_pc); }
    return execute_normal_opcode(opcode);
}

void CPU::handle_interrupts() {
    if (interrupts_enabled) {
        u8 fired_interrupts = interrupt_flag.value() & interrupt_enabled.value();

        if (!fired_interrupts) { return; }

        halted = false;
        stack_push(pc);

        bool handled_interrupt = false;

        handled_interrupt = handle_interrupt(0, interrupts::vblank, fired_interrupts);
        if (handled_interrupt) { return; }

        handled_interrupt = handle_interrupt(1, interrupts::lcdc_status, fired_interrupts);
        if (handled_interrupt) { return; }

        handled_interrupt = handle_interrupt(2, interrupts::timer, fired_interrupts);
        if (handled_interrupt) { return; }

        handled_interrupt = handle_interrupt(3, interrupts::serial, fired_interrupts);
        if (handled_interrupt) { return; }

        handled_interrupt = handle_interrupt(4, interrupts::joypad, fired_interrupts);
        if (handled_interrupt) { return; }
    }
}

bool CPU::handle_interrupt(u8 interrupt_bit, u16 interrupt_vector, u8 fired_interrupts) {
    using bitwise::check_bit;

    if (!check_bit(fired_interrupts, interrupt_bit)) { return false; }

    interrupt_flag.set_bit_to(interrupt_bit, false);
    pc.set(interrupt_vector);
    interrupts_enabled = false;
    return true;
}

u8 CPU::get_byte_from_pc() {
    u8 byte = mmu.read(Address(pc));
    pc.increment();

    return byte;
}

u8 CPU::peek_byte_from_pc(u8 offset) {
    u8 byte = mmu.read(Address(pc));
    return byte;
}

s8 CPU::get_signed_byte_from_pc() {
    u8 byte = get_byte_from_pc();
    return static_cast<s8>(byte);
}

s8 CPU::peek_signed_byte_from_pc(u8 offset) {
    u8 byte = peek_byte_from_pc();
    return static_cast<s8>(byte);
}

u16 CPU::get_word_from_pc(u8 offset) {
    u8 low_byte = get_byte_from_pc();
    u8 high_byte = get_byte_from_pc();

    return compose_bytes(high_byte, low_byte);
}

u16 CPU::peek_word_from_pc() {
    u8 low_byte = mmu.read(Address(pc));
    u8 high_byte = mmu.read(Address(pc) + 1);

    return compose_bytes(high_byte, low_byte);
}

void CPU::set_flag_zero(bool set) { f.set_flag_zero(set); }
void CPU::set_flag_subtract(bool set) { f.set_flag_subtract(set); }
void CPU::set_flag_half_carry(bool set) { f.set_flag_half_carry(set); }
void CPU::set_flag_carry(bool set) { f.set_flag_carry(set); }

bool CPU::is_condition(Condition condition) {
    bool should_branch;

    switch (condition) {
        case Condition::C:
            should_branch = f.flag_carry();
            break;
        case Condition::NC:
            should_branch = !f.flag_carry();
            break;
        case Condition::Z:
            should_branch = f.flag_zero();
            break;
        case Condition::NZ:
            should_branch = !f.flag_zero();
            break;
    }

    /* If the branch is taken, remember so that the correct processor cycles
     * can be used */
    branch_taken = should_branch;
    return should_branch;
}

void CPU::stack_push(const WordValue& reg) {
    sp.decrement();
    mmu.write(Address(sp), reg.high());
    sp.decrement();
    mmu.write(Address(sp), reg.low());
}

void CPU::stack_pop(WordValue& reg) {
    u8 low_byte = mmu.read(Address(sp));
    sp.increment();
    u8 high_byte = mmu.read(Address(sp));
    sp.increment();

    u16 value = compose_bytes(high_byte, low_byte);
    reg.set(value);
}

/* clang-format off */
Cycles CPU::execute_normal_opcode(const u8 opcode) {
    switch (opcode) {
        case 0x00: opcode_00(); break; case 0x01: opcode_01(); break; case 0x02: opcode_02(); break; case 0x03: opcode_03(); break; case 0x04: opcode_04(); break; case 0x05: opcode_05(); break; case 0x06: opcode_06(); break; case 0x07: opcode_07(); break; case 0x08: opcode_08(); break; case 0x09: opcode_09(); break; case 0x0A: opcode_0A(); break; case 0x0B: opcode_0B(); break; case 0x0C: opcode_0C(); break; case 0x0D: opcode_0D(); break; case 0x0E: opcode_0E(); break; case 0x0F: opcode_0F(); break;
        case 0x10: opcode_10(); break; case 0x11: opcode_11(); break; case 0x12: opcode_12(); break; case 0x13: opcode_13(); break; case 0x14: opcode_14(); break; case 0x15: opcode_15(); break; case 0x16: opcode_16(); break; case 0x17: opcode_17(); break; case 0x18: opcode_18(); break; case 0x19: opcode_19(); break; case 0x1A: opcode_1A(); break; case 0x1B: opcode_1B(); break; case 0x1C: opcode_1C(); break; case 0x1D: opcode_1D(); break; case 0x1E: opcode_1E(); break; case 0x1F: opcode_1F(); break;
        case 0x20: opcode_20(); break; case 0x21: opcode_21(); break; case 0x22: opcode_22(); break; case 0x23: opcode_23(); break; case 0x24: opcode_24(); break; case 0x25: opcode_25(); break; case 0x26: opcode_26(); break; case 0x27: opcode_27(); break; case 0x28: opcode_28(); break; case 0x29: opcode_29(); break; case 0x2A: opcode_2A(); break; case 0x2B: opcode_2B(); break; case 0x2C: opcode_2C(); break; case 0x2D: opcode_2D(); break; case 0x2E: opcode_2E(); break; case 0x2F: opcode_2F(); break;
        case 0x30: opcode_30(); break; case 0x31: opcode_31(); break; case 0x32: opcode_32(); break; case 0x33: opcode_33(); break; case 0x34: opcode_34(); break; case 0x35: opcode_35(); break; case 0x36: opcode_36(); break; case 0x37: opcode_37(); break; case 0x38: opcode_38(); break; case 0x39: opcode_39(); break; case 0x3A: opcode_3A(); break; case 0x3B: opcode_3B(); break; case 0x3C: opcode_3C(); break; case 0x3D: opcode_3D(); break; case 0x3E: opcode_3E(); break; case 0x3F: opcode_3F(); break;
        case 0x40: opcode_40(); break; case 0x41: opcode_41(); break; case 0x42: opcode_42(); break; case 0x43: opcode_43(); break; case 0x44: opcode_44(); break; case 0x45: opcode_45(); break; case 0x46: opcode_46(); break; case 0x47: opcode_47(); break; case 0x48: opcode_48(); break; case 0x49: opcode_49(); break; case 0x4A: opcode_4A(); break; case 0x4B: opcode_4B(); break; case 0x4C: opcode_4C(); break; case 0x4D: opcode_4D(); break; case 0x4E: opcode_4E(); break; case 0x4F: opcode_4F(); break;
        case 0x50: opcode_50(); break; case 0x51: opcode_51(); break; case 0x52: opcode_52(); break; case 0x53: opcode_53(); break; case 0x54: opcode_54(); break; case 0x55: opcode_55(); break; case 0x56: opcode_56(); break; case 0x57: opcode_57(); break; case 0x58: opcode_58(); break; case 0x59: opcode_59(); break; case 0x5A: opcode_5A(); break; case 0x5B: opcode_5B(); break; case 0x5C: opcode_5C(); break; case 0x5D: opcode_5D(); break; case 0x5E: opcode_5E(); break; case 0x5F: opcode_5F(); break;
        case 0x60: opcode_60(); break; case 0x61: opcode_61(); break; case 0x62: opcode_62(); break; case 0x63: opcode_63(); break; case 0x64: opcode_64(); break; case 0x65: opcode_65(); break; case 0x66: opcode_66(); break; case 0x67: opcode_67(); break; case 0x68: opcode_68(); break; case 0x69: opcode_69(); break; case 0x6A: opcode_6A(); break; case 0x6B: opcode_6B(); break; case 0x6C: opcode_6C(); break; case 0x6D: opcode_6D(); break; case 0x6E: opcode_6E(); break; case 0x6F: opcode_6F(); break;
        case 0x70: opcode_70(); break; case 0x71: opcode_71(); break; case 0x72: opcode_72(); break; case 0x73: opcode_73(); break; case 0x74: opcode_74(); break; case 0x75: opcode_75(); break; case 0x76: opcode_76(); break; case 0x77: opcode_77(); break; case 0x78: opcode_78(); break; case 0x79: opcode_79(); break; case 0x7A: opcode_7A(); break; case 0x7B: opcode_7B(); break; case 0x7C: opcode_7C(); break; case 0x7D: opcode_7D(); break; case 0x7E: opcode_7E(); break; case 0x7F: opcode_7F(); break;
        case 0x80: opcode_80(); break; case 0x81: opcode_81(); break; case 0x82: opcode_82(); break; case 0x83: opcode_83(); break; case 0x84: opcode_84(); break; case 0x85: opcode_85(); break; case 0x86: opcode_86(); break; case 0x87: opcode_87(); break; case 0x88: opcode_88(); break; case 0x89: opcode_89(); break; case 0x8A: opcode_8A(); break; case 0x8B: opcode_8B(); break; case 0x8C: opcode_8C(); break; case 0x8D: opcode_8D(); break; case 0x8E: opcode_8E(); break; case 0x8F: opcode_8F(); break;
        case 0x90: opcode_90(); break; case 0x91: opcode_91(); break; case 0x92: opcode_92(); break; case 0x93: opcode_93(); break; case 0x94: opcode_94(); break; case 0x95: opcode_95(); break; case 0x96: opcode_96(); break; case 0x97: opcode_97(); break; case 0x98: opcode_98(); break; case 0x99: opcode_99(); break; case 0x9A: opcode_9A(); break; case 0x9B: opcode_9B(); break; case 0x9C: opcode_9C(); break; case 0x9D: opcode_9D(); break; case 0x9E: opcode_9E(); break; case 0x9F: opcode_9F(); break;
        case 0xA0: opcode_A0(); break; case 0xA1: opcode_A1(); break; case 0xA2: opcode_A2(); break; case 0xA3: opcode_A3(); break; case 0xA4: opcode_A4(); break; case 0xA5: opcode_A5(); break; case 0xA6: opcode_A6(); break; case 0xA7: opcode_A7(); break; case 0xA8: opcode_A8(); break; case 0xA9: opcode_A9(); break; case 0xAA: opcode_AA(); break; case 0xAB: opcode_AB(); break; case 0xAC: opcode_AC(); break; case 0xAD: opcode_AD(); break; case 0xAE: opcode_AE(); break; case 0xAF: opcode_AF(); break;
        case 0xB0: opcode_B0(); break; case 0xB1: opcode_B1(); break; case 0xB2: opcode_B2(); break; case 0xB3: opcode_B3(); break; case 0xB4: opcode_B4(); break; case 0xB5: opcode_B5(); break; case 0xB6: opcode_B6(); break; case 0xB7: opcode_B7(); break; case 0xB8: opcode_B8(); break; case 0xB9: opcode_B9(); break; case 0xBA: opcode_BA(); break; case 0xBB: opcode_BB(); break; case 0xBC: opcode_BC(); break; case 0xBD: opcode_BD(); break; case 0xBE: opcode_BE(); break; case 0xBF: opcode_BF(); break;
        case 0xC0: opcode_C0(); break; case 0xC1: opcode_C1(); break; case 0xC2: opcode_C2(); break; case 0xC3: opcode_C3(); break; case 0xC4: opcode_C4(); break; case 0xC5: opcode_C5(); break; case 0xC6: opcode_C6(); break; case 0xC7: opcode_C7(); break; case 0xC8: opcode_C8(); break; case 0xC9: opcode_C9(); break; case 0xCA: opcode_CA(); break; case 0xCB: opcode_CB(); break; case 0xCC: opcode_CC(); break; case 0xCD: opcode_CD(); break; case 0xCE: opcode_CE(); break; case 0xCF: opcode_CF(); break;
        case 0xD0: opcode_D0(); break; case 0xD1: opcode_D1(); break; case 0xD2: opcode_D2(); break; case 0xD3: opcode_D3(); break; case 0xD4: opcode_D4(); break; case 0xD5: opcode_D5(); break; case 0xD6: opcode_D6(); break; case 0xD7: opcode_D7(); break; case 0xD8: opcode_D8(); break; case 0xD9: opcode_D9(); break; case 0xDA: opcode_DA(); break; case 0xDB: opcode_DB(); break; case 0xDC: opcode_DC(); break; case 0xDD: opcode_DD(); break; case 0xDE: opcode_DE(); break; case 0xDF: opcode_DF(); break;
        case 0xE0: opcode_E0(); break; case 0xE1: opcode_E1(); break; case 0xE2: opcode_E2(); break; case 0xE3: opcode_E3(); break; case 0xE4: opcode_E4(); break; case 0xE5: opcode_E5(); break; case 0xE6: opcode_E6(); break; case 0xE7: opcode_E7(); break; case 0xE8: opcode_E8(); break; case 0xE9: opcode_E9(); break; case 0xEA: opcode_EA(); break; case 0xEB: opcode_EB(); break; case 0xEC: opcode_EC(); break; case 0xED: opcode_ED(); break; case 0xEE: opcode_EE(); break; case 0xEF: opcode_EF(); break;
        case 0xF0: opcode_F0(); break; case 0xF1: opcode_F1(); break; case 0xF2: opcode_F2(); break; case 0xF3: opcode_F3(); break; case 0xF4: opcode_F4(); break; case 0xF5: opcode_F5(); break; case 0xF6: opcode_F6(); break; case 0xF7: opcode_F7(); break; case 0xF8: opcode_F8(); break; case 0xF9: opcode_F9(); break; case 0xFA: opcode_FA(); break; case 0xFB: opcode_FB(); break; case 0xFC: opcode_FC(); break; case 0xFD: opcode_FD(); break; case 0xFE: opcode_FE(); break; case 0xFF: opcode_FF(); break;
    }

    return !branch_taken
        ? opcode_cycles[opcode]
        : opcode_cycles_branched[opcode];
}

Cycles CPU::execute_cb_opcode(const u8 opcode) {
    switch (opcode) {
        case 0x00: opcode_CB_00(); break; case 0x01: opcode_CB_01(); break; case 0x02: opcode_CB_02(); break; case 0x03: opcode_CB_03(); break; case 0x04: opcode_CB_04(); break; case 0x05: opcode_CB_05(); break; case 0x06: opcode_CB_06(); break; case 0x07: opcode_CB_07(); break; case 0x08: opcode_CB_08(); break; case 0x09: opcode_CB_09(); break; case 0x0A: opcode_CB_0A(); break; case 0x0B: opcode_CB_0B(); break; case 0x0C: opcode_CB_0C(); break; case 0x0D: opcode_CB_0D(); break; case 0x0E: opcode_CB_0E(); break; case 0x0F: opcode_CB_0F(); break;
        case 0x10: opcode_CB_10(); break; case 0x11: opcode_CB_11(); break; case 0x12: opcode_CB_12(); break; case 0x13: opcode_CB_13(); break; case 0x14: opcode_CB_14(); break; case 0x15: opcode_CB_15(); break; case 0x16: opcode_CB_16(); break; case 0x17: opcode_CB_17(); break; case 0x18: opcode_CB_18(); break; case 0x19: opcode_CB_19(); break; case 0x1A: opcode_CB_1A(); break; case 0x1B: opcode_CB_1B(); break; case 0x1C: opcode_CB_1C(); break; case 0x1D: opcode_CB_1D(); break; case 0x1E: opcode_CB_1E(); break; case 0x1F: opcode_CB_1F(); break;
        case 0x20: opcode_CB_20(); break; case 0x21: opcode_CB_21(); break; case 0x22: opcode_CB_22(); break; case 0x23: opcode_CB_23(); break; case 0x24: opcode_CB_24(); break; case 0x25: opcode_CB_25(); break; case 0x26: opcode_CB_26(); break; case 0x27: opcode_CB_27(); break; case 0x28: opcode_CB_28(); break; case 0x29: opcode_CB_29(); break; case 0x2A: opcode_CB_2A(); break; case 0x2B: opcode_CB_2B(); break; case 0x2C: opcode_CB_2C(); break; case 0x2D: opcode_CB_2D(); break; case 0x2E: opcode_CB_2E(); break; case 0x2F: opcode_CB_2F(); break;
        case 0x30: opcode_CB_30(); break; case 0x31: opcode_CB_31(); break; case 0x32: opcode_CB_32(); break; case 0x33: opcode_CB_33(); break; case 0x34: opcode_CB_34(); break; case 0x35: opcode_CB_35(); break; case 0x36: opcode_CB_36(); break; case 0x37: opcode_CB_37(); break; case 0x38: opcode_CB_38(); break; case 0x39: opcode_CB_39(); break; case 0x3A: opcode_CB_3A(); break; case 0x3B: opcode_CB_3B(); break; case 0x3C: opcode_CB_3C(); break; case 0x3D: opcode_CB_3D(); break; case 0x3E: opcode_CB_3E(); break; case 0x3F: opcode_CB_3F(); break;
        case 0x40: opcode_CB_40(); break; case 0x41: opcode_CB_41(); break; case 0x42: opcode_CB_42(); break; case 0x43: opcode_CB_43(); break; case 0x44: opcode_CB_44(); break; case 0x45: opcode_CB_45(); break; case 0x46: opcode_CB_46(); break; case 0x47: opcode_CB_47(); break; case 0x48: opcode_CB_48(); break; case 0x49: opcode_CB_49(); break; case 0x4A: opcode_CB_4A(); break; case 0x4B: opcode_CB_4B(); break; case 0x4C: opcode_CB_4C(); break; case 0x4D: opcode_CB_4D(); break; case 0x4E: opcode_CB_4E(); break; case 0x4F: opcode_CB_4F(); break;
        case 0x50: opcode_CB_50(); break; case 0x51: opcode_CB_51(); break; case 0x52: opcode_CB_52(); break; case 0x53: opcode_CB_53(); break; case 0x54: opcode_CB_54(); break; case 0x55: opcode_CB_55(); break; case 0x56: opcode_CB_56(); break; case 0x57: opcode_CB_57(); break; case 0x58: opcode_CB_58(); break; case 0x59: opcode_CB_59(); break; case 0x5A: opcode_CB_5A(); break; case 0x5B: opcode_CB_5B(); break; case 0x5C: opcode_CB_5C(); break; case 0x5D: opcode_CB_5D(); break; case 0x5E: opcode_CB_5E(); break; case 0x5F: opcode_CB_5F(); break;
        case 0x60: opcode_CB_60(); break; case 0x61: opcode_CB_61(); break; case 0x62: opcode_CB_62(); break; case 0x63: opcode_CB_63(); break; case 0x64: opcode_CB_64(); break; case 0x65: opcode_CB_65(); break; case 0x66: opcode_CB_66(); break; case 0x67: opcode_CB_67(); break; case 0x68: opcode_CB_68(); break; case 0x69: opcode_CB_69(); break; case 0x6A: opcode_CB_6A(); break; case 0x6B: opcode_CB_6B(); break; case 0x6C: opcode_CB_6C(); break; case 0x6D: opcode_CB_6D(); break; case 0x6E: opcode_CB_6E(); break; case 0x6F: opcode_CB_6F(); break;
        case 0x70: opcode_CB_70(); break; case 0x71: opcode_CB_71(); break; case 0x72: opcode_CB_72(); break; case 0x73: opcode_CB_73(); break; case 0x74: opcode_CB_74(); break; case 0x75: opcode_CB_75(); break; case 0x76: opcode_CB_76(); break; case 0x77: opcode_CB_77(); break; case 0x78: opcode_CB_78(); break; case 0x79: opcode_CB_79(); break; case 0x7A: opcode_CB_7A(); break; case 0x7B: opcode_CB_7B(); break; case 0x7C: opcode_CB_7C(); break; case 0x7D: opcode_CB_7D(); break; case 0x7E: opcode_CB_7E(); break; case 0x7F: opcode_CB_7F(); break;
        case 0x80: opcode_CB_80(); break; case 0x81: opcode_CB_81(); break; case 0x82: opcode_CB_82(); break; case 0x83: opcode_CB_83(); break; case 0x84: opcode_CB_84(); break; case 0x85: opcode_CB_85(); break; case 0x86: opcode_CB_86(); break; case 0x87: opcode_CB_87(); break; case 0x88: opcode_CB_88(); break; case 0x89: opcode_CB_89(); break; case 0x8A: opcode_CB_8A(); break; case 0x8B: opcode_CB_8B(); break; case 0x8C: opcode_CB_8C(); break; case 0x8D: opcode_CB_8D(); break; case 0x8E: opcode_CB_8E(); break; case 0x8F: opcode_CB_8F(); break;
        case 0x90: opcode_CB_90(); break; case 0x91: opcode_CB_91(); break; case 0x92: opcode_CB_92(); break; case 0x93: opcode_CB_93(); break; case 0x94: opcode_CB_94(); break; case 0x95: opcode_CB_95(); break; case 0x96: opcode_CB_96(); break; case 0x97: opcode_CB_97(); break; case 0x98: opcode_CB_98(); break; case 0x99: opcode_CB_99(); break; case 0x9A: opcode_CB_9A(); break; case 0x9B: opcode_CB_9B(); break; case 0x9C: opcode_CB_9C(); break; case 0x9D: opcode_CB_9D(); break; case 0x9E: opcode_CB_9E(); break; case 0x9F: opcode_CB_9F(); break;
        case 0xA0: opcode_CB_A0(); break; case 0xA1: opcode_CB_A1(); break; case 0xA2: opcode_CB_A2(); break; case 0xA3: opcode_CB_A3(); break; case 0xA4: opcode_CB_A4(); break; case 0xA5: opcode_CB_A5(); break; case 0xA6: opcode_CB_A6(); break; case 0xA7: opcode_CB_A7(); break; case 0xA8: opcode_CB_A8(); break; case 0xA9: opcode_CB_A9(); break; case 0xAA: opcode_CB_AA(); break; case 0xAB: opcode_CB_AB(); break; case 0xAC: opcode_CB_AC(); break; case 0xAD: opcode_CB_AD(); break; case 0xAE: opcode_CB_AE(); break; case 0xAF: opcode_CB_AF(); break;
        case 0xB0: opcode_CB_B0(); break; case 0xB1: opcode_CB_B1(); break; case 0xB2: opcode_CB_B2(); break; case 0xB3: opcode_CB_B3(); break; case 0xB4: opcode_CB_B4(); break; case 0xB5: opcode_CB_B5(); break; case 0xB6: opcode_CB_B6(); break; case 0xB7: opcode_CB_B7(); break; case 0xB8: opcode_CB_B8(); break; case 0xB9: opcode_CB_B9(); break; case 0xBA: opcode_CB_BA(); break; case 0xBB: opcode_CB_BB(); break; case 0xBC: opcode_CB_BC(); break; case 0xBD: opcode_CB_BD(); break; case 0xBE: opcode_CB_BE(); break; case 0xBF: opcode_CB_BF(); break;
        case 0xC0: opcode_CB_C0(); break; case 0xC1: opcode_CB_C1(); break; case 0xC2: opcode_CB_C2(); break; case 0xC3: opcode_CB_C3(); break; case 0xC4: opcode_CB_C4(); break; case 0xC5: opcode_CB_C5(); break; case 0xC6: opcode_CB_C6(); break; case 0xC7: opcode_CB_C7(); break; case 0xC8: opcode_CB_C8(); break; case 0xC9: opcode_CB_C9(); break; case 0xCA: opcode_CB_CA(); break; case 0xCB: opcode_CB_CB(); break; case 0xCC: opcode_CB_CC(); break; case 0xCD: opcode_CB_CD(); break; case 0xCE: opcode_CB_CE(); break; case 0xCF: opcode_CB_CF(); break;
        case 0xD0: opcode_CB_D0(); break; case 0xD1: opcode_CB_D1(); break; case 0xD2: opcode_CB_D2(); break; case 0xD3: opcode_CB_D3(); break; case 0xD4: opcode_CB_D4(); break; case 0xD5: opcode_CB_D5(); break; case 0xD6: opcode_CB_D6(); break; case 0xD7: opcode_CB_D7(); break; case 0xD8: opcode_CB_D8(); break; case 0xD9: opcode_CB_D9(); break; case 0xDA: opcode_CB_DA(); break; case 0xDB: opcode_CB_DB(); break; case 0xDC: opcode_CB_DC(); break; case 0xDD: opcode_CB_DD(); break; case 0xDE: opcode_CB_DE(); break; case 0xDF: opcode_CB_DF(); break;
        case 0xE0: opcode_CB_E0(); break; case 0xE1: opcode_CB_E1(); break; case 0xE2: opcode_CB_E2(); break; case 0xE3: opcode_CB_E3(); break; case 0xE4: opcode_CB_E4(); break; case 0xE5: opcode_CB_E5(); break; case 0xE6: opcode_CB_E6(); break; case 0xE7: opcode_CB_E7(); break; case 0xE8: opcode_CB_E8(); break; case 0xE9: opcode_CB_E9(); break; case 0xEA: opcode_CB_EA(); break; case 0xEB: opcode_CB_EB(); break; case 0xEC: opcode_CB_EC(); break; case 0xED: opcode_CB_ED(); break; case 0xEE: opcode_CB_EE(); break; case 0xEF: opcode_CB_EF(); break;
        case 0xF0: opcode_CB_F0(); break; case 0xF1: opcode_CB_F1(); break; case 0xF2: opcode_CB_F2(); break; case 0xF3: opcode_CB_F3(); break; case 0xF4: opcode_CB_F4(); break; case 0xF5: opcode_CB_F5(); break; case 0xF6: opcode_CB_F6(); break; case 0xF7: opcode_CB_F7(); break; case 0xF8: opcode_CB_F8(); break; case 0xF9: opcode_CB_F9(); break; case 0xFA: opcode_CB_FA(); break; case 0xFB: opcode_CB_FB(); break; case 0xFC: opcode_CB_FC(); break; case 0xFD: opcode_CB_FD(); break; case 0xFE: opcode_CB_FE(); break; case 0xFF: opcode_CB_FF(); break;
    }

    return opcode_cycles_cb[opcode];
}

void CPU::trace_normal_opcode(const u8 opcode, u16 opcode_pc) {
    global_logger.set_newlines_enabled(false);
    log_trace("0x%04X | ", opcode_pc, opcode);

    switch (opcode) {
        case 0x00: trace_opcode_00(opcode, opcode_pc); break; case 0x01: trace_opcode_01(opcode, opcode_pc); break; case 0x02: trace_opcode_02(opcode, opcode_pc); break; case 0x03: trace_opcode_03(opcode, opcode_pc); break; case 0x04: trace_opcode_04(opcode, opcode_pc); break; case 0x05: trace_opcode_05(opcode, opcode_pc); break; case 0x06: trace_opcode_06(opcode, opcode_pc); break; case 0x07: trace_opcode_07(opcode, opcode_pc); break; case 0x08: trace_opcode_08(opcode, opcode_pc); break; case 0x09: trace_opcode_09(opcode, opcode_pc); break; case 0x0A: trace_opcode_0A(opcode, opcode_pc); break; case 0x0B: trace_opcode_0B(opcode, opcode_pc); break; case 0x0C: trace_opcode_0C(opcode, opcode_pc); break; case 0x0D: trace_opcode_0D(opcode, opcode_pc); break; case 0x0E: trace_opcode_0E(opcode, opcode_pc); break; case 0x0F: trace_opcode_0F(opcode, opcode_pc); break;
        case 0x10: trace_opcode_10(opcode, opcode_pc); break; case 0x11: trace_opcode_11(opcode, opcode_pc); break; case 0x12: trace_opcode_12(opcode, opcode_pc); break; case 0x13: trace_opcode_13(opcode, opcode_pc); break; case 0x14: trace_opcode_14(opcode, opcode_pc); break; case 0x15: trace_opcode_15(opcode, opcode_pc); break; case 0x16: trace_opcode_16(opcode, opcode_pc); break; case 0x17: trace_opcode_17(opcode, opcode_pc); break; case 0x18: trace_opcode_18(opcode, opcode_pc); break; case 0x19: trace_opcode_19(opcode, opcode_pc); break; case 0x1A: trace_opcode_1A(opcode, opcode_pc); break; case 0x1B: trace_opcode_1B(opcode, opcode_pc); break; case 0x1C: trace_opcode_1C(opcode, opcode_pc); break; case 0x1D: trace_opcode_1D(opcode, opcode_pc); break; case 0x1E: trace_opcode_1E(opcode, opcode_pc); break; case 0x1F: trace_opcode_1F(opcode, opcode_pc); break;
        case 0x20: trace_opcode_20(opcode, opcode_pc); break; case 0x21: trace_opcode_21(opcode, opcode_pc); break; case 0x22: trace_opcode_22(opcode, opcode_pc); break; case 0x23: trace_opcode_23(opcode, opcode_pc); break; case 0x24: trace_opcode_24(opcode, opcode_pc); break; case 0x25: trace_opcode_25(opcode, opcode_pc); break; case 0x26: trace_opcode_26(opcode, opcode_pc); break; case 0x27: trace_opcode_27(opcode, opcode_pc); break; case 0x28: trace_opcode_28(opcode, opcode_pc); break; case 0x29: trace_opcode_29(opcode, opcode_pc); break; case 0x2A: trace_opcode_2A(opcode, opcode_pc); break; case 0x2B: trace_opcode_2B(opcode, opcode_pc); break; case 0x2C: trace_opcode_2C(opcode, opcode_pc); break; case 0x2D: trace_opcode_2D(opcode, opcode_pc); break; case 0x2E: trace_opcode_2E(opcode, opcode_pc); break; case 0x2F: trace_opcode_2F(opcode, opcode_pc); break;
        case 0x30: trace_opcode_30(opcode, opcode_pc); break; case 0x31: trace_opcode_31(opcode, opcode_pc); break; case 0x32: trace_opcode_32(opcode, opcode_pc); break; case 0x33: trace_opcode_33(opcode, opcode_pc); break; case 0x34: trace_opcode_34(opcode, opcode_pc); break; case 0x35: trace_opcode_35(opcode, opcode_pc); break; case 0x36: trace_opcode_36(opcode, opcode_pc); break; case 0x37: trace_opcode_37(opcode, opcode_pc); break; case 0x38: trace_opcode_38(opcode, opcode_pc); break; case 0x39: trace_opcode_39(opcode, opcode_pc); break; case 0x3A: trace_opcode_3A(opcode, opcode_pc); break; case 0x3B: trace_opcode_3B(opcode, opcode_pc); break; case 0x3C: trace_opcode_3C(opcode, opcode_pc); break; case 0x3D: trace_opcode_3D(opcode, opcode_pc); break; case 0x3E: trace_opcode_3E(opcode, opcode_pc); break; case 0x3F: trace_opcode_3F(opcode, opcode_pc); break;
        case 0x40: trace_opcode_40(opcode, opcode_pc); break; case 0x41: trace_opcode_41(opcode, opcode_pc); break; case 0x42: trace_opcode_42(opcode, opcode_pc); break; case 0x43: trace_opcode_43(opcode, opcode_pc); break; case 0x44: trace_opcode_44(opcode, opcode_pc); break; case 0x45: trace_opcode_45(opcode, opcode_pc); break; case 0x46: trace_opcode_46(opcode, opcode_pc); break; case 0x47: trace_opcode_47(opcode, opcode_pc); break; case 0x48: trace_opcode_48(opcode, opcode_pc); break; case 0x49: trace_opcode_49(opcode, opcode_pc); break; case 0x4A: trace_opcode_4A(opcode, opcode_pc); break; case 0x4B: trace_opcode_4B(opcode, opcode_pc); break; case 0x4C: trace_opcode_4C(opcode, opcode_pc); break; case 0x4D: trace_opcode_4D(opcode, opcode_pc); break; case 0x4E: trace_opcode_4E(opcode, opcode_pc); break; case 0x4F: trace_opcode_4F(opcode, opcode_pc); break;
        case 0x50: trace_opcode_50(opcode, opcode_pc); break; case 0x51: trace_opcode_51(opcode, opcode_pc); break; case 0x52: trace_opcode_52(opcode, opcode_pc); break; case 0x53: trace_opcode_53(opcode, opcode_pc); break; case 0x54: trace_opcode_54(opcode, opcode_pc); break; case 0x55: trace_opcode_55(opcode, opcode_pc); break; case 0x56: trace_opcode_56(opcode, opcode_pc); break; case 0x57: trace_opcode_57(opcode, opcode_pc); break; case 0x58: trace_opcode_58(opcode, opcode_pc); break; case 0x59: trace_opcode_59(opcode, opcode_pc); break; case 0x5A: trace_opcode_5A(opcode, opcode_pc); break; case 0x5B: trace_opcode_5B(opcode, opcode_pc); break; case 0x5C: trace_opcode_5C(opcode, opcode_pc); break; case 0x5D: trace_opcode_5D(opcode, opcode_pc); break; case 0x5E: trace_opcode_5E(opcode, opcode_pc); break; case 0x5F: trace_opcode_5F(opcode, opcode_pc); break;
        case 0x60: trace_opcode_60(opcode, opcode_pc); break; case 0x61: trace_opcode_61(opcode, opcode_pc); break; case 0x62: trace_opcode_62(opcode, opcode_pc); break; case 0x63: trace_opcode_63(opcode, opcode_pc); break; case 0x64: trace_opcode_64(opcode, opcode_pc); break; case 0x65: trace_opcode_65(opcode, opcode_pc); break; case 0x66: trace_opcode_66(opcode, opcode_pc); break; case 0x67: trace_opcode_67(opcode, opcode_pc); break; case 0x68: trace_opcode_68(opcode, opcode_pc); break; case 0x69: trace_opcode_69(opcode, opcode_pc); break; case 0x6A: trace_opcode_6A(opcode, opcode_pc); break; case 0x6B: trace_opcode_6B(opcode, opcode_pc); break; case 0x6C: trace_opcode_6C(opcode, opcode_pc); break; case 0x6D: trace_opcode_6D(opcode, opcode_pc); break; case 0x6E: trace_opcode_6E(opcode, opcode_pc); break; case 0x6F: trace_opcode_6F(opcode, opcode_pc); break;
        case 0x70: trace_opcode_70(opcode, opcode_pc); break; case 0x71: trace_opcode_71(opcode, opcode_pc); break; case 0x72: trace_opcode_72(opcode, opcode_pc); break; case 0x73: trace_opcode_73(opcode, opcode_pc); break; case 0x74: trace_opcode_74(opcode, opcode_pc); break; case 0x75: trace_opcode_75(opcode, opcode_pc); break; case 0x76: trace_opcode_76(opcode, opcode_pc); break; case 0x77: trace_opcode_77(opcode, opcode_pc); break; case 0x78: trace_opcode_78(opcode, opcode_pc); break; case 0x79: trace_opcode_79(opcode, opcode_pc); break; case 0x7A: trace_opcode_7A(opcode, opcode_pc); break; case 0x7B: trace_opcode_7B(opcode, opcode_pc); break; case 0x7C: trace_opcode_7C(opcode, opcode_pc); break; case 0x7D: trace_opcode_7D(opcode, opcode_pc); break; case 0x7E: trace_opcode_7E(opcode, opcode_pc); break; case 0x7F: trace_opcode_7F(opcode, opcode_pc); break;
        case 0x80: trace_opcode_80(opcode, opcode_pc); break; case 0x81: trace_opcode_81(opcode, opcode_pc); break; case 0x82: trace_opcode_82(opcode, opcode_pc); break; case 0x83: trace_opcode_83(opcode, opcode_pc); break; case 0x84: trace_opcode_84(opcode, opcode_pc); break; case 0x85: trace_opcode_85(opcode, opcode_pc); break; case 0x86: trace_opcode_86(opcode, opcode_pc); break; case 0x87: trace_opcode_87(opcode, opcode_pc); break; case 0x88: trace_opcode_88(opcode, opcode_pc); break; case 0x89: trace_opcode_89(opcode, opcode_pc); break; case 0x8A: trace_opcode_8A(opcode, opcode_pc); break; case 0x8B: trace_opcode_8B(opcode, opcode_pc); break; case 0x8C: trace_opcode_8C(opcode, opcode_pc); break; case 0x8D: trace_opcode_8D(opcode, opcode_pc); break; case 0x8E: trace_opcode_8E(opcode, opcode_pc); break; case 0x8F: trace_opcode_8F(opcode, opcode_pc); break;
        case 0x90: trace_opcode_90(opcode, opcode_pc); break; case 0x91: trace_opcode_91(opcode, opcode_pc); break; case 0x92: trace_opcode_92(opcode, opcode_pc); break; case 0x93: trace_opcode_93(opcode, opcode_pc); break; case 0x94: trace_opcode_94(opcode, opcode_pc); break; case 0x95: trace_opcode_95(opcode, opcode_pc); break; case 0x96: trace_opcode_96(opcode, opcode_pc); break; case 0x97: trace_opcode_97(opcode, opcode_pc); break; case 0x98: trace_opcode_98(opcode, opcode_pc); break; case 0x99: trace_opcode_99(opcode, opcode_pc); break; case 0x9A: trace_opcode_9A(opcode, opcode_pc); break; case 0x9B: trace_opcode_9B(opcode, opcode_pc); break; case 0x9C: trace_opcode_9C(opcode, opcode_pc); break; case 0x9D: trace_opcode_9D(opcode, opcode_pc); break; case 0x9E: trace_opcode_9E(opcode, opcode_pc); break; case 0x9F: trace_opcode_9F(opcode, opcode_pc); break;
        case 0xA0: trace_opcode_A0(opcode, opcode_pc); break; case 0xA1: trace_opcode_A1(opcode, opcode_pc); break; case 0xA2: trace_opcode_A2(opcode, opcode_pc); break; case 0xA3: trace_opcode_A3(opcode, opcode_pc); break; case 0xA4: trace_opcode_A4(opcode, opcode_pc); break; case 0xA5: trace_opcode_A5(opcode, opcode_pc); break; case 0xA6: trace_opcode_A6(opcode, opcode_pc); break; case 0xA7: trace_opcode_A7(opcode, opcode_pc); break; case 0xA8: trace_opcode_A8(opcode, opcode_pc); break; case 0xA9: trace_opcode_A9(opcode, opcode_pc); break; case 0xAA: trace_opcode_AA(opcode, opcode_pc); break; case 0xAB: trace_opcode_AB(opcode, opcode_pc); break; case 0xAC: trace_opcode_AC(opcode, opcode_pc); break; case 0xAD: trace_opcode_AD(opcode, opcode_pc); break; case 0xAE: trace_opcode_AE(opcode, opcode_pc); break; case 0xAF: trace_opcode_AF(opcode, opcode_pc); break;
        case 0xB0: trace_opcode_B0(opcode, opcode_pc); break; case 0xB1: trace_opcode_B1(opcode, opcode_pc); break; case 0xB2: trace_opcode_B2(opcode, opcode_pc); break; case 0xB3: trace_opcode_B3(opcode, opcode_pc); break; case 0xB4: trace_opcode_B4(opcode, opcode_pc); break; case 0xB5: trace_opcode_B5(opcode, opcode_pc); break; case 0xB6: trace_opcode_B6(opcode, opcode_pc); break; case 0xB7: trace_opcode_B7(opcode, opcode_pc); break; case 0xB8: trace_opcode_B8(opcode, opcode_pc); break; case 0xB9: trace_opcode_B9(opcode, opcode_pc); break; case 0xBA: trace_opcode_BA(opcode, opcode_pc); break; case 0xBB: trace_opcode_BB(opcode, opcode_pc); break; case 0xBC: trace_opcode_BC(opcode, opcode_pc); break; case 0xBD: trace_opcode_BD(opcode, opcode_pc); break; case 0xBE: trace_opcode_BE(opcode, opcode_pc); break; case 0xBF: trace_opcode_BF(opcode, opcode_pc); break;
        case 0xC0: trace_opcode_C0(opcode, opcode_pc); break; case 0xC1: trace_opcode_C1(opcode, opcode_pc); break; case 0xC2: trace_opcode_C2(opcode, opcode_pc); break; case 0xC3: trace_opcode_C3(opcode, opcode_pc); break; case 0xC4: trace_opcode_C4(opcode, opcode_pc); break; case 0xC5: trace_opcode_C5(opcode, opcode_pc); break; case 0xC6: trace_opcode_C6(opcode, opcode_pc); break; case 0xC7: trace_opcode_C7(opcode, opcode_pc); break; case 0xC8: trace_opcode_C8(opcode, opcode_pc); break; case 0xC9: trace_opcode_C9(opcode, opcode_pc); break; case 0xCA: trace_opcode_CA(opcode, opcode_pc); break; case 0xCB: trace_opcode_CB(opcode, opcode_pc); break; case 0xCC: trace_opcode_CC(opcode, opcode_pc); break; case 0xCD: trace_opcode_CD(opcode, opcode_pc); break; case 0xCE: trace_opcode_CE(opcode, opcode_pc); break; case 0xCF: trace_opcode_CF(opcode, opcode_pc); break;
        case 0xD0: trace_opcode_D0(opcode, opcode_pc); break; case 0xD1: trace_opcode_D1(opcode, opcode_pc); break; case 0xD2: trace_opcode_D2(opcode, opcode_pc); break; case 0xD3: trace_opcode_D3(opcode, opcode_pc); break; case 0xD4: trace_opcode_D4(opcode, opcode_pc); break; case 0xD5: trace_opcode_D5(opcode, opcode_pc); break; case 0xD6: trace_opcode_D6(opcode, opcode_pc); break; case 0xD7: trace_opcode_D7(opcode, opcode_pc); break; case 0xD8: trace_opcode_D8(opcode, opcode_pc); break; case 0xD9: trace_opcode_D9(opcode, opcode_pc); break; case 0xDA: trace_opcode_DA(opcode, opcode_pc); break; case 0xDB: trace_opcode_DB(opcode, opcode_pc); break; case 0xDC: trace_opcode_DC(opcode, opcode_pc); break; case 0xDD: trace_opcode_DD(opcode, opcode_pc); break; case 0xDE: trace_opcode_DE(opcode, opcode_pc); break; case 0xDF: trace_opcode_DF(opcode, opcode_pc); break;
        case 0xE0: trace_opcode_E0(opcode, opcode_pc); break; case 0xE1: trace_opcode_E1(opcode, opcode_pc); break; case 0xE2: trace_opcode_E2(opcode, opcode_pc); break; case 0xE3: trace_opcode_E3(opcode, opcode_pc); break; case 0xE4: trace_opcode_E4(opcode, opcode_pc); break; case 0xE5: trace_opcode_E5(opcode, opcode_pc); break; case 0xE6: trace_opcode_E6(opcode, opcode_pc); break; case 0xE7: trace_opcode_E7(opcode, opcode_pc); break; case 0xE8: trace_opcode_E8(opcode, opcode_pc); break; case 0xE9: trace_opcode_E9(opcode, opcode_pc); break; case 0xEA: trace_opcode_EA(opcode, opcode_pc); break; case 0xEB: trace_opcode_EB(opcode, opcode_pc); break; case 0xEC: trace_opcode_EC(opcode, opcode_pc); break; case 0xED: trace_opcode_ED(opcode, opcode_pc); break; case 0xEE: trace_opcode_EE(opcode, opcode_pc); break; case 0xEF: trace_opcode_EF(opcode, opcode_pc); break;
        case 0xF0: trace_opcode_F0(opcode, opcode_pc); break; case 0xF1: trace_opcode_F1(opcode, opcode_pc); break; case 0xF2: trace_opcode_F2(opcode, opcode_pc); break; case 0xF3: trace_opcode_F3(opcode, opcode_pc); break; case 0xF4: trace_opcode_F4(opcode, opcode_pc); break; case 0xF5: trace_opcode_F5(opcode, opcode_pc); break; case 0xF6: trace_opcode_F6(opcode, opcode_pc); break; case 0xF7: trace_opcode_F7(opcode, opcode_pc); break; case 0xF8: trace_opcode_F8(opcode, opcode_pc); break; case 0xF9: trace_opcode_F9(opcode, opcode_pc); break; case 0xFA: trace_opcode_FA(opcode, opcode_pc); break; case 0xFB: trace_opcode_FB(opcode, opcode_pc); break; case 0xFC: trace_opcode_FC(opcode, opcode_pc); break; case 0xFD: trace_opcode_FD(opcode, opcode_pc); break; case 0xFE: trace_opcode_FE(opcode, opcode_pc); break; case 0xFF: trace_opcode_FF(opcode, opcode_pc); break;
    }

    printf("\n");
    global_logger.set_newlines_enabled(true);
}

void CPU::trace_cb_opcode(const u8 opcode, u16 opcode_pc) {
    global_logger.set_newlines_enabled(false);
    log_trace("0x%04X | ", opcode_pc, opcode);

    switch (opcode) {
        case 0x00: trace_opcode_CB_00(opcode, opcode_pc); break; case 0x01: trace_opcode_CB_01(opcode, opcode_pc); break; case 0x02: trace_opcode_CB_02(opcode, opcode_pc); break; case 0x03: trace_opcode_CB_03(opcode, opcode_pc); break; case 0x04: trace_opcode_CB_04(opcode, opcode_pc); break; case 0x05: trace_opcode_CB_05(opcode, opcode_pc); break; case 0x06: trace_opcode_CB_06(opcode, opcode_pc); break; case 0x07: trace_opcode_CB_07(opcode, opcode_pc); break; case 0x08: trace_opcode_CB_08(opcode, opcode_pc); break; case 0x09: trace_opcode_CB_09(opcode, opcode_pc); break; case 0x0A: trace_opcode_CB_0A(opcode, opcode_pc); break; case 0x0B: trace_opcode_CB_0B(opcode, opcode_pc); break; case 0x0C: trace_opcode_CB_0C(opcode, opcode_pc); break; case 0x0D: trace_opcode_CB_0D(opcode, opcode_pc); break; case 0x0E: trace_opcode_CB_0E(opcode, opcode_pc); break; case 0x0F: trace_opcode_CB_0F(opcode, opcode_pc); break;
        case 0x10: trace_opcode_CB_10(opcode, opcode_pc); break; case 0x11: trace_opcode_CB_11(opcode, opcode_pc); break; case 0x12: trace_opcode_CB_12(opcode, opcode_pc); break; case 0x13: trace_opcode_CB_13(opcode, opcode_pc); break; case 0x14: trace_opcode_CB_14(opcode, opcode_pc); break; case 0x15: trace_opcode_CB_15(opcode, opcode_pc); break; case 0x16: trace_opcode_CB_16(opcode, opcode_pc); break; case 0x17: trace_opcode_CB_17(opcode, opcode_pc); break; case 0x18: trace_opcode_CB_18(opcode, opcode_pc); break; case 0x19: trace_opcode_CB_19(opcode, opcode_pc); break; case 0x1A: trace_opcode_CB_1A(opcode, opcode_pc); break; case 0x1B: trace_opcode_CB_1B(opcode, opcode_pc); break; case 0x1C: trace_opcode_CB_1C(opcode, opcode_pc); break; case 0x1D: trace_opcode_CB_1D(opcode, opcode_pc); break; case 0x1E: trace_opcode_CB_1E(opcode, opcode_pc); break; case 0x1F: trace_opcode_CB_1F(opcode, opcode_pc); break;
        case 0x20: trace_opcode_CB_20(opcode, opcode_pc); break; case 0x21: trace_opcode_CB_21(opcode, opcode_pc); break; case 0x22: trace_opcode_CB_22(opcode, opcode_pc); break; case 0x23: trace_opcode_CB_23(opcode, opcode_pc); break; case 0x24: trace_opcode_CB_24(opcode, opcode_pc); break; case 0x25: trace_opcode_CB_25(opcode, opcode_pc); break; case 0x26: trace_opcode_CB_26(opcode, opcode_pc); break; case 0x27: trace_opcode_CB_27(opcode, opcode_pc); break; case 0x28: trace_opcode_CB_28(opcode, opcode_pc); break; case 0x29: trace_opcode_CB_29(opcode, opcode_pc); break; case 0x2A: trace_opcode_CB_2A(opcode, opcode_pc); break; case 0x2B: trace_opcode_CB_2B(opcode, opcode_pc); break; case 0x2C: trace_opcode_CB_2C(opcode, opcode_pc); break; case 0x2D: trace_opcode_CB_2D(opcode, opcode_pc); break; case 0x2E: trace_opcode_CB_2E(opcode, opcode_pc); break; case 0x2F: trace_opcode_CB_2F(opcode, opcode_pc); break;
        case 0x30: trace_opcode_CB_30(opcode, opcode_pc); break; case 0x31: trace_opcode_CB_31(opcode, opcode_pc); break; case 0x32: trace_opcode_CB_32(opcode, opcode_pc); break; case 0x33: trace_opcode_CB_33(opcode, opcode_pc); break; case 0x34: trace_opcode_CB_34(opcode, opcode_pc); break; case 0x35: trace_opcode_CB_35(opcode, opcode_pc); break; case 0x36: trace_opcode_CB_36(opcode, opcode_pc); break; case 0x37: trace_opcode_CB_37(opcode, opcode_pc); break; case 0x38: trace_opcode_CB_38(opcode, opcode_pc); break; case 0x39: trace_opcode_CB_39(opcode, opcode_pc); break; case 0x3A: trace_opcode_CB_3A(opcode, opcode_pc); break; case 0x3B: trace_opcode_CB_3B(opcode, opcode_pc); break; case 0x3C: trace_opcode_CB_3C(opcode, opcode_pc); break; case 0x3D: trace_opcode_CB_3D(opcode, opcode_pc); break; case 0x3E: trace_opcode_CB_3E(opcode, opcode_pc); break; case 0x3F: trace_opcode_CB_3F(opcode, opcode_pc); break;
        case 0x40: trace_opcode_CB_40(opcode, opcode_pc); break; case 0x41: trace_opcode_CB_41(opcode, opcode_pc); break; case 0x42: trace_opcode_CB_42(opcode, opcode_pc); break; case 0x43: trace_opcode_CB_43(opcode, opcode_pc); break; case 0x44: trace_opcode_CB_44(opcode, opcode_pc); break; case 0x45: trace_opcode_CB_45(opcode, opcode_pc); break; case 0x46: trace_opcode_CB_46(opcode, opcode_pc); break; case 0x47: trace_opcode_CB_47(opcode, opcode_pc); break; case 0x48: trace_opcode_CB_48(opcode, opcode_pc); break; case 0x49: trace_opcode_CB_49(opcode, opcode_pc); break; case 0x4A: trace_opcode_CB_4A(opcode, opcode_pc); break; case 0x4B: trace_opcode_CB_4B(opcode, opcode_pc); break; case 0x4C: trace_opcode_CB_4C(opcode, opcode_pc); break; case 0x4D: trace_opcode_CB_4D(opcode, opcode_pc); break; case 0x4E: trace_opcode_CB_4E(opcode, opcode_pc); break; case 0x4F: trace_opcode_CB_4F(opcode, opcode_pc); break;
        case 0x50: trace_opcode_CB_50(opcode, opcode_pc); break; case 0x51: trace_opcode_CB_51(opcode, opcode_pc); break; case 0x52: trace_opcode_CB_52(opcode, opcode_pc); break; case 0x53: trace_opcode_CB_53(opcode, opcode_pc); break; case 0x54: trace_opcode_CB_54(opcode, opcode_pc); break; case 0x55: trace_opcode_CB_55(opcode, opcode_pc); break; case 0x56: trace_opcode_CB_56(opcode, opcode_pc); break; case 0x57: trace_opcode_CB_57(opcode, opcode_pc); break; case 0x58: trace_opcode_CB_58(opcode, opcode_pc); break; case 0x59: trace_opcode_CB_59(opcode, opcode_pc); break; case 0x5A: trace_opcode_CB_5A(opcode, opcode_pc); break; case 0x5B: trace_opcode_CB_5B(opcode, opcode_pc); break; case 0x5C: trace_opcode_CB_5C(opcode, opcode_pc); break; case 0x5D: trace_opcode_CB_5D(opcode, opcode_pc); break; case 0x5E: trace_opcode_CB_5E(opcode, opcode_pc); break; case 0x5F: trace_opcode_CB_5F(opcode, opcode_pc); break;
        case 0x60: trace_opcode_CB_60(opcode, opcode_pc); break; case 0x61: trace_opcode_CB_61(opcode, opcode_pc); break; case 0x62: trace_opcode_CB_62(opcode, opcode_pc); break; case 0x63: trace_opcode_CB_63(opcode, opcode_pc); break; case 0x64: trace_opcode_CB_64(opcode, opcode_pc); break; case 0x65: trace_opcode_CB_65(opcode, opcode_pc); break; case 0x66: trace_opcode_CB_66(opcode, opcode_pc); break; case 0x67: trace_opcode_CB_67(opcode, opcode_pc); break; case 0x68: trace_opcode_CB_68(opcode, opcode_pc); break; case 0x69: trace_opcode_CB_69(opcode, opcode_pc); break; case 0x6A: trace_opcode_CB_6A(opcode, opcode_pc); break; case 0x6B: trace_opcode_CB_6B(opcode, opcode_pc); break; case 0x6C: trace_opcode_CB_6C(opcode, opcode_pc); break; case 0x6D: trace_opcode_CB_6D(opcode, opcode_pc); break; case 0x6E: trace_opcode_CB_6E(opcode, opcode_pc); break; case 0x6F: trace_opcode_CB_6F(opcode, opcode_pc); break;
        case 0x70: trace_opcode_CB_70(opcode, opcode_pc); break; case 0x71: trace_opcode_CB_71(opcode, opcode_pc); break; case 0x72: trace_opcode_CB_72(opcode, opcode_pc); break; case 0x73: trace_opcode_CB_73(opcode, opcode_pc); break; case 0x74: trace_opcode_CB_74(opcode, opcode_pc); break; case 0x75: trace_opcode_CB_75(opcode, opcode_pc); break; case 0x76: trace_opcode_CB_76(opcode, opcode_pc); break; case 0x77: trace_opcode_CB_77(opcode, opcode_pc); break; case 0x78: trace_opcode_CB_78(opcode, opcode_pc); break; case 0x79: trace_opcode_CB_79(opcode, opcode_pc); break; case 0x7A: trace_opcode_CB_7A(opcode, opcode_pc); break; case 0x7B: trace_opcode_CB_7B(opcode, opcode_pc); break; case 0x7C: trace_opcode_CB_7C(opcode, opcode_pc); break; case 0x7D: trace_opcode_CB_7D(opcode, opcode_pc); break; case 0x7E: trace_opcode_CB_7E(opcode, opcode_pc); break; case 0x7F: trace_opcode_CB_7F(opcode, opcode_pc); break;
        case 0x80: trace_opcode_CB_80(opcode, opcode_pc); break; case 0x81: trace_opcode_CB_81(opcode, opcode_pc); break; case 0x82: trace_opcode_CB_82(opcode, opcode_pc); break; case 0x83: trace_opcode_CB_83(opcode, opcode_pc); break; case 0x84: trace_opcode_CB_84(opcode, opcode_pc); break; case 0x85: trace_opcode_CB_85(opcode, opcode_pc); break; case 0x86: trace_opcode_CB_86(opcode, opcode_pc); break; case 0x87: trace_opcode_CB_87(opcode, opcode_pc); break; case 0x88: trace_opcode_CB_88(opcode, opcode_pc); break; case 0x89: trace_opcode_CB_89(opcode, opcode_pc); break; case 0x8A: trace_opcode_CB_8A(opcode, opcode_pc); break; case 0x8B: trace_opcode_CB_8B(opcode, opcode_pc); break; case 0x8C: trace_opcode_CB_8C(opcode, opcode_pc); break; case 0x8D: trace_opcode_CB_8D(opcode, opcode_pc); break; case 0x8E: trace_opcode_CB_8E(opcode, opcode_pc); break; case 0x8F: trace_opcode_CB_8F(opcode, opcode_pc); break;
        case 0x90: trace_opcode_CB_90(opcode, opcode_pc); break; case 0x91: trace_opcode_CB_91(opcode, opcode_pc); break; case 0x92: trace_opcode_CB_92(opcode, opcode_pc); break; case 0x93: trace_opcode_CB_93(opcode, opcode_pc); break; case 0x94: trace_opcode_CB_94(opcode, opcode_pc); break; case 0x95: trace_opcode_CB_95(opcode, opcode_pc); break; case 0x96: trace_opcode_CB_96(opcode, opcode_pc); break; case 0x97: trace_opcode_CB_97(opcode, opcode_pc); break; case 0x98: trace_opcode_CB_98(opcode, opcode_pc); break; case 0x99: trace_opcode_CB_99(opcode, opcode_pc); break; case 0x9A: trace_opcode_CB_9A(opcode, opcode_pc); break; case 0x9B: trace_opcode_CB_9B(opcode, opcode_pc); break; case 0x9C: trace_opcode_CB_9C(opcode, opcode_pc); break; case 0x9D: trace_opcode_CB_9D(opcode, opcode_pc); break; case 0x9E: trace_opcode_CB_9E(opcode, opcode_pc); break; case 0x9F: trace_opcode_CB_9F(opcode, opcode_pc); break;
        case 0xA0: trace_opcode_CB_A0(opcode, opcode_pc); break; case 0xA1: trace_opcode_CB_A1(opcode, opcode_pc); break; case 0xA2: trace_opcode_CB_A2(opcode, opcode_pc); break; case 0xA3: trace_opcode_CB_A3(opcode, opcode_pc); break; case 0xA4: trace_opcode_CB_A4(opcode, opcode_pc); break; case 0xA5: trace_opcode_CB_A5(opcode, opcode_pc); break; case 0xA6: trace_opcode_CB_A6(opcode, opcode_pc); break; case 0xA7: trace_opcode_CB_A7(opcode, opcode_pc); break; case 0xA8: trace_opcode_CB_A8(opcode, opcode_pc); break; case 0xA9: trace_opcode_CB_A9(opcode, opcode_pc); break; case 0xAA: trace_opcode_CB_AA(opcode, opcode_pc); break; case 0xAB: trace_opcode_CB_AB(opcode, opcode_pc); break; case 0xAC: trace_opcode_CB_AC(opcode, opcode_pc); break; case 0xAD: trace_opcode_CB_AD(opcode, opcode_pc); break; case 0xAE: trace_opcode_CB_AE(opcode, opcode_pc); break; case 0xAF: trace_opcode_CB_AF(opcode, opcode_pc); break;
        case 0xB0: trace_opcode_CB_B0(opcode, opcode_pc); break; case 0xB1: trace_opcode_CB_B1(opcode, opcode_pc); break; case 0xB2: trace_opcode_CB_B2(opcode, opcode_pc); break; case 0xB3: trace_opcode_CB_B3(opcode, opcode_pc); break; case 0xB4: trace_opcode_CB_B4(opcode, opcode_pc); break; case 0xB5: trace_opcode_CB_B5(opcode, opcode_pc); break; case 0xB6: trace_opcode_CB_B6(opcode, opcode_pc); break; case 0xB7: trace_opcode_CB_B7(opcode, opcode_pc); break; case 0xB8: trace_opcode_CB_B8(opcode, opcode_pc); break; case 0xB9: trace_opcode_CB_B9(opcode, opcode_pc); break; case 0xBA: trace_opcode_CB_BA(opcode, opcode_pc); break; case 0xBB: trace_opcode_CB_BB(opcode, opcode_pc); break; case 0xBC: trace_opcode_CB_BC(opcode, opcode_pc); break; case 0xBD: trace_opcode_CB_BD(opcode, opcode_pc); break; case 0xBE: trace_opcode_CB_BE(opcode, opcode_pc); break; case 0xBF: trace_opcode_CB_BF(opcode, opcode_pc); break;
        case 0xC0: trace_opcode_CB_C0(opcode, opcode_pc); break; case 0xC1: trace_opcode_CB_C1(opcode, opcode_pc); break; case 0xC2: trace_opcode_CB_C2(opcode, opcode_pc); break; case 0xC3: trace_opcode_CB_C3(opcode, opcode_pc); break; case 0xC4: trace_opcode_CB_C4(opcode, opcode_pc); break; case 0xC5: trace_opcode_CB_C5(opcode, opcode_pc); break; case 0xC6: trace_opcode_CB_C6(opcode, opcode_pc); break; case 0xC7: trace_opcode_CB_C7(opcode, opcode_pc); break; case 0xC8: trace_opcode_CB_C8(opcode, opcode_pc); break; case 0xC9: trace_opcode_CB_C9(opcode, opcode_pc); break; case 0xCA: trace_opcode_CB_CA(opcode, opcode_pc); break; case 0xCB: trace_opcode_CB_CB(opcode, opcode_pc); break; case 0xCC: trace_opcode_CB_CC(opcode, opcode_pc); break; case 0xCD: trace_opcode_CB_CD(opcode, opcode_pc); break; case 0xCE: trace_opcode_CB_CE(opcode, opcode_pc); break; case 0xCF: trace_opcode_CB_CF(opcode, opcode_pc); break;
        case 0xD0: trace_opcode_CB_D0(opcode, opcode_pc); break; case 0xD1: trace_opcode_CB_D1(opcode, opcode_pc); break; case 0xD2: trace_opcode_CB_D2(opcode, opcode_pc); break; case 0xD3: trace_opcode_CB_D3(opcode, opcode_pc); break; case 0xD4: trace_opcode_CB_D4(opcode, opcode_pc); break; case 0xD5: trace_opcode_CB_D5(opcode, opcode_pc); break; case 0xD6: trace_opcode_CB_D6(opcode, opcode_pc); break; case 0xD7: trace_opcode_CB_D7(opcode, opcode_pc); break; case 0xD8: trace_opcode_CB_D8(opcode, opcode_pc); break; case 0xD9: trace_opcode_CB_D9(opcode, opcode_pc); break; case 0xDA: trace_opcode_CB_DA(opcode, opcode_pc); break; case 0xDB: trace_opcode_CB_DB(opcode, opcode_pc); break; case 0xDC: trace_opcode_CB_DC(opcode, opcode_pc); break; case 0xDD: trace_opcode_CB_DD(opcode, opcode_pc); break; case 0xDE: trace_opcode_CB_DE(opcode, opcode_pc); break; case 0xDF: trace_opcode_CB_DF(opcode, opcode_pc); break;
        case 0xE0: trace_opcode_CB_E0(opcode, opcode_pc); break; case 0xE1: trace_opcode_CB_E1(opcode, opcode_pc); break; case 0xE2: trace_opcode_CB_E2(opcode, opcode_pc); break; case 0xE3: trace_opcode_CB_E3(opcode, opcode_pc); break; case 0xE4: trace_opcode_CB_E4(opcode, opcode_pc); break; case 0xE5: trace_opcode_CB_E5(opcode, opcode_pc); break; case 0xE6: trace_opcode_CB_E6(opcode, opcode_pc); break; case 0xE7: trace_opcode_CB_E7(opcode, opcode_pc); break; case 0xE8: trace_opcode_CB_E8(opcode, opcode_pc); break; case 0xE9: trace_opcode_CB_E9(opcode, opcode_pc); break; case 0xEA: trace_opcode_CB_EA(opcode, opcode_pc); break; case 0xEB: trace_opcode_CB_EB(opcode, opcode_pc); break; case 0xEC: trace_opcode_CB_EC(opcode, opcode_pc); break; case 0xED: trace_opcode_CB_ED(opcode, opcode_pc); break; case 0xEE: trace_opcode_CB_EE(opcode, opcode_pc); break; case 0xEF: trace_opcode_CB_EF(opcode, opcode_pc); break;
        case 0xF0: trace_opcode_CB_F0(opcode, opcode_pc); break; case 0xF1: trace_opcode_CB_F1(opcode, opcode_pc); break; case 0xF2: trace_opcode_CB_F2(opcode, opcode_pc); break; case 0xF3: trace_opcode_CB_F3(opcode, opcode_pc); break; case 0xF4: trace_opcode_CB_F4(opcode, opcode_pc); break; case 0xF5: trace_opcode_CB_F5(opcode, opcode_pc); break; case 0xF6: trace_opcode_CB_F6(opcode, opcode_pc); break; case 0xF7: trace_opcode_CB_F7(opcode, opcode_pc); break; case 0xF8: trace_opcode_CB_F8(opcode, opcode_pc); break; case 0xF9: trace_opcode_CB_F9(opcode, opcode_pc); break; case 0xFA: trace_opcode_CB_FA(opcode, opcode_pc); break; case 0xFB: trace_opcode_CB_FB(opcode, opcode_pc); break; case 0xFC: trace_opcode_CB_FC(opcode, opcode_pc); break; case 0xFD: trace_opcode_CB_FD(opcode, opcode_pc); break; case 0xFE: trace_opcode_CB_FE(opcode, opcode_pc); break; case 0xFF: trace_opcode_CB_FF(opcode, opcode_pc); break;
    }

    printf("\n");
    global_logger.set_newlines_enabled(true);
}
