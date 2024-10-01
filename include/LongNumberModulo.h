#pragma once
#include"LongNumber.h"

class LongNumberModulo {
private:
	LongNumber modulo;
	LongNumber mu;
	int digit_length;
public:
	LongNumberModulo(LongNumber& mod);

	LongNumber add(LongNumber& first, LongNumber& second);
	LongNumber sub(LongNumber& first, LongNumber& second);


	LongNumber mult(LongNumber& first, uint32_t& second);
	LongNumber mult(LongNumber& first, LongNumber& second);

	LongNumber square(LongNumber& number);

	LongNumber power(LongNumber& number, LongNumber& power);

	LongNumber barrett(LongNumber& number);
	LongNumber calculateMu(LongNumber& mod);
};
