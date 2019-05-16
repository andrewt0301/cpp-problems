//
// Created by Tatarnikov_A on 17.04.2019.
//

#include "Number.h"

#include <algorithm>
#include <iterator>

/**
 * Copies digits starting from lower digits and skipping leading zeros (e.g. 001 is copied as 1).
 */
template <typename ISrc, typename IDest>
size_t copyDigits(ISrc begin, ISrc end, IDest dest)
{
    size_t copied = 0;

    const ISrc nonZeroBegin = std::find_if(begin, end, [](auto x) { return x != 0; });
    while (end != nonZeroBegin)
    {
        *dest++ = *(--end);
        copied++;
    }

    return copied;
}

Number::Number(const std::initializer_list<Digit>& digits)
    : _digits(),
      _negative{false}
{
    _digits.reserve(digits.size());
    copyDigits(digits.begin(), digits.end(), std::back_inserter(_digits));
}

Number::Number(Digits digits, bool negative)
    : _digits(),
      _negative{negative}
{
    _digits.reserve(digits.size());
    copyDigits(digits.rbegin(), digits.rend(), std::back_inserter(_digits));
}

Number::Number(const std::string &str)
    : _digits(),
      _negative{false}
{
    if (str.empty())
        return;

    size_t skip = 0;

    for (; skip < str.length() && str[skip] == '-'; ++skip)
        _negative = !_negative;

    for (; skip < str.length() && str[skip] == '0'; ++skip)
        ;

    _digits.reserve(str.length() - skip);
    for (size_t index = str.length(); index > skip; --index)
    {
        char ch = str[index - 1];
        if ('0' <= ch && ch <= '9')
            _digits.push_back(ch - '0');
    }
}

Number::Number()
    : _digits(),
      _negative(false)
{
}

Number::Number(const Number& number, size_t grow)
    : _digits(number.length() + grow),
      _negative{number.isNegative()}
{
    for (size_t i = 0; i < number.length(); ++i)
        (*this)[i] = number[i];
}

Number::Number(size_t length, bool negative)
   : _digits(length),
     _negative{negative}
{
}

Number::Digit& Number::operator[](size_t index)
{
    return _digits[index];
}

Number::Digit Number::operator[](size_t index) const
{
    return _digits[index];
}

std::pair<Number, Number> Number::split() const
{
    size_t loLength = length() / 2;

    Number lo;
    copyDigits(_digits.rbegin() + loLength, _digits.rend(), std::back_inserter(lo._digits));

    if (lo.length() > 0)
        lo._negative = _negative;

    Number hi;
    copyDigits(_digits.rbegin(), _digits.rbegin() + loLength, std::back_inserter(hi._digits));

    if (hi.length() > 0)
        hi._negative = _negative;

    return {hi, lo};
}

bool Number::operator==(const Number& number) const
{
    return isNegative() == number.isNegative() && _digits == number._digits;
}

Number Number::operator-() const
{
    Number number{*this};
    number._negative = !_negative;
    return number;
}

Number Number::operator<<(size_t shift)
{
    if (length() == 0)
        return *this;

    Number number(length() + shift, isNegative());

    for (size_t i = 0; i < length(); ++i)
        number[i + shift] = (*this)[i];

    return number;
}

Number operator+(const Number& lhs, const Number& rhs)
{
    if (lhs.length() == 0)
        return rhs;

    if (rhs.length() == 0)
        return lhs;

    if (lhs.isNegative() == rhs.isNegative())
        return add(lhs, rhs);

    if (isGreaterUnsigned(lhs, rhs))
        return sub(lhs, rhs);
    else
        return -sub(rhs, lhs);
}

Number operator-(const Number& lhs, const Number& rhs)
{
    if (lhs.length() == 0)
        return -rhs;

    if (rhs.length() == 0)
        return lhs;

    if (lhs.isNegative() != rhs.isNegative())
        return add(lhs, rhs);

    if (isGreaterUnsigned(lhs, rhs))
        return sub(lhs, rhs);
    else
        return -sub(rhs, lhs);
}

