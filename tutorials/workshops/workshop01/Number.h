//
// Created by Tatarnikov_A on 17.04.2019.
//

#ifndef TUTORIALS_NUMBER_H
#define TUTORIALS_NUMBER_H

#include <initializer_list>
#include <iostream>
#include <vector>

/**
 * The Number class implements numbers that consist of an arbitrary number of digits.
 */
class Number {
private:
    using Digits = std::vector<int>;
    using Initializer = std::initializer_list<int>;

    Digits _digits;
public:
    /** Creates a number from a list of digits. */
    Number(Initializer digits);

    /** Creates a number of the specified number of digits. All digits are equal to 0. */
    explicit Number(size_t length);

    /** Creates a copy of the specified number. */
    Number(const Number& number);

    /** Returns the number of digits in the number. */
    size_t length() const;

    /** Returns a reference to a digit by its index. */
    int operator[](size_t index) const;

    /** Returns a digit by its index. */
    int& operator[](size_t index);

    /** Adds a number to the current number. */
    Number& operator+=(const Number& number);

    /** Adds two numbers. */
    friend Number operator+(const Number& lhs, const Number& rhs);

    /** Prints the number to a stream. */
    friend std::ostream& operator<<(std::ostream& out, const Number& number);
};

#endif //TUTORIALS_NUMBER_H
