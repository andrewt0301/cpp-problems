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
        T     value;
        Node* prev;
        Node* next;

        Node(T v, Node* p, Node* n) : value{v}, prev{p}, next{n} {}
    };

    class Iterator
    {
    public:
        friend class LinkedList;

        explicit Iterator(Node* node) : _node(node) {}

        T  operator*() const { return _node->value; }
        T& operator*()       { return _node->value; }

        bool operator==(const Iterator& other) const { return this->_node == other._node; }
        bool operator!=(const Iterator& other) const { return this->_node != other._node; }

        /** Prefix increment. */
        Iterator& operator++()
        {
            _node = _node->next;
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
            _node = _node->prev;
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
            _head->prev = node;

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
            _tail->next = node;

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

    Iterator begin()
    {
        return Iterator{_head};
    }

    Iterator end()
    {
        return Iterator{nullptr};
    }

    void swap(Iterator& lhs, Iterator& rhs)
    {
        // TODO
    }

    Iterator remove(const Iterator& it)
    {
        if (it == end())
            throw std::out_of_range("No element to delete!");

        Node* curr = it._node;
        Node* next = curr->next;

        unlink(curr);
        delete curr;

        return Iterator(next);
    }

    void insertionSort()
    {
        Node* j = _head->next;
        while (j != nullptr)
        {
            const T key = j->value;
            Node*  next = j->next;

            Node* i = j->prev;
            while (i->prev != nullptr && i->value > key)
                i = i->prev;

            if (i != j)
            {
                unlink(j);

                j->prev = i->prev;
                j->next = i;

                if (i->prev != nullptr)
                    i->prev->next = j;
                else
                    _head = j;

                i->prev = j;
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
    }

    Node*  _head;
    Node*  _tail;
    size_t _size;
};

#endif //TUTORIALS_LINKEDLIST_H