Number operator*(const Number& lhs, const Number& rhs)
{
    if (lhs.length() == 0 || rhs.length() == 0)
        return Number{};

    if (lhs.length() < rhs.length())
        return mul(rhs, lhs);
    else
        return mul(lhs, rhs);
}

void Number::shrink(size_t delta)
{
    if (delta < length())
        _digits.resize(length() - delta);
}

Number add(const Number& lhs, const Number& rhs)
{
    if (lhs.length() < rhs.length())
        return add(rhs, lhs);

    const Number& src{rhs};
    Number       dest{lhs, 1};

    for (size_t index = 0; index < src.length(); ++index)
        dest[index] += src[index];

    Number::Digit carry = 0;
    size_t zeroDigits = 0;

    for (size_t index = 0; index < dest.length(); ++index)
    {
        Number::Digit& digit = dest[index];

        digit += carry;
        carry = 0;

        if (digit >= Number::DIGIT_LEN)
        {
            carry = 1;
            digit -= Number::DIGIT_LEN;
        }

        if (digit == 0)
            zeroDigits++;
        else
            zeroDigits = 0;
    }

    // Deletes zeros from the high part if there are any.
    if (zeroDigits > 0)
        dest.shrink(zeroDigits);

    return dest;
}

Number sub(const Number& lhs, const Number& rhs)
{
    const Number& src = rhs;
    Number       dest = lhs;

    for (size_t index = 0; index < src.length(); ++index)
        dest[index] -= src[index];

    Number::Digit carry = 0;
    size_t zeroDigits = 0;

    for (size_t index = 0; index < dest.length(); ++index)
    {
        Number::Digit& digit = dest[index];

        digit -= carry;
        carry = 0;

        if (digit < 0)
        {
            carry = 1;
            digit += Number::DIGIT_LEN;
        }

        if (digit == 0)
            zeroDigits++;
        else
            zeroDigits = 0;
    }

    // Deletes zeros from the high part if there are any.
    if (zeroDigits > 0)
        dest.shrink(zeroDigits);

    return dest;
}

Number mul(const Number& lhs, const Number& rhs)
{
    Number dest(lhs.length() + rhs.length(), lhs.isNegative() != rhs.isNegative());
    size_t zeroDigits = 0;

    for (int i = 0; i < rhs.length(); ++i)
    {
        const Number::Digit digit1 = rhs[i];
        if (digit1 != 0)
        {
            for (int j = 0; j < lhs.length(); ++j)
            {
                Number::Digit digit2 = lhs[j];
                dest[j + i] += digit1 * digit2;
            }

            Number::Digit carry = 0;
            for (int k = i; k < dest.length(); ++k)
            {
                Number::Digit& digit = dest[k];

                digit += carry;
                carry = 0;

                if (digit >= Number::DIGIT_LEN)
                {
                    carry = digit / Number::DIGIT_LEN;
                    digit = digit % Number::DIGIT_LEN;
                }

                if (digit == 0)
                    zeroDigits++;
                else
                    zeroDigits = 0;
            }
        }
    }

    // Deletes zeros from the high part if there are any.
    if (zeroDigits > 0)
        dest.shrink(zeroDigits);

    return dest;
}

std::ostream& operator<<(std::ostream& out, const Number& number)
{
    size_t length = number.length();

    if (length == 0) {
        out << '0';
        return out;
    }

    if (number.isNegative())
        out << '-';

    for (size_t i = length; i > 0; --i)
        out << static_cast<int64_t>(number[i - 1]);

    return out;
}

bool isGreaterUnsigned(const Number &lhs, const Number &rhs)
{
    if (lhs.length() > rhs.length())
        return true;

    if (lhs.length() < rhs.length())
        return false;

    for (size_t index = lhs.length(); index > 0; --index)
    {
        Number::Digit dlhs = lhs[index - 1];
        Number::Digit drhs = rhs[index - 1];

        if (dlhs > drhs)
            return true;

        if (dlhs < drhs)
            return false;
    }

    return false;
}
