//
// Created by Tatarnikov_A on 18.04.2019.
//

#ifndef TUTORIALS_TIME_H
#define TUTORIALS_TIME_H

#include <ctime>

constexpr clock_t CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000;

/**
 * Executes the specified function and measures its execution in milliseconds.
 *
 * @tparam T Function type.
 * @param func Function to be executed.
 * @return Execution time in milliseconds.
 */
template <typename T>
long calcExecTime(T func)
{
    clock_t start = clock();
    func();
    clock_t end = clock();

    clock_t diff = end - start;
    long time = diff / CLOCKS_PER_MS;

    return time;
}

/**
 * Executes the specified function multiple times and measures its average execution in milliseconds.
 *
 * @tparam T Function type.
 * @param func Function to be executed.
 * @param repeat Number of times the function is to be executed.
 * @return Average execution time in milliseconds.
 */
 template <typename T>
long calcAverageExecTime(T func, int repeat)
{
    clock_t start = clock();

    for (int i = 0; i < repeat; ++i)
        func();

    clock_t end = clock();

    clock_t diff = end - start;
    clock_t average = diff / repeat;
    long time = average / CLOCKS_PER_MS;

    return time;
}

#endif //TUTORIALS_TIME_H
