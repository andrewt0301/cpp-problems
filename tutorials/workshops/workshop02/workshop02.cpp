//
// Created by Tatarnikov_A on 29.04.2019.
//

#include <iostream>
#include <vector>

#include "../Random.h"
#include "../Time.h"

#include "Sorting.h"

using IntVector = std::vector<int>;

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

    return 0;
}
