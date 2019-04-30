//
// Created by Tatarnikov_A on 17.04.2019.
//

#include "Number.h"

#include <algorithm>
#include <iterator>

Number::Number(Initializer digits) : _digits{std::rbegin(digits), std::rend(digits)}
{
}

Number::Number(size_t length) : _digits(length, 0) {
}

size_t Number::length() const
{
    return _digits.size();
}

int Number::operator[](size_t index) const
{
    return _digits[index];
}

int& Number::operator[](size_t index)
{
    return _digits[index];
}

Number& Number::operator+=(const Number& number)
{
    const size_t len = std::min(length(), number.length());

    int carry = 0;
    size_t index = 0;

    for (; index < len; ++index)
    {
        int& digit = _digits[index];

        digit += (carry + number[index]);
        carry = digit / 10;
        digit %= 10;
    }

    if (index < length())
        // Adds overflow digit to the next digit.
        _digits[index] += carry;
    else
        // Returns overflow digit back to the last digit.
        _digits[index - 1] += 10 * carry;

    return *this;
}

void Number::shiftLeft()
{
    // TODO
}

std::ostream& operator<<(std::ostream& out, const Number& number)
{
    bool skipZeros = true;
    for (auto it = number._digits.crbegin(); it != number._digits.crend(); ++it)
    {
        int val = *it;
        if (skipZeros && val == 0)
            continue;

        out << val;
        skipZeros = false;
    }

    return out;
}
