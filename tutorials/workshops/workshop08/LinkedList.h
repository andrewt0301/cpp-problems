//
// Created by Tatarnikov_A on 16.05.2019.
//

#ifndef TUTORIALS_LINKEDLIST_H
#define TUTORIALS_LINKEDLIST_H

#include <iostream>
#include <stdexcept>

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

    class Iterator
    {
    public:
        explicit Iterator(Node* node) : _node(node) {}

        T  operator*() const { return _node->_value; }
        T& operator*()       { return _node->_value; }

        bool operator==(const Iterator& other) const { return this->_node == other._node; }
        bool operator!=(const Iterator& other) const { return this->_node != other._node; }

        /** Prefix increment. */
        Iterator& operator++()
        {
            _node = _node->_next;
            return *this;
        }

        /** Postfix increment. */
        Iterator operator++(int)
        {
            Iterator prev = *this;
            ++(*this);
            return prev;
        }

        /** Prefix decrement */
        Iterator& operator--()
        {
            _node = _node->_prev;
            return *this;
        }

        /** Postfix decrement. */
        Iterator operator--(int)
        {
            Iterator prev = *this;
            --(*this);
            return prev;
        }

    private:
       Node* _node;
    };

public:
    LinkedList() : _head{nullptr}, _tail{nullptr}, _size{0}
    {}

    ~LinkedList()
    {
        clear();
    }

    size_t size()
    {
        return _size;
    }

    void pushFront(T value)
    {
        Node* node = new Node(value, nullptr, _head);

        if (_head != nullptr)
            _head->_prev = node;

        _head = node;

        if (_tail == nullptr)
            _tail = node;

        _size++;
    }

    T popFront()
    {
        // TODO
        return 0;
    }

    void pushBack(T value)
    {
        Node* node = new Node(value, _tail, nullptr);

        if (_tail != nullptr)
            _tail->_next = node;

        _tail = node;

        if (_head == nullptr)
            _head = node;

        _size++;
    }

    T popBack()
    {
        // TODO
        return 0;
    }

    void pushAllFront(LinkedList&& list)
    {
        if (_head == nullptr)
        {
            _head = list._head;
            _tail = list._tail;
        }
        else
        {
            _head->_prev = list._tail;
            if (list._tail != nullptr)
                list._tail->_next = _head;
            _head = list._head;
        }

        list._head = nullptr;
        list._tail = nullptr;

        _size += list.size();
    }

    void pushAllBack(LinkedList&& list)
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

        _size += list.size();
    }

    T operator[](size_t index) const
    {
        if (index >= size())
            throw std::out_of_range("Index out of bounds!");

        Node* node = _head;
        for (size_t i = 0; i < index; ++i)
            node = node->_next;

        return node->_value;
    }

    void reverse()
    {
        Node* newHead = nullptr;
        Node* newTail = nullptr;

        while (_head != nullptr)
        {
            Node* curr = _head;
            _head = _head->_next;

            curr->_next = newHead;
            curr->_prev = nullptr;

            if (newHead != nullptr)
                newHead->_prev = curr;

            newHead = curr;

            if (newTail == nullptr)
                newTail = curr;
        }

        _head = newHead;
        _tail = newTail;
    }

    void clear()
    {
        Node* p = _head;

        _head = nullptr;
        _tail = nullptr;

        while (p != nullptr)
        {
            Node* tmp = p;
            p = p->_next;
            delete tmp;
        }
    }

    Iterator begin()
    {
        return Iterator{_head};
    }

    Iterator end()
    {
        return Iterator{nullptr};
    }

    void remove(Iterator& it)
    {
        // TODO
    }

    void swap(Iterator& lhs, Iterator& rhs)
    {
        // TODO
    }

    void insertionSort()
    {
        Node* i = _head->_next;
        while (i != nullptr)
        {
            Node* next = i->_next;

            const T key = i->_value;
            Node* j = i->_prev;

            while (j->_prev != nullptr && j->_value > key)
                j = j->_prev;

            if (i->_prev != nullptr)
                i->_prev->_next = i->_next;

            if (i->_next != nullptr)
                i->_next->_prev = i->_prev;

            /*
            i->_prev = j->_prev;
            i->_next = j;

            if (j->_prev != nullptr)
                j->_prev->_next = i;
            j->_prev = i;*/

            i = next;
        }
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
    Node*  _head;
    Node*  _tail;
    size_t _size;
};


#endif //TUTORIALS_LINKEDLIST_H
