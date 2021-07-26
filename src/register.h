#pragma once

#include "definitions.h"

class ByteRegister : Noncopyable {
public:
    ByteRegister() = default;
    virtual ~ByteRegister() = default;

    virtual void set(u8 new_value);
    void reset();
    auto value() const -> u8;

    auto check_bit(u8 bit) const -> bool;
    void set_bit_to(u8 bit, bool set);

    void increment();
    void decrement();

    auto operator==(u8 other) const -> bool;

protected:
    u8 val = 0x0;
};

class FlagRegister : public ByteRegister {
public:
    FlagRegister() = default;

    /* Specialise behaviour for the flag register 'f'.
     * (its lower nibble is always 0s */
    void set(u8 new_value) override;

    void set_flag_zero(bool set);
    void set_flag_subtract(bool set);
    void set_flag_half_carry(bool set);
    void set_flag_carry(bool set);

    auto flag_zero() const -> bool;
    auto flag_subtract() const -> bool;
    auto flag_half_carry() const -> bool;
    auto flag_carry() const -> bool;

    auto flag_zero_value() const -> u8;
    auto flag_subtract_value() const -> u8;
    auto flag_half_carry_value() const -> u8;
    auto flag_carry_value() const -> u8;
};

class WordValue : Noncopyable {
public:
    WordValue() = default;
    virtual ~WordValue() = default;

    virtual void set(u16 new_value) = 0;

    virtual auto value() const -> u16 = 0;

    virtual auto low() const -> u8 = 0;
    virtual auto high() const -> u8 = 0;
};

class WordRegister : public WordValue {
public:
    WordRegister() = default;

    void set(u16 new_value) override;

    auto value() const -> u16 override;

    auto low() const -> u8 override;
    auto high() const -> u8 override;

    void increment();
    void decrement();

private:
    u16 val = 0x0;
};

class RegisterPair : public WordValue {
public:
    RegisterPair(ByteRegister& high, ByteRegister& low);

    void set(u16 word) override;

    auto value() const -> u16 override;

    auto low() const -> u8 override;
    auto high() const -> u8 override;

    void increment();
    void decrement();

private:
    ByteRegister& low_byte;
    ByteRegister& high_byte;
};
