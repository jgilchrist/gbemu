#include "cpu.h"
#include "opcode_names.h"
#include "opcode_format_strings.h"
#include "../util/bitwise.h"

using bitwise::compose_bytes;

/* clang-format off */

void CPU::trace_opcode_00(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_01(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_02(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_03(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_04(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_05(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_06(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_07(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_08(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_09(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_0A(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_0B(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_0C(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_0D(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_0E(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_0F(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_10(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_11(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_12(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_13(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_14(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_15(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_16(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_17(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_18(u8 opcode, u16 opcode_pc) {
    auto operand = peek_signed_byte_from_pc();
    printf(opcode_format_strings[opcode].c_str(), operand);
}
 
void CPU::trace_opcode_19(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_1A(u8 opcode, u16 opcode_pc) {
    auto operand = mmu.read(opcode_pc + 1);
    printf(opcode_format_strings[opcode].c_str(), operand);
}

void CPU::trace_opcode_1B(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_1C(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_1D(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_1E(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_1F(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_20(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_21(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_22(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_23(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_24(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_25(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_26(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_27(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_28(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_29(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_2A(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_2B(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_2C(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_2D(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_2E(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_2F(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_30(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_31(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_32(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_33(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_34(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_35(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_36(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_37(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_38(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_39(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_3A(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_3B(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_3C(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_3D(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_3E(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_3F(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_40(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_41(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_42(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_43(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_44(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_45(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_46(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_47(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_48(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_49(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_4A(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_4B(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_4C(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_4D(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_4E(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_4F(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_50(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_51(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_52(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_53(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_54(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_55(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_56(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_57(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_58(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_59(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_5A(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_5B(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_5C(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_5D(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_5E(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_5F(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_60(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_61(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_62(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_63(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_64(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_65(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_66(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_67(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_68(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_69(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_6A(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_6B(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_6C(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_6D(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_6E(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_6F(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_70(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_71(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_72(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_73(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_74(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_75(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_76(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_77(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_78(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_79(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_7A(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_7B(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_7C(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_7D(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_7E(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_7F(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_80(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_81(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_82(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_83(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_84(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_85(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_86(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_87(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_88(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_89(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_8A(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_8B(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_8C(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_8D(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_8E(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_8F(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_90(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_91(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_92(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_93(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_94(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_95(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_96(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_97(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_98(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_99(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_9A(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_9B(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_9C(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_9D(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_9E(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_9F(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_A0(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_A1(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_A2(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_A3(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_A4(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_A5(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_A6(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_A7(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_A8(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_A9(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_AA(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_AB(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_AC(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_AD(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_AE(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_AF(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_B0(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_B1(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_B2(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_B3(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_B4(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_B5(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_B6(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_B7(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_B8(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_B9(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_BA(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_BB(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_BC(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_BD(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_BE(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_BF(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_C0(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_C1(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_C2(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_C3(u8 opcode, u16 opcode_pc) {
    auto jump_loc = peek_word_from_pc();
    printf(opcode_format_strings[opcode].c_str(), jump_loc);
}

void CPU::trace_opcode_C4(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_C5(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_C6(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_C7(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_C8(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_C9(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CA(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB(u8 opcode, u16 opcode_pc) { /* External Ops */ 
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CC(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CD(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CE(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CF(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_D0(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_D1(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_D2(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_D3(u8 opcode, u16 opcode_pc) { /* Undefined */ 
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_D4(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_D5(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_D6(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_D7(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_D8(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_D9(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_DA(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_DB(u8 opcode, u16 opcode_pc) { /* Undefined */ 
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_DC(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_DD(u8 opcode, u16 opcode_pc) { /* Undefined */ 
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_DE(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_DF(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_E0(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_E1(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_E2(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_E3(u8 opcode, u16 opcode_pc) { /* Undefined */ 
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_E4(u8 opcode, u16 opcode_pc) { /* Undefined */ 
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_E5(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_E6(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_E7(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_E8(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_E9(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_EA(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_EB(u8 opcode, u16 opcode_pc) { /* Undefined */ 
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_EC(u8 opcode, u16 opcode_pc) { /* Undefined */ 
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_ED(u8 opcode, u16 opcode_pc) { /* Undefined */ 
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_EE(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_EF(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_F0(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_F1(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_F2(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_F3(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_F4(u8 opcode, u16 opcode_pc) { /* Undefined */ 
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_F5(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_F6(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_F7(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_F8(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_F9(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_FA(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_FB(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_FC(u8 opcode, u16 opcode_pc) { /* Undefined */ 
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_FD(u8 opcode, u16 opcode_pc) { /* Undefined */ 
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_FE(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}

void CPU::trace_opcode_FF(u8 opcode, u16 opcode_pc) {
    // printf(opcode_format_strings[opcode].c_str());
}


/**
 * This section contains two-byte opcodes, which are triggered when prefixed with
 * the CB trace_instruction above.
 */

void CPU::trace_opcode_CB_00(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_01(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_02(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_03(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_04(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_05(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_06(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_07(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_08(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_09(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_0A(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_0B(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_0C(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_0D(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_0E(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_0F(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_10(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_11(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_12(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_13(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_14(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_15(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_16(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_17(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_18(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_19(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_1A(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_1B(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_1C(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_1D(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_1E(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_1F(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_20(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_21(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_22(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_23(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_24(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_25(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_26(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_27(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_28(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_29(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_2A(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_2B(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_2C(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_2D(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_2E(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_2F(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_30(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_31(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_32(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_33(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_34(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_35(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_36(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_37(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_38(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_39(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_3A(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_3B(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_3C(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_3D(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_3E(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_3F(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_40(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_41(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_42(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_43(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_44(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_45(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_46(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_47(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_48(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_49(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_4A(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_4B(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_4C(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_4D(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_4E(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_4F(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_50(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_51(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_52(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_53(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_54(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_55(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_56(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_57(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_58(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_59(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_5A(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_5B(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_5C(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_5D(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_5E(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_5F(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_60(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_61(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_62(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_63(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_64(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_65(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_66(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_67(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_68(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_69(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_6A(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_6B(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_6C(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_6D(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_6E(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_6F(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_70(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_71(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_72(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_73(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_74(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_75(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_76(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_77(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_78(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_79(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_7A(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_7B(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_7C(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_7D(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_7E(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_7F(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_80(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_81(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_82(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_83(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_84(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_85(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_86(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_87(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_88(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_89(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_8A(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_8B(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_8C(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_8D(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_8E(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_8F(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_90(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_91(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_92(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_93(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_94(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_95(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_96(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_97(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_98(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_99(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_9A(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_9B(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_9C(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_9D(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_9E(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_9F(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_A0(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_A1(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_A2(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_A3(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_A4(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_A5(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_A6(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_A7(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_A8(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_A9(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_AA(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_AB(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_AC(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_AD(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_AE(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_AF(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_B0(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_B1(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_B2(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_B3(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_B4(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_B5(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_B6(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_B7(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_B8(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_B9(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_BA(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_BB(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_BC(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_BD(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_BE(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_BF(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_C0(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_C1(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_C2(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_C3(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_C4(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_C5(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_C6(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_C7(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_C8(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_C9(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_CA(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_CB(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_CC(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_CD(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_CE(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_CF(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_D0(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_D1(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_D2(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_D3(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_D4(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_D5(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_D6(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_D7(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_D8(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_D9(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_DA(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_DB(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_DC(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_DD(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_DE(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_DF(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_E0(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_E1(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_E2(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_E3(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_E4(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_E5(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_E6(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_E7(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_E8(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_E9(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_EA(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_EB(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_EC(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_ED(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_EE(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_EF(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_F0(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_F1(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_F2(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_F3(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_F4(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_F5(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_F6(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_F7(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_F8(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_F9(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_FA(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_FB(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_FC(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_FD(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_FE(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}

void CPU::trace_opcode_CB_FF(u8 opcode, u16 opcode_pc) {
    printf(opcode_cb_format_strings[opcode].c_str());
}
