//
// Created by Andrei Tatarnikov on 2019-04-14.
//

#ifndef TUTORIALS_MULTIPLICATOR_H
#define TUTORIALS_MULTIPLICATOR_H

#include "Number.h"

class Multiplicator {
public:
    int gradeSchool(int x, int y);
    int divideAndConquer(int x, int y);
    int karatsuba(int x, int y);

    Number gradeSchool(const Number& x, const Number& y);
    Number divideAndConquer(const Number& x, const Number& y);
    Number karatsuba(const Number& x, const Number& y);
};

#endif //TUTORIALS_MULTIPLICATOR_H
