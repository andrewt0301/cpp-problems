//
// Created by Tatarnikov_A on 17.04.2019.
//

#ifndef TUTORIALS_NUMBER_H
#define TUTORIALS_NUMBER_H

#include <initializer_list>
#include <iostream>
#include <vector>

class Number {
private:
    using Digits = std::vector<int>;
    using SizeType = std::vector<int>::size_type;
    using Initializer = std::initializer_list<int>;

    Digits _digits;

public:
    Number(Initializer digits);
    int operator[](SizeType index);
    SizeType length();

    friend std::ostream& operator<<(std::ostream& out, const Number& number);
};

#endif //TUTORIALS_NUMBER_H
