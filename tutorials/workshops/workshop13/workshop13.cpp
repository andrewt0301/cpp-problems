//
// Created by Tatarnikov_A on 06.06.2019.
//

#include "Dijkstra.h"
#include "GraphMap.h"
#include "GraphMultimap.h"
#include "BFS.h"
#include "DFS.h"

#include <iostream>

void printBfsVertex(Node<int>* node, BfsVertex<int>* vertex)
{
    std::cout << node->tag;

    std::cout << ": dist=" << vertex->distance;
    std::cout << ", prev=";

    if (vertex->prev != nullptr)
        std::cout << vertex->prev->tag;
    else
        std::cout << "nullptr";

    std::cout << std::endl;
}

void printDfsVertex(Node<int>* node, DfsVertex<int>* vertex)
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
}

void printDijkstraPath(Node<int>* node, PathVertex<int>* vertex)
{
    std::cout << node->tag;
    std::cout << " dist=" << vertex->dist;
    std::cout << " prev=";

    if (vertex->prev != nullptr)
        std::cout << vertex->prev;
    else
        std::cout << "nullptr";

    std::cout << std::endl;
}

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
    std::map<Node*, BfsVertex<int>> bfsPaths = bfs(graph, node1, printBfsVertex);

    std::cout << std::endl << "***************" << std::endl;
    for (auto& p : bfsPaths)
        printBfsVertex(p.first, &p.second);

    std::cout << std::endl << "*************** DFS ***************:" << std::endl;
    std::map<Node*, DfsVertex<int>> dfsPaths = dfs(graph, node1, printDfsVertex);

    std::cout << std::endl << "***************" << std::endl;
    for (auto& p : dfsPaths)
        printDfsVertex(p.first, &p.second);

    std::cout << std::endl << "*************************************" << std::endl;
}

template <typename TGraph>
void testDijkstra()
{
    using  Graph = TGraph;
    using  Node  = Node<int>;
    using Vertex = PathVertex<int>;

    Graph graph;

    Node* node1 = graph.addNode(1);
    Node* node2 = graph.addNode(2);
    Node* node3 = graph.addNode(3);
    Node* node4 = graph.addNode(4);
    Node* node5 = graph.addNode(5);

    graph.addEdge(node1, node2, 3);
    graph.addEdge(node1, node3, 6);
    graph.addEdge(node3, node4, 4);
    graph.addEdge(node4, node5, 1);
    graph.addEdge(node5, node2, 0);

    std::cout << graph;

    std::cout << std::endl << "************** Dijkstra **************:" << std::endl;

    std::map<Node*, Vertex> paths = dijkstra(graph, node1);

    for (auto& p : paths)
        printDijkstraPath(p.first, &p.second);
}

int main()
{
    testBfsDfs<GraphMultimap<int>>();

    //testBfsDfs<GraphMap<int>>();

    testDijkstra<GraphMultimap<int>>();

    return 0;
}
