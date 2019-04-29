//
// Created by Tatarnikov_A on 29.04.2019.
//

#include <iostream>
#include <vector>

#include "../CSV.h"
#include "../Random.h"
#include "../Time.h"

#include "Sorting.h"

using IntVector = std::vector<int>;

int main()
{
    // Here hold our performance measures.
    Samples<long> samples;

    // Random generator of 3-digit values we are going to sort.
    Random random(3);

    // length is the length of array to be sorted.
    // We increase length with step 100.
    // We use large vector lengths because modern computers sort vectors very quickly.
    for (long length = 100; length <= 7000; length += 100)
    {
        // Test data: vectors of integers to be sorted.
        // We need multiple vectors as sorting of a single vector can be done quicker than 1 millisecond.
        std::vector<IntVector> testData(10);

        // We generate values in advance in order to exclude generation cost from result.
        for (IntVector& values : testData)
            values = randomVector(random, length);

        // We sort all vectors in test data and measure the sorting time.
        long insertionSortTime = calcExecTime([&testData]()
        {
            for (IntVector& values : testData)
                insertionSort(values);
        });

        // We add a sample to the samples vector.
        samples.push_back({length, insertionSortTime});
    }

    // We save samples to a CSV files.
    generateCSV("samples.csv", samples);

    return 0;
}
