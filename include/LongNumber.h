#pragma once
#include <iostream>
#include <stdint.h>
#include <string>

static const int NUMBER_LENGTH = 64;

class LongNumber {
public:
    uint32_t number_array[NUMBER_LENGTH];

    LongNumber();
    LongNumber(const LongNumber& other);
    LongNumber(const uint32_t number);
    LongNumber(const std::string hex);

    static LongNumber zero();
    static LongNumber one();

    LongNumber operator+(LongNumber& other) const;
    LongNumber operator-(LongNumber& other) const;

    LongNumber operator*(uint32_t integer) const;
    LongNumber operator*(LongNumber& other) const;

    LongNumber operator&(LongNumber& other) const;
    LongNumber operator|(LongNumber& other) const;
    LongNumber operator^(LongNumber& other) const;

    LongNumber operator/(LongNumber& other) const;
    LongNumber operator%(LongNumber& other) const;

    LongNumber power(LongNumber& other) const;

    int bitLength() const;
    int digitLength() const;

    LongNumber rightDigitShift(int shift) const;
    LongNumber leftDigitShift(int shift) const;

    LongNumber rightBitShift(int shift) const;
    LongNumber leftBitShift(int shift) const;

    bool operator<(LongNumber& other) const;
    bool operator>(LongNumber& other) const;
    bool operator<=(LongNumber& other) const;
    bool operator>=(LongNumber& other) const;

    bool operator==(LongNumber& other) const;
    bool operator!=(LongNumber& other) const;

    bool isZero() const;

    static LongNumber gcd(LongNumber& first, LongNumber& other);
    static LongNumber lcm(LongNumber& first, LongNumber& other);

    std::string toDecimal() const;
    std::string toHex() const;

    friend std::ostream& operator<<(std::ostream& os, const LongNumber& number);
};

LongNumber convertToNumber(std::string hex);
