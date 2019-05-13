//
// Created by Tatarnikov_A on 17.04.2019.
//

#ifndef TUTORIALS_NUMBER_H
#define TUTORIALS_NUMBER_H

#include <initializer_list>
#include <iostream>
#include <vector>
#include <string>

/**
 * The Number class implements numbers that consist of an arbitrary number of digits.
 */
class Number {
public:
    /** Digits are stored using the int type. */
    using Digit = int8_t;

    /** Digits are stored in a vector. */
    using Digits = std::vector<Digit>;

    /** Digit length. */
    static constexpr Digit DIGIT_LEN = 10;

    /** Constructs a number from a list of digits. */
    Number(const std::initializer_list<Digit>& digits);

    /** Constructs a number from a vector of digits. */
    Number(Digits digits, bool negative);

    /** Constructs a number from a string. */
    Number(const std::string &str);

    /** Constructs an empty zero number. */
    Number();

    /** Returns the number of digits in the number. */
    inline size_t length() const { return _digits.size(); }

    /** Checks whether the number is negative. */
    inline bool isNegative() const { return _negative; }

    /** Splits a number into two equal parts. */
    std::pair<Number, Number> split() const;

    /** Returns a reference to a digit by its index. */
    Digit operator[](size_t index) const;

    /** Returns a digit by its index. Write access is private. */
    Digit& operator[](size_t index);

    /** Checks equality of two numbers. */
    bool operator==(const Number& number) const;

    /** Returns a negated copy of the current number. */
    Number operator-() const;

    /** Shifts the number to the left by the specified number of digits. */
    Number operator<<(size_t shift);

    /** Adds one number to another. */
    friend Number operator+(const Number& lhs, const Number& rhs);

    /** Subtracts one number from another. */
    friend Number operator-(const Number& lhs, const Number& rhs);

    /** Multiplies one number by another using the Grade School algorithm. */
    friend Number operator*(const Number& lhs, const Number& rhs);

private:
    /** Constructs an empty number with the specified size. */
    explicit Number(size_t length);

    /** Vector that stores digits. Digits are stored from low to high. */
    Digits _digits;

    /** Flag that shows that the number is negative or positive. */
    bool _negative;
};

/** Prints the number to an output stream. */
std::ostream& operator<<(std::ostream& out, const Number& number);

#endif //TUTORIALS_NUMBER_H
