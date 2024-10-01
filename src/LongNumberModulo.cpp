#include "LongNumberModulo.h"

LongNumberModulo::LongNumberModulo(LongNumber& mod)
{
    modulo = mod;
    mu = calculateMu(mod);
    digit_length = modulo.digitLength();

}

LongNumber LongNumberModulo::add(LongNumber& first, LongNumber& second)
{
    LongNumber result = first + second;
    return barrett(result);
}

LongNumber LongNumberModulo::sub(LongNumber& first, LongNumber& second)
{
    LongNumber result;
    if (first < second) {
        result = second - first;
        result = barrett(result);
        result = modulo - result;
    }
    else {
        result = first - second;
        result = barrett(result);
    }
    return result;
}

LongNumber LongNumberModulo::mult(LongNumber& first, uint32_t& second)
{
    LongNumber result = first * second;

    return barrett(result);
}

LongNumber LongNumberModulo::mult(LongNumber& first, LongNumber& second)
{
    LongNumber result = first * second;
    std::cout << result << '\n';
    return barrett(result);
}

LongNumber LongNumberModulo::square(LongNumber& number)
{
    LongNumber result = number * number;
    return barrett(result);
}

LongNumber LongNumberModulo::power(LongNumber& number, LongNumber& power)
{
    LongNumber result(1);

    for (int i = power.bitLength() - 1; i >= 0; i--) {
        uint32_t bit = power.number_array[i / 32] >> i % 32;
        bit = bit & 1;
        if (bit == 1) {
            result = mult(number, result);
        }
        if (i > 0) {
            result = mult(result,result);
        }
    }
    return result;
}


LongNumber LongNumberModulo::barrett(LongNumber& number)
{
    if (number < modulo) {
        return number;
    }
    LongNumber q = number.rightDigitShift(digit_length - 1);
    q = q * mu;
    q = q.rightDigitShift(digit_length + 1);

    q = q * modulo;
    LongNumber r = number - q;

    while (r >= modulo) {
        r = r - modulo;
    }
    return r;
}

LongNumber LongNumberModulo::calculateMu(LongNumber& mod)
{
    int digit_length = mod.digitLength();
    LongNumber beta(1);
    beta = beta.leftDigitShift(digit_length * 2);
    return beta / mod;
}
