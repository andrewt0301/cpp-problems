//
// Created by Tatarnikov_A on 06.06.2019.
//

#ifndef TUTORIALS_NODE_H
#define TUTORIALS_NODE_H

template <typename T>
struct Node
{
    T tag;

    explicit Node(T t) : tag{t} {}
};

template <typename T, typename U>
struct Edge
{
    Node<T>* src;
    Node<T>* dest;
    U tag;

    Edge(Node<T>* s, Node<T>* d, U t) : src{s}, dest{d}, tag{t} {}
    Edge() : src{nullptr}, dest{nullptr}, tag{0} {}

    operator Node<T>*() const { return dest; }
    bool operator==(Node<T>* node) { return dest == node; }
};

enum class Color
{
    WHITE,
    GRAY,
    BLACK
};

#endif //TUTORIALS_NODE_H
