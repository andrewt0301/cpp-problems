//
// Created by Andrei Tatarnikov on 2019-04-14.
//

#ifndef TUTORIALS_RANDOM_H
#define TUTORIALS_RANDOM_H

#include <random>

/**
 * The class provides functionality to generate random numbers.
 */
class Random {
private:
    std::default_random_engine gen;
    std::uniform_int_distribution<> dis;
public:

    /**
     * Constructs a generator of digit beloging to the specified range.
     *
     * @param start Range start.
     * @param end Range end.
     */
    Random(int start, int end);

    /**
     * Constructs a generator of k-digit random numbers.
     *
     * E.g. 3-digit numbers are numbers in the range [0, 999].
     *
     * @param k Number of digits.
     */
    explicit Random(int k);

    /**
     * Generates a next random number.
     *
     * @return Next random number.
     */
    int next();
};

/**
 * Creates a vector of random values of the specified length.
 *
 * @param random Random number generator.
 * @param length Length of the vector.
 * @return New vector of random values.
 */
std::vector<int> randomVector(Random& random, size_t length);

#endif //TUTORIALS_RANDOM_H
