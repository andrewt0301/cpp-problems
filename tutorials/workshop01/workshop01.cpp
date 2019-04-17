//
// Created by Andrei Tatarnikov on 2019-04-14.
//

#include <ctime>
#include <iostream>
#include <vector>

#include "Number.h"
#include "Multiplicator.h"
#include "Random.h"

long diffclock(clock_t start, clock_t end)
{
    clock_t diff = end - start;
    long diffms = diff / (CLOCKS_PER_SEC / 1000);

    return diffms;
}

template <typename T>
long measure(const std::vector<int>& values, T func)
{
    clock_t start = clock();

    int result = 0;
    for (int value : values)
    {
        func(value);
    }

    clock_t end = clock();

    long time = diffclock(start, end);
    long average = time / values.size();

    return average;
}

struct Sample
{
    int  k;
    long ms1;
    long ms2;
    long ms3;
};

int main()
{
    Number number{1,2,3,4};

    const int MAX_K = 8;

    std::vector<Sample> samples(MAX_K);

    for (int k = 0; k < MAX_K; ++k)
    {
        Random random{k};

    }

    //std::cout << quickExp(10, 4) << std::endl;

    /*std::cout << random.next() << std::endl;
    std::cout << random.next() << std::endl;
    std::cout << random.next() << std::endl;
     */

    Multiplicator mul;
    //std::cout << mul.gradeSchool(15, 3) << std::endl;

    std::cout << mul.divideAndConquer(3, 2) << std::endl;
    std::cout << mul.divideAndConquer(15, 3) << std::endl;
    std::cout << mul.divideAndConquer(1, 1) << std::endl;
    std::cout << mul.divideAndConquer(2, 1) << std::endl;
    std::cout << mul.divideAndConquer(1, 2) << std::endl;
    std::cout << mul.divideAndConquer(3, 2) << std::endl;
    std::cout << mul.divideAndConquer(2, 4) << std::endl;
    std::cout << mul.divideAndConquer(16, 4) << std::endl;
    std::cout << mul.divideAndConquer(32, 2) << std::endl;
    std::cout << mul.divideAndConquer(3, 1) << std::endl;
    std::cout << mul.divideAndConquer(5, 7) << std::endl;
    std::cout << mul.divideAndConquer(-5, 7) << std::endl;
    std::cout << mul.divideAndConquer(11, 7) << std::endl;
    std::cout << "////////////////////////" << std::endl;

#define divideAndConquer karatsuba

    std::cout << mul.divideAndConquer(3, 2) << std::endl;
    std::cout << mul.divideAndConquer(15, 3) << std::endl;
    std::cout << mul.divideAndConquer(1, 1) << std::endl;
    std::cout << mul.divideAndConquer(2, 1) << std::endl;
    std::cout << mul.divideAndConquer(1, 2) << std::endl;
    std::cout << mul.divideAndConquer(3, 2) << std::endl;
    std::cout << mul.divideAndConquer(2, 4) << std::endl;
    std::cout << mul.divideAndConquer(16, 4) << std::endl;
    std::cout << mul.divideAndConquer(32, 2) << std::endl;
    std::cout << mul.divideAndConquer(3, 1) << std::endl;
    std::cout << mul.divideAndConquer(5, 7) << std::endl;
    std::cout << mul.divideAndConquer(-5, 7) << std::endl;
    std::cout << mul.divideAndConquer(11, 7) << std::endl;
#undef divideAndConquer

    //std::cout << (~(static_cast<unsigned int>(~0) << 3)) << std::endl;

    return 0;
}