//
// Created by Tatarnikov_A on 16.05.2019.
//

#ifndef TUTORIALS_LINKEDLIST_H
#define TUTORIALS_LINKEDLIST_H

#include <iostream>
#include <stdexcept>

#include <iostream>

using namespace std;

template <typename T>
class LinkedList {
public:
    struct Node
    {
        T     value;
        Node* prev;
        Node* next;

        Node(T v, Node* p, Node* n) : value{v}, prev{p}, next{n} {}
    };

public:

    LinkedList()
        : _head{nullptr}, _tail{nullptr}, _size{0}
    {}

    LinkedList(const std::initializer_list<T>& values)
        : _head{nullptr}, _tail{nullptr}, _size{0}
    {
        for (const T& value : values)
            pushBack(value);
    }

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
            _head->prev = node;

        _head = node;

        if (_tail == nullptr)
            _tail = node;

        _size++;
    }

    void pushBack(T value)
    {
        Node* node = new Node(value, _tail, nullptr);

        if (_tail != nullptr)
            _tail->next = node;

        _tail = node;

        if (_head == nullptr)
            _head = node;

        _size++;
    }

    T popFront()
    {
        if (_head == nullptr)
            throw std::out_of_range("List is empty!");

        Node* node = _head;
        T value = node->value;
        erase(node);

        return value;
    }

    T popBack()
    {
        if (_tail == nullptr)
            throw std::out_of_range("List is empty!");

        Node* node = _tail;
        T value = node->value;
        erase(node);

        return value;
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
            _head->prev = list._tail;
            if (list._tail != nullptr)
                list._tail->next = _head;
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
            _tail->next = list._head;
            if (list._head != nullptr)
                list._head->prev = _tail;
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
            node = node->next;

        return node->value;
    }

    void reverse()
    {
        Node* newHead = nullptr;
        Node* newTail = nullptr;

        while (_head != nullptr)
        {
            Node* curr = _head;
            _head = _head->next;

            curr->next = newHead;
            curr->prev = nullptr;

            if (newHead != nullptr)
                newHead->prev = curr;

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
            p = p->next;
            delete tmp;
        }
    }

    void insertionSort()
    {
        for (Node* j = _head->next; j != nullptr;)
        {
            const T key = j->value;
            Node* const next = j->next;

            Node* i = j->prev;
            while (i != nullptr && i->value > key)
                i = i->prev;

            if (j->prev != i)
            {
                unlink(j);
                insertAfter(i, j);
            }

            j = next;
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const LinkedList& list)
    {
        out << '{';
        for (Node* p = list._head; p != nullptr; p = p->next)
        {
            out << p->value;
            if (p->next != nullptr)
                out << ", ";
        }
        out << '}';
        return out;
    }

private:

    void erase(Node* node)
    {
        unlink(node);
        delete node;
    }

    void unlink(Node* node)
    {
        if (node->prev != nullptr)
            node->prev->next = node->next;
        else
            _head = node->next;

        if (node->next != nullptr)
            node->next->prev = node->prev;
        else
            _tail = node->prev;

        _size--;
    }

    void insertAfter(Node* first, Node* second)
    {
        second->prev = first;

        if (first != nullptr)
        {
            second->next = first->next;

            first->next->prev = second;
            first->next = second;
        }
        else
        {
            second->next = _head;
            _head = second;
            if (_tail == nullptr)
                _tail = _head;
        }

        _size++;
    }

    void insertBefore(Node* first, Node* second)
    {
        second->next = first;
        // TODO
    }

    Node*  _head;
    Node*  _tail;
    size_t _size;
};

/*
class Iterator
{
public:
    friend class LinkedList;

    explicit Iterator(Node* node) : _node(node) {}

    T  operator*() const { return _node->value; }
    T& operator*()       { return _node->value; }

    bool operator==(const Iterator& other) const { return this->_node == other._node; }
    bool operator!=(const Iterator& other) const { return this->_node != other._node; }

    Iterator& operator++()
    {
        _node = _node->next;
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator prev = *this;
        ++(*this);
        return prev;
    }

    Iterator& operator--()
    {
        _node = _node->prev;
        return *this;
    }

    Iterator operator--(int)
    {
        Iterator prev = *this;
        --(*this);
        return prev;
    }

private:
    Node* _node;
};
*/

#endif //TUTORIALS_LINKEDLIST_H
