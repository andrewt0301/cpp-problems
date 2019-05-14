//
// Created by Tatarnikov_A on 29.04.2019.
//

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

#include "../CSV.h"
#include "../Random.h"
#include "../Time.h"

#include "Sorting.h"

using IntVector = std::vector<int>;

/**
 * Creates a copy of test data and sorts each vector in the test data with the specified function.
 */
long calcExecTime(std::vector<IntVector> testData, std::function<void(IntVector&)> func)
{
    return calcExecTime([&testData, func]()
    {
        for (IntVector& values : testData)
            func(values);
    });
}

/**
 * Generates test data represented by a vector of vectors of the specified length
 * each filled with random values.
 *
 * @param random Random value generator.
 * @param length Length of vectors of random values.
 * @param count Number of vectors.
 * @return Vectors of random values.
 */
std::vector<IntVector> randomTestData(Random& random, size_t length, size_t count)
{
    std::vector<IntVector> testData(count);

    for (IntVector& values : testData)
        values = randomVector(random, length);

    return testData;
}

int main()
{
    // Here we hold our performance measures.
    Samples<long> samples;

    // Random generator of 3-digit values.
    Random random(3);

    // length is the length of array to be sorted.
    // We increase length with step 100.
    // We use large vector lengths because modern computers sort vectors very quickly.
    for (long length = 100; length <= 7000; length += 100)
    {
        // Test data: vectors of integers to be sorted.
        // We need multiple vectors as sorting of a single vector can be done quicker than 1 millisecond.
        // We generate values in advance in order to exclude generation cost from result.
        std::vector<IntVector> testData = randomTestData(random, length, 10);

        // We sort all vectors with insertion sort and measure the sorting time.
        const long insertionSortTime = calcExecTime(testData, [](IntVector& values)
        {
            insertionSort(values);
        });

        // We sort all vectors with std::sort and measure the sorting time.
        const long stdSortTime = calcExecTime(testData, [](IntVector& values)
        {
            std::sort(values.begin(), values.end());
        });

        // We add a sample to the samples vector.
        samples.push_back({length, insertionSortTime, stdSortTime});
    }

    // We save samples to a CSV files.
    generateCSV("sorting.csv", samples);

    return 0;
}
