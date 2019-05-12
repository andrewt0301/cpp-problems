//
// Created by Andrei Tatarnikov on 2019-04-14.
//

#ifndef TUTORIALS_MULTIPLICATOR_H
#define TUTORIALS_MULTIPLICATOR_H

#include "Number.h"

class Multiplicator {
public:
    static int gradeSchool(int x, int y);
    static int divideAndConquer(int x, int y);
    static int karatsuba(int x, int y);

    static Number gradeSchool(const Number& x, const Number& y);
    static Number divideAndConquer(const Number& x, const Number& y);
    static Number karatsuba(const Number& x, const Number& y);
};

#endif //TUTORIALS_MULTIPLICATOR_H
