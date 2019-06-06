//
// Created by Tatarnikov_A on 06.06.2019.
//

#ifndef TUTORIALS_NODE_H
#define TUTORIALS_NODE_H

enum class Color
{
    WHITE,
    GRAY,
    BLACK
};

template <typename T>
struct Node
{
    T tag;

    Node(T t) : tag{t} {}
};

#endif //TUTORIALS_NODE_H
