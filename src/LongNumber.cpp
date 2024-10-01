#include "LongNumber.h"
#include <string>


LongNumber::LongNumber() {
	for (int i = 0; i < NUMBER_LENGTH; i++)
	{
		number_array[i] = 0;
	}
}

LongNumber::LongNumber(const LongNumber& other)
{
	for (int i = 0; i < NUMBER_LENGTH; i++)
	{
		number_array[i] = other.number_array[i];
	}
}

LongNumber::LongNumber(const uint32_t number)
{
	*this = LongNumber();
	number_array[0] = number;
}

LongNumber::LongNumber(const std::string hex)
{
	*this = convertToNumber(hex);
}

LongNumber LongNumber::zero()
{
	return LongNumber(0);
}

LongNumber LongNumber::one()
{
	return LongNumber(1);
}

LongNumber LongNumber::operator+(LongNumber& other) const
{
	LongNumber result;
	uint32_t carry = 0;

	for (int i = 0; i < NUMBER_LENGTH; i++)
	{
		uint64_t temp = static_cast<uint64_t>(this->number_array[i]) + other.number_array[i] + carry;
		result.number_array[i] = temp & UINT32_MAX;
		carry = temp >> 32;
	}
	return result;
}

LongNumber LongNumber::operator-(LongNumber& other) const
{
	LongNumber result;
	uint32_t borrow = 0;

	for (int i = 0; i < NUMBER_LENGTH; i++)
	{
		int64_t temp = static_cast<int64_t>(this->number_array[i]) - static_cast<int64_t>(other.number_array[i]) - borrow;
		if (temp >= 0) {
			result.number_array[i] = static_cast<uint32_t>(temp);
			borrow = 0;
		}
		else {
			result.number_array[i] = static_cast<uint32_t>(UINT32_MAX + temp + 1);
			borrow = 1;
		}
	}
	if (borrow == 1) {
		throw std::invalid_argument("number \n" + convertToHex(*this) + "\nsmaller than \n" + convertToHex(other));
	}
	return result;
}



LongNumber LongNumber::operator*(uint32_t other) const
{
	uint32_t carry = 0;
	LongNumber result;
	for (int i = 0; i < NUMBER_LENGTH; i++) {
		uint64_t temp = static_cast<uint64_t>(this->number_array[i]) * static_cast<uint64_t>(other) + static_cast<uint64_t>(carry);
		result.number_array[i] = static_cast<uint32_t>(temp & UINT32_MAX);
		carry = static_cast<uint32_t>(temp >> 32);
	}
	result.number_array[NUMBER_LENGTH - 1] = carry;
	return result;
}

LongNumber LongNumber::operator *(LongNumber& other) const
{
	LongNumber result;
	for (int i = 0; i < NUMBER_LENGTH; i++) {
		LongNumber temp = *this * other.number_array[i];
		temp = temp.leftDigitShift(i);
		result = result + temp;
	}
	return result;
}

LongNumber LongNumber::operator/(LongNumber& other) const
{
	int k = other.bitLength();
	LongNumber Q;
	LongNumber R(*this);
	while (R >= other) {
		int temp = R.bitLength();
		LongNumber C = other.leftBitShift(temp - k);
		if (R < C) {
			temp--;
			C = other.leftBitShift(temp - k);
		}
		R = R - C;
		LongNumber powerOfTwo(1);
		powerOfTwo = powerOfTwo.leftBitShift(temp - k);
		Q = Q + powerOfTwo;
	}
	return Q;
}

LongNumber LongNumber::operator%(LongNumber& other) const
{
	int k = other.bitLength();
	LongNumber Q;
	LongNumber R(*this);
	while (R >= other) {
		int temp = R.bitLength();
		LongNumber C = other.leftBitShift(temp - k);
		if (R < C) {
			temp--;
			C = other.leftBitShift(temp - k);
		}
		R = R - C;
		LongNumber power_of_two(1);
		power_of_two = power_of_two.leftBitShift(temp - k);
		Q = Q + power_of_two;
	}
	return R;
}

