//
// Created by Andrei Tatarnikov on 2019-05-25.
//

#include <iostream>

using std::cout;
using std::endl;

#include "RedBlackTree.h"

int main()
{
    RedBlackTree<int> tree;

    cout << tree << endl;

    auto x = [](int a) { return 0; };
    auto y = 10;


    cout << typeid(x).name() << endl;

    return 0;
}
