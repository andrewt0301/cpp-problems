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
  * @tparam T Value type.
  * @param data Vector of values to be sorted.
  */
template <typename T>
void insertionSort(std::vector<T>& data)
{
    for (size_t i = 1; i < data.size(); ++i)
    {
        const T key = data[i];

        size_t j = i;
        while (j >= 1 && data[j - 1] > key)
        {
            data[j] = data[j - 1];
            --j;
        }

        data[j] = key;
    }
}

/**
  * Sorts an array of values into ascending numerical order using the shell sort algorithm.
  *
  * Time complexity: {@code O(N^(3/2)}, where N is the length of the array.
  *
  * @tparam T Value type.
  * @param data Array of values to be sorted.
  */
template <typename T>
void shellSort(std::vector<T>& data)
{
    const size_t size = data.size();

    for (size_t h = size / 2; h >= 1; h /= 2)
    {
        for (size_t i = h; i < size; ++i)
        {
            const T key = data[i];

            size_t j = i;
            while (j >= h && data[j - h] > key) {
                data[j] = data[j - h];
                j -= h;
            }

            data[j] = key;
        }
    }
}

/**
  * Sorts an array of values into ascending numerical order using the selection sort algorithm.
  *
  * Time complexity: {@code O(N^2)}, where N is the length of the array.
  *
  * @tparam T Value type.
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
  * @tparam T Value type.
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
  * @tparam T Value type.
  * @tparam K Value range size.
  * @param data Vector of integer values to be sorted.
  */
template <typename T, size_t K>
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
 * Merges two adjacent sorted ranges in an array into a single sorted range.
 *
 * @tparam T Value type.
 * @param data Array to be merged.
 * @param temp Temporary array to be used for merge.
 * @param start Start position of the first range (included).
 * @param split End position of the first range, followed by start position of
 *              the second range (included).
 * @param end End position of the second range (included).
 */
template <typename T>
void merge(std::vector<T>& data, std::vector<T>& temp, size_t start, size_t split, size_t end) {

    // Copies both sorted ranges to temp.
    for (size_t i = start, j = 0; i <= end; ++i, ++j)
        temp[j] = data[i];

    const size_t  leftEnd = split - start;
    const size_t rightEnd = end - start;

    // Merges the two ranges and saves the result to the data array.
    for (size_t i = start, l = 0, r = leftEnd + 1; i <= end; ++i)
    {
        const bool  isLeftEmpty = l > leftEnd;
        const bool isRightEmpty = r > rightEnd;

        if ((!isLeftEmpty && !isRightEmpty && temp[l] < temp[r]) || isRightEmpty)
            data[i] = temp[l++];
        else
            data[i] = temp[r++];
    }
}

/**
 * Sorts the specified range in an array of values into ascending
 * numerical order using the merge sort algorithm.
 *
 * Time complexity: {@code Θ(N lg N)}, where N is the length of the sorted range.
 *
 * @tparam T Value type.
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
            mergeSort(data, temp, start, split);

        if (split != end)
            mergeSort(data, temp, split + 1, end);

        merge(data, temp, start, split, end);
    }
}

/**
  * Sorts an array of values into ascending numerical order using the merge sort algorithm.
  *
  * Time complexity: {@code Θ(N log N)}, where N is the length of the array.
  *
  * @tparam T Value type.
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
 * Partitions a range of some array into two parts.
 *
 * Partitioning is done in such a way that
 * the first part contains values less or equal (<=) than the pivot element and
 * the second part contains values greater (>) than the pivot element.
 * The pivot element is chosen to be the last element in the range.
 *
 * @tparam T Value type.
 * @param data Array to be partitioned.
 * @param start Range start index (included).
 * @param end Range end index (included).
 * @return Position of the split (index of the pivot element in the rearranged array).
 */
template <typename T>
size_t partition(std::vector<T>& data, size_t start, size_t end)
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

/**
 * Sorts the specified range in an array of values into ascending
 * numerical order using the quick sort algorithm.
  *
  * Time complexity: worst case {@code O(N^2)}, expected {@code O(N log N)},
  * where N is the length of the array.
  *
  * @tparam T Value type.
  * @param data Vector of values to be sorted.
  * @param start Range start index (included).
  * @param end Range end index (included).
  */
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

/**
  * Sorts an array of values into ascending numerical order using the quick sort algorithm.
  *
  * Time complexity: worst case {@code O(N^2)}, expected {@code O(N log N)},
  * where N is the length of the array.
  *
  * @tparam T Value type.
  * @param data Vector of values to be sorted.
  */
template <typename T>
void quickSort(std::vector<T>& data)
{
    size_t size = data.size();
    if (size > 1)
        quickSort(data, 0, size - 1);
}

#endif //TUTORIALS_SORTING_H
