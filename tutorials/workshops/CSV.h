//
// Created by Tatarnikov_A on 29.04.2019.
//

#ifndef TUTORIALS_CSV_H
#define TUTORIALS_CSV_H

/**
 * This module provides facilities to generate CSV files with some sample values.
 */

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

/**
 * Type for a sample that is represented by a vector of values of some type T.
 */
template <typename T>
using Sample = std::vector<T>;

/**
 * Type for a vector of samples that store values of some type T.
 */
template <typename T>
using Samples = std::vector<Sample<T>>;

/**
 * Saves the specified samples vector to a CSV file.
 *
 * @tparam T Type of values in the samples.
 * @param samples Vector of samples.
 */
template <typename T>
void generateCSV(const std::string& fileName, const Samples<T>& samples)
{
    std::ofstream out{fileName, std::ofstream::out};

    for (const Sample<T>& sample : samples)
    {
        std::copy(sample.cbegin(), sample.cend(), std::ostream_iterator<int>(out, ";"));
        out << std::endl;
    }

    out.close();
}

#endif //TUTORIALS_CSV_H
