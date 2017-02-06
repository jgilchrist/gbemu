#pragma once

#include "definitions.h"

class ByteRegister : Noncopyable {
public:
    virtual ~ByteRegister() = default;

    virtual void set(const u8 new_value);
    void reset();
    u8 value() const;

    bool check_bit(u8 bit) const;
    void set_bit_to(u8 bit, bool set);

    void increment();
    void decrement();

    bool operator==(u8 other) const;

protected:
    u8 val;
};

class FlagRegister : public ByteRegister {
public:
    /* Specialise behaviour for the flag register 'f'.
     * (its lower nibble is always 0s */
    void set(const u8 new_value) override;

    void set_flag_zero(bool set);
    void set_flag_subtract(bool set);
    void set_flag_half_carry(bool set);
    void set_flag_carry(bool set);

    bool flag_zero() const;
    bool flag_subtract() const;
    bool flag_half_carry() const;
    bool flag_carry() const;

    u8 flag_zero_value() const;
    u8 flag_subtract_value() const;
    u8 flag_half_carry_value() const;
    u8 flag_carry_value() const;
};

class WordRegister : Noncopyable {
public:
    void set(const u16 new_value);
    u16 value() const;

    u8 low() const;
    u8 high() const;

    void increment();
    void decrement();

private:
    u16 val;
};

class RegisterPair : Noncopyable {
public:
    RegisterPair(ByteRegister& high, ByteRegister& low);

    void set(const u16 word);

    u8 low() const;
    u8 high() const;

    u16 value() const;

    void increment();
    void decrement();

private:
    ByteRegister& low_byte;
    ByteRegister& high_byte;
};