LongNumber LongNumber::power(LongNumber& other) const
{
	LongNumber result(1);

	for (int i = other.bitLength() - 1; i >= 0; i--) {
		uint32_t bit = other.number_array[i / 32] >> i % 32;
		bit = bit & 1;
		if (bit == 1) {
			result = *this * result;
		}
		if (i > 0) {
			result = result * result;
		}
	}
	return result;
}

int LongNumber::bitLength() const
{
	int digit = NUMBER_LENGTH - 1;
	while (this->number_array[digit] == 0) {
		digit--;
	}
	if (digit == -1) return 0;
	int bit_length = digit * 32;
	uint32_t temp = this->number_array[digit];
	while (temp != 0) {
		temp >>= 1;
		bit_length++;
	}
	return bit_length;
}

int LongNumber::digitLength() const
{
	for (int i = NUMBER_LENGTH - 1; i >= 0; i--) {
		if (number_array[i] != 0) {
			return i + 1;
		}
	}
	return 0;
}



bool LongNumber::operator<(LongNumber& other) const
{
	int i = NUMBER_LENGTH - 1;
	while (this->number_array[i] == other.number_array[i] && i >= 0) {
		i--;
	}
	if (i == -1) return false;
	return this->number_array[i] < other.number_array[i];
}

bool LongNumber::operator>(LongNumber& other) const
{
	int i = NUMBER_LENGTH - 1;
	while (this->number_array[i] == other.number_array[i] && i >= 0) {
		i--;
	}
	if (i == -1) return false;
	return this->number_array[i] > other.number_array[i];
}

bool LongNumber::operator<=(LongNumber& other) const
{
	return *this < other || *this == other;
}

bool LongNumber::operator>=(LongNumber& other) const
{
	return *this > other || *this == other;
}

bool LongNumber::operator==(LongNumber& other) const
{
	int i = NUMBER_LENGTH - 1;
	while (this->number_array[i] == other.number_array[i] && i >= 0) {
		i--;
	}
	return i == -1;
}

bool LongNumber::operator!=(LongNumber& other) const
{
	return !(*this == other);
}

bool LongNumber::isZero() const
{
    int i = NUMBER_LENGTH - 1;
	while (this->number_array[i] == 0) {
		i--;
	}
	return i == -1;
}

LongNumber LongNumber::gcd(LongNumber& first,LongNumber& second)
{
	LongNumber q, r = 0;
	LongNumber first_temp = first;
	LongNumber second_temp = second;

	LongNumber nul = zero();

	while (second_temp > nul) {
		q = first_temp / second_temp;
		LongNumber q_temp = q * second_temp;
		r = first_temp - q_temp;
		first_temp = second_temp;
		second_temp = r;
	}
	return first_temp;
}

LongNumber LongNumber::lcm(LongNumber& first,LongNumber& second)
{
	LongNumber a = (first * second);
	LongNumber b = gcd(first,second);
	return a / b;
}

LongNumber LongNumber::rightDigitShift(int shift) const
{
	LongNumber result;
	for (int i = NUMBER_LENGTH - 1; i >= shift; i--) {
		result.number_array[i - shift] = this->number_array[i];
	}
	return result;
}

LongNumber LongNumber::leftDigitShift(int shift) const
{
	LongNumber result;
	for (int i = 0; i < NUMBER_LENGTH - shift; i++) {
		result.number_array[i + shift] = this->number_array[i];
	}
	return result;
}

