//
// Created by Tatarnikov_A on 16.05.2019.
//

#ifndef TUTORIALS_LINKEDLIST_H
#define TUTORIALS_LINKEDLIST_H

#include <iostream>

template <typename T>
class LinkedList {
public:
    struct Node
    {
        T     _value;
        Node* _prev;
        Node* _next;

        Node(T value, Node* prev, Node* next) : _value{value}, _prev{prev}, _next{next} {}
    };

    // TODO
    class Iterator
    {
    public:
        T  operator*() const;
        T& operator*();

        bool operator==(const Iterator&) const;
        bool operator!=(const Iterator&) const;

        /** Prefix increment. */
        Iterator& operator++();
        /** Postfix increment. */
        Iterator operator++(int);

        /** Prefix decrement */
        Iterator& operator--();
        /** Postfix decrement. */
        Iterator operator--(int);
    };

public:
    LinkedList() : _head{nullptr}, _tail{nullptr}
    {}

    ~LinkedList()
    {
        Node* p = _head;
        while (p != nullptr)
        {
            Node* tmp = p;
            p = p->_next;
            delete tmp;
        }
    }

    void push_front(T value)
    {
        Node* node = new Node(value, nullptr, _head);

        if (_head != nullptr)
            _head->_prev = node;

        _head = node;

        if (_tail == nullptr)
            _tail = node;
    }

    T pop_front()
    {
        // TODO
        return 0;
    }

    void push_back(T value)
    {
        Node* node = new Node(value, _tail, nullptr);

        if (_tail != nullptr)
            _tail->_next = node;

        _tail = node;

        if (_head == nullptr)
            _head = node;
    }

    T pop_back()
    {
        // TODO
        return 0;
    }

    void mergeBack(LinkedList&& list)
    {
        if (_tail == nullptr)
        {
            _head = list._head;
            _tail = list._tail;
        }
        else
        {
            _tail->_next = list._head;
            if (list._head != nullptr)
                list._head->_prev = _tail;
            _tail = list._tail;
        }

        list._head = nullptr;
        list._tail = nullptr;
    }

    size_t size()
    {
        // TODO
        return 0;
    }

    T operator[](size_t index) const
    {
        // TODO
        return 0;
    }

    void reverse()
    {
        // TODO
    }

    void clear()
    {
        // TODO
    }

    Iterator begin()
    {
        // TODO
        return 0;
    }

    Iterator end()
    {
        // TODO
        return 0;
    }

    void remove(Iterator& it)
    {
        // TODO
    }

    void swap(Iterator& lhs, Iterator& rhs)
    {
        // TODO
    }

    friend std::ostream& operator<<(std::ostream& out, const LinkedList& list)
    {
        out << '{';
        for (Node* p = list._head; p != nullptr; p = p->_next)
        {
            out << p->_value;
            if (p->_next != nullptr)
                out << ", ";
        }
        out << '}';
        return out;
    }

private:
    Node* _head;
    Node* _tail;
};

#endif //TUTORIALS_LINKEDLIST_H
