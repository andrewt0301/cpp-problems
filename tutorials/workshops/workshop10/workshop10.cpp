//
// Created by Andrei Tatarnikov on 2019-05-25.
//

#include <iostream>

using std::cout;
using std::endl;

#include "RedBlackTree.h"

void printBar()
{
    cout << endl;
    for (size_t i = 0; i < 100; ++i)
        cout << '_';
    cout << endl;
}

void testRotate()
{
    RedBlackTree<int> tree;

    for (int key : {7, 4, 3, 6, 2, 11, 9, 18, 14, 12, 17, 19, 22, 20})
        tree.insert(key);

    printBar();
    tree.printAsRBTree(cout);

    auto x1 = tree.search(11);
    tree.leftRotate(x1);

    printBar();
    tree.printAsRBTree(cout);

    auto x2 = tree.search(18);
    tree.rightRotate(x2);

    printBar();
    tree.printAsRBTree(cout);

    printBar();
}

int main()
{
    testRotate();

    RedBlackTree<int> tree;

    tree.printAsRBTree(cout);


/*
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
*/

    tree.printAsRBTree(cout);

    return 0;
}
