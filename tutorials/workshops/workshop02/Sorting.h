//
// Created by Tatarnikov_A on 19.04.2019.
//

#ifndef TUTORIALS_SORTING_H
#define TUTORIALS_SORTING_H

/**
  * Sorts an array of integers into ascending numerical order using the insertion sort algorithm.
  *
  * Time complexity: {@code O(N^2)}, where N is the length of the array.
  *
  * @param data Vector of values to be sorted.
  */
template <typename T>
void insertionSort(std::vector<T>& data)
{
    for (int i = 1; i < data.size(); ++i)
    {
        const T key = data[i];

        int j = i - 1;
        while (j >= 0 && data[j] > key)
        {
            data[j + 1] = data[j];
            --j;
        }

        data[j + 1] = key;
    }
}

/**
  * Sorts an array of integers into ascending numerical order using the selection sort algorithm.
  *
  * Time complexity: {@code O(N^2)}, where N is the length of the array.
  *
  * @param data Vector of values to be sorted.
  */
template <typename T>
void selectionSort(std::vector<T>& data)
{
    const size_t size = data.size();

    if (size <= 1)
        return;

    for (size_t i = 0; i < size; ++i)
    {
        size_t minIdx = i;
        T min = data[minIdx];

        for (size_t j = i + 1; j < size; ++j)
        {
            const T key = data[j];
            if (key < min)
            {
                minIdx = j;
                min = key;
            }
        }

        if (minIdx != i)
        {
            data[minIdx] = data[i];
            data[i] = min;
        }
    }
}

/**
  * Sorts an array of integers into ascending numerical order using the bubble sort algorithm.
  *
  * Time complexity: {@code O(N^2)}, where N is the length of the array.
  *
  * @param data Vector of values to be sorted.
  */
template <typename T>
void bubbleSort(std::vector<T>& data)
{
    const size_t size = data.size();

    if (size <= 1)
        return;

    for (size_t i = 0; i < size - 1; ++i)
    {
        bool noSwaps = true;

        for (size_t j = size - 1; j > i; --j)
        {
            const size_t k = j - 1;

            const T valJ = data[j];
            const T valK = data[k];

            if (valJ < valK) {
                data[j] = valK;
                data[k] = valJ;
                noSwaps = false;
            }
        }

        if (noSwaps)
            break;
    }
}

#endif //TUTORIALS_SORTING_H
