//
// Created by Tatarnikov_A on 06.06.2019.
//

#include "Node.h"

#include "GraphMap.h"
#include "GraphMultimap.h"

#include <iostream>
#include <map>

int main()
{
/*
    std::multimap<int, int> multimap;

    multimap.insert({1, 0});
    multimap.insert({1, 2});
    multimap.insert({1, 2});
    multimap.insert({1, 4});



    multimap.insert({2, 0});
    multimap.insert({2, 2});
    multimap.insert({3, 2});
    multimap.insert({4, 4});




    for (auto& e : multimap)
        std::cout << e.first << ":" << e.second << std::endl;

    std::cout << "*****************" << std::endl;

    auto range = multimap.equal_range(1);
    for (auto it = range.first; it != range.second;)
    {
        std::cout << it->first << ":" << it->second << std::endl;
        it = multimap.erase(it);

    }


    std::cout << "*****************" << std::endl;

    for (auto& e : multimap)
        std::cout << e.first << ":" << e.second << std::endl;

*/

    using Graph = GraphMap<int>;
    using Node  = Node<int>;

    Graph graph;

    Node* node1 = graph.addNode(1);
    Node* node2 = graph.addNode(6);
    Node* node3 = graph.addNode(3);
    Node* node4 = graph.addNode(4);

    graph.addEdge(node1, node2);
    graph.addEdge(node1, node3);
    graph.addEdge(node4, node3);

    std::cout << graph;
    std::cout << std::endl << "***************" << std::endl;

    graph.removeNode(node4);
    graph.removeEdge(node1, node2);

    std::cout << graph;

    return 0;
}
