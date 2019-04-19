//
// Created by Andrei Tatarnikov on 2019-04-14.
//

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include "Multiplicator.h"
#include "Number.h"
#include "Random.h"
#include "Sorting.h"
#include "Time.h"

using IntVector = std::vector<int>;

using Sample = IntVector;

void generateCsv(const std::vector<Sample>& samples)
{
    std::ofstream out{"test.csv", std::ofstream::out};

    for (const Sample& sample : samples)
    {
        std::copy(sample.cbegin(), sample.cend(), std::ostream_iterator<int>(out, ";"));
        out << std::endl;
    }

    out.close();
}

int main()
{
    // Test data: vectors of integers to be sorted.
    // We need so many vectors as sorting of a single vector is done quicker than 1 millisecond.
    std::vector<IntVector> testData(1000);

    // Random generator of 2-digit values.
    Random random(2);

    // We generate values in advance in order to exclude generation cost from result.
    for (IntVector& values : testData)
        values = randomVector(random, 150);

    /*
    std::cout << "*********************************************" << std::endl;
    std::cout << "Initial data: " << std::endl;

    for (const IntVector& values : testData)
    {
        std::copy(values.cbegin(), values.cend(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
    */

    long sortingTime = calcExecTime([&testData]()
    {
        for (IntVector& values : testData)
            insertionSort(values);
    });

    /*
    std::cout << "*********************************************" << std::endl;
    std::cout << "Sorted data: " << std::endl;

    for (const IntVector& values : testData)
    {
        std::copy(values.cbegin(), values.cend(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
    */

    std::cout << "*********************************************" << std::endl;
    std::cout << "Sorting time: "  << sortingTime << " ms." << std::endl;

    // My computer gives:
    // Sorting time: 39 ms.

    std::vector<Sample> samples;

    samples.push_back({1, 2, 3});
    samples.push_back({2, 4, 5});
    samples.push_back({3, 6, 7});

    generateCsv(samples);

    return 0;
}