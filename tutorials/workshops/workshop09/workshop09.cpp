//
// Created by Andrei Tatarnikov on 2019-05-19.
//

#include <iostream>
#include <vector>

#include "../Random.h"
#include "Heap.h"
#include "PriorityQueue.h"

using std::cout;
using std::endl;

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& a)
{
    std::copy(a.begin(), a.end(), std::ostream_iterator<T>(out, " "));
    return out;
}

void testHeapSort()
{
    Random random(0, 99);

    const std::vector<int> data = randomVector(random, 10);
    cout << data << endl;

    std::vector<int> dataMin{data};
    heapsort(dataMin, dataMin.size(), std::greater<>());
    cout << dataMin << endl;

    std::vector<int> dataMax{data};
    heapsort(dataMax, dataMax.size(), std::less<>());
    cout << dataMax << endl;
}

void testPriorityQueue()
{
    cout << "Min Queue:" << endl;
    PriorityQueue<int, std::greater<>> maxQueue;

    maxQueue.insert(5);
    maxQueue.insert(10);
    maxQueue.insert(15);
    maxQueue.insert(20);

    std::cout << maxQueue << endl;
    maxQueue.setKey(1, 1);

    std::cout << maxQueue << endl;
    std::cout << maxQueue.pop() << endl;
    std::cout << maxQueue.pop() << endl;
    std::cout << maxQueue.pop() << endl;
    std::cout << maxQueue << endl;

    cout << "Min Queue:" << endl;
    PriorityQueue<int, std::less<>> minQueue;

    minQueue.insert(5);
    minQueue.insert(10);
    minQueue.insert(15);
    minQueue.insert(20);

    std::cout << minQueue << endl;
    minQueue.setKey(1, 1);

    std::cout << minQueue << endl;
    std::cout << minQueue.pop() << endl;
    std::cout << minQueue.pop() << endl;
    std::cout << minQueue.pop() << endl;
    std::cout << minQueue << endl;
}

int main()
{
    cout << "------------------------------" << endl;
    cout << "Testing HeapSort:" << endl;

    testHeapSort();

    cout << "------------------------------" << endl;
    cout << "Testing PriorityQueue:" << endl;

    testPriorityQueue();

    return 0;
}
