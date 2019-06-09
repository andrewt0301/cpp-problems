//
// Created by Tatarnikov_A on 06.06.2019.
//

#include "GraphMap.h"
#include "GraphMultimap.h"
#include "BFS.h"
#include "DFS.h"

#include <iostream>

int main()
{
    using Graph = GraphMultimap<int>;
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

    graph.removeNode(node4);
    graph.removeEdge(node1, node2);

    std::cout << std::endl << "*************** BST: " << std::endl;

    bfs(graph, node1, [](Node* node, BfsVertex<int>* vertex)
    {
        std::cout << node->tag;

        std::cout << ": dist=" << vertex->distance;
        std::cout << ", prev=";

        if (vertex->prev != nullptr)
            std::cout << vertex->prev->tag;
        else
            std::cout << "nullptr";

        std::cout << std::endl;
    });

    std::cout << std::endl << "*************** DST: " << std::endl;

    dfs(graph, node1, [](Node* node, DfsVertex<int>* vertex)
    {
        std::cout << node->tag;

        std::cout << ": d=" << vertex->d;
        std::cout << ": f=" << vertex->f;
        std::cout << ", prev=";

        if (vertex->prev != nullptr)
            std::cout << vertex->prev->tag;
        else
            std::cout << "nullptr";

        std::cout << std::endl;
    });

    std::cout << std::endl << "***************" << std::endl;

    std::cout << graph;
    std::cout << std::endl << "***************" << std::endl;
    std::cout << graph;
    std::cout << std::endl << "***************" << std::endl;

    auto r = graph.getNodes();
    for (auto it = r.first; it != r.second; ++it)
    {
        std::cout << (*it)->tag << std::endl;
    }

    std::cout << std::endl << "***************" << std::endl;

    auto r1 = graph.getEdges(node1);
    for (auto it = r1.first; it != r1.second; ++it)
    {
           std::cout << (*it)->tag << std::endl;
    }

    return 0;
}
