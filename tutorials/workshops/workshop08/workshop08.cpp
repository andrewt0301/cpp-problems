//
// Created by Tatarnikov_A on 16.05.2019.
//

#include <iostream>

#include "LinkedList.h"

int main()
{
    LinkedList<int> list;

    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_back(5);
    list.push_back(6);
    list.push_back(7);

    std::cout << list;

    return 0;
}