LongNumber LongNumber::leftBitShift(int shift) const
{
	int digit_shifts = shift / 32;
	int bit_shifts = shift % 32;
	uint32_t carry = 0;

	LongNumber temp(*this);
	LongNumber result;

	if (bit_shifts == 0) {
		for (int i = 0; i < NUMBER_LENGTH; i++)
		{
			temp.number_array[i] = this->number_array[i];
		}
		for (int j = digit_shifts; j < NUMBER_LENGTH; j++)
		{
			result.number_array[j] = temp.number_array[j - digit_shifts];
		}
	}
	else {
		for (int i = 0; i < NUMBER_LENGTH; i++) {
			temp.number_array[i] = (this->number_array[i] << shift) + carry;
			carry = (this->number_array[i] >> (32 - shift));
		}
		for (int j = digit_shifts; j < NUMBER_LENGTH; j++)
		{
			result.number_array[j] = temp.number_array[j - digit_shifts];
		}
	}
	return result;
}
LongNumber LongNumber::rightBitShift(int shift) const
{
	int digit_shifts = shift / 32;
	int bit_shifts = shift % 32;
	uint32_t carry = 0;

	LongNumber temp(*this);
	LongNumber result;

	if (bit_shifts == 0) {
		for (int i = 0; i < NUMBER_LENGTH; i++)
		{
			temp.number_array[i] = this->number_array[i];
		}
		for (int j = NUMBER_LENGTH - 1 - digit_shifts; j >= 0; j-- )
		{
			result.number_array[j] = temp.number_array[j - digit_shifts];
		}
	}
	else {
		for (int i = NUMBER_LENGTH - 1; i >= 0; i--) {
			temp.number_array[i] = (this->number_array[i] >> shift) + (carry << (32 - shift));
			carry = this->number_array[i] & static_cast<uint32_t>(bit_shifts);
		}

		for (int j = NUMBER_LENGTH - 1 - digit_shifts; j >= 0; j--)
		{
			result.number_array[j] = temp.number_array[j + digit_shifts];
		}
	}
	return result;
}


std::ostream& operator<<(std::ostream& os, const LongNumber& number)
{
	os << convertToHex(number);
	return os;
}

char convertDigitToHex(uint32_t digit)
{
	std::string hexs = "0123456789abcdef";
	return hexs[digit];
}

uint32_t convertHexToDigit(char hex)
{
	if (hex == '0') return 0;
	if (hex == '1') return 1;
	if (hex == '2') return 2;
	if (hex == '3') return 3;
	if (hex == '4') return 4;
	if (hex == '5') return 5;
	if (hex == '6') return 6;
	if (hex == '7') return 7;
	if (hex == '8') return 8;
	if (hex == '9') return 9;
	if (hex == 'A' || hex == 'a') return 10;
	if (hex == 'B' || hex == 'b') return 11;
	if (hex == 'C' || hex == 'c') return 12;
	if (hex == 'D' || hex == 'd') return 13;
	if (hex == 'E' || hex == 'e') return 14;
	if (hex == 'F' || hex == 'f') return 15;

	throw std::invalid_argument("Digit is incorrect");
}

LongNumber convertToNumber(std::string hex)
{
	LongNumber result;
	for (int i = 0; i < hex.length(); i++) {
		uint32_t modulo = i % 8;
		uint32_t digit = convertHexToDigit(hex[hex.length() - i - 1]);
		result.number_array[i/8] += digit * (1 << (4 * modulo));
	}
	return result;
}

std::string convertToHex(LongNumber number)
{
	std::string hex = "";
	for (int i = 0; i < NUMBER_LENGTH*8; i++) {
		uint32_t modulo = i % 8;
		hex += convertDigitToHex((number.number_array[i/8] >> (4 * modulo)) & 15);
	}
	hex = hex.erase(hex.find_last_not_of('0') + 1);
	std::string reverse_hex;
	for (int i = hex.length() - 1; i >= 0; i--) {
		reverse_hex += hex[i];
	}
	return reverse_hex;
}


std::string convertToDecimal(LongNumber number){
    auto ten = LongNumber(10);

    std::string result = "";
    do {
        result += ('0' + (number % ten).number_array[0]);
        number = number / ten;
    }
    while(!number.isZero());
   	std::string reverse_result;
	for (int i = result.length() - 1; i >= 0; i--) {
		reverse_result += result[i];
	}
	return reverse_result;
}
