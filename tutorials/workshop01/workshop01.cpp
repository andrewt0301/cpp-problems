//
// Created by Andrei Tatarnikov on 2019-04-14.
//

#include <iostream>
#include <time>

#include "Random.h"
#include "Multiplicator.h"

int main()
{

    Random random{3};

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