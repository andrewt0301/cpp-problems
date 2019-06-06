//
// Created by Tatarnikov_A on 06.06.2019.
//

#include "GraphMap.h"
#include "GraphMultimap.h"

#include <iostream>

int main()
{
    using Graph = GraphMap<int>;
    using Node  = Node<int>;

    Graph graph;

    Node* node1 = graph.addNode(1);
    Node* node2 = graph.addNode(6);
    Node* node3 = graph.addNode(3);
    Node* node4 = graph.addNode(4);
    Node* node5 = graph.addNode(5);

    graph.addEdge(node1, node2);
    graph.addEdge(node1, node3);
    graph.addEdge(node4, node3);
    graph.addEdge(node3, node5);

    std::cout << graph;
    std::cout << std::endl << "***************" << std::endl;

    /*
    graph.removeNode(node4);
    graph.removeEdge(node1, node2);
     */

    std::cout << std::endl << "***************" << std::endl;

    graph.bfs(node1, [](Node* node, int distance, Node* prev)
    {
        std::cout << node->tag;

        std::cout << ": dist=" << distance;
        std::cout << ", prev=";

        if (prev != nullptr)
            std::cout << prev->tag;
        else
            std::cout << "nullptr";

        std::cout << std::endl;
    });

    std::cout << std::endl << "***************" << std::endl;

    std::cout << graph;

    return 0;
}
