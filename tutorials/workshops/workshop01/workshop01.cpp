//
// Created by Andrei Tatarnikov on 2019-04-14.
//

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include "../CSV.h"
#include "../Random.h"
#include "../Time.h"

#include "Number.h"
#include "NumberTests.h"

#include "Multiplicator.h"
#include "MultiplicatorTests.h"

using std::cout;
using std::endl;

using NumberVector = std::vector<Number>;

Number randomNumber(Random& random, size_t length)
{
    std::vector<int> data = randomVector(random, length);
    Number::Digits digits(length);

    for (size_t i = 0; i < length; ++i)
        digits[i] = data[i];

    return Number{digits, random.next() % 2 == 0};
}

NumberVector randomNumberVector(Random& random, size_t length, size_t count)
{
    NumberVector numbers{count};

    for (Number& number : numbers)
        number = randomNumber(random, length);

    return numbers;
}

int main()
{
    // Check than the implementation is correct.
    runNumberTests();
    runMultiplicatorTests();

    // Here hold our performance measures.
    Samples<long> samples;

    // This Random generates digits.
    Random random{1};

    for (size_t length = 1; length <= 2048; length *= 2)
    {
        const NumberVector testData = randomNumberVector(random, length, 5 * 2);

        long gradeSchoolTime = calcExecTime([&testData]()
        {
            for (size_t index = 0; index < testData.size() / 2; ++index)
                Multiplicator::gradeSchool(testData[index], testData[index * 2]);
        });

        long divideAndConquerTime = calcExecTime([&testData]()
        {
            for (size_t index = 0; index < testData.size() / 2; ++index)
                Multiplicator::divideAndConquer(testData[index], testData[index * 2]);
        });

        long karatsubaTime = calcExecTime([&testData]()
        {
            for (size_t index = 0; index < testData.size() / 2; ++index)
                Multiplicator::karatsuba(testData[index], testData[index * 2]);
        });

        // We add a sample to the samples vector.
        samples.push_back({static_cast<long>(length), gradeSchoolTime, divideAndConquerTime, karatsubaTime});
    }

    // We save samples to a CSV file.
    generateCSV("number_mult.csv", samples);

    return 0;
}
