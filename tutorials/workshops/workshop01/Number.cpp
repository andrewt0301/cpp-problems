//
// Created by Tatarnikov_A on 17.04.2019.
//

#include "Number.h"

#include <algorithm>
#include <iterator>

template <typename ISrc, typename IDest>
size_t copyDigits(ISrc begin, ISrc end, IDest dest)
{
    size_t nonZeroLenght = 0;

    for (ISrc it = begin; it != end; ++it)
    {
        auto digit = *it;
        *dest++ = digit;

        if (digit != 0 || nonZeroLenght != 0)
            nonZeroLenght++;
    }

    return nonZeroLenght;
}

Number::Number(std::initializer_list<Digit> digits)
    : _digits(new Digits(digits.size())),
      _start{0},
      _length(digits.size()),
      _nonZeroLength{0},
      _negative{false}
{
    _nonZeroLength = copyDigits(std::crbegin(digits), std::crend(digits), (*_digits).begin());
}

Number::Number(Digits digits)
    : _digits(new Digits(digits.size())),
      _start{0},
      _length(digits.size()),
      _nonZeroLength{0},
      _negative{false}
{
    _nonZeroLength = copyDigits(digits.begin(), digits.end(), (*_digits).begin());
}

Number::Number(size_t length)
    : _digits{new Digits(length, 0)},
      _start{0},
      _length{length},
      _nonZeroLength{0},
      _negative(false)
{
}

inline size_t Number::length() const
{
    return _length;
}

inline size_t Number::nonZeroLength() const
{
    return _nonZeroLength;
}

inline bool Number::isNegative() const
{
    return _negative;
}

Number::Digit Number::operator[](size_t index) const
{
    size_t i = _start + index;
    if (i > _length)
        throw std::out_of_range("Index out of bounds.");

    return (*_digits)[i];
}

Number::Digit& Number::operator[](size_t index)
{
    size_t i = _start + index;
    if (i > _length)
        throw std::out_of_range("Index out of bounds.");

    return (*_digits)[i];
}

Number Number::operator-() const
{
    Number number{*this};

    if (number.nonZeroLength() > 0)
        number._negative = !_negative;
    else
        number._negative = false;

    return number;
}

void add(Number& lhs, const Number& rhs)
{
    const size_t length = std::min(lhs.length(), rhs.nonZeroLength());

    int carry = 0;
    size_t index = 0;

    for (; index < length; ++index)
    {
        Number::Digit& digit = lhs[index];

        digit += (carry + rhs[index]);
        carry = digit / 10;
        digit %= 10;
    }

    if (index < lhs.length())
        // Adds overflow digit to the next digit.
        lhs[index] += carry;
    else
        // Returns overflow digit back to the last digit.
        lhs[index - 1] += 10 * carry;
}

Number& Number::operator+=(const Number& number)
{
    if (number.nonZeroLength() == 0)
    {
        // number == 0;
        return *this;
    }

    if (nonZeroLength() == 0) {
        // this == 0.
        *this = number;
    }
    else if (isNegative() == number.isNegative())
    {
        // this and number have equal sign.
        if (_digits.use_count() > 1)
            _digits = Number::DigitsPtr(new Digits(*_digits));

        add(*this, number);
    }
    else if (_digits.get() == number._digits.get())
    {
        // this == -number.
        *this = Number(length());
    }
    else if (!isNegative())
    {
        // this is positive, number is negative.
        add(*this, number);
    }
    else
    {
        // this is negative, number is positive.
        add(*this, number);
    }

    return *this;
}

Number& Number::operator-=(const Number& number)
{
    return *this += -number;
}

Number operator+(const Number& lhs, const Number& rhs)
{
    if (lhs.nonZeroLength() > rhs.nonZeroLength())
        return Number{lhs} += rhs;
    else
        return Number{rhs} += lhs;
}

Number operator-(const Number& lhs, const Number& rhs)
{
    return lhs + (-rhs);
}

std::ostream& operator<<(std::ostream& out, const Number& number)
{
    size_t length = number.nonZeroLength();

    if (length == 0) {
        out << '0';
        return out;
    }

    if (number.isNegative())
        out << '-';

    for (size_t i = length; i > 0; --i)
    {
        Number::Digit digit = number[i - 1];
        out << digit;
    }

    return out;
}
