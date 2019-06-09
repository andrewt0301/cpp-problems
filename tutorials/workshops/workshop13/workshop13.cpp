//
// Created by Tatarnikov_A on 06.06.2019.
//

#include "GraphMap.h"
#include "GraphMultimap.h"
#include "BFS.h"
#include "DFS.h"

#include <iostream>

template <typename TGraph>
void testBfsDfs()
{
    using Graph = TGraph;
    using Node  = Node<int>;

    Graph graph;

    Node* node1 = graph.addNode(1);
    Node* node2 = graph.addNode(2);
    Node* node3 = graph.addNode(3);
    Node* node4 = graph.addNode(4);
    Node* node5 = graph.addNode(5);
    Node* node6 = graph.addNode(6);
    Node* node7 = graph.addNode(7);
    Node* node8 = graph.addNode(8);

    graph.addEdge(node1, node2);
    graph.addEdge(node1, node3);
    graph.addEdge(node3, node4);
    graph.addEdge(node4, node5);
    graph.addEdge(node5, node8);
    graph.addEdge(node6, node7);
    graph.addEdge(node7, node2);
    graph.addEdge(node8, node6);

    std::cout << graph;
    std::cout << std::endl << "*************** Remove *************" << std::endl;

    graph.removeEdge(node7, node2);
    graph.removeNode(node7);

    std::cout << graph;

    std::cout << std::endl << "*************** BFS ***************:" << std::endl;

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

    std::cout << std::endl << "*************** DFS ***************:" << std::endl;

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
}

int main()
{

    testBfsDfs<GraphMultimap<int>>();
    //testBfsDfs<GraphMap<int>>();

    return 0;
}
