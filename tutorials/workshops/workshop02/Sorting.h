//
// Created by Tatarnikov_A on 19.04.2019.
//

#ifndef TUTORIALS_SORTING_H
#define TUTORIALS_SORTING_H

/**
  * Sorts an array of values into ascending numerical order using the insertion sort algorithm.
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
  * Sorts an array of values into ascending numerical order using the selection sort algorithm.
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
  * Sorts an array of values into ascending numerical order using the bubble sort algorithm.
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

/**
  * Sorts an array of integer values into ascending numerical order using the counting sort algorithm.
  *
  * Time complexity: {@code Θ(N)}, where N is the length of the array.
  *
  * @tparam T Integer value exact type.
  * @tparam K Integer value range size.
  * @param data Vector of integer values to be sorted.
  */
template <typename T, int K>
void countingSort(std::vector<T>& data)
{
    std::vector<T> input(data);

    size_t counts[K] = {0};

    for (T val : input)
        ++counts[val];

    for (size_t i = 1; i < K; ++i)
        counts[i] += counts[i - 1];

    for (size_t i = input.size(); i >= 1; --i)
    {
        const T val = input[i - 1];
        data[--counts[val]] = val;
    }
}

/**
  * Sorts an array of values into ascending numerical order using the bubble sort algorithm.
  *
  * Time complexity: {@code Θ(N^2)}, where N is the length of the array.
  *
  * @param data Vector of values to be sorted.
  */
template <typename T>
void mergeSort(std::vector<T>& data)
{
    // TODO
}


template <typename T>
int partition(std::vector<T>& data, size_t start, size_t end);

template <typename T>
void quickSort(std::vector<T>& data, size_t start, size_t end);

template <typename T>
void swap(std::vector<T>& data, size_t i, size_t j)
{
    T temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

template <typename T>
void quickSort(std::vector<T>& data)
{
    if (data.size() > 1)
        quickSort(data, 0, data.size() - 1);
}

template <typename T>
void quickSort(std::vector<T>& data, size_t start, size_t end)
{
    size_t length = end - start;
    if (length > 1)
    {
        size_t split = partition(data, start, end);
        quickSort(data, start, split - 1);
        quickSort(data, split + 1, end);
    }
}

template <typename T>
int partition(std::vector<T>& data, size_t start, size_t end)
{
    const T pivot = data[end];
    size_t split = start;

    for (size_t i = start; i < end; ++i)
    {
        if (data[i] <= pivot)
        {
            swap(data, split, i);
            split++;
        }
    }

    swap(data, split, end);
    return split;
}

#endif //TUTORIALS_SORTING_H
