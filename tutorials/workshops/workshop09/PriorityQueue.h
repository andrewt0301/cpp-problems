//
// Created by Andrei Tatarnikov on 2019-05-19.
//

#ifndef TUTORIALS_PRIORITYQUEUE_H
#define TUTORIALS_PRIORITYQUEUE_H

#include <vector>
#include <iterator>
#include <iostream>

#include "Heap.h"

template <typename T, typename TPred>
class PriorityQueue
{
private:
    TPred _pred;
    std::vector<T> _data;

    void resize(size_t size)
    {
        _data.resize(size);
    }

public:
    explicit PriorityQueue(TPred pred) : _pred{pred}, _data{}
    {
    }

    PriorityQueue() : _pred{TPred()}, _data{}
    {
    }

    inline size_t size() const
    {
        return _data.size();
    }

    T operator[](size_t i)
    {
        return _data[i];
    }

    T top() const
    {
        return _data[0];
    }

    T pop()
    {
        T top = _data[0];

        _data[0] = _data[size() - 1];
        resize(size() - 1);
        heapify(_data, size(), 0, TPred());

        return top;
    }

    void setKey(size_t i, T key)
    {
        _data[i] = key;

        while (i > 0 && _pred(_data[i], _data[parent(i)]))
        {
            swap(_data, i, parent(i));
            i = parent(i);
        }

    }

    void insert(T key)
    {
       resize(size() + 1);
       setKey(size() - 1, key);
    }

    friend std::ostream& operator<<(std::ostream& out, const PriorityQueue& queue)
    {
        std::copy(queue._data.begin(), queue._data.end(), std::ostream_iterator<int>(out, " "));
        return out;
    }

};

#endif //TUTORIALS_PRIORITYQUEUE_H
