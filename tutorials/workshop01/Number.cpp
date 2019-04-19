//
// Created by Tatarnikov_A on 17.04.2019.
//

#include "Number.h"

Number::Number(Initializer digist) : _digits(digist)
{
}

Number::SizeType Number::length()
{
    return _digits.size();
}

int Number::operator[](Number::SizeType index)
{
    return _digits[index];
}

void Number::add(const Number &number)
{
    // TODO
}

void Number::shiftLeft()
{
    // TODO
}

std::ostream& operator<<(std::ostream& out, const Number& number)
{
    for (int digit : number._digits)
        out << digit;
    return out;
}
