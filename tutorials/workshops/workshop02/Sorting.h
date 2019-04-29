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

#endif //TUTORIALS_SORTING_H
