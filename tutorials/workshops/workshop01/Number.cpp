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
void copyDigits(ISrc begin, ISrc end, IDest dest)
{
    const ISrc nonZeroBegin = std::find_if(begin, end, [](auto x) { return x != 0; });
    while (end != nonZeroBegin)
    {
        *dest++ = *(--end);
    }
}

/**
 * Checks whether one of digit vector is larger than another.
 * If their length is equal, the highest digit is compared.
 */
bool isGreater(const Number::Digits& lhs, const Number::Digits& rhs)
{
    if (lhs.size() > rhs.size())
        return true;

    if (lhs.size() < rhs.size())
        return false;

    for (size_t index = lhs.size(); index > 0; --index)
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

/**
 * Adds two vectors of digits.
 */
Number::Digits add(const Number::Digits& lhs, const Number::Digits& rhs)
{
    if (lhs.size() < rhs.size())
        return add(rhs, lhs);

    const Number::Digits& src = rhs;
    Number::Digits       dest = lhs;

    for (size_t index = 0; index < src.size(); ++index)
        dest[index] += src[index];

    Number::Digit carry = 0;
    for (Number::Digit& digit : dest)
    {
        digit += carry;
        carry = 0;

        if (digit >= Number::DIGIT_LEN)
        {
            carry = 1;
            digit -= Number::DIGIT_LEN;
        }
    }

    if (carry != 0)
        dest.push_back(carry);

    return dest;
}

/**
 * Subtracts one digit vector from another. Requires that the first vector is larger.
 */
Number::Digits sub(const Number::Digits& lhs, const Number::Digits& rhs)
{
    const Number::Digits& src = rhs;
    Number::Digits       dest = lhs;

    for (size_t index = 0; index < src.size(); ++index)
        dest[index] -= src[index];

    Number::Digit carry = 0;
    for (Number::Digit& digit : dest)
    {
        digit -= carry;
        carry = 0;

        if (digit < 0)
        {
            carry = 1;
            digit += Number::DIGIT_LEN;
        }
    }

    return dest;
}

/**
 * Multiplies two vectors of digits.
 */
Number::Digits mul(const Number::Digits& lhs, const Number::Digits& rhs)
{
    if (lhs.size() < rhs.size())
        return mul(rhs, lhs);

    Number::Digits dest(lhs.size() + rhs.size());

    for (int i = 0; i < rhs.size(); ++i)
    {
        const Number::Digit digit1 = rhs[i];
        if (digit1 != 0)
        {
            for (int j = 0; j < lhs.size(); ++j)
            {
                Number::Digit digit2 = lhs[j];
                dest[j + i] += digit1 * digit2;
            }

            Number::Digit carry = 0;
            for (int k = i; k < dest.size(); ++k)
            {
                Number::Digit& digit = dest[k];

                digit += carry;
                carry = 0;

                if (digit >= Number::DIGIT_LEN)
                {
                    carry = digit / Number::DIGIT_LEN;
                    digit = digit % Number::DIGIT_LEN;
                }
            }
        }
    }

    return dest;
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

    if (length() == 0)
        _negative = false;
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

    if (length() == 0)
        _negative = false;
}

Number::Number()
    : _digits(),
      _negative(false)
{
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

Number::Digit Number::operator[](size_t index) const
{
    return _digits[index];
}

Number::Digit& Number::operator[](size_t index)
{
    return _digits[index];
}

bool Number::operator==(const Number& number) const
{
    return _negative == number._negative && _digits == number._digits;
}

Number Number::operator-() const
{
    Number number{*this};

    if (number.length() > 0)
        number._negative = !_negative;

    return number;
}

Number Number::operator<<(size_t shift)
{
    if (length() == 0)
        return *this;

    Digits digits(length() + shift);
    std::copy(_digits.begin(), _digits.end(), digits.begin() + shift);

    return Number{digits, isNegative()};
}

Number operator+(const Number& lhs, const Number& rhs)
{
    if (lhs.length() == 0)
        return rhs;

    if (rhs.length() == 0)
        return lhs;

    if (lhs.isNegative() == rhs.isNegative())
    {
        Number::Digits digits = add(lhs._digits, rhs._digits);
        return Number{digits, lhs.isNegative()};
    }

    if (isGreater(lhs._digits, rhs._digits))
    {
        Number::Digits digits = sub(lhs._digits, rhs._digits);
        return Number{digits, lhs.isNegative()};
    }
    else
    {
        Number::Digits digits = sub(rhs._digits, lhs._digits);
        return Number{digits, !lhs.isNegative()};
    }
}

Number operator-(const Number& lhs, const Number& rhs)
{
    if (lhs.length() == 0)
        return -rhs;

    if (rhs.length() == 0)
        return lhs;

    if (lhs.isNegative() != rhs.isNegative())
    {
        Number::Digits digits = add(lhs._digits, rhs._digits);
        return Number{digits, lhs.isNegative()};
    }

    if (isGreater(lhs._digits, rhs._digits))
    {
        Number::Digits digits = sub(lhs._digits, rhs._digits);
        return Number{digits, lhs.isNegative()};
    }
    else
    {
        Number::Digits digits = sub(rhs._digits, lhs._digits);
        return Number{digits, !lhs.isNegative()};
    }
}

Number operator*(const Number& lhs, const Number& rhs)
{
    if (lhs.length() == 0 || rhs.length() == 0)
        return Number{};

    Number::Digits digits = mul(rhs._digits, lhs._digits);
    return Number{digits, lhs.isNegative() != rhs.isNegative()};
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
