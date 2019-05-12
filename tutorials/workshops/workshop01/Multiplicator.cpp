//
// Created by Andrei Tatarnikov on 2019-04-14.
//

#include "Multiplicator.h"

#include <algorithm>
#include <iostream>

inline void setSign(int& value, bool& isNeg)
{
    if (value < 0) {
        value = -value;
        isNeg = !isNeg;
    }
}

int gradeSchool(int x, int y)
{
    int res = 0;

    while (y != 0)
    {
        if ((y & 1) != 0)
        res += x;
        x <<= 1;
        y >>= 1;
    }

    return res;
}

int divideAndConquer(int x, int y, int size)
{
    if (x == 0 || y == 0)
        return 0;

    if (size == 1)
        return gradeSchool(x, y);

    const int newSize = size >> 1;
    const int mask = ~(~0 << newSize);

    int xl = x >> newSize;
    int xr = x & mask;

    int yl = y >> newSize;
    int yr = y & mask;

    int p1 = divideAndConquer(xl, yl, newSize);
    int p2 = divideAndConquer(xr, yr, newSize);
    int p3 = divideAndConquer(xl, yr, newSize);
    int p4 = divideAndConquer(xr, yl, newSize);

    return (p1 << size) + ((p3 + p4) << newSize) + p2;
}

int karatsuba(int x, int y, int size)
{
    if (x == 0 || y == 0)
        return 0;

    if (size == 1)
        return gradeSchool(x, y);

    const int newSize = size >> 1;
    const int mask = ~(~0 << newSize);

    int xl = x >> newSize;
    int xr = x & mask;

    int yl = y >> newSize;
    int yr = y & mask;

    int p1 = karatsuba(xl, yl, newSize);
    int p2 = karatsuba(xr, yr, newSize);

    int xs = xl + xr;
    int ys = yl + yr;

    int p3 = karatsuba(xs, ys, newSize);
    int z = p3 - p1 - p2;

    return (p1 << size) + (z << newSize) + p2;
}

int Multiplicator::gradeSchool(int x, int y)
{
    if (x == 0 || y == 0)
        return 0;

    bool isNeg = false;

    ::setSign(x, isNeg);
    ::setSign(y, isNeg);

    if (x < y)
        std::swap(x, y);

    int res = ::gradeSchool(x, y);
    return isNeg ? -res : res;
}

int Multiplicator::divideAndConquer(int x, int y)
{
    bool isNeg = false;

    ::setSign(x, isNeg);
    ::setSign(y, isNeg);

    int res = ::divideAndConquer(x, y, sizeof(int) * 8);
    return isNeg ? -res : res;
}

int Multiplicator::karatsuba(int x, int y)
{
    bool isNeg = false;

    ::setSign(x, isNeg);
    ::setSign(y, isNeg);

    int res = ::karatsuba(x, y, sizeof(int) * 8);
    return isNeg ? -res : res;
}

Number Multiplicator::gradeSchool(const Number& x, const Number& y)
{
    return x * y;
}

Number Multiplicator::divideAndConquer(const Number& x, const Number& y)
{
    if (x.length() < y.length())
        return divideAndConquer(y, x);

    if (y.length() == 0)
        return Number{};

    if (y.length() == 1)
        return x * y;

    std::pair<Number, Number> xSplit = x.split();
    std::pair<Number, Number> ySplit = y.split();

    Number& xl = xSplit.first;
    Number& xr = xSplit.second;
    size_t xs = x.length() - xl.length();

    Number& yl = ySplit.first;
    Number& yr = ySplit.second;
    size_t ys = y.length() - yl.length();

    Number p1 = divideAndConquer(xl, yl);
    Number p2 = divideAndConquer(xr, yr);
    Number p3 = divideAndConquer(xl, yr);
    Number p4 = divideAndConquer(xr, yl);

    return (p1 << (xs + ys)) + (p3 << xs) + (p4 << ys) + p2;
}

Number Multiplicator::karatsuba(const Number& x, const Number& y)
{
    // TODO:
    return Number{1,2,3};
}
