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

    tree.insert(5);
    cout << tree << endl;
    tree.insert(2);
    cout << tree << endl;
    tree.insert(3);
    cout << tree << endl;
    tree.insert(8);
    cout << tree << endl;
    tree.insert(9);
    cout << tree << endl;
    tree.insert(1);
    cout << tree << endl;

    tree.remove(5);
    cout << tree << endl;


    return 0;
}
