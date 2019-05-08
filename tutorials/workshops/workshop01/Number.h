//
// Created by Tatarnikov_A on 17.04.2019.
//

#ifndef TUTORIALS_NUMBER_H
#define TUTORIALS_NUMBER_H

#include <initializer_list>
#include <iostream>
#include <memory>
#include <vector>

/**
 * The Number class implements numbers that consist of an arbitrary number of digits.
 */
class Number {
public:
    /** Digits are stored using the int type. */
    using Digit = int;

    /** Digits are stored in a vector. */
    using Digits = std::vector<Digit>;

    /** Vector of digits is stored in a shared pointer to apply the copy-on-write strategy. */
    using DigitsPtr = std::shared_ptr<Digits>;

    /** Constructs a number from a list of digits. */
    Number(std::initializer_list<Digit> digits);

    /** Constructs a number from a vector of digits. */
    explicit Number(Digits digits);

    /** Constructs a number of the specified number of digits. All digits are equal to 0. */
    explicit Number(size_t length);

    /** Returns the number of digits in the number. */
    inline size_t length() const;

    /** Returns the number of digits excluding zeros in high positions. */
    inline size_t nonZeroLength() const;

    /** Checks whether the number is negative. */
    inline bool isNegative() const;

    /** Returns a reference to a digit by its index. */
    Digit operator[](size_t index) const;

    /** Returns a digit by its index. Write access is private. */
    Digit& operator[](size_t index);

    /** Splits a number into two equal parts. */
    std::pair<Number, Number> split() const;

    /** Returns a negated copy of the current number. */
    Number operator-() const;

    /** Adds a number to the current number. */
    Number& operator+=(const Number& number);

    /** Subtracts a number from the current number. */
    Number& operator-=(const Number& number);

private:

    /** Vector that stores digits. */
    DigitsPtr _digits;

    /** Start position in the vector. */
    size_t _start;

    /** The number of digits. */
    size_t _length;

    /** The number of digits excluding zeros in high positions. */
    size_t _nonZeroLength;

    /** Flag that shows that the number is negative or positive. */
    bool _negative;
};

/** Adds one number to another. */
Number operator+(const Number& lhs, const Number& rhs);

/** Subtracts one number from another. */
Number operator-(const Number& lhs, const Number& rhs);

/** Prints the number to an output stream. */
std::ostream& operator<<(std::ostream& out, const Number& number);

#endif //TUTORIALS_NUMBER_H
