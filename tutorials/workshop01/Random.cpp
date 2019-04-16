//
// Created by Andrei Tatarnikov on 2019-04-14.
//

#include "Random.h"

#include <random>

int quickExp(int val, int pow)
{
    int res = 1;
    while (pow != 0)
    {
        if ((pow & 1) != 0)
            res *= val;
        val *= val;
        pow >>= 1;
    }
    return res;
}

Random::Random(int k)
{
    int limit = quickExp(10, k) - 1;
    dis = std::uniform_int_distribution<>{-limit, +limit};
}

int Random::next()
{
    return dis(gen);
}
