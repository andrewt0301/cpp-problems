//
// Created by Andrei Tatarnikov on 2019-04-14.
//

#include "Random.h"

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

Random::Random(int start, int end)
{
    dis = std::uniform_int_distribution<>{start, end};
}

Random::Random(int k)
{
    int limit = quickExp(10, k) - 1;
    dis = std::uniform_int_distribution<>{0, limit};
}

int Random::next()
{
    return dis(gen);
}

std::vector<int> randomVector(Random& random, size_t length)
{
    std::vector<int> result(length);

    for (int& v : result)
        v = random.next();

    return result;
}
