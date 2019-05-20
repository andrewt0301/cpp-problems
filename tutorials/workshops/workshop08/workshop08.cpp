//
// Created by Tatarnikov_A on 16.05.2019.
//

#include <iostream>

#include "LinkedList.h"

int main()
{
    LinkedList<int> list1;

    list1.pushFront(1);
    list1.pushFront(2);
    list1.pushFront(3);
    list1.pushBack(5);
    list1.pushBack(6);
    list1.pushBack(7);

    LinkedList<int> list2;

    list2.pushBack(8);
    list2.pushBack(9);
    list2.pushBack(10);

    std::cout << list1 << std::endl;
    std::cout << list2 << std::endl;

    list1.pushAllBack(std::move(list2));

    std::cout << list1 << std::endl;
    std::cout << list2 << std::endl;

    list1.reverse();
    std::cout << list1 << std::endl;

    return 0;
}
