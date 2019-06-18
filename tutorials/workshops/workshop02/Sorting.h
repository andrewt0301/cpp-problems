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

template <typename T>
void mergeSort(std::vector<T>& data, std::vector<T>& temp, size_t start, size_t end);

template <typename T>
void merge(std::vector<T>& data, std::vector<T>& temp, int start, int split, int end);

/**
  * Sorts an array of values into ascending numerical order using the merge sort algorithm.
  *
  * Time complexity: {@code Θ(N log N)}, where N is the length of the array.
  *
  * @param data Vector of values to be sorted.
  */
template <typename T>
void mergeSort(std::vector<T>& data)
{
    size_t size = data.size();
    if (size > 1)
    {
        std::vector<T> temp(data);
        mergeSort(data, temp, 0, size - 1);
    }
}

/**
 * Sorts the specified range in an array of values into ascending
 * numerical order using the merge sort algorithm.
 *
 * Time complexity: {@code Θ(N lg N)}, where N is the length of the sorted range.
 *
 * @param data Vector of values to be sorted.
 * @param start Range start index (included).
 * @param end Range end index (included).
 */
template <typename T>
void mergeSort(std::vector<T>& data, std::vector<T>& temp, size_t start, size_t end) {

    if (start < end)
    {
        size_t split = (start + end) / 2;

        if (split != start)
            mergeSort(data, start, split);

        if (split != end)
            mergeSort(data, split + 1, end);

        merge(data, temp, start, split, end);
    }
}

/**
 * Merges two adjacent sorted ranges in an array into a single sorted range.
 *
 * @param data Array to be merged.
 * @param temp Temporary array to be used for merge.
 * @param start Start position of the first range (included).
 * @param split End position of the first range, followed by start position of
 *              the second range (included).
 * @param end End position of the second range (included).
 */
template <typename T>
void merge(std::vector<T>& data, std::vector<T>& temp, int start, int split, int end) {

    /*
    // Creates a copy of the first (left) range.
    final int leftLen = split - start + 1;
    final int[] leftData = new int[leftLen + 1];
    System.arraycopy(data, start, leftData, 0, leftLen);
    leftData[leftLen] = Integer.MAX_VALUE;

    // Creates a copy of the second (right) range.
    final int rightLen = end - split;
    final int[] rightData = new int[rightLen + 1];
    System.arraycopy(data, split + 1, rightData, 0, rightLen);
    rightData[rightLen] = Integer.MAX_VALUE;

    // Merges the two ranges and saves the result to the data array.
    for (int index = start, leftIndex = 0, rightIndex = 0; index <= end; ++index)
    {
        final int left = leftData[leftIndex];
        final int right = rightData[rightIndex];

        if (left <= right) {
            data[index] = left;
            leftIndex++;
        } else {
            data[index] = right;
            rightIndex++;
        }
    }*/
}

template <typename T>
int partition(std::vector<T>& data, size_t start, size_t end);

template <typename T>
void quickSort(std::vector<T>& data, size_t start, size_t end);

/**
  * Sorts an array of values into ascending numerical order using the quick sort algorithm.
  *
  * Time complexity: worst case {@code O(N^2)}, expected {@code O(N log N)},
  * where N is the length of the array.
  *
  * @param data Vector of values to be sorted.
  */
template <typename T>
void quickSort(std::vector<T>& data)
{
    size_t size = data.size();
    if (size > 1)
        quickSort(data, 0, size - 1);
}

template <typename T>
void quickSort(std::vector<T>& data, size_t start, size_t end)
{
    if (start < end)
    {
        size_t split = partition(data, start, end);

        if (split != start)
            quickSort(data, start, split - 1);

        if (split != end)
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
            std::swap(data[split], data[i]);
            split++;
        }
    }

    std::swap(data[split], data[end]);
    return split;
}

#endif //TUTORIALS_SORTING_H
