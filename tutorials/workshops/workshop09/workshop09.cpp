//
// Created by Andrei Tatarnikov on 2019-05-19.
//

#include <iostream>
#include <vector>

#include "../Random.h"
#include "Heap.h"


using std::cout;
using std::endl;

template <typename T>
void printData(const T& a)
{
    std::copy(std::begin(a), std::end(a), std::ostream_iterator<int>(cout, " "));
    cout << endl;
}

void testHeapSort()
{
    Random random(0, 99);

    const std::vector<int> data = randomVector(random, 10);
    printData(data);

    std::vector<int> dataMin{data};
    heap::heapsort(dataMin, dataMin.size(), std::greater<>());
    printData(dataMin);

    std::vector<int> dataMax{data};
    heap::heapsort(dataMax, dataMax.size(), std::less<>());
    printData(dataMax);
}

int main()
{
    testHeapSort();


    return 0;
}