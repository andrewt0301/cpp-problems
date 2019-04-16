//
// Created by Tatarnikov_A on 17.04.2019.
//

#include "Number.h"

Number::Number(Initializer digist) : _digits(digist)
{
}

int Number::operator[](Number::SizeType index)
{
    return _digits[index];
}

Number::SizeType Number::length()
{
    return _digits.size();
}

std::ostream& operator<<(std::ostream& out, const Number& number)
{
    return out;
}